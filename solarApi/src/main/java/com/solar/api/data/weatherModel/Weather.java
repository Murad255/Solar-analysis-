package com.solar.api.data.weatherModel;

import lombok.*;

import javax.persistence.Table;
import java.io.Serializable;
@Data
@RequiredArgsConstructor
@AllArgsConstructor
@Table(name = "weather")
public class Weather implements Serializable {
      int id;
      String main;
      String description;
      String icon;
      int timezone;
}
