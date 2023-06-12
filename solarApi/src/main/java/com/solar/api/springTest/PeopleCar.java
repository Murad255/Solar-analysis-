package com.solar.api.springTest;

import lombok.*;
import javax.persistence.*;

@Data
@Getter
@Setter
@ToString
@RequiredArgsConstructor
@Builder
@AllArgsConstructor
@Table(name = "PeopleCar")
@Entity
public class PeopleCar {

        @Id
        @GeneratedValue(strategy = GenerationType.AUTO)
        long id;

        //...
        String name;

        @OneToOne(cascade = CascadeType.ALL)
        @JoinColumn(name = "PeopleCar_id", referencedColumnName = "id")
        private Person person;

//        @ManyToOne
//        @JoinColumn(name = "person_id")
//        @ManyToOne
//        @OneToOne
//        @JoinColumn(name="person_id", nullable=false)
//        Person person;
}
