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

};


LedControl::LedControl(int led, int state, unsigned long prev, long interv):ledPin(led), ledState(state), previousMillis(prev), interval(interv){}

void LedControl::getPinLogs(){
  String logging = "Pin " + String(this->ledPin) + " updated status to: " + String(this->ledState);
  Serial.println(logging);
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


void loop() {
 
  checkUpdate(L1);
  checkUpdate(L2);
  checkUpdate(L3);
  checkUpdate(L4);
  checkUpdate(L5);
}
