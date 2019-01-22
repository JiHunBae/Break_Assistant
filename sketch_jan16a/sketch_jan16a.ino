#define ad 20 // 알람 시작 거리
#define bd 10 // 브레이크 시작 거리

#include <Servo.h>
Servo myservo;

void alarmFunc(int); // 알람 모듈 함수
void servoFunc(int); // 브레이크 모듈 함수

int echoPin = 12; // 거리 센서 echo 핀 번호
int trigPin = 13; // 거리 센서 trig 핀 번호
int alarmPin = 11; // 알람 모듈 핀 번호

void setup() {
  Serial.begin(9600); // 통신 속도 초당 9600bit 설정
  myservo.attach(10); // 서보모터 핀 번호
  pinMode(echoPin, INPUT); // echoPin 입력
  pinMode(trigPin, OUTPUT); // trigPin 출력
  pinMode(alarmPin, OUTPUT); // alarmPin 출력
}

void loop() {
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // 초음파 시작
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // 초음파 종료

  unsigned long t = pulseIn(echoPin, HIGH); // echo 유지 시간 저장
  float d = ((float)(340 * t) / 10000) / 2; // HIGH 였을 때 시간을 이용해 거리 계산

  /*거리에 따른 센서 반응*/
  servoFunc(d); // 브레이크 모듈 함수
  alarmFunc(d); // 알람 모듈 함수
  
  Serial.print(d); // 거리 출력
  Serial.println("cm");
  delay(500);
}

void alarmFunc(int d){ // 알람 모듈 함수
  if(d <= ad){
    analogWrite (alarmPin, 30);
  }
  else{
    noTone(alarmPin);
  }
}

void servoFunc(int d){ // 브레이크 모듈 함수
  int i = 1;
  if(d <= bd){
    for(i = 1;i<=180;i++)
       myservo.write(i);
  }
  
  else {
    myservo.write(i);
  }
}
