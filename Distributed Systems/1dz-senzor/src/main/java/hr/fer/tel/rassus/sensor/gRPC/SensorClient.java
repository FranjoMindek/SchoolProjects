package hr.fer.tel.rassus.sensor.gRPC;

import hr.fer.tel.rassus.sensor.SensorUnit;
import hr.fer.tel.rassus.sensor.models.SensorReading;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import io.grpc.StatusRuntimeException;

import java.util.concurrent.TimeUnit;
import java.util.logging.Logger;

public class SensorClient {
    private static final Logger logger = Logger.getLogger(SensorClient.class.getName());

    private final ManagedChannel channel;
    private final ReadingExchangeGrpc.ReadingExchangeBlockingStub readingExchangeBlockingStub;
    private final SensorUnit sensorUnit;

    public SensorClient(String host, int port, SensorUnit sensorUnit) {
        this.sensorUnit = sensorUnit;
        this.channel = ManagedChannelBuilder.forAddress(host, port).usePlaintext().build();
        this.readingExchangeBlockingStub = ReadingExchangeGrpc.newBlockingStub(channel);

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.err.println("Shutting down gRPC client since JVM is shutting down");
            try {
                SensorClient.this.stop();
            } catch (InterruptedException e) {
                e.printStackTrace(System.err);
            }
            System.err.println("Server shut down");
        }));
    }

    public void stop() throws InterruptedException {
        channel.shutdown().awaitTermination(5, TimeUnit.SECONDS);
    }
    public SensorReading readingExchange() throws InterruptedException {
        Empty request = Empty.newBuilder().build();
        SensorReading sensorReading = new SensorReading();
        logger.info("Sending reading exchange request.");
        try {
            SensorReadingGRPC response = readingExchangeBlockingStub.readingExchange(request);
            logger.info("Received: [temperature: " + response.getTemperature()
                    + ", pressure: " + response.getPressure()
                    + ", humidity: " + response.getHumidity()
                    + ", co: " + response.getCo()
                    + ", so2: " + response.getSo2()
                    + ", no2: " + response.getNo2()
                    + "]");
            sensorReading.setPressure(response.getPressure());
            sensorReading.setHumidity(response.getHumidity());
            sensorReading.setTemperature(response.getTemperature());
            sensorReading.setCo(response.getCo());
            sensorReading.setNo2(response.getNo2());
            sensorReading.setSo2(response.getSo2());
        } catch (StatusRuntimeException e) {
            this.sensorUnit.nearestIsDown();
            logger.info("RPC failed: " + e.getMessage());
            this.stop();
        }
        return sensorReading;
    }

//    public static void main(String[] args) throws InterruptedException {
//        SimpleUnaryRPCClient client = new SimpleUnaryRPCClient("127.0.0.1", 3000);
//        client.requestUppercase();
//        client.stop();
//    }
}
