package com.adarsh.model.trains.web;

import com.adarsh.model.trains.service.MQTTService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@Slf4j
@RestController
public class JMRIMQTTNodesController {

    @Autowired
    MQTTService mqttService;

    @GetMapping("/node/{nodeId}")
    public String getNodeData(@PathVariable("nodeId") String nodeId) throws Exception {
        return this.mqttService.getData(nodeId);
    }

}
