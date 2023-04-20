package hr.fer.tel.rassus.sensor.gRPC;

import hr.fer.tel.rassus.sensor.SensorUnit;
import io.grpc.Server;
import io.grpc.ServerBuilder;

import java.io.IOException;
import java.util.concurrent.TimeUnit;
import java.util.logging.Logger;

public class SensorServer {
    private static final Logger logger = Logger.getLogger(SensorServer.class.getName());

    private Server server;
    private final ReadingExchangeService service;
    private final int port;
    private SensorUnit sensorUnit;

    public SensorServer(ReadingExchangeService service, int port) {
        this.service = service;
        this.port = port;
    }

    public void start() throws IOException {
        server = ServerBuilder.forPort(this.port)
                .addService(this.service)
                .build().start();
        logger.info("Started server on " + port);

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.err.println("Shutting down gRPC server since JVM is shutting down");
            try {
                SensorServer.this.stop();
            } catch (InterruptedException e) {
                e.printStackTrace(System.err);
            }
            System.err.println("Server shut down");
        }));
    }

    public void stop() throws InterruptedException {
        if (server != null) {
            server.shutdown().awaitTermination(2, TimeUnit.SECONDS);
        }
    }

    public void blockUntilShutdown() throws InterruptedException {
        if (server != null) {
            server.awaitTermination();
        }
    }

//    public static void main(String[] args) throws IOException, InterruptedException {
//        final SimpleUnaryRPCServer server = new SimpleUnaryRPCServer(new UppercaseService(), 3000);
//        server.start();
//        server.blockUntilShutdown();
//    }
}
