package hr.fer.tel.rassus.server.models;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class UpdateInsertDeleteResponse {
    int id;
    boolean valid;
}
