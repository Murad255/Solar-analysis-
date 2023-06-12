package com.solar.api.springTest;

import org.springframework.data.repository.CrudRepository;

public interface CarRepo extends CrudRepository<PeopleCar, Long> {
}