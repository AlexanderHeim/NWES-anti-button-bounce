class LED{

private:
  int led;
  int anzahl;
  int intervall = 0;
  int counter=0;
  long int letzteZeit=0;
  bool blinkForEver=false;
public:   
  LED(int a){
    pinMode(a, OUTPUT);
    this->led=a;
  }

  void aus(){
    digitalWrite(led, LOW);
    resetLED();
  }

  void ein(){
    digitalWrite(led, HIGH);
    resetLED();
  }

  void resetLED(){
    blinkForEver = false;
    intervall=0;
    counter=0;
  }

  void blinken(int i, int u){
    counter=0;
    intervall=u;
    anzahl=i;
  }

  void blinken(int i){
    intervall=i;
    blinkForEver=true;
  }

  void check(){
    if(intervall == 0) return;
    if(counter<anzahl*2 || blinkForEver){
     if(millis()>=letzteZeit+intervall){
       digitalWrite(led, !digitalRead(led));
       counter++;
       letzteZeit=millis();
     }
    }
  }
};

class CButton{

  private:
    bool rising = false;
    bool falling = false;
    bool pressed = false;
    int pin;
    long int prellZeit=50;

  public:

    CButton(int pin_, long int prellZeit_){
      this->pin = pin_;
      pinMode(pin_, INPUT);
      this->prellZeit=prellZeit_;
    }
    
    boolean ispressed(){
      return pressed;
    }

    boolean isRising(){
      return rising;
    }

    boolean isFalling(){
      return falling;
    }
    
    void check(){
      static bool oldState=false;
      bool currentState;
      static long int risingTime=0;
      static long int fallingTime=0;
      static int oldPressed=false;
      
      currentState = digitalRead(pin);
      if(!oldState && currentState){
        risingTime = millis();
      }
      if((millis() >= risingTime + prellZeit)&&currentState)
      {
        pressed = currentState;
      }
      if(oldState && !currentState){
        fallingTime = millis();
      }
      if((millis() >= fallingTime + prellZeit)&&!currentState)
      {
        pressed = currentState;
      }
      oldState = currentState;
      
      rising = pressed && !oldPressed;
      falling = !pressed && oldPressed;
      oldPressed=pressed;
    }  
};

LED led1(5);
LED led2(10);
LED led3(13);
CButton but1(2, 500);

void setup() {
  Serial.begin(9600);
  led1.blinken(2000);
  led2.blinken(1000);
}


void loop() {
  static int z=0;
  static int k=0;
  led1.check();
  led2.check();
  led3.check();
  but1.check();
  if(but1.isRising()){
    led3.blinken(500);
  }
  if(but1.isRising()) z++;
  Serial.print(z);
  Serial.print(" | ");
  if(but1.isFalling()) k++;
  Serial.println(k);
}
