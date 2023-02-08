/* Author: Pantar Catalin (@Catalinos on github)

  This program counts up to 31 and lights up the LEDs in order to show the binary representation of that number

  It uses 7-3 pins with 7 being LSB and 3 being MSB

*/

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

// setting up the pins as outputs and also the serial monitor for printing
void setup() {
  Serial.begin(9600);
  pinMode(L1.ledPin, OUTPUT);
  pinMode(L2.ledPin, OUTPUT);
  pinMode(L3.ledPin, OUTPUT);
  pinMode(L4.ledPin, OUTPUT);
  pinMode(L5.ledPin, OUTPUT);

}


int length = 5;
int counter = 0;
int freq = 100;

// this function will reset the leds when the counter reaches the maximum value
void resetLEDS(LedControl *Led_Array){
  
  for(int i=0;i<length;i++){
    Led_Array[i].updateLedState(LOW);
  }

}

// this function helps us view the counted numbers in binary and decimal from the serial monitor
void print_toSerial(LedControl *Led_Array){

    for(int i=length-1;i>=0;i--){
    Serial.print(Led_Array[i].ledState);
    Serial.print(' ');
  }
  Serial.print(" ----> " + String(counter));
  Serial.println();

}

// function to set our led states HIGH/LOW
void updateLEDS_counter(LedControl *Led_Array){

    for(int i=0;i<length;i++){
    digitalWrite(Led_Array[i].ledPin,Led_Array[i].ledState);
  }
  print_toSerial(Led_Array);

}

// this is the main function
void countLED(){
  LedControl Led_Array[] = {L1, L2, L3, L4, L5};
  counter+=1;

  if(counter%32==0){
    counter = 0;
    resetLEDS(Led_Array);
  }

  for(int i=0;i<length;i++){
    int mask = 0x01 << i;
    Led_Array[i].ledState = (mask & counter) >> i;
  }

  updateLEDS_counter(Led_Array);
  
}

// looping function
void loop() {
  
  countLED();
  delay(freq);

}
