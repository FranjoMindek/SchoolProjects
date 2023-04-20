package fer.tel.rassus.humiditymicroservice;

import com.opencsv.bean.CsvToBeanBuilder;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.io.*;
import java.util.List;

@SpringBootApplication
public class HumidityMicroserviceApplication implements CommandLineRunner {
	SensorRepository sensorRepository;

	@Autowired
	public void setSensorRepository(SensorRepository sensorRepository) {
		this.sensorRepository = sensorRepository;
	}

	public static void main(String[] args) {
		SpringApplication.run(HumidityMicroserviceApplication.class, args);
	}

	@Override
	public void run(String... args) throws Exception {
		InputStream is  = this.getClass().getResourceAsStream("/readings.csv");
		Reader r = new BufferedReader(new InputStreamReader(is));
		List<SensorReading> readings = new CsvToBeanBuilder<SensorReading>(r)
				.withType(SensorReading.class).build().parse();

		long l = 0;
		for(SensorReading reading: readings) reading.setId(l++);

		this.sensorRepository.saveAll(readings);
	}
}
