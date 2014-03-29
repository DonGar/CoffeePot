
#define SENSOR 4
#define INDICATOR 3
#define VALVE 2

#define MIN_TIME 2000
#define MAX_TIME 20000

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

unsigned long down = 0;

void loop() {
  bool waterLow = digitalRead(SENSOR);

  unsigned long now = millis();  

  // If the water is low, but we turned off, turn on.
  if (waterLow && !down) {
    down = now;
    flowOn();
    
    // Minimum activation time to reduce chatter.
    delay(MIN_TIME);
  }

  // If the water is not low, but we are on, turn off.
  if (!waterLow && down) {
    down = 0;
    flowOff();
    
    // Minimum activation time to reduce chatter.
    delay(MIN_TIME);
  }

  // If the water if flowing, see if it's reached the emergency cut off limit.  
  if ((waterLow && down) && (now > down + MAX_TIME)) {
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
