package com.solar.api.domain.model;

import lombok.*;

import javax.persistence.*;


@EqualsAndHashCode
@Data
@Getter
@Setter
@ToString
@RequiredArgsConstructor
@Builder
@AllArgsConstructor
@Table(name = "SensorData")
@Entity
public class SensorData {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    public long id;

    public int cleanI;
    public int cleanV;
    public double normalA;
    public double normalV;
    String time;
    long timestamp;

    double main_temp;
    double main_feels_like;
    double main_temp_min;
    double main_temp_max;
    int main_pressure;
    int main_humidity;
    int main_sea_level;
    int main_grnd_level;

    int visibility;

    double wind_speed;
    int wind_deg;
    double wind_gust;

    int clouds_all;
    double rain_1h;

//  "main": {
//        "temp": 298.48,
//                "feels_like": 298.74,
//                "temp_min": 297.56,
//                "temp_max": 300.05,
//                "pressure": 1015,
//                "humidity": 64,
//                "sea_level": 1015,
//                "grnd_level": 933
//    },
//            "visibility": 10000,
//            "wind": {
//        "speed": 0.62,
//                "deg": 349,
//                "gust": 1.18
//    },
//            "rain": {
//        "1h": 3.16
//    },
//            "clouds": {
//        "all": 100
//    },

}
