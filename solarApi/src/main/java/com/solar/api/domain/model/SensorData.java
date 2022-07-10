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
}
