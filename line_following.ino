// ================= SENSOR PINS =================
int S1 = A5;
int S2 = A4;
int S3 = A3;
int S4 = A2;
int S5 = A1;

int threshold = 690;

// ================= MOTOR PINS =================
int MR_PWM = 9;
int MR_DIR = 7;
int ML_PWM = 10;
int ML_DIR = 8;

// ================= SPEED =================
int straightSpeed = 180;
int turnSpeed     = 140;
int sharpSpeed    = 120;
int recoverySpeed = 180;

int turn45Speed = 100;
int turn75Speed = 90;

bool lastLeft = false;
bool lastRight = false;

unsigned long lastLineTime = 0;
const unsigned long stopDelay = 800;

void setup() {
  pinMode(MR_PWM, OUTPUT);
  pinMode(MR_DIR, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(ML_DIR, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  bool s1 = analogRead(S1) > threshold;
  bool s2 = analogRead(S2) > threshold;
  bool s3 = analogRead(S3) > threshold;
  bool s4 = analogRead(S4) > threshold;
  bool s5 = analogRead(S5) > threshold;

  bool online = s1 || s2 || s3 || s4 || s5;
  if (online) lastLineTime = millis();

  // ================= STRAIGHT =================
  if (!s1 && s2 && s3 && s4 && !s5) {
    moveForward(straightSpeed);
    lastLeft = lastRight = false;
  }

  // ================= 45 DEG LEFT =================
  else if (!s1 && s2 && s3 && !s4 && !s5) {
    left45(turn45Speed);
    lastLeft = true; lastRight = false;
  }

  // ================= 45 DEG RIGHT =================
  else if (!s1 && !s2 && s3 && s4 && !s5) {
    right45(turn45Speed);
    lastRight = true; lastLeft = false;
  }

  // ================= 75 DEG LEFT =================
  else if (s1 && s2 && s3 && !s4 && !s5) {
    left75(turn75Speed);
    lastLeft = true; lastRight = false;
  }

  // ================= 75 DEG RIGHT =================
  else if (!s1 && !s2 && s3 && s4 && s5) {
    right75(turn75Speed);
    lastRight = true; lastLeft = false;
  }

  // ================= SLIGHT RIGHT =================
  else if (!s1 && !s2 && !s3 && s4 && s5) {
    rightTurn(turnSpeed);
    lastRight = true; lastLeft = false;
  }

  // ================= SLIGHT LEFT =================
  else if (s1 && s2 && !s3 && !s4 && !s5) {
    leftTurn(turnSpeed);
    lastLeft = true; lastRight = false;
  }

  // ================= SHARP RIGHT =================
  else if (!s1 && !s2 && !s3 && !s4 && s5) {
    pivotRight(sharpSpeed);
    lastRight = true; lastLeft = false;
  }

  // ================= SHARP LEFT =================
  else if (s1 && !s2 && !s3 && !s4 && !s5) {
    pivotLeft(sharpSpeed);
    lastLeft = true; lastRight = false;
  }

  // ================= LOST / END =================
  // ================= LOST / RECOVERY =================
else if (!s1 && !s2 && !s3 && !s4 && !s5) {

  // NEVER STOP – ALWAYS SEARCH
  if (lastLeft) {
    pivotLeft(recoverySpeed);   // search left
  }
  else if (lastRight) {
    pivotRight(recoverySpeed);  // search right
  }
  else {
    // first time lost → slow spin
    pivotLeft(120);
  }
}

  // ================= FALLBACK =================
  else {
    moveForward(turnSpeed);
  }
}

// ================= MOTOR FUNCTIONS =================

void moveForward(int spd) {
  digitalWrite(MR_DIR, HIGH);
  digitalWrite(ML_DIR, HIGH);
  analogWrite(MR_PWM, spd);
  analogWrite(ML_PWM, spd);
}

void leftTurn(int spd) {
  digitalWrite(MR_DIR, HIGH);
  digitalWrite(ML_DIR, HIGH);
  analogWrite(MR_PWM, spd);
  analogWrite(ML_PWM, spd - 30);
}

void rightTurn(int spd) {
  digitalWrite(MR_DIR, HIGH);
  digitalWrite(ML_DIR, HIGH);
  analogWrite(MR_PWM, spd - 30);
  analogWrite(ML_PWM, spd);
}

// ===== 45 DEG =====
void left45(int spd) {
  digitalWrite(MR_DIR, HIGH);
  digitalWrite(ML_DIR, HIGH);
  analogWrite(MR_PWM, spd);
  analogWrite(ML_PWM, spd - 45);
}

void right45(int spd) {
  digitalWrite(MR_DIR, HIGH);
  digitalWrite(ML_DIR, HIGH);
  analogWrite(MR_PWM, spd - 45);
  analogWrite(ML_PWM, spd);
}

// ===== 75 DEG =====
void left75(int spd) {
  digitalWrite(MR_DIR, HIGH);
  digitalWrite(ML_DIR, HIGH);
  analogWrite(MR_PWM, spd);
  analogWrite(ML_PWM, 20);
}

void right75(int spd) {
  digitalWrite(MR_DIR, HIGH);
  digitalWrite(ML_DIR, HIGH);
  analogWrite(MR_PWM, 20);
  analogWrite(ML_PWM, spd);
}

// ===== PIVOT =====
void pivotLeft(int spd) {
  digitalWrite(MR_DIR, HIGH);
  digitalWrite(ML_DIR, LOW);
  analogWrite(MR_PWM, spd);
  analogWrite(ML_PWM, spd);
}

void pivotRight(int spd) {
  digitalWrite(MR_DIR, LOW);
  digitalWrite(ML_DIR, HIGH);
  analogWrite(MR_PWM, spd);
  analogWrite(ML_PWM, spd);
}

void stopRobo() {
  analogWrite(MR_PWM, 0);
  analogWrite(ML_PWM, 0);
}