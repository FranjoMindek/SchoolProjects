package hr.fer.tel.rassus.server.services;

import hr.fer.tel.rassus.server.models.Sensor;
import hr.fer.tel.rassus.server.models.SensorRegistration;
import hr.fer.tel.rassus.server.models.UpdateInsertDeleteResponse;
import hr.fer.tel.rassus.server.models.mapper.SensorMapper;
import hr.fer.tel.rassus.server.repository.SensorRepository;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class SensorService {

    private final SensorRepository sensorRepository;


    public SensorService(SensorRepository sensorRepository) {
        this.sensorRepository = sensorRepository;
    }

    public UpdateInsertDeleteResponse insertSensor(SensorRegistration sensorRegistration) {
        return this.sensorRepository.insertSensor(SensorMapper.toSensor(sensorRegistration));
    }

    public SensorRegistration getSensor(int id) {
        Sensor sensor = this.sensorRepository.getSensor(id);
        if (sensor != null) {
            return SensorMapper.toSensorReading(sensor);
        }
        return null;
    }

    public SensorRegistration getNearestSensor(int id) {
        Sensor sensor = this.sensorRepository.getNearestSensor(id);
        if (sensor != null) {
            return SensorMapper.toSensorReading(sensor);
        }
        return null;
    }

    public List<Sensor> getSensors() {
        return this.sensorRepository.getSensors();
    }
}
