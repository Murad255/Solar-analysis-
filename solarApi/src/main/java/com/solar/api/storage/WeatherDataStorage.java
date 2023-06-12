package com.solar.api.storage;


import com.fasterxml.jackson.databind.ObjectMapper;
import com.solar.api.data.WeatherData;
import org.springframework.stereotype.Service;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

@Service
public class WeatherDataStorage {

    private  String API_KEY = "49e051dfdea01c5914b5d50df927d6d7";
    private  String LAT = "55.789891461972296";
    private  String LON = "37.594098919974975";


    public WeatherData GetWeatherData()  {
        try {
            String urlToRead = "https://api.openweathermap.org/data/2.5/weather?lat=" + LAT + "&lon=" + LON + "&appid=" + API_KEY + "&units=metric";

            StringBuilder result = new StringBuilder();
            URL url = new URL(urlToRead);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(conn.getInputStream()))) {
                for (String line; (line = reader.readLine()) != null; ) {
                    result.append(line);
                }
            }
            String answer = result.toString();

            ObjectMapper mapper = new ObjectMapper();
            WeatherData weatherData = mapper.readValue(answer, WeatherData.class);
            //System.out.println(weatherData.toString());
            return  weatherData;
        }
        catch (Exception ex){
            return null;
        }
    }

}
