package hr.fer.tel.rassus.sensor.models;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class SensorRegistration {
    double latitude;
    double longitude;
    String ip;
    String port;
}
