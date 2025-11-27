String voice;

const int led1 = 2;
const int led2 = 3;
const int Fan = 4;
const int buzz = 5;

bool alarmOn = false;   // Alarm state
unsigned long lastBlink = 0;
bool ledState = false;

void allon() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(Fan, HIGH);
}

void alloff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(Fan, LOW);
  digitalWrite(buzz, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(Fan, OUTPUT);
}

void loop() {

  // ----------- READ VOICE COMMAND -------------
  while (Serial.available()) {
    delay(10);
    char c = Serial.read();
    if (c == '#') break;
    voice += c;
  }

  if (voice.length() > 0) {
    Serial.println(voice);

    if (voice == "Green lights on") {
      digitalWrite(led1, HIGH);
    }
    else if (voice == "lights off") {
      digitalWrite(led1, LOW);
    }
    else if (voice == "Red lights on") {
      digitalWrite(led2, HIGH);
    }
    else if (voice == "Red lights off") {
      digitalWrite(led2, LOW);
    }
    else if (voice == "Fan on") {
      digitalWrite(Fan, HIGH);
    }
    else if (voice == "Fan off") {
      digitalWrite(Fan, LOW);
    }
    else if (voice == "*all on") {
      allon();
    }
    else if (voice == "*all off") {
      alloff();
    }

    // ✅ ALARM ON
    else if (voice == "Alarm") {
      digitalWrite(buzz, HIGH);
      alarmOn = true;
    }

    // ✅ ALARM OFF
    else if (voice == "Alarm off") {
      digitalWrite(buzz, LOW);
      alarmOn = false;
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }

    voice = "";
  }

  // ----------- ALARM LOOP LOGIC -------------
  if (alarmOn) {
    unsigned long currentTime = millis();
    if (currentTime - lastBlink >= 500) {
      ledState = !ledState;
      digitalWrite(led1, ledState);
      digitalWrite(led2, ledState);
      lastBlink = currentTime;
    }
  }
}
