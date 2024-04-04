#include <LiquidCrystal.h>
#include <string.h>

int buffer,val[13];
char input[16];
int on_off = 1;
char key[] = {'0','1','2','3','4','5','6','7','8','9'};
// char *A[] = {"A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","A10","A11","A12"}; // if it doesnt work then below

int A[] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12};

int lcd_power = 13;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 1);
  pinMode(lcd_power,OUTPUT);
}

void addkey(char n){
  input[buffer++] = n;
  input[buffer] = '\0';
}

void backspace(){
  if(buffer>0){
    buffer--;
  }
}

void printout(){
  lcd.setCursor(0,0);
  int i=0;
  while(i<buffer){
    lcd.print(input[i++]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(on_off == 1){
    digitalWrite(lcd_power,HIGH);
    printout();
  }
  else{
    digitalWrite(lcd_power,LOW);
  }
  
  for(int i=0;i<13;i++){
    val[i] = analogRead(A[i]);
    // Serial.print(val[i]);
    // Serial.print("\t");
    if(val[i] >= 570){
        if(i<10 && on_off==1){
          addkey(key[i]);
          }
        else if(i==11 && on_off==1){
          addkey(' ');
        }
        else if(i==10 && on_off==1){
          lcd.clear();
          backspace();

        }
      
      
      else if(i==12){
        on_off = 1 - on_off;
          lcd.clear();
          buffer=0;
          input[buffer]="\0";
      }
      while(val[i]>= 570){
        val[i] = analogRead(A[i]);
      }
    }

  }


}
