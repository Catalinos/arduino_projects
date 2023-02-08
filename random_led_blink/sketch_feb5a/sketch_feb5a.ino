// led control class

class LedControl{

  public:
    int ledPin;
    int ledState;
    unsigned long previousMillis;
    long interval;
    
    LedControl(): ledPin(7), ledState(LOW), previousMillis(0), interval(0){};
    LedControl(int led, int state, unsigned long prev, long interv);
    void getPinLogs(); // this will print to the serial monitor any led status change
    void updateLedState(int state){this->ledState = state;}
    void low_Activation(int state);

};


LedControl::LedControl(int led, int state, unsigned long prev, long interv):ledPin(led), ledState(state), previousMillis(prev), interval(interv){}

void LedControl::getPinLogs(){
  String logging = "Pin " + String(this->ledPin) + " updated status to: " + String(this->ledState);
  Serial.println(logging);
}

void LedControl::low_Activation(int state){
      if(state==0)
        this->ledState = HIGH;
      else
        this->ledState = LOW;
    }

LedControl L1(7,LOW,0,2000);
LedControl L2(6,LOW,0,1500);
LedControl L3(5,LOW,0,1000);
LedControl L4(4,LOW,0,500);
LedControl L5(3,LOW,0,100);


void setup() {
  Serial.begin(9600);
  pinMode(L1.ledPin, OUTPUT);
  pinMode(L2.ledPin, OUTPUT);
  pinMode(L3.ledPin, OUTPUT);
  pinMode(L4.ledPin, OUTPUT);
  pinMode(L5.ledPin, OUTPUT);

}


// led state change function
void checkUpdate(LedControl &L){

  unsigned long currentMillis = millis();
  if(currentMillis - L.previousMillis >= L.interval){
    L.previousMillis = currentMillis;
    if(L.ledState == HIGH)
      L.ledState = LOW;
    else
      L.ledState = HIGH;
    if(L.ledPin == 7)
      L.getPinLogs();
  }
  digitalWrite(L.ledPin, L.ledState);

}

// led count function
int length = 4;
int isOn[] = {0, 0, 0, 0, 0};
int counter = 0;

void resetLEDS(LedControl *Led_Array){
  for(int i=0;i<length;i++){
    Led_Array[i].updateLedState(LOW);
  }
}

void updateLEDS_counter(LedControl *Led_Array){
    for(int i=0;i<length;i++){
    digitalWrite(Led_Array[i].ledPin,Led_Array[i].ledState);
  }
}

void countLED(){
  LedControl Led_Array[] = {L1, L2, L3, L4, L5};
  counter+=1;
  if(counter%31==0){
    counter = 0;
    resetLEDS(Led_Array);
  }
  
  for(int i=0;counter>0;i++){
    Led_Array[i].low_Activation(counter%2);
  }

  Serial.println(counter);

  updateLEDS_counter(Led_Array);
  
}

void loop() {
  
  countLED();
  delay(1000);
  // checkUpdate(L1);
  // checkUpdate(L2);
  // checkUpdate(L3);
  // checkUpdate(L4);
  // checkUpdate(L5);
}
