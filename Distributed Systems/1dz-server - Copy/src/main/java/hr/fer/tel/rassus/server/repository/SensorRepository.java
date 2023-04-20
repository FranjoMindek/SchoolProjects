package hr.fer.tel.rassus.server.repository;

import hr.fer.tel.rassus.server.models.Sensor;
import hr.fer.tel.rassus.server.models.UpdateInsertDeleteResponse;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.logging.Logger;

@Repository
public class SensorRepository {
    List<Sensor> data = new ArrayList<>();
    Map<Integer, Sensor> nearestData = new HashMap<>();
    private static final Logger logger = Logger.getLogger(SensorRepository.class.getName());

    public UpdateInsertDeleteResponse insertSensor(Sensor sensor) {
        UpdateInsertDeleteResponse updateInsertDeleteResponse = new UpdateInsertDeleteResponse();
        logger.info("insertSensor: Adding new Sensor: " + sensor);
        this.data.add(sensor);
        updateInsertDeleteResponse.setId(sensor.getId());
        updateInsertDeleteResponse.setValid(true);
        return updateInsertDeleteResponse;
    }

    public List<Sensor> getSensors() {
        return data;
    }

    // id krece od 0 inkrementalno pa se savrseno mapira na array
    public Sensor getSensor(int id) {
        if (this.data.size() < id) {
            logger.info("getSensor: Received sensor with invalid id.");
            return null;
        }
        return this.data.get(id);

    }

    public Sensor getNearestSensor(int id) {
        if (this.data.size() == 1) {
            logger.info("getNearestSensor: Sadly the first sensor can't have a nearest companion.");
            return null;
        }
        if (this.data.size() < id)  {
            logger.info("getNearestSensor: Received sensor with invalid id.");
            return null;
        }
        if (!nearestData.containsKey(id)) {
            Sensor first = data.get(id);
            AtomicReference<Double> smallestDistance = new AtomicReference<>(Double.MAX_VALUE);
            AtomicInteger smallestId = new AtomicInteger();
            data.stream().filter(sensor -> sensor.getId() != id).forEach(second -> {
                /*
                 * R ← 6371;
                 * dlon ← lon2 − lon1;
                 * dlat ← lat2 − lat1;
                 * a ← (sin(dlat/2))2 + cos(lat1) ∗ cos(lat2) ∗ (sin(dlon/2))2;
                 * c ← 2 ∗ atan2(sqrt(a), sqrt(1 − a));
                 * d ← R ∗ c;
                 * */
                double dlon = second.getLongitude() - first.getLongitude();
                double dlat = second.getLatitude() - first.getLatitude();
                double a = Math.pow(Math.sin(dlat / 2), 2) +
                                Math.cos(first.getLatitude()) *
                                Math.cos(second.getLatitude()) *
                                Math.pow(Math.sin(dlon / 2), 2);
                double c = Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
                double distance = c * 6371;
                logger.info("getNearestSensor: For sensor with id " + id + ", sensor with " + second.getId() + " has distance of: " + distance);
                if (distance < smallestDistance.get()) {
                    smallestDistance.set(distance);
                    smallestId.set(second.getId());
                }
            });
            this.nearestData.put(id, this.data.get(smallestId.get()));
        }
        return nearestData.get(id);
    }

}
