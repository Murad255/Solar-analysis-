package com.solar.api.data.weatherModel;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.RequiredArgsConstructor;

import javax.persistence.Table;
import java.io.Serializable;

@Data
@RequiredArgsConstructor
@AllArgsConstructor
@Table(name = "clouds")
public class Clouds implements Serializable {
    int all;
}
