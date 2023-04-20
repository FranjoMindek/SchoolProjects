package hr.fer.tel.rassus.sensor.retrofit;

import hr.fer.tel.rassus.sensor.models.Reading;
import hr.fer.tel.rassus.sensor.models.SensorReading;
import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Path;

import java.util.List;

public interface ReadingApi {

    @GET("/reading/bySensor/{id}")
    Call<List<Reading>> getReadingsById(@Path("id") int sensorId);

    @POST("/reading/insert/{id}")
    Call<Void> insertReadingById(@Path("id") int sensorId, @Body SensorReading sensorReading);

}
