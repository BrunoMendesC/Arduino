int pot = 0;
boolean a = 0;
int pin[6] = {6,9,5,10,11,3};

void setup(){
  
  for(byte b = 0; b <6; b++){
  pinMode( pin[b], OUTPUT);
  }
  
  pinMode(2, INPUT_PULLUP);
}

void loop(){
    
      pot = map (analogRead(A0), 0, 1023, 100, 2000);
  
      if(digitalRead(2) == LOW){
      a = !a;
      delay(300);
      } 
  
    if( a == 1){
for(int x=0; x<6;x=x+2){
  digitalWrite(pin[x], HIGH);
  digitalWrite(pin[x+1], HIGH);
  analogWrite (pin[x-1],50);
  analogWrite (pin[x-2],50);
  digitalWrite(pin[x-3], LOW);
  digitalWrite(pin[x-4], LOW);
  pot = map (analogRead(A0), 0, 1023, 100, 2000);
  delay(pot);
}
for(int x=5; x>=0;x=x-2){
  analogWrite(pin[x-1],50);
  analogWrite(pin[x],50);
  digitalWrite(pin[x-2],HIGH);
  digitalWrite(pin[x-3],HIGH);
  digitalWrite(pin[x+2],LOW);
  digitalWrite(pin[x+1],LOW);
  pot = map (analogRead(A0), 0, 1023, 100, 2000);
  delay(pot);
  }
  digitalWrite(pin[0],LOW);
  digitalWrite(pin[1],LOW);
  pot = map (analogRead(A0), 0, 1023, 100, 2000);
  delay(pot);
    
    
    
}   
} 
