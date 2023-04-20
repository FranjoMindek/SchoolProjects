package com.example.aggregatormicroservice;

import retrofit2.Call;
import retrofit2.http.GET;

public interface SensorApi {

    @GET("/api/reading")
    Call<SensorReadingDTO> getSensorReading();
}
