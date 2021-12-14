int trig = 7, echo = 13;
long duration;
float distance;

char t;
int r1 = 6, r2 = 5, l1 = 11, l2 = 10, led = 9, mic = 12;

void setup() {
  ///Sonar pins
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  //Led and MIC
  pinMode(led, OUTPUT);
  pinMode(mic, OUTPUT);

  ///Motor Driver pins
  pinMode(r1, OUTPUT);  //right motors forward
  pinMode(r2, OUTPUT);  //right motors reverse
  pinMode(l1, OUTPUT);  //left motors forward
  pinMode(l2, OUTPUT);  //left motors reverse

  
  Serial.begin(9600);

}

void loop() {
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);

  if (Serial.available()) {
    t = Serial.read();
  }

  if (distance < 30) {
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);

    for (int i = 0; i < 10; i++) {
      Serial.println("mic");
      digitalWrite(led, HIGH);
      digitalWrite(mic, HIGH);
      delay(50);
      digitalWrite(led, LOW);
      digitalWrite(mic, LOW);
      delay(30);

    }
    //delay(1000);
    digitalWrite(led, LOW);

    analogWrite(r1, 150);
    digitalWrite(r2, LOW);
    digitalWrite(l1, LOW);
    analogWrite(l2, 170);
    delay(500);
    digitalWrite(r1, LOW);
    analogWrite(r2, 150);
    analogWrite(l1, 170);
    digitalWrite(l2, LOW);
    delay(500);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    t = 'B';
  }
  else {
    if (t == 'F') {          //move forward(all motors rotate in forward direction)
      analogWrite(r1, 150);
      digitalWrite(r2, LOW);
      analogWrite(l1, 180);
      digitalWrite(l2, LOW);
    }

    else if (t == 'B') {    //move reverse (all motors rotate in reverse direction)
      for (int i = 0; i < 10; i++) {
        Serial.println("mic");
        digitalWrite(led, HIGH);
        digitalWrite(mic, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        digitalWrite(mic, LOW);
        delay(30);

      }
      delay(500);
      digitalWrite(r1, LOW);
      analogWrite(r2, 150);
      digitalWrite(l1, LOW);
      analogWrite(l2, 170);
      delay(1000);
      t = 'S';
    }

    else if (t == 'L') {    //turn right (left side motors rotate in forward direction, right side motors rotate in reverse direction for 100ms & stop)
      analogWrite(r1, 150);
      digitalWrite(r2, LOW);
      digitalWrite(l1, LOW);
      analogWrite(l2, 170);
      delay(150);
      t = 'S';
    }

    else if (t == 'R') {    //turn left (right side motors rotate in forward direction, left side motors rotate in reverse direction for 100ms & stop)
      digitalWrite(r1, LOW);
      analogWrite(r2, 150);
      analogWrite(l1, 170);
      digitalWrite(l2, LOW);
      delay(150);
      t = 'S';
    }

    else if (t == 'S') {    //STOP (all motors stop)
      digitalWrite(r1, LOW);
      digitalWrite(r2, LOW);
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(led, HIGH);
      delay(2000);
      digitalWrite(led, LOW);
    }
  }
}
