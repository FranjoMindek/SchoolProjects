package hr.fer.tel.rassus.sensor.gRPC;

import hr.fer.tel.rassus.sensor.SensorUnit;
import hr.fer.tel.rassus.sensor.models.SensorReading;
import io.grpc.stub.StreamObserver;

import java.util.logging.Logger;

public class ReadingExchangeService extends ReadingExchangeGrpc.ReadingExchangeImplBase {
    private static final Logger logger = Logger.getLogger(ReadingExchangeService.class.getName());
    private final SensorUnit sensorUnit;

    public ReadingExchangeService(SensorUnit sensorUnit) {
        this.sensorUnit = sensorUnit;
    }

    @Override
    public void readingExchange(Empty request, StreamObserver<SensorReadingGRPC> responseObserver){
        logger.info("Got a reading exchange request.");

        // if there is request after there is no data left to read, sensorReading will have values 0
        SensorReading sensorReading = this.sensorUnit.getReading();
        SensorReadingGRPC response = SensorReadingGRPC.newBuilder()
                .setCo(sensorReading.getCo())
                .setSo2(sensorReading.getSo2())
                .setHumidity(sensorReading.getHumidity())
                .setPressure(sensorReading.getPressure())
                .setTemperature(sensorReading.getTemperature())
                .setNo2(sensorReading.getNo2())
                .build();

        responseObserver.onNext(response);

        logger.info("Responding with: [temperature: " + response.getTemperature()
                + ", pressure: " + response.getPressure()
                + ", humidity: " + response.getHumidity()
                + ", co: " + response.getCo()
                + ", so2: " + response.getSo2()
                + ", no2: " + response.getNo2()
                + "]");

        responseObserver.onCompleted();
    }

}
