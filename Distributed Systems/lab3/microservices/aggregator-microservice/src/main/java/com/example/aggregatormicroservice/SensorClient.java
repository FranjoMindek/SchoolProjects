package com.example.aggregatormicroservice;

import retrofit2.Retrofit;
import retrofit2.converter.jackson.JacksonConverterFactory;

import java.io.IOException;

public class SensorClient {
    private final String baseURL;
    private final SensorApi sensorApi;

    public SensorClient(String url) {
        this.baseURL = url;
        Retrofit retrofit = new Retrofit
                .Builder()
                .baseUrl(this.baseURL)
                .addConverterFactory(JacksonConverterFactory.create())
                .build();
        this.sensorApi = retrofit.create(SensorApi.class);
    }

    public SensorReadingDTO getSensorReading() {
        try {
            return sensorApi.getSensorReading().execute().body();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
