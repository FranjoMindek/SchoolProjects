package hr.fer.tel.rassus.server.repository;

import hr.fer.tel.rassus.server.models.Reading;
import hr.fer.tel.rassus.server.models.UpdateInsertDeleteResponse;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

@Repository
public class ReadingRepository {
    Map<Integer, List<Reading>> data = new HashMap<>();
    private static final Logger logger = Logger.getLogger(ReadingRepository.class.getName());

    public List<Reading> getReadingsById(int id) {
        if (!data.containsKey(id))
            return null;
        return this.data.get(id);
    }

    public UpdateInsertDeleteResponse insertReadingById(Reading reading, int id) {
        UpdateInsertDeleteResponse updateInsertDeleteResponse = new UpdateInsertDeleteResponse();
        logger.info("insertReadingById: Sensor with id " + id + " is adding new Reading: " + reading);
        this.data.computeIfAbsent(id, key -> new ArrayList<>()).add(reading);
        updateInsertDeleteResponse.setId(reading.getId());
        updateInsertDeleteResponse.setValid(true);
        return updateInsertDeleteResponse;
    }

}
