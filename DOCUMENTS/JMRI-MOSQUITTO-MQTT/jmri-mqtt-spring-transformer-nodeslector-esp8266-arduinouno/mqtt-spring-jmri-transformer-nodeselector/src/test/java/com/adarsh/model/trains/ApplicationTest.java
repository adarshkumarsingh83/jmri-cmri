package com.adarsh.model.trains;

import com.adarsh.model.trains.beans.NodeConfigurations;

import static com.adarsh.model.trains.service.MQTTService.*;


public class ApplicationTest {


    private String findBoardPin(NodeConfigurations.Nodes node, Integer pinNo, String state) {
        String data = "";
        int pin = pinNo - 1;
        int board = (pin / 16);
        if (board <= node.getTurnoutBoardCount() + node.getLightBoardCount()
                && pin <= (node.getTurnoutBoardCount() + node.getLightBoardCount()) * 16) {
            int totalPins = (board * 16);
            pin = (pin - totalPins);
            pin = (pin == -1) ? 0 : pin;
            data = (board < 10 ? "0" + board : board) + ":" + (pin < 10 ? "0" + pin : pin) + ":" + state;
        }
        return data;
    }


    public String nodeWiseDataGenerated(String type, NodeConfigurations.Nodes node, Integer inputPin, String state) {
        System.out.print(inputPin + ":");
        if (type.equals(TURNOUT)) {
            inputPin = (inputPin - node.getTurnoutStartAddress());
            inputPin = (inputPin * 2);
            if (state.equals(TH)) {
                inputPin = inputPin - 1;
            }
            // todo find board and pin for the turnout based on configuration
            return this.findBoardPin(node, inputPin, state);
        } else if (type.equals(SIGNAL)) {
            inputPin = (inputPin - node.getSignalStartAddress()) + (node.getTurnoutBoardCount() * 16);
            // todo find board and pin for the signal based on configuration
            return this.findBoardPin(node, inputPin, state);
        } else if (type.equals(LIGHT)) {
            inputPin = (inputPin - node.getLightStartAddress()) + (node.getTurnoutBoardCount() * 16) + node.getSignalCount();
            // todo find board and pin for the light based on configuration
            return this.findBoardPin(node, inputPin, state);
        }
        return null;
    }

    public static void main(String[] args) throws Exception {
        ApplicationTest applicationTest = new ApplicationTest();
        NodeConfigurations.Nodes node = new NodeConfigurations.Nodes();
        node.setTurnoutBoardCount(2);
        node.setTurnoutCount((node.getTurnoutBoardCount() * 16) / 2);
        node.setLightBoardCount(5);
        node.setSignalCount(30);
        node.setLightCount((node.getLightBoardCount() * 16) - (node.getSignalCount() * 3));
        node.setLightStartAddress(10000);
        node.setTurnoutStartAddress(20000);
        node.setSignalStartAddress(30000);

        int pins = (node.getTurnoutBoardCount() + node.getLightBoardCount()) * 16;
        int totalTurnoutsLimit = node.getTurnoutCount();
        int totalSignalLimit = node.getSignalCount();
        for (int i = 1; i <= pins; i++) {
            if (i <= totalTurnoutsLimit) {
                System.out.println(applicationTest.nodeWiseDataGenerated(TURNOUT, node, i + 20000, TH));
                System.out.println(applicationTest.nodeWiseDataGenerated(TURNOUT, node, i + 20000, CL));
            } else if ((i <= totalTurnoutsLimit + totalSignalLimit)) {
                System.out.println(applicationTest.nodeWiseDataGenerated(SIGNAL, node, (i + 30000 - node.getTurnoutCount()), ON));
                System.out.println(applicationTest.nodeWiseDataGenerated(SIGNAL, node, (i + 30000 - node.getTurnoutCount()), OFF));
            } else {
                if (i == (totalTurnoutsLimit + totalSignalLimit) + 1) {
                    i = (totalTurnoutsLimit * 2) + totalSignalLimit + 1;
                }
                System.out.println(applicationTest.nodeWiseDataGenerated(LIGHT, node, ((i - ((totalTurnoutsLimit * 2) + totalSignalLimit))) + 10000, ON));
                System.out.println(applicationTest.nodeWiseDataGenerated(LIGHT, node, ((i - ((totalTurnoutsLimit * 2) + totalSignalLimit))) + 10000, OFF));
            }
        }
    }
}
