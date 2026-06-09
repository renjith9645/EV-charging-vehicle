int relay_1 = 2 ;
int relay_2 = 3 ;
int relay_3 = 4 ;
int relay_4 = 5 ;
int ir_1 = 8;
int ir_2 = 9;
int ir_3 = 10;
int ir_4 = 11;


unsigned long startTime1, startTime2, startTime3, startTime4;
bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
const long interval = 5000; 

void setup() {
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_3, INPUT);
  pinMode(ir_4, INPUT);
}


void loop() {

  if(digitalRead(ir_1) == 0 && flag1 == 0) {
    digitalWrite(relay_1, HIGH); 
    startTime1 = millis();      
    flag1 = 1;                  
  }
  if(flag1 == 1 && (millis() - startTime1 >= interval)) {
    digitalWrite(relay_1, LOW);
    flag1 = 0;                   
  }

  
  if(digitalRead(ir_2) == 0 && flag2 == 0) {
    digitalWrite(relay_2, HIGH);
    startTime2 = millis();
    flag2 = 1;
  }
  if(flag2 == 1 && (millis() - startTime2 >= interval)) {
    digitalWrite(relay_2, LOW);
    flag2 = 0;
  }
    if(digitalRead(ir_3) == 0 && flag3 == 0) {
    digitalWrite(relay_3, HIGH);
    startTime2 = millis();
    flag3 = 1;
  }
  if(flag3 == 1 && (millis() - startTime2 >= interval)) {
    digitalWrite(relay_3, LOW);
    flag3 = 0;
  }
    if(digitalRead(ir_4) == 0 && flag4 == 0) {
    digitalWrite(relay_4, HIGH);
    startTime2 = millis();
    flag4 = 1;
  }
  if(flag4 == 1 && (millis() - startTime2 >= interval)) {
    digitalWrite(relay_4, LOW);
    flag4 = 0;
  }
}