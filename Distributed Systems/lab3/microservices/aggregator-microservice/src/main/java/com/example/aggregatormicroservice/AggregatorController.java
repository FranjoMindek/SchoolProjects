package com.example.aggregatormicroservice;

import com.netflix.appinfo.InstanceInfo;
import com.netflix.discovery.EurekaClient;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.List;

@Slf4j
@RestController
@RequestMapping("/reading")
public class AggregatorController {
    @Value("${sensor.temperature.unit}")
    private String unit;

    private final SensorClient temperatureClient;
    private final SensorClient humidityClient;
    private final EurekaClient eurekaClient;

    public AggregatorController(EurekaClient eurekaClient) {
        this.eurekaClient = eurekaClient;

        this.humidityClient = new SensorClient(this.getUrl("HUMIDITY-SENSOR"));
        this.temperatureClient = new SensorClient(this.getUrl("TEMPERATURE-SENSOR"));
    }

    private String getUrl(String applicationName) {
        return this.eurekaClient.getNextServerFromEureka(applicationName, false).getHomePageUrl();
    }

    @GetMapping()
    public List<SensorReadingDTO> getSensor() {
        List<SensorReadingDTO> list = new ArrayList<>();
        log.info(this.unit);

        list.add(this.humidityClient.getSensorReading());
        if("K".equals(this.unit)) {
            SensorReadingDTO sensorReadingDTO = this.temperatureClient.getSensorReading();
            sensorReadingDTO.setValue(toKelvin(sensorReadingDTO.getValue()));
            sensorReadingDTO.setUnit("K");
            list.add(sensorReadingDTO);
        } else { list.add(this.temperatureClient.getSensorReading()); }

        return list;
    }

    public static double toKelvin(double celsiusValue) { return 273.15 + celsiusValue; }

}
