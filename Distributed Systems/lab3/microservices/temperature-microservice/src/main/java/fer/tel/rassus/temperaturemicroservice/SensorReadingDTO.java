package fer.tel.rassus.temperaturemicroservice;

import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public class SensorReadingDTO {
    private String name, unit;
    private Double value;
}
