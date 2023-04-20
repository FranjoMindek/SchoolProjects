package hr.fer.tel.rassus.lab2.sensor;

import hr.fer.tel.rassus.lab2.models.SensorData;
import hr.fer.tel.rassus.lab2.models.SernsorInfo;
import hr.fer.tel.rassus.lab2.network.EmulatedSystemClock;
import org.apache.commons.csv.CSVFormat;
import org.apache.commons.csv.CSVParser;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;
import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.json.JSONObject;

import java.io.File;
import java.io.IOException;
import java.io.Reader;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.Duration;
import java.util.*;


public class Sensor {
    private final int PORT;
    private final int ID;
    private boolean running;
    private final KafkaProducer<String, String> producer;
    private final KafkaConsumer<String, String> consumer;
    private final EmulatedSystemClock scalarTime;
    private final long timeStarted;
    private int[] vectorTime;
    private Map<Integer, SernsorInfo>  otherSensors;
    private List<Integer> sensorReadings;
    private SensorUDP UDPServer;
    private List<SensorData> lastReadings;

    public Sensor(String id, String port) throws InterruptedException {
        this.running = false;
        this.otherSensors = new HashMap<>();
        this.sensorReadings = new ArrayList<>();
        this.lastReadings = new ArrayList<>();

        try {
            Reader reader = Files.newBufferedReader(
                    Paths.get(new File("src/main/resources/readings.csv").getAbsolutePath()));
            CSVParser records = CSVFormat.DEFAULT
                    .withFirstRecordAsHeader()
                    .withIgnoreHeaderCase()
                    .withTrim()
                    .parse(reader);
            for(var record : records) {
                String dataString = record.get("NO2");
                this.sensorReadings.add(dataString.equals("") ? 0 : Integer.parseInt(dataString));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

//        final Scanner scanner = new Scanner(System.in);
//        ID = scanner.nextInt();
//        PORT = scanner.nextInt();
//        scanner.close();
        this.ID = Integer.parseInt(id);
        this.PORT = Integer.parseInt(port);

        Properties kafkaProps = new Properties();
        kafkaProps.put("bootstrap.servers", "localhost:9092");
        kafkaProps.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        kafkaProps.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        this.producer = new KafkaProducer<String, String>(kafkaProps);
        kafkaProps.remove("key.serializer");
        kafkaProps.remove("value.serializer");
        kafkaProps.put("key.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        kafkaProps.put("value.deserializer","org.apache.kafka.common.serialization.StringDeserializer");
        kafkaProps.put("group.id", "Sensor" + this.ID + System.currentTimeMillis());
        this.consumer = new KafkaConsumer<String, String>(kafkaProps);
        this.consumer.subscribe(Arrays.asList("Command", "Register"));

        this.scalarTime = new EmulatedSystemClock();
        this.timeStarted = System.currentTimeMillis();
        this.vectorTime = new int[10];

        while(!running) {
            ConsumerRecords<String, String> records = this.consumer.poll(Duration.ofMillis(100));
            for(var record : records) {
                if(record.topic().equals("Command") && record.value().equals("Start")) {
                    this.running = true;
                    System.out.println("Received Command: Start");
                }
            }
        }

        Thread kafkaThread = new Thread(() -> {
            while(running) {
                ConsumerRecords<String, String> records = this.consumer.poll(Duration.ofMillis(100));
                for(var record : records) {
                    if(record.topic().equals("Command") && record.value().equals("Stop")) {
                        this.running = false;
                        System.out.println("Received Command: Stop");
                    }
                    else if(record.topic().equals("Register")) {
                        JSONObject json = new JSONObject(record.value());
                        if(json.get("port").equals(this.PORT)) break;
                        SernsorInfo sernsorInfo = new SernsorInfo(
                                (Integer) json.get("id"),
                                (String) json.get("address"),
                                (Integer) json.get("port")
                        );
                        this.otherSensors.put((Integer) json.get("port"), sernsorInfo);
                        System.out.println("Received Register: " + json);
                    }
                }
            }
        });
        kafkaThread.start();

        this.producer.send(new ProducerRecord<>(
                "Register", new JSONObject(new SernsorInfo(this.ID, "localhost", this.PORT)).toString()
        ));
        System.out.println("Sent Register: " + new JSONObject(new SernsorInfo(this.ID, "localhost", this.PORT)));

        // kreni citati
        Thread UDPthread = new Thread(() -> {
            Random timeToSleep = new Random();
            try {
                this.UDPServer = new SensorUDP(this.ID, this.PORT, this.scalarTime, this.vectorTime, this.otherSensors,
                        this.sensorReadings, this.timeStarted, this.lastReadings);
            } catch (UnknownHostException | SocketException e) {
                throw new RuntimeException(e);
            }
            while(running){
                try {
                    Thread.sleep((timeToSleep.nextInt(2)+2)*1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                if(running) {
                    try {
                        this.UDPServer.send();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
            try {
                this.UDPServer.close();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        UDPthread.start();

        // svakih 5 sekundi
        Thread readingsThread = new Thread(() -> {
            while(running){
                try {
                    Thread.sleep(5*1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
//                if(running) {
                List<SensorData> readings = new ArrayList<>(this.lastReadings);
                this.lastReadings.clear();
                System.out.println("Sortirano po skalarnom vremenu:");
                readings.sort(Comparator.comparingInt(SensorData::getSTime));
                System.out.println(Arrays.toString(readings.toArray()));
                System.out.println("Sortirano po vektorskom vremenu");
                readings.sort((SensorData a, SensorData b) -> {
                    for(int i = 0; i < a.getVTime().length; i++){
                        if(a.getVTime()[i] < b.getVTime()[i]) return a.getVTime()[i] - b.getVTime()[i];
                    }
                    return 0;
                });
                System.out.println(Arrays.toString(readings.toArray()));
                System.out.print("Average value: ");
                System.out.println(readings.stream().mapToInt(SensorData::getReading).average());
//                }
                // 0 0 1, 0 0 2
                // 2 0 1, 1 0 2
            }
        });
        readingsThread.start();



        kafkaThread.join();
        readingsThread.join();
        UDPthread.join();

    }

    public static void main(String args[]) throws InterruptedException {
        if(args.length < 2) {
            System.out.println("Please enter ID and PORT as args");
            return;
        }
        new Sensor(args[0], args[1]);
    }
}
