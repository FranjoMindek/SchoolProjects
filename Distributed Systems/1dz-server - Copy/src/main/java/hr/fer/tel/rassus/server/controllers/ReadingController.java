package hr.fer.tel.rassus.server.controllers;


import hr.fer.tel.rassus.server.models.Reading;
import hr.fer.tel.rassus.server.models.SensorReading;
import hr.fer.tel.rassus.server.models.UpdateInsertDeleteResponse;
import hr.fer.tel.rassus.server.services.ReadingService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.util.List;

@RestController
@RequestMapping("/reading")
public class ReadingController {

    private final ReadingService readingService;

    public ReadingController(ReadingService readingService) {
        this.readingService = readingService;
    }

    @PostMapping("/insert/{id}")
    public ResponseEntity<?> insertReadingById(@PathVariable("id") int sensorId,
                                  @RequestBody SensorReading sensorReading) {
        UpdateInsertDeleteResponse updateInsertDeleteResponse = this.readingService.insertReading(sensorId, sensorReading);
        if (updateInsertDeleteResponse.isValid()){
            return ResponseEntity.created(URI.create("/reading/get/" + updateInsertDeleteResponse.getId())).build();
        } else {
            return ResponseEntity.noContent().build();
        }
    }

    @GetMapping("/get/bySensor/{id}")
    public ResponseEntity<List<Reading>> getReadingsById(@PathVariable("id") int sensorId) {
        List<Reading> readingList = this.readingService.getReadingsById(sensorId);
        if (readingList != null) {
            return ResponseEntity.ok(readingList);
        } else {
            return ResponseEntity.noContent().build();
        }
    }
  // TODO 4.3  Spremanje očitanja pojedinog senzora

  // TODO 4.5  Popis očitanja pojedinog senzora

}