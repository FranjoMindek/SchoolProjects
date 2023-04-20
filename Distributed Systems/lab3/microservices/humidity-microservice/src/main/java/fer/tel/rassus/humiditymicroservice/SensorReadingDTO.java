package fer.tel.rassus.humiditymicroservice;

import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public class SensorReadingDTO {
    private String name, unit;
    private Double value;
}
