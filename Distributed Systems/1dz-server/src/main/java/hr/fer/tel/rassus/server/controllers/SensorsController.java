package hr.fer.tel.rassus.server.controllers;

import hr.fer.tel.rassus.server.models.Sensor;
import hr.fer.tel.rassus.server.models.SensorRegistration;
import hr.fer.tel.rassus.server.models.UpdateInsertDeleteResponse;
import hr.fer.tel.rassus.server.services.SensorService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.util.List;

@RestController
@RequestMapping("/sensor")
public class SensorsController {
    private final SensorService sensorService;

    public SensorsController(SensorService sensorService) {
        this.sensorService = sensorService;
    }

    @GetMapping("/")
    public String test() {
        return "Hello World!";
    }

    @PostMapping("/insert")
    public ResponseEntity<?> insertSensor(@RequestBody SensorRegistration sensorRegistration) {
        UpdateInsertDeleteResponse updateInsertDeleteResponse = this.sensorService.insertSensor(sensorRegistration);
        if (updateInsertDeleteResponse.isValid()){
            return ResponseEntity.created(URI.create("/sensor/get/" + updateInsertDeleteResponse.getId())).build();
        }
        return null;
    }

    @GetMapping("/get/{id}")
    public ResponseEntity<SensorRegistration> getSensor(@PathVariable("id") int id) {
        SensorRegistration sensorRegistration = this.sensorService.getSensor(id);
        if(sensorRegistration != null) {
            return ResponseEntity.ok(sensorRegistration);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @GetMapping("/get/nearest/{id}")
    public ResponseEntity<SensorRegistration> getNearestSensor(@PathVariable("id") int id) {
        SensorRegistration sensorRegistration = this.sensorService.getNearestSensor(id);
        if(sensorRegistration != null) {
            return ResponseEntity.ok(sensorRegistration);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @GetMapping("/get")
    public ResponseEntity<List<Sensor>> getSensors() {
        List<Sensor> sensorList = this.sensorService.getSensors();
        if(!sensorList.isEmpty()) {
            return ResponseEntity.ok(sensorList);
        } else {
            return ResponseEntity.noContent().build();
        }
    }

}
