// C++ code
//
// 
const int IN1 = 9;  const int IN2 = 10; // موتور شمال
const int IN3 = 5;  const int IN4 = 6;  // موتور يمين

const int IR[] = {A0, A1, A2, A3, A4, A5};

// --- الإعدادات المتفق عليها ---
int speedLeft = 100;  
int speedRight = 75;  
int speedTurn = 110;    

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  for(int i=0; i<6; i++) pinMode(IR[i], INPUT);
}

void loop() {
  // قراءة الحساسات
  int s0 = digitalRead(IR[0]); int s1 = digitalRead(IR[1]);
  int s2 = digitalRead(IR[2]); int s3 = digitalRead(IR[3]);
  int s4 = digitalRead(IR[4]); int s5 = digitalRead(IR[5]);

  int active = 0; // القيمة اللي بيقرأها لما يشوف الخط

  // 1. حالة الـ 6 سينسورات (التوقف التام)
  if (s0 == active && s1 == active && s2 == active && s3 == active && s4 == active && s5 == active) {
    stopRobot();
  }
  
  // 2. أولوية اليمين: لو النص (s2, s3) مع اليمين (s4, s5) قارين -> يلف يمين
  else if ((s2 == active || s3 == active) && (s4 == active || s5 == active)) {
    turnRight();
  }

  // 3. أولوية الشمال: لو النص (s2, s3) مع الشمال (s0, s1) قارين -> يلف شمال
  else if ((s2 == active || s3 == active) && (s0 == active || s1 == active)) {
    turnLeft();
  }

  // 4. للأمام فقط: لو النص بس هو اللي قاري والاطراف لأ
  else if (s2 == active || s3 == active) {
    moveForward();
  }

  // 5. حالات الدوران المنفردة (لو لمس طرف واحد بس)
  else if (s4 == active || s5 == active) {
    turnRight();
  }
  else if (s0 == active || s1 == active) {
    turnLeft();
  }

  // 6. لو مفيش أي حاجة قارية (تاه)
  else {
    stopRobot();
  }
}

// --- الدوال التنفيذية ---
void moveForward() {
  digitalWrite(IN1, LOW); analogWrite(IN2, speedLeft); 
  digitalWrite(IN3, LOW); analogWrite(IN4, speedRight); 
}

void turnRight() {
  digitalWrite(IN1, LOW); analogWrite(IN2, speedTurn); 
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); 
}

void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); analogWrite(IN4, speedTurn); 
}

void stopRobot() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}