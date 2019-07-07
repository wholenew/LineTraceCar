//大会午後用
//pwmを5v0vに変更

#include <Servo.h>

#define R_PWM 6
#define R_IN 12
#define L_PWM 5
#define L_IN 13
#define servoPin 10
int pre0 = 0;
int pre1 = 0;
int pre2 = 0;
int pre3 = 0;
int pre5 = 0;
int timeFlag = 0;

int r_pwm = 250;
int l_pwm = 250;

int servoValue = 0;
Servo servo;


int onetimeFlag = 0;

int lineTime = 0;
int sensor0 = 0;//一番右
int sensor1 = 0;//右
int sensor2 = 0;//左
int sensor3 = 0;//一番左
int sensor5 = 0;//中央

int interSectionFlag = 0;
int interSectionTime = 0;

int rCurbCount = 0;
int lCurbCount = 0;

int lCurbFlag = 0;
int lCurbTime = 0;

int sensorFlag1 = 0;
int sensorFlag2 = 0;

int centerTime = 0;
int centerFlag1 = 0;
int centerFlag2 = 0;



int whiteThreshold = 500;
int blackThreshold = 700; //黒と判断するライン　交差点で使う
float white1 = 40;
float white2 = 30;
float black = 830; //センサーは黒を踏んだ時に800-830くらいになるようにしておく


int currentSensor = 10;
int course = 1;
int sensorFlag = 0;

int dif = 0;
int dif2 = 0;

int startTimeCount = 0;
int ontime = 1;

void setup() {
  Serial.begin(19200);
  pinMode(R_IN, OUTPUT);
  pinMode(L_IN, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);

  servo.attach(servoPin);
  servo.write(29);

  delay(5000);

}

void loop() {



    //コメントで消さないように注意********************************
    sensor0 = digitalRead(2);//一番右
    sensor1 = analogRead(1);//右
    sensor2 = analogRead(2);//左
    sensor3 = digitalRead(8);//一番左
    sensor5 = digitalRead(4);//中央
    //*************************************************************


    /*
      while(1){
      //直線テスト
          servo.write(28);//直進
          digitalWrite(L_IN,LOW);
          analogWrite(L_PWM,250);
          digitalWrite(R_IN,LOW);
          analogWrite(R_PWM,250);
      }
    */
    /*
      while(1){//右2中央28左53
      servo.write(2);//右
      delay(5000);

      servo.write(28);//直進
      delay(5000);

      servo.write(53);//左
      delay(5000);
      }
    */







/*


    Serial.print("s0:");
    Serial.print(sensor0);
    Serial.print("     s1 :");
    Serial.print(sensor1);
    Serial.print("     s5 :");
    Serial.print(sensor5);
    Serial.print("     s2 :");
    Serial.print(sensor2);
    Serial.print("     s3 :");
    Serial.print(sensor3);
    Serial.println(":");
    delay(1000);
    servo.write(28);//center

  }

  */
  /*

    //ロケットダッシュ
    /*
    if(sensor1>=sensor2&&sensor0==0&&sensor3==0){
      if(centerFlag1==0){
        centerTime=millis();
      }
      centerFlag1=1;
      centerFlag2=0;
    }else if(sensor2>=sensor1&&sensor0==0&&sensor3==0){
      if(centerFlag2==0){
        centerTime=millis();
      }
      centerFlag1=0;
      centerFlag2=1;
    }else if(sensor1>=sensor2&&sensor0==0&&sensor3==0){
      centerFlag1=1;
      centerFlag2=0;
    }else if(sensor2>=sensor1&&sensor0==0&&sensor3==0){
      centerFlag1=0;
      centerFlag2=1;
    }else{
      centerTime=0;
      centerFlag1=0;
      centerFlag2=0;
    }

  */
  
  


  if (sensor0 == 1 || sensor1 > blackThreshold || sensor2 > blackThreshold || sensor3 == 1) {
    sensorFlag1 = 0;
    sensorFlag2 = 0;
  }

  currentSensor = 11;
  if (sensor0 == 1) {
    currentSensor = 1;
    sensorFlag1 = 1;
    sensorFlag2 = 0;
  } else if (sensor3 == 1) {
    currentSensor = 6;
    sensorFlag1 = 0;
    sensorFlag2 = 1;
  } else if (sensor1 >= sensor2) {
    currentSensor = 2;
  } else if (sensor2 >= sensor1) {
    currentSensor = 5;
  }


  if (sensorFlag1 == 1) {
    currentSensor = 1;
  }
  if (sensorFlag2 == 1) {
    currentSensor = 6;
  }

  //交差点か直線で全白の場合
  if (sensorFlag1 != 1 && sensorFlag2 != 1 && sensor0 == 0 && sensor1 < whiteThreshold && sensor2 < whiteThreshold && sensor3 == 0 && interSectionFlag == 0 && sensor5 == 0) {
    interSectionTime = millis();
    interSectionFlag = 1;
    currentSensor = 10;
  } else if (sensorFlag1 != 1 && sensorFlag2 != 1 && sensor0 == 0 && sensor1 < whiteThreshold && sensor2 < whiteThreshold && sensor3 == 0 && interSectionFlag == 1 && sensor5 == 0) {
    if (millis() - interSectionTime > 50) {
      interSectionTime = 0;
      interSectionFlag = 0;
      currentSensor = 11; //交差点対策currentSensor11にする
    } else {
      currentSensor = 10;
    }
  } else {
    interSectionTime = 0;
    interSectionFlag = 0;
  }

  if (currentSensor == 3) {
    currentSensor = 2;
  } else if (currentSensor == 4) {
    currentSensor = 5;
  }





  if(sensor0==1){
    pre0=1;
  }
  if(sensor1 > blackThreshold){
    pre1=1;
  }
  if(sensor2 > blackThreshold){
    pre2=1;
  }
  if(sensor3==1){
    pre3=1;
  }
  if(sensor5==1){
    pre5=1;
  }

  if (timeFlag == 0) {
    timeFlag = 1;
    lineTime = millis();
  } else if (timeFlag == 1 && millis() - lineTime > 300) {
    timeFlag = 0;
    if(pre0==1&&pre1==1&&pre2==1&&pre3==1&&pre5==1){
         if(sensor0==1){
         currentSensor=12;
         }
        if(sensor1 > blackThreshold){
        currentSensor=12;
         }
         if(sensor2 > blackThreshold){
           currentSensor=15;
         }
        if(sensor3==1){
          currentSensor=15;
         }
        if(sensor5==1){
          currentSensor=10;
        }
    }
    pre0=0;
    pre1=0;
    pre2=0;
    pre3=0;
    pre5=0;
    
    
  }
  

  /*

  if (timeFlag == 0) {
    timeFlag = 1;
    lineTime = millis();
    pre1 = 0;
    pre6 = 0;
  } else if (timeFlag == 1 && millis() - lineTime > 250) {
    timeFlag = 0;
    if (pre1 > 2 && pre6 > 2) {
      if (currentSensor == 1) {
        currentSensor = 13;
      } else if (currentSensor == 6) {
        currentSensor = 16;
      }
    }
    /*else if(pre1>0&&pre6>0){
      if(){
        currentSensor=12;
      }else if(currentSensor==6){
       currentSensor=15;
      }
      }
    */

    /*
    pre1 = 0;
    pre6 = 0;

  } else {
    switch (currentSensor) {
      case 1: pre1++;
      //case 2: pre2++;
      //case 5: pre5++;
      case 6: pre6++;
        //case 11: pre11++;
    }
  }


*/

  nomal();
}


