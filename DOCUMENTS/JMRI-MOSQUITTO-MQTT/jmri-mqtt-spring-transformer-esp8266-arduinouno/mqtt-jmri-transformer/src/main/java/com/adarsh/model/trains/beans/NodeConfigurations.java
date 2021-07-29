package com.adarsh.model.trains.beans;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

import java.util.List;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */
@Data
@Component
@ConfigurationProperties("node.configurations")
public class NodeConfigurations {

    public List<Nodes> nodes;

    @Data
    public static class Nodes {
        String nodeId;
        Integer lightStartAddress;
        Integer lightCount;
        Integer turnoutStartAddress;
        Integer turnoutCount;
        Integer signalStartAddress;
        Integer signalCount;
    }
}
