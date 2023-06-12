package com.solar.api.data.weatherModel;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.Table;
import java.io.Serializable;
@Data
@RequiredArgsConstructor
@AllArgsConstructor
@Table(name = "main")
public class MainWeatherData implements Serializable {
    double temp;
    double feels_like;
    double temp_min;
    double temp_max;
    int pressure;
    int humidity;
    int sea_level;
    int grnd_level;
}
