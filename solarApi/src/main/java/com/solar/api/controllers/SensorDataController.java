package com.solar.api.controllers;

import com.solar.api.domain.model.SensorData;
import com.solar.api.domain.repo.SensorDataRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.support.ServletUriComponentsBuilder;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.Optional;

@RestController
@RequestMapping("/SensorData")
public class SensorDataController {

    @Autowired
    private SensorDataRepo service;

    @GetMapping("/")
    public Iterable<SensorData> read() {
        return service.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<SensorData> read(@PathVariable("id") Long id) {
        Optional<SensorData> foundAnswer = service.findById(id);
        SensorData answer = foundAnswer.isPresent() ? foundAnswer.get() : new SensorData();

        if (answer == null) {
            return ResponseEntity.notFound().build();
        } else {
            return ResponseEntity.ok(answer);
        }

    }

    @PostMapping("/")
    public ResponseEntity<SensorData> create(@RequestBody SensorData student) throws URISyntaxException {
        SensorData createdStudent = service.save(student);

        URI uri = ServletUriComponentsBuilder.fromCurrentRequest()
                .path("/{id}")
                .buildAndExpand(createdStudent.getId())
                .toUri();

        return ResponseEntity.created(uri)
                .body(createdStudent);

    }

    @PutMapping("/{id}")
    public ResponseEntity<SensorData> update(@RequestBody SensorData student, @PathVariable Long id) {

        student.setId(id);
        SensorData  updatedStudent = service.save( student);

        if (updatedStudent == null) {
            return ResponseEntity.notFound().build();
        } else {
            return ResponseEntity.ok(updatedStudent);
        }
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Object> deleteStudent(@PathVariable Long id) {
        service.deleteById(id);

        return ResponseEntity.noContent().build();
    }
}
