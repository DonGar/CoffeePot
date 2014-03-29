
#define SENSOR 4
#define INDICATOR 3
#define VALVE 2

#define DEBOUNCE_START_DELAY 2000
#define MAX_FLOW_TIME 20000

void setup() {
  pinMode(SENSOR, INPUT);
  pinMode(VALVE, OUTPUT);
  pinMode(INDICATOR, OUTPUT);
  
  digitalWrite(VALVE, LOW);
  digitalWrite(INDICATOR, LOW);
}

void flowOn() {
  digitalWrite(VALVE, HIGH);
  digitalWrite(INDICATOR, HIGH);
}

void flowOff() {
  digitalWrite(VALVE, LOW);
  digitalWrite(INDICATOR, LOW);
}

unsigned long water_low_detected = 0;
unsigned long water_flowing = 0;

void loop() {
  bool sensor_low = digitalRead(SENSOR);

  unsigned long now = millis();

  // If water switches to low, record it switched to low.
  if (sensor_low && !water_low_detected) {
    water_low_detected = now;
  }
  
  // If water stays low for longer than DEBOUNCE_START_DELAY, flow water into tank.
  if (water_low_detected && !water_flowing && (now > (water_low_detected + DEBOUNCE_START_DELAY))) {
    water_flowing = now;
    flowOn();
  }

  // If the water is not low, but we are on, turn off.
  if (!sensor_low && water_low_detected) {
    water_low_detected = 0;
    water_flowing = 0;
    flowOff();
  }

  // If the water is flowing, see if it's reached the emergency cut off limit.  
  if (water_flowing && (now > (water_flowing + MAX_FLOW_TIME))) {
    flowOff();

    // We never exit this state, you have to reset the device.    
    while (true) {
        digitalWrite(INDICATOR, LOW);
        delay(500);
        digitalWrite(INDICATOR, HIGH);
        delay(500);
    }
  }
}
