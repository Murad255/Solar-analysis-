package com.solar.api;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.solar.api.data.WeatherData;
import com.solar.api.data.weatherModel.Weather;
import com.solar.api.storage.WeatherDataStorage;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class TestGetRequest {
    private static String API_KEY = "49e051dfdea01c5914b5d50df927d6d7";
   // private static String API_KEY = "dc420b4243492d00f3e5909765aa462e";
    private static String LAT = "55.789891461972296";
    private static String LON = "37.594098919974975";

    static  String remp = "{\n" +
            "  \"coord\": {\n" +
            "    \"lon\": 10.99,\n" +
            "    \"lat\": 44.34\n" +
            "  },\n" +
            "  \"weather\": [\n" +
            "    {\n" +
            "      \"id\": 501,\n" +
            "      \"main\": \"Rain\",\n" +
            "      \"description\": \"moderate rain\",\n" +
            "      \"icon\": \"10d\"\n" +
            "    }\n" +
            "  ],\n" +
            "  \"base\": \"stations\",\n" +
            "  \"main\": {\n" +
            "    \"temp\": 298.48,\n" +
            "    \"feels_like\": 298.74,\n" +
            "    \"temp_min\": 297.56,\n" +
            "    \"temp_max\": 300.05,\n" +
            "    \"pressure\": 1015,\n" +
            "    \"humidity\": 64,\n" +
            "    \"sea_level\": 1015,\n" +
            "    \"grnd_level\": 933\n" +
            "  },\n" +
            "  \"visibility\": 10000,\n" +
            "  \"wind\": {\n" +
            "    \"speed\": 0.62,\n" +
            "    \"deg\": 349,\n" +
            "    \"gust\": 1.18\n" +
            "  },\n" +
            "  \"rain\": {\n" +
            "    \"1h\": 3.16\n" +
            "  },\n" +
            "  \"clouds\": {\n" +
            "    \"all\": 100\n" +
            "  },\n" +
            "  \"dt\": 1661870592,\n" +
            "  \"sys\": {\n" +
            "    \"type\": 2,\n" +
            "    \"id\": 2075663,\n" +
            "    \"country\": \"IT\",\n" +
            "    \"sunrise\": 1661834187,\n" +
            "    \"sunset\": 1661882248\n" +
            "  },\n" +
            "  \"timezone\": 7200,\n" +
            "  \"id\": 3163858,\n" +
            "  \"name\": \"Zocca\",\n" +
            "  \"cod\": 200\n" +
            "} ";
    public static void main2(String[] args) throws Exception {
//
//       String urlToRead =  "https://api.openweathermap.org/data/2.5/weather?lat="+LAT+"&lon="+LON+"&appid="+API_KEY+"&units=metric";
//
//        StringBuilder result = new StringBuilder();
//        URL url = new URL(urlToRead);
//        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
//        conn.setRequestMethod("GET");
//        try (BufferedReader reader = new BufferedReader(
//                new InputStreamReader(conn.getInputStream()))) {
//            for (String line; (line = reader.readLine()) != null; ) {
//                result.append(line);
//            }
//        }
//        String answer = result.toString();
//
//        ObjectMapper mapper = new ObjectMapper();

        WeatherDataStorage dataStorage = new WeatherDataStorage();
        WeatherData weatherData = dataStorage.GetWeatherData();//mapper.readValue(remp, WeatherData.class);

        System.out.println(weatherData.toString());
    }

}
