package com.solar.api.data;

import com.solar.api.data.weatherModel.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.RequiredArgsConstructor;

import java.io.Serializable;

@Data
@RequiredArgsConstructor
@AllArgsConstructor
public class WeatherData implements Serializable {
    Coord coord;
    Weather[]  weather;
    String  base;
    MainWeatherData main;
    int visibility;
    Wind wind;
    Clouds clouds;
    int dt;
    Sys sys;

    String timezone;
    int id;
    String name;
    int cod;
    Rain rain;
}
