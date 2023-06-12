package com.solar.api.domain.model;

import javax.persistence.MappedSuperclass;

@MappedSuperclass
public abstract class Sensor {

    String name;
    int type;

    public SensorData[] GetData(){
        //TODO
        System.out.println("GetData");
        return null;
    }

}
