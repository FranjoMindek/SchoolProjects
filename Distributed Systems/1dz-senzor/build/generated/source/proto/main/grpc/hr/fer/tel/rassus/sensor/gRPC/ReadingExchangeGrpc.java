package hr.fer.tel.rassus.sensor.gRPC;

import static io.grpc.MethodDescriptor.generateFullMethodName;

/**
 */
@javax.annotation.Generated(
    value = "by gRPC proto compiler (version 1.41.0)",
    comments = "Source: readingExchange.proto")
@io.grpc.stub.annotations.GrpcGenerated
public final class ReadingExchangeGrpc {

  private ReadingExchangeGrpc() {}

  public static final String SERVICE_NAME = "hr.fer.tel.rassus.ReadingExchange";

  // Static method descriptors that strictly reflect the proto.
  private static volatile io.grpc.MethodDescriptor<hr.fer.tel.rassus.sensor.gRPC.Empty,
      hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC> getReadingExchangeMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "ReadingExchange",
      requestType = hr.fer.tel.rassus.sensor.gRPC.Empty.class,
      responseType = hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<hr.fer.tel.rassus.sensor.gRPC.Empty,
      hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC> getReadingExchangeMethod() {
    io.grpc.MethodDescriptor<hr.fer.tel.rassus.sensor.gRPC.Empty, hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC> getReadingExchangeMethod;
    if ((getReadingExchangeMethod = ReadingExchangeGrpc.getReadingExchangeMethod) == null) {
      synchronized (ReadingExchangeGrpc.class) {
        if ((getReadingExchangeMethod = ReadingExchangeGrpc.getReadingExchangeMethod) == null) {
          ReadingExchangeGrpc.getReadingExchangeMethod = getReadingExchangeMethod =
              io.grpc.MethodDescriptor.<hr.fer.tel.rassus.sensor.gRPC.Empty, hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(SERVICE_NAME, "ReadingExchange"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  hr.fer.tel.rassus.sensor.gRPC.Empty.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC.getDefaultInstance()))
              .setSchemaDescriptor(new ReadingExchangeMethodDescriptorSupplier("ReadingExchange"))
              .build();
        }
      }
    }
    return getReadingExchangeMethod;
  }

  /**
   * Creates a new async stub that supports all call types for the service
   */
  public static ReadingExchangeStub newStub(io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<ReadingExchangeStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<ReadingExchangeStub>() {
        @java.lang.Override
        public ReadingExchangeStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new ReadingExchangeStub(channel, callOptions);
        }
      };
    return ReadingExchangeStub.newStub(factory, channel);
  }

  /**
   * Creates a new blocking-style stub that supports unary and streaming output calls on the service
   */
  public static ReadingExchangeBlockingStub newBlockingStub(
      io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<ReadingExchangeBlockingStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<ReadingExchangeBlockingStub>() {
        @java.lang.Override
        public ReadingExchangeBlockingStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new ReadingExchangeBlockingStub(channel, callOptions);
        }
      };
    return ReadingExchangeBlockingStub.newStub(factory, channel);
  }

  /**
   * Creates a new ListenableFuture-style stub that supports unary calls on the service
   */
  public static ReadingExchangeFutureStub newFutureStub(
      io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<ReadingExchangeFutureStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<ReadingExchangeFutureStub>() {
        @java.lang.Override
        public ReadingExchangeFutureStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new ReadingExchangeFutureStub(channel, callOptions);
        }
      };
    return ReadingExchangeFutureStub.newStub(factory, channel);
  }

  /**
   */
  public static abstract class ReadingExchangeImplBase implements io.grpc.BindableService {

    /**
     */
    public void readingExchange(hr.fer.tel.rassus.sensor.gRPC.Empty request,
        io.grpc.stub.StreamObserver<hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC> responseObserver) {
      io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall(getReadingExchangeMethod(), responseObserver);
    }

    @java.lang.Override public final io.grpc.ServerServiceDefinition bindService() {
      return io.grpc.ServerServiceDefinition.builder(getServiceDescriptor())
          .addMethod(
            getReadingExchangeMethod(),
            io.grpc.stub.ServerCalls.asyncUnaryCall(
              new MethodHandlers<
                hr.fer.tel.rassus.sensor.gRPC.Empty,
                hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC>(
                  this, METHODID_READING_EXCHANGE)))
          .build();
    }
  }

  /**
   */
  public static final class ReadingExchangeStub extends io.grpc.stub.AbstractAsyncStub<ReadingExchangeStub> {
    private ReadingExchangeStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected ReadingExchangeStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new ReadingExchangeStub(channel, callOptions);
    }

    /**
     */
    public void readingExchange(hr.fer.tel.rassus.sensor.gRPC.Empty request,
        io.grpc.stub.StreamObserver<hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC> responseObserver) {
      io.grpc.stub.ClientCalls.asyncUnaryCall(
          getChannel().newCall(getReadingExchangeMethod(), getCallOptions()), request, responseObserver);
    }
  }

  /**
   */
  public static final class ReadingExchangeBlockingStub extends io.grpc.stub.AbstractBlockingStub<ReadingExchangeBlockingStub> {
    private ReadingExchangeBlockingStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected ReadingExchangeBlockingStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new ReadingExchangeBlockingStub(channel, callOptions);
    }

    /**
     */
    public hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC readingExchange(hr.fer.tel.rassus.sensor.gRPC.Empty request) {
      return io.grpc.stub.ClientCalls.blockingUnaryCall(
          getChannel(), getReadingExchangeMethod(), getCallOptions(), request);
    }
  }

  /**
   */
  public static final class ReadingExchangeFutureStub extends io.grpc.stub.AbstractFutureStub<ReadingExchangeFutureStub> {
    private ReadingExchangeFutureStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected ReadingExchangeFutureStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new ReadingExchangeFutureStub(channel, callOptions);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC> readingExchange(
        hr.fer.tel.rassus.sensor.gRPC.Empty request) {
      return io.grpc.stub.ClientCalls.futureUnaryCall(
          getChannel().newCall(getReadingExchangeMethod(), getCallOptions()), request);
    }
  }

  private static final int METHODID_READING_EXCHANGE = 0;

  private static final class MethodHandlers<Req, Resp> implements
      io.grpc.stub.ServerCalls.UnaryMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ServerStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ClientStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.BidiStreamingMethod<Req, Resp> {
    private final ReadingExchangeImplBase serviceImpl;
    private final int methodId;

    MethodHandlers(ReadingExchangeImplBase serviceImpl, int methodId) {
      this.serviceImpl = serviceImpl;
      this.methodId = methodId;
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public void invoke(Req request, io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        case METHODID_READING_EXCHANGE:
          serviceImpl.readingExchange((hr.fer.tel.rassus.sensor.gRPC.Empty) request,
              (io.grpc.stub.StreamObserver<hr.fer.tel.rassus.sensor.gRPC.SensorReadingGRPC>) responseObserver);
          break;
        default:
          throw new AssertionError();
      }
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public io.grpc.stub.StreamObserver<Req> invoke(
        io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        default:
          throw new AssertionError();
      }
    }
  }

  private static abstract class ReadingExchangeBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoFileDescriptorSupplier, io.grpc.protobuf.ProtoServiceDescriptorSupplier {
    ReadingExchangeBaseDescriptorSupplier() {}

    @java.lang.Override
    public com.google.protobuf.Descriptors.FileDescriptor getFileDescriptor() {
      return hr.fer.tel.rassus.sensor.gRPC.ReadingExchangeOuterClass.getDescriptor();
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.ServiceDescriptor getServiceDescriptor() {
      return getFileDescriptor().findServiceByName("ReadingExchange");
    }
  }

  private static final class ReadingExchangeFileDescriptorSupplier
      extends ReadingExchangeBaseDescriptorSupplier {
    ReadingExchangeFileDescriptorSupplier() {}
  }

  private static final class ReadingExchangeMethodDescriptorSupplier
      extends ReadingExchangeBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoMethodDescriptorSupplier {
    private final String methodName;

    ReadingExchangeMethodDescriptorSupplier(String methodName) {
      this.methodName = methodName;
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.MethodDescriptor getMethodDescriptor() {
      return getServiceDescriptor().findMethodByName(methodName);
    }
  }

  private static volatile io.grpc.ServiceDescriptor serviceDescriptor;

  public static io.grpc.ServiceDescriptor getServiceDescriptor() {
    io.grpc.ServiceDescriptor result = serviceDescriptor;
    if (result == null) {
      synchronized (ReadingExchangeGrpc.class) {
        result = serviceDescriptor;
        if (result == null) {
          serviceDescriptor = result = io.grpc.ServiceDescriptor.newBuilder(SERVICE_NAME)
              .setSchemaDescriptor(new ReadingExchangeFileDescriptorSupplier())
              .addMethod(getReadingExchangeMethod())
              .build();
        }
      }
    }
    return result;
  }
}
