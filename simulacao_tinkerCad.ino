/*

		Autores: Brenda Xavier de Moura
				 Flora Silvério Alexandre
			     Luana Correa dos Santos
                 
      Torre CSX-21 de desinfecção de ambientes por meio de UV
  */

// include the library code:
#include <LiquidCrystal.h>

#include <IRremote.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int const PINO_RECEPTOR = 7;
IRrecv receptor(PINO_RECEPTOR);
decode_results valorSaida;

int LED_VERMELHO = 10;
int LED_VERDE = 9;

void setup() {
  
  Serial.begin(9600);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(6,INPUT);
  
  //Inicia o receptor
  receptor.enableIRIn();
  
 // lcd.begin(16, 2);
 // lcd.print("hello, world!");
}

void loop() {
  int sinalPir = digitalRead(6);
  
   if(sinalPir == 1){
    digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(LED_VERDE, LOW);
      lcd.begin(16, 2);
      lcd.print("Perigo - Parar");
      delay(1000);
      lcd.clear();
  }else{   
  lcd.clear();
  }
  
  if (receptor.decode(&valorSaida)) {
    
    // Recebe o próximo valor
    receptor.resume(); 
     
    
    if (valorSaida.value == 0xFD00FF){ //power
      
      //garantindo que todos os led fiquem apagados
      digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(LED_VERDE, LOW);
      
      lcd.begin(16, 2);
      lcd.print("CSX-21 Ligada");
      delay(500);
      lcd.clear();
      
      lcd.begin(16, 2);
      lcd.print("Aguardando Acao");
      delay(1000);
      lcd.clear();
      
      
    }
     else if(valorSaida.value == 0xFD08F7 ){ //btn 1 braco
      
      //liga led do braco e mantem torre desligada
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_VERDE, LOW);
      lcd.begin(16, 2); 
      lcd.print("Braco - Seguro");
      delay(1000);
      lcd.clear(); 
       
       //fungos, bacterias, virus até 1s para matar segundo a tabela de dosagem
      lcd.begin(16, 2);
      lcd.print("37 tipos matados");
      delay(1000);
      lcd.clear(); 
      
      //fungos, bacterias, virus até 2s para matar segundo a tabela de dosagem
      lcd.begin(16, 2);
      lcd.print("+8 tipos matados");
      delay(1000);
      lcd.clear(); 
      
      //fungos, bacterias, virus até 3s para matar segundo a tabela de dosagem
      lcd.begin(16, 2);
      lcd.print("+2 tipos matados");
      delay(1000);
      lcd.clear();
      
      //fungos, bacterias, virus até 5s para matar segundo a tabela de dosagem
      lcd.begin(16, 2);
      lcd.print("+2 tipos matados");
      delay(2000);
      lcd.clear(); 
       
      
      //fungos, bacterias, virus até 22s para matar segundo a tabela de dosagem
      lcd.begin(16, 2);
      lcd.print("Desinfectando");
      delay(8000);
      lcd.clear(); 
      lcd.print("59 tps tabela ok"); 
      
      lcd.clear();
      lcd.print("Finalizado"); 
      delay(1000);
      lcd.clear();
    }
    else if (valorSaida.value == 0xFD8877) { //btn 2 torre
      //liga torre e mantem braco desligado
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      lcd.begin(16, 2);
      lcd.print("Torre - Segura");
      delay(1000);
      lcd.clear();
       
    }else if (valorSaida.value == 0xFD48B7){ //btn 3 torre + braco
       
      //liga torre e mantem braco desligado
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, HIGH);
      lcd.begin(16, 2);
      lcd.print("Combo - Seguro");
      delay(1000);
      lcd.clear(); 
    
      
      
    }else if (valorSaida.value == 0xFD28D7){
      digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(LED_VERDE, LOW);
      lcd.clear();
      lcd.print("Perigo - Parar");
      delay(2000);
    }
  }
  delay(100);
  
  
}
 