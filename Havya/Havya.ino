#include <LiquidCrystal.h>
LiquidCrystal lcd(A1, A0, 13, 12, 11, 10);
//button config
#define bir  7
#define iki  8
#define uc   5
#define dort 6
#define pwm  9
#define adc A2
byte customChar[8] = {
  0b01000,
  0b10100,
  0b01000,
  0b00011,
  0b00100,
  0b00100,
  0b00011,
  0b00000
};
void setup() {
  pinMode(bir,      INPUT_PULLUP);
  pinMode(iki,      INPUT_PULLUP);
  pinMode(uc,       INPUT_PULLUP);
  pinMode(dort,     INPUT_PULLUP);
  pinMode(pwm,      OUTPUT);
  digitalWrite(pwm, LOW);
  pinMode(adc,      INPUT);
  analogReference(DEFAULT); 
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ARDUINO GELSTRME");
  lcd.setCursor(0, 1);
  lcd.print("    PLATFORMU   ");
  delay(1000);
  lcd.clear();
}
int  analog = 0;
int  set    = 240, sett = 0;
bool sil    = true;
void loop() {
  analog = 0;
  for ( int i = 0; i < 25; i++ ) {
    analog += analogRead(adc);
    delay(5);
  }
  analog = analog / 25;
  analog = map(analog, 0, 720, 0, 450);

  if ( !digitalRead(uc) ) {
    set = set + 8;
    if ( set > 720 ) set = 720;
  }
  if ( !digitalRead(iki) ) {
    set = set - 8;
    if ( set < 240 ) set = 240;
  }
  if ( !digitalRead(bir) ) set = 240;
  if ( !digitalRead(dort) ) set = 560;
  sett = map(set, 0, 720, 0, 450);

  if ( analog > 465 ) {
    lcd.setCursor(0, 0);
    lcd.print("R:");
    lcd.print("ERR");
    sil = true;
  } else {
    if ( sil ) {
      sil = false;
      lcd.setCursor(0, 0);
      lcd.print("       ");
    }
    lcd.setCursor(0, 0);
    lcd.print("R:");
    lcd.print(analog);
    lcd.write(byte(0));
  }
  lcd.setCursor(10, 0);
  lcd.print("S:");
  lcd.print(sett);
  lcd.write(byte(0));

  lcd.setCursor(0, 1);
  lcd.print("150");

  lcd.setCursor(5, 1);
  lcd.print("-");

  lcd.setCursor(10, 1);
  lcd.print("+");

  lcd.setCursor(13, 1);
  lcd.print("350");

  if ( analog < sett ) digitalWrite(pwm, HIGH);
  if ( analog > sett ) digitalWrite(pwm, LOW);

}

