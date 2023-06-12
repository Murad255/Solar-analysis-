package com.solar.api.data.weatherModel;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.RequiredArgsConstructor;

import javax.persistence.Table;
import java.io.Serializable;
@Data
@RequiredArgsConstructor
@AllArgsConstructor
@Table(name = "wind")
public class Wind implements Serializable {
    double speed;
    int deg;
    double gust;
}
