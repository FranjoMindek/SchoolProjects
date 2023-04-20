package hr.fer.tel.rassus.sensor.models.mapper;

import hr.fer.tel.rassus.sensor.models.Reading;
import hr.fer.tel.rassus.sensor.models.SensorReading;

public class ReadingMappeer {
//    public static int readingId = 1;
    public static Reading toReading(SensorReading sensorReading) {
        Reading reading = new Reading();
        reading.setCo(sensorReading.getCo());
        reading.setSo2(sensorReading.getSo2());
        reading.setHumidity(sensorReading.getHumidity());
        reading.setPressure(sensorReading.getPressure());
        reading.setTemperature(sensorReading.getTemperature());
        reading.setNo2(sensorReading.getNo2());
//        reading.setId(readingId++);

        return reading;
    }

    public static SensorReading toSensorReading(Reading reading) {
        SensorReading sensorReading = new SensorReading();
        sensorReading.setCo(reading.getCo());
        sensorReading.setSo2(reading.getSo2());
        sensorReading.setHumidity(reading.getHumidity());
        sensorReading.setPressure(reading.getPressure());
        sensorReading.setTemperature(reading.getTemperature());
        sensorReading.setNo2(reading.getNo2());

        return sensorReading;
    }
}
