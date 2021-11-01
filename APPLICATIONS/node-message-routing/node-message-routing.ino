
#include "Config.h"

int temp = 0;
bool flag = true;
int i = 0;
bool snap = false;
bool servo = false;
bool sign2 = false;
bool sign3 = false;
bool light = false;

Node emptyNode{
  .nodeNo = -1,
  .lightStartAddress = -1,
  .lightCount = -1,
  .signal2LedStartAddress = -1,
  .signal2LedCount = -1,
  .signal3LedStartAddress = -1,
  .signal3LedCount = -1,
  .turnoutServoSartAddress = -1,
  .turnoutServoCount = -1,
  .turnoutSnapSartAddress = -1,
  .turnoutSnapCount = -1,
};


void setup() {
  Serial.begin(MESSAGE_BROAD_RATE);

}

void loop() {

  if (flag) {
    for (int i = 0; i < NODE_COUNT; i++) {
      displayNode(nodes[i], 0);
    }
    flag = false;
  }

  temp = random(SNAP_SWITCHES_MIN, SNAP_SWITCHES_MAX);
  displayNode(findNode(temp), temp);

  temp = random(SERVO_SWITCHES_MIN, SERVO_SWITCHES_MAX);
  displayNode(findNode(temp), temp);

  temp = random(SIGNALS_2LED_MIN, SIGNALS_2LED_MAX);
  displayNode(findNode(temp), temp);

  temp = random(SIGNALS_3LED_MIN, SIGNALS_3LED_MAX);
  displayNode(findNode(temp), temp);

  temp = random(LIGHTS_MIN, LIGHTS_MAX);
  displayNode(findNode(temp), temp);
  delay(DELEY_TIME);
}

Node findNode(long address) {

  Serial.print(" Input address ");
  Serial.print(address);
  Serial.println();

  snap = false;
  servo = false;
  sign2 = false;
  sign3 = false;
  light = false;

  if (address >= SNAP_SWITCHES_MIN && address <= SNAP_SWITCHES_MAX) {
    snap = true;
  } else if (address >= SERVO_SWITCHES_MIN &&  address <= SERVO_SWITCHES_MAX) {
    servo = true;
  } else if (address >= SIGNALS_2LED_MIN && address <= SIGNALS_2LED_MAX) {
    sign2 = true;
  } else if (address >= SIGNALS_3LED_MIN && address <= SIGNALS_3LED_MAX) {
    sign3 = true;
  } else if (address >= LIGHTS_MIN && address <= LIGHTS_MAX) {
    light = true;
  }

  for (int i = 0; i < NODE_COUNT; i++) {
    if (snap) {
      if (address >= nodes[i].turnoutSnapSartAddress && address <= nodes[i].turnoutSnapSartAddress + nodes[i].turnoutSnapCount) {
        return nodes[i];
      }
    } else if (servo) {
      if (address >= nodes[i].turnoutServoSartAddress && address <= nodes[i].turnoutServoSartAddress + nodes[i].turnoutServoCount) {
        return nodes[i];
      }
    } else if (sign2) {
      if (address >= nodes[i].signal2LedStartAddress && address <= nodes[i].signal2LedStartAddress + nodes[i].signal2LedCount) {
        return nodes[i];
      }
    } else if (sign3) {
      if (address >= nodes[i].signal3LedStartAddress && address <= nodes[i].signal3LedStartAddress + nodes[i].signal3LedCount) {
        return nodes[i];
      }
    } else if (light) {
      if (address >= nodes[i].lightStartAddress && address <= nodes[i].lightStartAddress + nodes[i].lightCount) {
        return nodes[i];
      }
    }
  }
  return emptyNode;
}

void displayNode(Node node, long address) {
  if (node.nodeNo != -1) {
    Serial.print(" Node ");
    Serial.print(node.nodeNo);
    Serial.println();
    Serial.print(" Light Starting Address ");
    Serial.print(node.lightStartAddress);
    Serial.print(" LightCount ");
    Serial.print(node.lightCount);
    Serial.println();
    Serial.print(" 2LedSignal Starting Address ");
    Serial.print(node.signal2LedStartAddress);
    Serial.print(" 2LedSignalCount ");
    Serial.print(node.signal2LedCount);
    Serial.println();
    Serial.print(" 3LedSignal Starting Address ");
    Serial.print(node.signal3LedStartAddress);
    Serial.print(" 3LedSignalCount ");
    Serial.print(node.signal3LedCount);
    Serial.println();
    Serial.print(" ServoTurout Starting Address ");
    Serial.print(node.turnoutServoSartAddress);
    Serial.print(" ServoTurnoutCount ");
    Serial.print(node.turnoutServoCount);
    Serial.println();
    Serial.print(" SnapTurout Starting Address ");
    Serial.print(node.turnoutSnapSartAddress);
    Serial.print(" SnapTurnoutCount ");
    Serial.print(node.turnoutSnapCount);
    Serial.println();
    Serial.println();
  } else {
    Serial.print(" NODE NOT CONFIGURED FOR ADDRESS  ");
    Serial.print(address);
    Serial.println();
    Serial.println();
  }
}
