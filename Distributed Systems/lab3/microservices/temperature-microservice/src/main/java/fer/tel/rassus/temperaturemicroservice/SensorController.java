package fer.tel.rassus.temperaturemicroservice;

import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Optional;

@RequiredArgsConstructor
@RestController
@RequestMapping("/reading") // kako REST api ako je 1 dokument uvijek? readings implicira kolekciju
public class SensorController {
    private final SensorRepository sensorRepository;

    @GetMapping()
    public SensorReadingDTO getSensorReading() {
        long id = System.currentTimeMillis() / 1000 / 60; // milisekunde -> sekunde -> minute
        id = (id % 100) + 1;

        Optional<SensorReading> sensorReading = this.sensorRepository.findById(id);
        return sensorReading.map(reading ->
             new SensorReadingDTO(
                "Temperature",
                "C",
                Double.valueOf(reading.getTemperature()))
        ).orElse(null);
    }
}