void nomal() {

  switch (currentSensor) {
    case 1://右へカーブ
      servoValue = 5; //右2中央28左53
      l_pwm = 200;
      r_pwm = 125; //小さいほど強くなる

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      //digitalWrite(R_IN,LOW);
      //analogWrite(R_PWM,r_pwm);

      //右空転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,LOW);

      //右後転
      //digitalWrite(R_IN,HIGH);
      //digitalWrite(R_PWM,LOW);
      //digitalWrite(R_IN, HIGH);
      //analogWrite(R_PWM, r_pwm);

      //右停止
      digitalWrite(R_IN, HIGH);
      digitalWrite(R_PWM, HIGH);

      //サーボ
      servo.write(servoValue);

      break;

    case 2://右寄りに進む
      servoValue = 23; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);

      break;

    case 5://左寄りに進む
      servoValue = 33; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);

      break;

    case 6://左へカーブ
      servoValue = 53; ////右2中央28左53
      l_pwm = 125; //小さいほど強くなる
      r_pwm = 200;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      //digitalWrite(L_IN,LOW);
      //analogWrite(L_PWM,l_pwm);

      //左空転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,LOW);

      //左後転
      //digitalWrite(L_IN,HIGH);
      //digitalWrite(L_PWM,LOW);
      //digitalWrite(L_IN,HIGH);
      //analogWrite(L_PWM,l_pwm);

      //左ブレーキ
      digitalWrite(L_IN, HIGH);
      digitalWrite(L_PWM, HIGH);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);

      break;

     case 10://直進
       servoValue = 28; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);


      break;



     case 11://交差点
      servoValue = 28; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);
  
      delay(100);

      break;

    case 12://右寄りに進む
      servoValue = 23; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);
      delay(50);
      break;

    case 13://右寄りに進む
      servoValue = 32; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);
      delay(100);
      break;


    case 15://左寄りに進む
      servoValue = 33; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);
      delay(50);
      break;

    case 16://左寄りに進む
      servoValue = 23; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);
      delay(100);
      break;
        
    default:
      servoValue = 28; //右2中央28左53
      l_pwm = 220;
      r_pwm = 220;

      //左正転
      //digitalWrite(L_IN,LOW);
      //digitalWrite(L_PWM,HIGH);
      digitalWrite(L_IN, LOW);
      analogWrite(L_PWM, l_pwm);

      //右正転
      //digitalWrite(R_IN,LOW);
      //digitalWrite(R_PWM,HIGH);
      digitalWrite(R_IN, LOW);
      analogWrite(R_PWM, r_pwm);

      //サーボ
      servo.write(servoValue);

      break;
  }

  switch (currentSensor) {
    case 1: Serial.println("右端:");
      break;
    case 2: Serial.println("右:");
      break;
    case 3: Serial.println("センター右:");
      break;
    case 4: Serial.println("センター左:");
      break;
    case 5: Serial.println("左:");
      break;
    case 6: Serial.println("左端:");
      break;
    case 10: Serial.println("直進:");
      break;
    case 11: Serial.println("交差点:");
      break;
    default:
    Serial.println(currentSensor); 
    Serial.println("default:");
      break;
  }

  /*
  Serial.print(currentSensor);
  Serial.print("     s1 :");
  Serial.print(sensor1);
  Serial.print("     s2 :");
  Serial.println(sensor2);
*/
  delay(1);
}


// ブレーキ
void brake() {
  digitalWrite(L_IN, HIGH);
  digitalWrite(L_PWM, HIGH);
  digitalWrite(R_IN, HIGH);
  digitalWrite(R_PWM, HIGH);

}


