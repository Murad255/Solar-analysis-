package com.solar.api.springTest;

import org.springframework.data.repository.CrudRepository;

public interface CatRepos extends CrudRepository<Cat, Long> {
}