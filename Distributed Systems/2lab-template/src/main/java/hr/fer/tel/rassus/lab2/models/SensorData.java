package hr.fer.tel.rassus.lab2.models;

import lombok.*;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class SensorData {
    int sTime;
    int[] vTime;
    int reading;
}
