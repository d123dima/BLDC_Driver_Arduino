//----Зачем всё это?
//----Серега - вонючий хуй

//---CONFIG_END---
#define VT_1 15  //A1
#define VT_2 10  //D10
#define VT_3 17  //A3
#define VT_4 9   //D9
#define VT_5 19  //A3
#define VT_6 3   //D3


int pwm;
// float I_A_ADC;
// float I_B_ADC;
// float I_C_ADC;

int I_A_ADC;
int I_B_ADC;
int I_C_ADC;

void setup() {
  // Serial.begin(15200);  // Скорость работы монитор порта
  pinMode(4, INPUT);   // D4
  pinMode(5, INPUT);   // D5
  pinMode(6, INPUT);   // D6
  pinMode(12, INPUT);  //D12
  pinMode(18, INPUT);  //A4
  pinMode(A6, INPUT);  //A6
  //-------------Датчики тока----------
  pinMode(A0, INPUT);  //A0
  pinMode(A2, INPUT);  //A2
  pinMode(A7, INPUT);  //A7

  pinMode(VT_1, OUTPUT);  //A1 (1 транзистор)
  pinMode(VT_2, OUTPUT);  // D10 (2 транзистор)
  pinMode(VT_3, OUTPUT);  //A3 (3 транзистор)
  pinMode(VT_4, OUTPUT);  //D9 (4  транзистор)
  pinMode(VT_5, OUTPUT);  //A5 (5 транзистор)
  pinMode(VT_6, OUTPUT);  //D3 (6 транзистор)
  TCCR1A = 0b00000001;    //D9
  TCCR1B = 0b00001010;    //D10
  TCCR2B = 0b00000010;    // x8; D3
  TCCR2A = 0b00000011;    // fast pwm
}

