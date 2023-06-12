package com.solar.api.springTest;

import lombok.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.persistence.*;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import java.util.ArrayList;
import java.util.List;

@EqualsAndHashCode
@Data
@Getter
@Setter
@ToString
@RequiredArgsConstructor
@Builder
@AllArgsConstructor
@Table(name = "Person")
@Entity
public class Person {


    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
     long id;

    String name;

    @OneToMany(
            cascade = CascadeType.ALL,
            orphanRemoval = true
    )
    @JoinTable(
            name = "Cat_ref",
            joinColumns = @JoinColumn(name = "Person_id"),
            inverseJoinColumns = @JoinColumn(name = "Cat_id")
    )
     List<Cat> cats = new ArrayList<>();

//    @OneToOne(mappedBy = "person")
//    Car car;


//    public void CallYourPet(){
//        pet.Say();
//    }

}
