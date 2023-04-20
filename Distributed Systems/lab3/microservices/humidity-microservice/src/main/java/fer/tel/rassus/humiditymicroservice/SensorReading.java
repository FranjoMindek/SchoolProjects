package fer.tel.rassus.humiditymicroservice;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@NoArgsConstructor
@ToString
@Entity
public class SensorReading {
    @Id
    private Long id;

    private String temperature, pressure, humidity, co, no2, so2;
}
