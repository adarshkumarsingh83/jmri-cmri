package com.adarsh.model.trains.beans;

import lombok.Data;

import java.io.Serializable;

@Data
public class RequestBean implements Serializable {

    String topic;
    String data;
}
