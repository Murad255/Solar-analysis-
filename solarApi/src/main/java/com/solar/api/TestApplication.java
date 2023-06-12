package com.solar.api;

import com.solar.api.springTest.*;
import lombok.extern.apachecommons.CommonsLog;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

import java.util.ArrayList;

@CommonsLog
public class TestApplication {


//    static private MedicamentData medicamens;
//
//    @Autowired
//    static Person person;
//    static private GatewayOpenerRepo gatewayOpeners;

    public static void main2(String... args) throws Exception {
        ConfigurableApplicationContext context =  SpringApplication.run(TestApplication.class, args);

        //Person person= ApplicationParam.getSpringApplicationContext().getBean("Person", Person.class);
        try {

            Person person = new Person(1, "Stive2",new ArrayList<Cat>());
            person.getCats().add(new Cat(1, "16"));
            person.getCats().add(new Cat(2, "2"));
            person.getCats().add(new Cat(3, "3"));

            PeopleCar car = new PeopleCar(1L,"ewfw",person);
          //  person.setCar(car);
//
//            PersonRepo personRepo = context.getBean(PersonRepo.class);
//            personRepo.save(person);

            CarRepo carRepo = context.getBean(CarRepo.class);
            carRepo.save(car);
        }
        catch (Exception ex){
            log.error(ex.getMessage());
        }

        //person.CallYourPet();

//        SpringApplication.run(Application.class, args);
//        System.out.print("///////newmed ");
//
//        medicamens = new MedicamentData();
//        List<Medicament>  med = medicamens.read();
//
//       // med.size();
//        System.out.print("///////Size = "+med.size());
//
//        ConfigurableApplicationContext context = SpringApplication.run(Application.class);
//        ApplicationParam.setSpringApplicationContext(context);
//        MedicamentRepo repository = context.getBean(MedicamentRepo.class);
//
//        GatewayOpenerRepo  getOps = context.getBean(GatewayOpenerRepo.class);

//        DataConnectorHandler.beginNoAnnotation(ApplicationParam.getSpringApplicationContext());
//        String str = "<Module><Name>wather1</Name><BDType>Medicament</BDType><BDIndex>1</BDIndex></Module>";
//        Message msg = new Message(str);
//        String dbDataXml =  DataConnectorHandler.onMessageReceived(msg);

        // save a couple of customers
        //repository.save(new  Medicament(27L,"mezim",4L,5L,26,"tatlets",0L,0));
//        repository.save(new  Medicament("Chloe", "O'Brian"));
//        repository.save(new  Medicament("Kim", "Bauer"));
//        repository.save(new  Medicament("David", "Palmer"));
//        repository.save(new  Medicament("Michelle", "Dessler"));

        // fetch all customers
//        Iterable<Medicament> customers = repository.findAll();
//        System.out.println("Customers found with findAll():");
//        System.out.println("-------------------------------");
//        for (Medicament customer : customers) {
//            System.out.println(customer);
//        }
//        System.out.println();
//
//        // fetch an individual customer by ID
//        //Medicament customer = repository.findById(1L).get(); //findOne(1L);
//        List<GatewayOpener> datas  = getOps.findByLogin("logDemo");
//        GatewayOpener datas2  = getOps.findById(1L).get();
//
//        System.out.println("Customer found with findOne(1L):");
//        System.out.println("--------------------------------");
//        System.out.println(datas2);
//        System.out.println();
//
//        // fetch customers by last name
//        //List<Medicament> bauers = repository.findBySlotId(3L);
//
//        System.out.println("Customer found with repository.findBySlotId(3L):");
//        System.out.println("--------------------------------------------");
//        for (GatewayOpener bauer : datas) {
//            System.out.println(bauer);
//        }
//
//        context.close();
    }
}
