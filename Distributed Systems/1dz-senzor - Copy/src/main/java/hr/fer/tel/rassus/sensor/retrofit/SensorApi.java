package hr.fer.tel.rassus.sensor.retrofit;

import hr.fer.tel.rassus.sensor.models.Reading;
import hr.fer.tel.rassus.sensor.models.Sensor;
import hr.fer.tel.rassus.sensor.models.SensorReading;
import hr.fer.tel.rassus.sensor.models.SensorRegistration;
import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Path;

import java.util.List;

public interface SensorApi {

    @POST("/sensor/insert")
    Call<Void> insertSensor(@Body SensorRegistration sensorRegistration);

    @GET("/sensor/get/nearest/{id}")
    Call<SensorRegistration> getNearestSensor(@Path("id") int sensorId);

    @GET("/sensor/get")
    Call<List<Sensor>> getSensors();

}
