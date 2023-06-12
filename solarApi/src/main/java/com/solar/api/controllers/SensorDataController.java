package com.solar.api.controllers;

import com.solar.api.data.WeatherData;
import com.solar.api.domain.model.SensorData;
import com.solar.api.domain.repo.SensorDataRepo;
import com.solar.api.storage.WeatherDataStorage;
import lombok.extern.apachecommons.CommonsLog;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.support.ServletUriComponentsBuilder;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.Optional;

@RestController
@CommonsLog
@RequestMapping("/SensorData")
public class SensorDataController {

    @Autowired
    private SensorDataRepo service;
    @Autowired
    WeatherDataStorage weatherDataStorage;
    @GetMapping("/")
    public Iterable<SensorData> read() {
        return service.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<SensorData> read(@PathVariable("id") Long id) {
        Optional<SensorData> foundAnswer = service.findById(id);
        SensorData answer = foundAnswer.isPresent() ? foundAnswer.get() : new SensorData();

        if (answer == null) {
            return ResponseEntity.notFound().build();
        } else {
            return ResponseEntity.ok(answer);
        }

    }

    @PostMapping("/")
    public ResponseEntity<SensorData> create(@RequestBody SensorData data) throws URISyntaxException {
        log.info("PutMapping V =" + data.normalV);
        UpdateSensorData(data);
        SensorData createdStudent = service.save(data);
        URI uri = ServletUriComponentsBuilder.fromCurrentRequest()
                .path("/{id}")
                .buildAndExpand(createdStudent.getId())
                .toUri();

        return ResponseEntity.created(uri)
                .body(createdStudent);

    }

    @PutMapping("/{id}")
    public ResponseEntity<SensorData> update(@RequestBody SensorData data, @PathVariable Long id) {
        log.info("PutMapping V =" + data.normalV);
        data.setId(id);
        UpdateSensorData(data);
        SensorData  updatedStudent = service.save( data);

        if (updatedStudent == null) {
            return ResponseEntity.notFound().build();
        } else {
            return ResponseEntity.ok(updatedStudent);
        }
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Object> deleteStudent(@PathVariable Long id) {
        service.deleteById(id);

        return ResponseEntity.noContent().build();
    }


    void UpdateSensorData(SensorData sensorData){
        WeatherData weatherData = weatherDataStorage.GetWeatherData();
        sensorData.setMain_temp(weatherData.getMain().getTemp());
        sensorData.setMain_feels_like(weatherData.getMain().getFeels_like());
        sensorData.setMain_temp_min(weatherData.getMain().getTemp_min());
        sensorData.setMain_temp_max(weatherData.getMain().getTemp_max());
        sensorData.setMain_pressure(weatherData.getMain().getPressure());
        sensorData.setMain_humidity(weatherData.getMain().getHumidity());
        sensorData.setMain_sea_level(weatherData.getMain().getSea_level());
        sensorData.setMain_grnd_level(weatherData.getMain().getGrnd_level());

        sensorData.setVisibility(weatherData.getVisibility());

        sensorData.setWind_speed(weatherData.getWind().getSpeed());
        sensorData.setWind_deg(weatherData.getWind().getDeg());
        sensorData.setWind_gust(weatherData.getWind().getGust());

        sensorData.setClouds_all(weatherData.getClouds().getAll());
        sensorData.setVisibility(weatherData.getVisibility());
        if(weatherData.getRain()!=null)
            sensorData.setRain_1h(weatherData.getRain().get_1h());


    }
}
