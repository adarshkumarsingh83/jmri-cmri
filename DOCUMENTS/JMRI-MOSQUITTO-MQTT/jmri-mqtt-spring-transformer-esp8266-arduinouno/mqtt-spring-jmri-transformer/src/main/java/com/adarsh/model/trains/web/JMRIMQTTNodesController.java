package com.adarsh.model.trains.web;

import com.adarsh.model.trains.beans.RequestBean;
import com.adarsh.model.trains.service.MQTTService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@Slf4j
@RestController
public class JMRIMQTTNodesController {

    @Autowired
    MQTTService mqttService;

    @GetMapping("/node/{nodeId}")
    public String getNodeData(@PathVariable("nodeId") String nodeId) throws Exception {
        return this.mqttService.getData(nodeId);
    }


    @PostMapping("/node/{nodeId}")
    public String postNodeData(@PathVariable("nodeId") String nodeId, @RequestBody RequestBean data) throws Exception {
        try {
            this.mqttService.publish(data.getTopic(), data.getData(), 1, false);
        }catch (Exception e){
            return "PROCESSED-FAILED";
        }
        return "PROCESSED-SUCCESS";
    }
}
