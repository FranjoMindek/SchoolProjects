package hr.fer.tel.rassus.sensor;

/*
senzor
-> registracija kod servera
-> ocitaj podatke
-> dohvati najblizeg
ako postoji:
	-> zahtjev za dostavu ocitanja susjedu
	-> primi ocitanja od susjeda
	-> kalibriraj podatke
-> pohrani ocitanja na serveru
 */

import hr.fer.tel.rassus.sensor.models.Sensor;
import hr.fer.tel.rassus.sensor.models.SensorRegistration;
import hr.fer.tel.rassus.sensor.retrofit.RetrofitImplementation;

import java.io.IOException;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {
        String url = "http://localhost:8090";
        int numOfSensors = 1; // malo messy za logove al se moze vise od 1 pokrenuti

        for(int i = 0; i < numOfSensors; i++) {
            Thread t = new Thread(new SensorUnit(url, ThreadLocalRandom.current().nextInt(2000, 3000)));
            t.start();
        }
    }

    public static void testRetrofit(String url){
        RetrofitImplementation retrofitImplementation = new RetrofitImplementation(url);

        SensorRegistration sensor1 = new SensorRegistration(41.41, 41.41, "11.11.11.11", "1111");
        SensorRegistration sensor2 = new SensorRegistration(42.42, 42.42, "22.22.22.22", "2222");
        SensorRegistration sensor3 = new SensorRegistration(43.43, 43.43, "33.33.33.33", "3333");



        System.out.println("==============================================");
        System.out.println("=========== Starting retrofit test ===========");
        System.out.println("==============================================");
        System.out.println("Inserting sensor1, id = " + retrofitImplementation.insertSensor(sensor1));
        System.out.println("Inserting sensor2, id = " + retrofitImplementation.insertSensor(sensor2));
        System.out.println("Inserting sensor3, id = " + retrofitImplementation.insertSensor(sensor3));
        System.out.println("==============================================");
        System.out.print("Getting list of all sensors: ");
        List<Sensor> sensorList = retrofitImplementation.getSensors();
        System.out.println(sensorList);
        System.out.println("==============================================");
        System.out.println("Getting sensor2 nearest sensor");
        SensorRegistration sensorRegistration1 = retrofitImplementation.getNearestSensor(1);
        System.out.println(sensorRegistration1);
        System.out.println("Getting sensor3 nearest sensor");
        SensorRegistration sensorRegistration2 = retrofitImplementation.getNearestSensor(2);
        System.out.println(sensorRegistration2);


    }
}
