package com.solar.api.springTest;


import lombok.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.persistence.*;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

@EqualsAndHashCode
@Data
@Getter
@Setter
@ToString
@RequiredArgsConstructor
@Builder
@AllArgsConstructor
@Table(name = "Cat")
@Entity
public class Cat implements  Pet{

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    public long id;

    String name;


    @Override
    public void Say() {
        System.out.println("Cat say");
    }
}
