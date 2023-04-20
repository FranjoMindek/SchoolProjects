package hr.fer.tel.rassus.sensor.models.mapper;


import hr.fer.tel.rassus.sensor.models.Sensor;
import hr.fer.tel.rassus.sensor.models.SensorRegistration;

public class SensorMapper {
//    private static int sensorId = 1;
    public static SensorRegistration toSensorReading(Sensor sensor) {
        SensorRegistration sensorRegistration = new SensorRegistration();
        sensorRegistration.setIp(sensor.getIp());
        sensorRegistration.setPort(sensor.getPort());
        sensorRegistration.setLatitude(sensor.getLatitude());
        sensorRegistration.setLongitude(sensor.getLongitude());

        return sensorRegistration;
    }

    public static Sensor toSensor(SensorRegistration sensorRegistration) {
        Sensor sensor = new Sensor();
        sensor.setIp(sensorRegistration.getIp());
        sensor.setPort(sensorRegistration.getPort());
        sensor.setLongitude(sensorRegistration.getLongitude());
        sensor.setLatitude(sensorRegistration.getLatitude());
//        sensor.setId(sensorId++);

        return sensor;
    }
}
