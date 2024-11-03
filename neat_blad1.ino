#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>
#define led_vermelha 4
#define led_verde 5
#define botao_entrada 9
#define botao_saida 8
int carros = 0;
int sensorState = 0;
Adafruit_LiquidCrystal lcd_1(0);
Servo entrada;
Servo saida;
bool alteracoes=true;
int pos_entrada = 90;
int pos_saida = 90;

void setup()
{
    lcd_1.begin(16, 2);
    pinMode(led_vermelha, OUTPUT);
    pinMode(led_verde, OUTPUT);
    pinMode(botao_saida, INPUT_PULLUP);
	pinMode(botao_entrada, INPUT_PULLUP);
  	lcd_1.setBacklight(0);
  	entrada.attach(3);
  	saida.attach(6);
    entrada.write(pos_entrada);
  	saida.write(pos_saida);
  	
}

void loop()
{
  	bool estado_botao_entrada = digitalRead(botao_entrada);
  	bool estado_botao_saida = digitalRead(botao_saida);
  	if (alteracoes == true) {
  		lcd_1.setBacklight(1);
  		lcd_1.setCursor(0, 0);
    	lcd_1.print(" Estacionamento ");
    	lcd_1.setCursor(0, 1);
    	lcd_1.print("    Bom  Dia    ");
    	alteracoes=false;
  	}

  	if (estado_botao_entrada == LOW){
    	while(digitalRead(botao_entrada) == LOW){}
      	if (carros<5){
        	pos_entrada=180;
      		entrada.write(pos_entrada);
      		lcd_1.setBacklight(1);
      		lcd_1.setCursor(0, 1);
        	lcd_1.print("   Bem - vindo   ");
          	for(int i=0;i<5;i++){
             	delay(500);
  	  			tone(2,2000);
  	  			delay(200);
  	  			noTone(2);
            } 
        	delay(1000);
        	pos_entrada=90;
      		entrada.write(pos_entrada);
        	carros++;
        } else {
          	lcd_1.setBacklight(1);
      		lcd_1.setCursor(0, 0);
        	lcd_1.print(" Estacionamento ");
          	lcd_1.setCursor(0, 1);
          	lcd_1.print("      cheio     ");
        	tone(2,100);
  	  		delay(100);
  	  		noTone(2);
        	delay(3500);
        }
    	alteracoes=true;
      	
  	}
  	if (estado_botao_saida == LOW){
    	while(digitalRead(botao_saida) == LOW){}
      	if (carros>0){
        	pos_saida=180;
      		saida.write(pos_saida);
      		lcd_1.setBacklight(1);
      		lcd_1.setCursor(0, 1);
        	lcd_1.print("   Boa  viagem   ");
          	for(int i=0;i<5;i++){
             	delay(500);
  	  			tone(2,2000);
  	  			delay(200);
  	  			noTone(2);
            } 
        	delay(1000);
        	pos_saida=90;
      		saida.write(pos_saida);
        	carros--;
        } else {
          	lcd_1.setBacklight(1);
      		lcd_1.setCursor(0, 0);
        	lcd_1.print(" Estacionamento ");
          	lcd_1.setCursor(0, 1);
          	lcd_1.print("      vazio     ");
  	  		tone(2,100);
  	  		delay(200);
  	  		noTone(2);
        	delay(3500);
        }
    	alteracoes=true;
      	
  	}
    delay(10);
  	if (carros<5){
    	digitalWrite(led_vermelha, LOW);
        digitalWrite(led_verde, HIGH);
    } else {
      	digitalWrite(led_vermelha, HIGH);
        digitalWrite(led_verde, LOW);
    }
}