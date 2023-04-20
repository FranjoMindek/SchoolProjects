package hr.fer.tel.rassus.sensor.models;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class SensorReading {
    double temperature;
    double pressure;
    double humidity;
    double co;
    double so2;
    double no2;
}
