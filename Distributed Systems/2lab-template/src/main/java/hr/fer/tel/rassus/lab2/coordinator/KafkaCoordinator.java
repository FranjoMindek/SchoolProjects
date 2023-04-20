package hr.fer.tel.rassus.lab2.coordinator;

import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.Producer;
import org.apache.kafka.clients.producer.ProducerRecord;

import java.util.Properties;
import java.util.Scanner;

public class KafkaCoordinator {
    private Producer<String, String> producer;

    public KafkaCoordinator() throws InterruptedException {
        Properties kafkaProps = new Properties();
        kafkaProps.put("bootstrap.servers", "localhost:9092");
        kafkaProps.put("retries", 3);
        kafkaProps.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        kafkaProps.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        this.producer = new KafkaProducer<String, String>(kafkaProps);

//        final Scanner scanner = new Scanner(System.in);
//
//        while(true){
//            String line = scanner.nextLine();
//            if(line.equals("Start")) this.start();
//            else if(line.equals("Stop")) {
//                this.stop();
//                break;
//            }
//        }
//        scanner.close();

        this.start();
        Thread.sleep(25*1000); // ugasi se nakon 25 sekundi jer input u program ne radi bas najbolje na Windowsu :/
        this.stop();
    }

    public void start() {
        producer.send(new ProducerRecord<>("Command", "Start"));
    }

    public void stop() {
        producer.send(new ProducerRecord<>("Command", "Stop"));
        producer.close();
    }


    public static void main(String[] args) throws InterruptedException {
        new KafkaCoordinator();
    }
}
