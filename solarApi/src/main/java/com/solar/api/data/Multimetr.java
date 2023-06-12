package com.solar.api.data;

import com.solar.api.domain.model.Sensor;
import com.solar.api.domain.model.SensorData;
import lombok.*;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;


@EqualsAndHashCode
@Data
@Getter
@Setter
@ToString
@RequiredArgsConstructor
@Builder
@AllArgsConstructor
@Table(name = "Multimetr")
@Entity
public class Multimetr extends Sensor {
    @Id
    @Column(name = "id", nullable = false)
    private Long id;

    @Override
    public SensorData[] GetData(){
        //TODO
        System.out.println("modiffed GetData");
        return null;
    }
}
