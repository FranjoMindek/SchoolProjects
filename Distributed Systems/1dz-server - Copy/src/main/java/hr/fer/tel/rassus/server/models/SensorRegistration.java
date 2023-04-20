package hr.fer.tel.rassus.server.models;

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
