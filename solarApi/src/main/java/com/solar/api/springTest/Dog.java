package com.solar.api.springTest;

import org.springframework.stereotype.Component;

@Component("Dog")
public class Dog implements Pet{
    public Dog(){
        System.out.println("Dog create");
    }
    @Override
    public void Say() {
        System.out.println("Dog say");
    }
}
