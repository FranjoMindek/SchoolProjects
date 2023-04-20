package hr.fer.tel.rassus.lab2.sensor;

import hr.fer.tel.rassus.lab2.models.SensorData;
import hr.fer.tel.rassus.lab2.models.SernsorInfo;
import hr.fer.tel.rassus.lab2.network.EmulatedSystemClock;
import hr.fer.tel.rassus.lab2.network.SimpleSimulatedDatagramSocket;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.*;
import java.net.*;
import java.util.*;

public class SensorUDP {
    private final DatagramSocket socket;
    private EmulatedSystemClock scalarTime;
    private int[] vectorTime;
    private Map<Integer, SernsorInfo> otherSensors;
    private List<Integer> sensorReadings;
    private final long timeStarted;
    private boolean running;
    private Thread recieveThread;
    private final int ID;
    private final int PORT;
    private List<SensorData> lastReadings;
    private int currentId;
    private Map<Integer, Set<Integer>> toAck;
    private Map<Integer, Set<Integer>> alreadyRead;

    SensorUDP(int ID, int PORT, EmulatedSystemClock scalarTime, int[] vectorTime,Map<Integer, SernsorInfo>  otherSensors,
              List<Integer> sensorReadings, long timeStarted, List<SensorData> lastReadings) throws UnknownHostException, SocketException {
        this.socket = new SimpleSimulatedDatagramSocket(PORT, 0.3, 1000); //SOCKET
        this.running = true;
        this.scalarTime = scalarTime;
        this.vectorTime = vectorTime;
        this.otherSensors = otherSensors;
        this.sensorReadings = sensorReadings;
        this.timeStarted = timeStarted;
        this.PORT = PORT;
        this.ID = ID;
        this.lastReadings = lastReadings;
        this.currentId = 0;
        this.toAck = new HashMap<>();
        this.alreadyRead = new HashMap<>();
        this.receive();
    }

    public void send() throws IOException {
        this.vectorTime[this.ID] = this.vectorTime[this.ID] + 1;
        int sTime = (int) ((this.scalarTime.currentTimeMillis() - this.timeStarted) / 1000);
        int[] vTime = Arrays.copyOf(this.vectorTime, this.vectorTime.length);
        int reading = this.sensorReadings.get(sTime % this.sensorReadings.size());

        SensorData data = new SensorData(sTime, vTime, reading);
        this.lastReadings.add(data);
        JSONObject json = new JSONObject(data);
        json.put("id", currentId);
        System.out.println("Datagram data is " + json);
        byte[] byteData = json.toString().getBytes();
        for(var sensorInfo : this.otherSensors.values()) {
            System.out.println("Sending to: " + sensorInfo.getAddress() + ":" + sensorInfo.getPort());
            DatagramPacket packet = new DatagramPacket(
                    byteData, byteData.length, InetAddress.getByName(sensorInfo.getAddress()), sensorInfo.getPort()
            );
            this.socket.send(packet);
        }
        this.checkRetransmission(currentId, json);
        this.toAck.put(currentId++, new HashSet<>(this.otherSensors.keySet()));
    }

    public void checkRetransmission(int id, JSONObject json){
        new Thread( () -> {
            for(int i = 0; i < 3; i++){
                try {
                    Thread.sleep(3*1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                Set<Integer> toRetransmission = this.toAck.get(id);
                if(toRetransmission.isEmpty() || !this.running) break;
                byte[] byteData = json.toString().getBytes();
                for(Integer port : toRetransmission) {
                    System.out.println("Retransmission sending to: " + otherSensors.get(port).getAddress() + ":" + port);
                    DatagramPacket packet = null;
                    try {
                        packet = new DatagramPacket(
                                byteData, byteData.length, InetAddress.getByName(otherSensors.get(port).getAddress()), port);
                    } catch (UnknownHostException e) {
                        throw new RuntimeException(e);
                    }
                    try {
                        this.socket.send(packet);
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }).start();
    }

    public void receive() {
        this.recieveThread = new Thread(() -> {
            byte[] rcvBuf = new byte[512];
            while (this.running) {
                DatagramPacket rcvPacket = new DatagramPacket(rcvBuf, rcvBuf.length);
                try {
                    socket.receive(rcvPacket);

                    String dataString = new String(rcvPacket.getData(), rcvPacket.getOffset(), rcvPacket.getLength());
                    if(dataString.charAt(0) != '{'){
                        System.out.println("Received ack for datagram with id: " + dataString);
                        this.toAck.get(Integer.parseInt(dataString)).remove(rcvPacket.getPort());
                    } else {
                        try {
                            System.out.println("Received JSON is " + dataString);
                            JSONObject json = new JSONObject(dataString);

                            System.out.println("Sending ACK for ID " + json.getInt("id") + " and PORT " + rcvPacket.getPort());
                            byte[] byteData = String.valueOf(json.getInt("id")).getBytes();
                            DatagramPacket packet = new DatagramPacket(
                                    byteData, byteData.length, rcvPacket.getAddress(), rcvPacket.getPort()
                            );
                            this.socket.send(packet);

                            if(this.alreadyRead.containsKey(rcvPacket.getPort())){
                                if(this.alreadyRead.get(rcvPacket.getPort()).contains(json.getInt("id"))){
                                    System.out.println("Discarding already received JSON");
                                    continue;
                                }
                            }

                            int[] timeArray = new int[10];
                            JSONArray jsonArray = (JSONArray) json.get("VTime");
                            for (int i = 0; i < timeArray.length; i++) {
                                timeArray[i] = jsonArray.getInt(i);
                            }
                            this.vectorTime[this.otherSensors.get(rcvPacket.getPort()).getId()] =
                                    this.vectorTime[this.otherSensors.get(rcvPacket.getPort()).getId()] + 1;
                            for(int i = 0; i < this.vectorTime.length; i++) {
                                if(this.vectorTime[i] < timeArray[i]) this.vectorTime[i] = timeArray[i];
                            }
                            SensorData sensorData = new SensorData(
                                    json.getInt("STime"),
                                    Arrays.copyOf(this.vectorTime, this.vectorTime.length),
                                    json.getInt("reading")
                            );
                            this.lastReadings.add(sensorData);
                            if(this.alreadyRead.containsKey(rcvPacket.getPort())){
                                this.alreadyRead.get(rcvPacket.getPort()).add(json.getInt("id"));
                            } else {
                                this.alreadyRead.put(rcvPacket.getPort(), new HashSet<>(json.getInt("id")));
                            }

                        } catch (JSONException e) {
                            System.out.println("This should be a JSON: " + dataString);
                        }
                    }
                } catch (IOException ignored) {
                }



            }
        });
        recieveThread.start();

    }

    public void close() throws InterruptedException {
        this.running = false;
        this.recieveThread.join();
        Thread.sleep(1000); // jer je toliki delay kod slanja -> nema pametnije rjesenja jer se oni desavaju u zasebnoj dretvi
        this.socket.close();
    }
}
