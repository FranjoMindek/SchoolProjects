package hr.fer.tel.rassus.sensor.retrofit;

import hr.fer.tel.rassus.sensor.models.Reading;
import hr.fer.tel.rassus.sensor.models.Sensor;
import hr.fer.tel.rassus.sensor.models.SensorReading;
import hr.fer.tel.rassus.sensor.models.SensorRegistration;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.jackson.JacksonConverterFactory;

import java.io.IOException;
import java.util.List;
import java.util.logging.Logger;

public class RetrofitImplementation {
    private final String baseURL;
    private final ReadingApi readingApi;
    private final SensorApi sensorApi;
    private static final Logger logger = Logger.getLogger(RetrofitImplementation.class.getName());

    public RetrofitImplementation(String url) {
        this.baseURL = url;
        Retrofit retrofit = new Retrofit.Builder().baseUrl(url)
                .addConverterFactory(JacksonConverterFactory.create()).build();
        this.readingApi = retrofit.create(ReadingApi.class);
        this.sensorApi = retrofit.create(SensorApi.class);
    }

    // SENSORS STUFF
    public List<Sensor> getSensors() {
        try {
            return sensorApi.getSensors().execute().body();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public SensorRegistration getNearestSensor(int sensorId) {
        try {
            return sensorApi.getNearestSensor(sensorId).execute().body();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public int insertSensor(SensorRegistration sensorRegistration) {
        try {
            Response<Void> response = sensorApi.insertSensor(sensorRegistration).execute();
            String location = response.headers().get("Location");
            logger.info("Created new sensor at location: " + location);
            return Integer.parseInt(location.substring(location.lastIndexOf("/")+1));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    //READING STUFF
    public List<Reading> getReadingById(int sensorId) {
        try {
            return readingApi.getReadingsById(sensorId).execute().body();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void insertReading(int sensorId, SensorReading sensorReading) {
        try {
            Response<Void> response = readingApi.insertReadingById(sensorId, sensorReading).execute();
            String location = response.headers().get("Location");
            logger.info("Created new reading at location: " + location);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
