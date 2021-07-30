package com.adarsh.model.trains.beans;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;
import org.springframework.validation.annotation.Validated;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.util.List;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */
@Data
@Component
@Validated
@ConfigurationProperties("node.configurations")
public class NodeConfigurations {

    public List<Nodes> nodes;
    @NotBlank(message = "lightStartingAddress is mandatory properties in configuration ")
    @NotNull(message = "lightStartingAddress is mandatory properties in configuration ")
    Integer lightStartingAddress;
    @NotBlank(message = "turnoutStartingAddress is mandatory properties in configuration ")
    @NotNull(message = "turnoutStartingAddress is mandatory properties in configuration ")
    Integer turnoutStartingAddress;
    @NotBlank(message = "signalStartingAddress is mandatory properties in configuration ")
    @NotNull(message = "signalStartingAddress is mandatory properties in configuration ")
    Integer signalStartingAddress;

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
