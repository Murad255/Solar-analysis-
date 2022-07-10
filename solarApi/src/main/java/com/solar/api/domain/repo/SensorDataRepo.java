package com.solar.api.domain.repo;

import com.solar.api.domain.model.SensorData;
import org.springframework.data.repository.CrudRepository;

public interface SensorDataRepo extends CrudRepository<SensorData, Long> {

}
