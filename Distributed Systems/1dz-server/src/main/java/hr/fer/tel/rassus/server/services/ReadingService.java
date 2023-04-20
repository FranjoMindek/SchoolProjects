package hr.fer.tel.rassus.server.services;

import hr.fer.tel.rassus.server.models.Reading;
import hr.fer.tel.rassus.server.models.SensorReading;
import hr.fer.tel.rassus.server.models.UpdateInsertDeleteResponse;
import hr.fer.tel.rassus.server.models.mapper.ReadingMappeer;
import hr.fer.tel.rassus.server.repository.ReadingRepository;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ReadingService {

    private final ReadingRepository readingRepository;
    private final SensorService sensorService;

    public ReadingService(ReadingRepository readingRepository, SensorService sensorService){
        this.readingRepository = readingRepository;
        this.sensorService = sensorService;
    }

    public UpdateInsertDeleteResponse insertReading(int id, SensorReading sensorReading) {
        return this.readingRepository.insertReadingById(ReadingMappeer.toReading(sensorReading), id);
    }

    public List<Reading> getReadingsById(int id) {
        return this.readingRepository.getReadingsById(id);
    }
}
