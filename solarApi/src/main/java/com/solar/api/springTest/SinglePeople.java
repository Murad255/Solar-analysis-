package com.solar.api.springTest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component("SinglePeople")
public class SinglePeople {

//    @Autowired
//    Person petPerson;

    @Autowired
    @Qualifier("Dog")
    Pet pet;

    public  SinglePeople(){
        System.out.println("SinglePeople create");
    }

    public void CallPet(){
        //petPerson.CallYourPet();
        pet.Say();
    }
}
