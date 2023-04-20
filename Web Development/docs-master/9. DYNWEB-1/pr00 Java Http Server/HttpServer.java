import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;
import java.util.Map;
import java.util.StringTokenizer;
import java.time.format.DateTimeFormatter;

public class HttpServer implements Runnable {
    static final int PORT = 80;
    public enum ResponseCode {
        OK200, FileNotFound404, UnknownMethod501
    }
    private Socket socket;
    public HttpServer(Socket s) {
        socket = s;
    }
    private static final Map<ResponseCode,String> HttpResponseCodeMap = Map.of(
        ResponseCode.OK200, "HTTP/1.1 200 OK",
        ResponseCode.FileNotFound404, "HTTP/1.1 404 File Not Found",
        ResponseCode.UnknownMethod501, "HTTP/1.1 501 Not Implemented");
    private static final Map<ResponseCode,String> HttpResponseCodeFileMap = Map.of(
        ResponseCode.OK200, "index.html",
        ResponseCode.FileNotFound404, "404.html",
        ResponseCode.UnknownMethod501, "501.html");

    static final File WWW_ROOT = new File("."); // new File("./www.hr");

    private void sendFile (ResponseCode responseCode, String fileName, PrintWriter txtOut, BufferedOutputStream binOut) throws IOException {
        if (responseCode != ResponseCode.OK200 ) {
            fileName = HttpResponseCodeFileMap.get(responseCode);
        } else if (fileName.endsWith("/")) {
            fileName += HttpResponseCodeFileMap.get(responseCode);  // da dobijemo: /index.html ili /neki-dir/index.html
        }
        // we return the not supported file to the client
        File file = new File(WWW_ROOT, fileName);
        if (!file.exists() || file.isDirectory()) {
            sendFile(ResponseCode.FileNotFound404, null, txtOut, binOut);
        } else {
            int fileLength = (int) file.length();
            byte[] fileData = readFileData(file, fileLength);
            printAndLog(txtOut, HttpResponseCodeMap.get(responseCode));
            printAndLog(txtOut, "Server: Java HTTP Server demo");
            printAndLog(txtOut, "Date: " + new Date());
            printAndLog(txtOut, "Content-type: " + guessMimeType(fileName));
            printAndLog(txtOut, "Content-length: " + fileLength);
            printAndLog(txtOut, ""); // Vazno: prazna linija koja razdvaja header i content !!
            txtOut.flush(); // flush character output stream buffer
            // binarni sadrzaj:
            binOut.write(fileData, 0, fileLength);
            //logHttpOut(new String(fileData));
            binOut.flush();
        }
    }
    // ovo je naravno nepotpuno...
    private String guessMimeType(String fileName) {
        if (fileName.toLowerCase().endsWith(".css")) return "text/css";
        else if (fileName.toLowerCase().endsWith(".png")) return "image/png";
        else if (fileName.toLowerCase().endsWith(".js")) return "application/javascript";
        else return "text/html";
    }

    private void printAndLog(PrintWriter txtOut, String msg){
        txtOut.println(msg);
        logHttpOut(msg);
    }

    private int rowCounterIn = 0;
    private void logHttpIn(String msg) {
        log("|HTTP-IN|" + String.format("%03d", ++rowCounterIn) + "|" + msg);
    }

    private int rowCounterOut = 0;
    private void logHttpOut(String msg) {
        log("|HTTP-OUT|" + String.format("%03d", ++rowCounterOut) + "|" + msg);
    }

    private static DateTimeFormatter tf = DateTimeFormatter.ofPattern("HH:mm:ss.SSSS");
    private static void log(String msg) {
        System.out.println(tf.format(java.time.LocalTime.now()) + "  " + msg);

    }
    @Override
    public void run() {
        // ovo se obavlja u svojoj posebnoj dretvi
        BufferedReader in = null;
        PrintWriter txtOut = null;
        BufferedOutputStream binOut = null;
        String fileRequested = null;

        try {
            // ulazni tok podataka:
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            // izlazni tokovi, tekstualni i binarni:
            txtOut = new PrintWriter(socket.getOutputStream());
            binOut = new BufferedOutputStream(socket.getOutputStream());
            // citamo ulaz dok ne dođemo do CRLF, pamtimo samo prvu liniju (naravno, to inace ne bi radili :))
            String input, firstLine = null;
            while ((input = in.readLine()) != null) {
                logHttpIn(input);
                if (firstLine == null) {
                    firstLine = input;
                }
                if (input.equals("")) break;
            }
            // Parsiramo na primitivan nacin prvu liniju da vidimo je li to GET
            StringTokenizer parse = new StringTokenizer(firstLine);
            String method = parse.nextToken().toUpperCase(); // HTTP method
            fileRequested = parse.nextToken().toLowerCase(); // datoteka?

            // podrzavamo samo GET:
            if (method.equals("GET")) {
                sendFile(ResponseCode.OK200, fileRequested, txtOut, binOut);
            } else {
                sendFile(ResponseCode.UnknownMethod501, null, txtOut, binOut);
            }
        } catch (IOException ioe) {
            log("Server error : " + ioe);
        } finally {
            try {
                in.close();
                txtOut.close();
                binOut.close();
                socket.close();
            } catch (Exception e) {
                log("Error: " + e.getMessage());
            }
            log("Connection closed.\n");
        }
    }

    private byte[] readFileData(File file, int fileLength) throws IOException {
        FileInputStream fileIn = null;
        byte[] fileData = new byte[fileLength];

        try {
            fileIn = new FileInputStream(file);
            fileIn.read(fileData);
        } finally {
            if (fileIn != null)
                fileIn.close();
        }
        return fileData;
    }

    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(PORT);
            log("Server started.\nListening for connections on port : " + PORT + " ...\n");
            while (true) {
                HttpServer myWorker = new HttpServer(ss.accept());
                log("Connecton opened.");
                // Otvoriti posebnu dretvu koja se obraditi zahtjev:
                Thread thread = new Thread(myWorker);
                thread.start();
            }
        } catch (IOException e) {
            log("Error : " + e.getMessage());
        }
    }
}