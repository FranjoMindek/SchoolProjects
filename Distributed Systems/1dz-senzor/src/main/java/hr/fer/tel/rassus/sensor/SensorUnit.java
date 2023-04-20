package hr.fer.tel.rassus.sensor;

import hr.fer.tel.rassus.sensor.gRPC.ReadingExchangeService;
import hr.fer.tel.rassus.sensor.gRPC.SensorClient;
import hr.fer.tel.rassus.sensor.gRPC.SensorServer;
import hr.fer.tel.rassus.sensor.models.SensorReading;
import hr.fer.tel.rassus.sensor.models.SensorRegistration;
import hr.fer.tel.rassus.sensor.retrofit.RetrofitImplementation;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Optional;
import java.util.concurrent.ThreadLocalRandom;
import java.util.stream.Stream;

public class SensorUnit implements Runnable {
    private RetrofitImplementation retrofitImplementation;
    private SensorClient sensorClient;
    private SensorServer sensorServer;
    private ReadingExchangeService readingExchangeService;
    private int sensorServerPort;
    private int sensorId;
    private String nearestPort;
    private long createdMilis;
    private boolean nearestActive;
    private boolean dataToRead;

    public SensorUnit(String webserverUrl, int sensorServerPort) throws IOException, InterruptedException {
        this.dataToRead = true;
        this.sensorServerPort = sensorServerPort;
        this.readingExchangeService = new ReadingExchangeService(this);

        this.retrofitImplementation = new RetrofitImplementation(webserverUrl);
        SensorRegistration sensorRegistration = new SensorRegistration(
                ThreadLocalRandom.current().nextDouble(15.87, 16.00),
                ThreadLocalRandom.current().nextDouble(45.75, 45.85),
                "127.0.0.1",
                Integer.toString(this.sensorServerPort)
        );

        this.sensorServer = new SensorServer(this.readingExchangeService, this.sensorServerPort);
        this.sensorServer.start();
//        this.sensorServer.blockUntilShutdown();
        this.createdMilis = System.currentTimeMillis();

        this.sensorId = this.retrofitImplementation.insertSensor(sensorRegistration);
        SensorRegistration nearestSensor = this.retrofitImplementation.getNearestSensor(this.sensorId);
        if (nearestSensor == null) {
            this.nearestActive = false;
        } else {
            this.nearestActive = true;
            this.nearestPort = nearestSensor.getPort();
            this.sensorClient = new SensorClient("127.0.0.1", Integer.parseInt(nearestPort), this);
        }
    }

    public void nearestIsDown() throws InterruptedException {
        this.nearestActive = false;
    }

    public boolean getNearestActive(){
        return this.nearestActive;
    }

    private void loop() throws InterruptedException {
        while ( dataToRead ) {
            Thread.sleep(ThreadLocalRandom.current().nextLong(2,5) * 1000);
            SensorReading sensorReading = this.getReading();

            if (dataToRead) {
                if (nearestActive) {
                    SensorReading nearestReading = this.sensorClient.readingExchange();
                    this.retrofitImplementation.insertReading(sensorId, this.makeCalibratedReading(sensorReading, nearestReading));
                } else {
                    this.retrofitImplementation.insertReading(sensorId, sensorReading);
                }
            }
        }
    }

    private SensorReading makeCalibratedReading(SensorReading sensorReading, SensorReading nearestReading){
        SensorReading calibratedReading = new SensorReading();
        if (sensorReading.getTemperature() != 0 && nearestReading.getTemperature() != 0) {
            calibratedReading.setTemperature((sensorReading.getTemperature() + nearestReading.getTemperature())/2);
        } else if (sensorReading.getTemperature() != 0) {
            calibratedReading.setTemperature(sensorReading.getTemperature());
        } else if (nearestReading.getTemperature() != 0) {
            calibratedReading.setTemperature(nearestReading.getTemperature());
        }
        if (sensorReading.getHumidity() != 0 && nearestReading.getHumidity() != 0) {
            calibratedReading.setHumidity((sensorReading.getHumidity() + nearestReading.getHumidity())/2);
        } else if (sensorReading.getHumidity() != 0) {
            calibratedReading.setHumidity(sensorReading.getHumidity());
        } else if (nearestReading.getHumidity() != 0) {
            calibratedReading.setHumidity(nearestReading.getHumidity());
        }
        if (sensorReading.getPressure() != 0 && nearestReading.getPressure() != 0) {
            calibratedReading.setPressure((sensorReading.getPressure() + nearestReading.getPressure())/2);
        } else if (sensorReading.getPressure() != 0) {
            calibratedReading.setPressure(sensorReading.getPressure());
        } else if (nearestReading.getPressure() != 0) {
            calibratedReading.setPressure(nearestReading.getPressure());
        }
        if (sensorReading.getCo() != 0 && nearestReading.getCo() != 0) {
            calibratedReading.setCo((sensorReading.getCo() + nearestReading.getCo())/2);
        } else if (sensorReading.getCo() != 0) {
            calibratedReading.setCo(sensorReading.getCo());
        } else if (nearestReading.getCo() != 0) {
            calibratedReading.setCo(nearestReading.getCo());
        }
        if (sensorReading.getSo2() != 0 && nearestReading.getSo2() != 0) {
            calibratedReading.setSo2((sensorReading.getSo2() + nearestReading.getSo2())/2);
        } else if (sensorReading.getSo2() != 0) {
            calibratedReading.setSo2(sensorReading.getSo2());
        } else if (nearestReading.getSo2() != 0) {
            calibratedReading.setSo2(nearestReading.getSo2());
        }
        if (sensorReading.getNo2() != 0 && nearestReading.getNo2() != 0) {
            calibratedReading.setNo2((sensorReading.getNo2() + nearestReading.getNo2())/2);
        } else if (sensorReading.getNo2() != 0) {
            calibratedReading.setNo2(sensorReading.getNo2());
        } else if (nearestReading.getNo2() != 0) {
            calibratedReading.setNo2(nearestReading.getNo2());
        }
        return calibratedReading;
    }

    public int getSecondsAlive() {
        return (int)((System.currentTimeMillis() - this.createdMilis) / 1000);
    }

    public SensorReading getReading() {
        SensorReading sensorReading = new SensorReading();
        try (Stream<String> lines = Files.lines(Path.of(new File("src/main/resources/readings.csv").getAbsolutePath()))) {
            Optional<String> line = lines.skip(getSecondsAlive()).findFirst();
            if(line.isPresent()){
                String[] readingValues = line.get().split(",", -1);
                if(!readingValues[0].equals("")) sensorReading.setTemperature(Double.parseDouble(readingValues[0]));
                if(!readingValues[1].equals("")) sensorReading.setPressure(Double.parseDouble(readingValues[1]));
                if(!readingValues[2].equals("")) sensorReading.setHumidity(Double.parseDouble(readingValues[2]));
                if(!readingValues[3].equals("")) sensorReading.setCo(Double.parseDouble(readingValues[3]));
                if(!readingValues[4].equals("")) sensorReading.setNo2(Double.parseDouble(readingValues[4]));
                if(!readingValues[5].equals("")) sensorReading.setSo2(Double.parseDouble(readingValues[5]));
            } else {
                this.dataToRead = false;
                this.sensorServer.stop(); // nema se sto vise slati, msm ionako ce se ugasiti sljedeci loop preko hooka
                return sensorReading; // values are 0 -> won't change outcome, better than null pointer
            }
        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
        return sensorReading;
    }


    @Override
    public void run() {
        try {
            this.loop();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
