/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


package hr.fer.tel.rassus.lab2.network;

import java.util.Random;

/**
 *
 * @author Aleksandar
 */
public class EmulatedSystemClock {

    private final long startTime;
    private final double jitter; //jitter per second,  percentage of deviation per 1 second

    public EmulatedSystemClock() {
        startTime = System.currentTimeMillis();
        Random r = new Random();
        jitter = (r.nextInt(20 )) / 100d; //divide by 10 to get the interval between [0, 20], and then divide by 100 to get percentage
    }

    public long currentTimeMillis() {
        long current = System.currentTimeMillis();
        long diff = current - startTime;
        double coef = 1.0 * diff / 1000;
        return startTime + Math.round(diff * Math.pow((1+jitter), coef));
    }


}