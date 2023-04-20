package hr.fer.tel.rassus.sensor.models;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class Sensor {
    int id;
    double latitude;
    double longitude;
    String ip;
    String port;
}
