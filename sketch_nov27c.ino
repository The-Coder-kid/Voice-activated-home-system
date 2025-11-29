String voice;

int led1 = 2;
int led2 = 3;

void allon() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}

void alloff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {

  while (Serial.available()) {
    delay(10);
    char c = Serial.read();
    if (c == '#') {
      break;
    }
    voice += c;
  }

  if (voice.length() > 0) {
    Serial.println(voice);

    if (voice == "Green lights on") {
      digitalWrite(led1, HIGH);
    }
    else if (voice == "Green lights off") {
      digitalWrite(led1, LOW);
    }
    else if (voice == "Red lights on") {
      digitalWrite(led2, HIGH);
    }
    else if (voice == "Red lights off") {
      digitalWrite(led2, LOW);
    }
    else if (voice == "*All on") {
      allon();
    }
    else if (voice == "*All off") {
      alloff();
    }

    voice = "";
  }
}
