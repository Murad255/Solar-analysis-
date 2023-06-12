package com.solar.api.data.weatherModel;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.RequiredArgsConstructor;

import javax.persistence.Table;
import java.io.Serializable;

@Data
@RequiredArgsConstructor
@AllArgsConstructor
@Table(name = "sys")
public class Sys implements Serializable {
    int type;
    int id;
    String country;
    int sunrise;
    int sunset;
}
