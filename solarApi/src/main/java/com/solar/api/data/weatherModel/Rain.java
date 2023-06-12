package com.solar.api.data.weatherModel;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.RequiredArgsConstructor;

import javax.persistence.Table;
import javax.xml.bind.annotation.XmlElement;
import java.io.Serializable;

@Data
@RequiredArgsConstructor
@AllArgsConstructor
@Table(name = "rain")
public class Rain implements Serializable {

    @XmlElement(name="1h")
    @JsonProperty("1h")
    double _1h;
}
