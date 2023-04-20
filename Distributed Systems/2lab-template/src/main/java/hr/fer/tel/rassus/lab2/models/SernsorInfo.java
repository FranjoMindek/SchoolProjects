package hr.fer.tel.rassus.lab2.models;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@AllArgsConstructor
@ToString
public class SernsorInfo {
    int id;
    String address;
    int port;
}