void loop() {
  pwm = analogRead(A6);  // читаем с потенциометра, он в А6
  pwm = map(pwm, 0, 1023, 0, 255);
  pwm = constrain(pwm, 0, 255);
  
    boolean a = digitalRead(4);    //считываем DIP1
    boolean b = digitalRead(5);    //считываем DIP2
    boolean c = digitalRead(6);
    // Serial.println(pwm);
  // Serial.print(a);
  // Serial.print(b);
  // Serial.println(c);
  boolean GO = digitalRead(12);    //считываем D12
  boolean BACK = digitalRead(18);  //считываем A4
//------------опрос ДТ----------
//  I_A_ADC = analogRead(A0)/4;    //считываем ДТ1
//   I_A_ADC= (I_A_ADC/1024.0f*5.0f-2.5)*13.3f;
//  I_B_ADC = analogRead(A2);    //считываем ДТ2
//   I_B_ADC= (I_B_ADC/1024.0f*5.0f-2.5)*13.3f;
  // I_C_ADC = analogRead(A7);   //считываем ДТ3
//   I_C_ADC= (I_C_ADC/1024.0f*5.0f-2.5)*13.3f;
  //  Serial.print("I_A=");
  // Serial.print(I_A_ADC);
  // Serial.print("           I_B=");
  // Serial.print(I_B_ADC);
  // Serial.print("             I_C=");
  // Serial.println(I_C_ADC);
//   Serial.print("GO = ");
//   Serial.println(GO);
//   Serial.print("BACK = ");
//   Serial.println(BACK);

//-------------Опрос закончен---------
  if ((GO == 1 && BACK == 0 && pwm != 255)) {      // ПОЛОЖЕНИЕ ВПЕРЕД
                                   //первый случай вперёд
    if (a == 1 && b == 0 && c == 1) {
      digitalWrite(VT_5, LOW);
      analogWrite(VT_4, pwm);
      digitalWrite(VT_1, HIGH);
      digitalWrite(VT_3, HIGH);
      digitalWrite(VT_2, HIGH);
      digitalWrite(VT_6, HIGH);
    }
    //второй случай вперёд
    if (a == 1 && b == 0 && c == 0) {
      digitalWrite(VT_5, LOW);
      analogWrite(VT_2, pwm);
      digitalWrite(VT_1, HIGH);
      digitalWrite(VT_3, HIGH);
      digitalWrite(VT_4, HIGH);
      digitalWrite(VT_6, HIGH);
    }
    //третий случай вперёд
    if (a == 1 && b == 1 && c == 0) {
      digitalWrite(VT_3, LOW);
      analogWrite(VT_2, pwm);
      digitalWrite(VT_1, HIGH);
      digitalWrite(VT_6, HIGH);
      digitalWrite(VT_5, HIGH);
      digitalWrite(VT_4, HIGH);
    }
    // четвертый случай вперёд
    if (a == 0 && b == 1 && c == 0) {
      digitalWrite(VT_3, LOW);
      analogWrite(VT_6, pwm);
      digitalWrite(VT_4, HIGH);
      digitalWrite(VT_5, HIGH);
      digitalWrite(VT_2, HIGH);
      digitalWrite(VT_1, HIGH);
    }
    //пятый случай вперёд
    if (a == 0 && b == 1 && c == 1) {
      digitalWrite(VT_1, LOW);
      analogWrite(VT_6, pwm);
      digitalWrite(VT_3, HIGH);
      digitalWrite(VT_2, HIGH);
      digitalWrite(VT_5, HIGH);
      digitalWrite(VT_4, HIGH);
    }
    //шестой случай вперёд
    if (a == 0 && b == 0 && c == 1) {
      digitalWrite(VT_1, LOW);
      analogWrite(VT_4, pwm);
      digitalWrite(VT_2, HIGH);
      digitalWrite(VT_5, HIGH);
      digitalWrite(VT_3, HIGH);
      digitalWrite(VT_6, HIGH);
    }
  }

  if (BACK == 1 && GO == 0 && pwm != 255) {    // ПОЛОЖЕНИЕ НАЗАД
    //первый случай назад
    if (a == 1 && b == 0 && c == 1) {
      digitalWrite(VT_3, LOW);
      analogWrite(VT_6, pwm);
      digitalWrite(VT_2, HIGH);
      digitalWrite(VT_1, HIGH);
      digitalWrite(VT_4, HIGH);
      digitalWrite(VT_5, HIGH);
    }
    //второй случай назад
    if (a == 0 && b == 0 && c == 1) {
      digitalWrite(VT_3, LOW);
      analogWrite(VT_2, pwm);
      digitalWrite(VT_6, HIGH);
      digitalWrite(VT_4, HIGH);
      digitalWrite(VT_1, HIGH);
      digitalWrite(VT_5, HIGH);
    }
    //третий случай  назад
    if (a == 0 && b == 1 && c == 1) {
      digitalWrite(VT_5, LOW);
      analogWrite(VT_2, pwm);
      digitalWrite(VT_1, HIGH);
      digitalWrite(VT_4, HIGH);
      digitalWrite(VT_3, HIGH);
      digitalWrite(VT_6, HIGH);
    }
    // четвертый случай  назад
    if (a == 0 && b == 1 && c == 0) {
      digitalWrite(VT_5, LOW);
      analogWrite(VT_4, pwm);
      digitalWrite(VT_1, HIGH);
      digitalWrite(VT_3, HIGH);
      digitalWrite(VT_2, HIGH);
      digitalWrite(VT_6, HIGH);
    }
    //пятый случай  назад
    if (a == 1 && b == 1 && c == 0) {
      digitalWrite(VT_1, LOW);
      analogWrite(VT_4, pwm);
      digitalWrite(VT_2, HIGH);
      digitalWrite(VT_5, HIGH);
      digitalWrite(VT_3, HIGH);
      digitalWrite(VT_6, HIGH);
    }
    //шестой случай назад
    if (a == 1 && b == 0 && c == 0) {
      digitalWrite(VT_1, LOW);
      analogWrite(VT_6, pwm);
      digitalWrite(VT_2, HIGH);
      digitalWrite(VT_3, HIGH);
      digitalWrite(VT_5, HIGH);
      digitalWrite(VT_4, HIGH);
    }
  }
  if ((BACK == 0 && GO == 0) | pwm == 255) {
    digitalWrite(VT_1, HIGH);
    digitalWrite(VT_4, HIGH);
    digitalWrite(VT_2, HIGH);
    digitalWrite(VT_3, HIGH);
    digitalWrite(VT_5, HIGH);
    digitalWrite(VT_6, HIGH);
  }
}
