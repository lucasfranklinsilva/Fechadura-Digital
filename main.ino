#include <LiquidCrystal.h>

char keypad[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

char password[6] = {'1', '2', '3', '4', '5', '6'};  //Initial Password
char input_password[6];   //User Password
int mode = 1; //Mode 1 Check Passowrd, Mode 2 Change Password
int count = 0;  //Aux count variable

LiquidCrystal lcd(2, 7, 12, 24, 25, 26);

void setup()
{
  //Pinos ligados aos pinos 1, 2, 3 e 4 do teclado - Linhas
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  //Pinos ligados aos pinos 5, 6, 7 e 8 do teclado - Colunas
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(13, INPUT);
  
  Serial.begin(9600);
  Serial.println("Entre com a senha: ");
  Serial.println();
  lcd.begin(16, 2);

}
 
void loop()
{
  Serial.println(count);
 //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
   if(mode == 1) lcd.print("Senha");
   if(mode == 2) lcd.print("Senha Antiga");
   if(mode == 3) lcd.print("Nova Senha");
   if(count>=1){
   for(int j = 0; j<count; j++){
      lcd.setCursor(j, 1);
      lcd.print("*");
   }
    
   }
   
   getKey();
}

void getKey(){

   for (int ti = 3; ti<7; ti++)
    {
    //Alterna o estado dos pinos das linhas
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(ti, HIGH);
    
    //Verifica se alguma tecla da coluna 1 foi pressionada
    if (digitalRead(8) == HIGH)
    {
       count = count + 1;
       init_password(ti-2, 1);
       while(digitalRead(8) == HIGH){}
    }
 
    //Verifica se alguma tecla da coluna 2 foi pressionada    
    if (digitalRead(9) == HIGH)
    {
      count = count + 1;
      init_password(ti-2, 2);
      while(digitalRead(9) == HIGH){};
    }
    
    //Verifica se alguma tecla da coluna 3 foi pressionada
    if (digitalRead(10) == HIGH)
    {
      count = count + 1;
      init_password(ti-2, 3);
      while(digitalRead(10) == HIGH){}
    }
    
    //Verifica se alguma tecla da coluna 4 foi pressionada
    if (digitalRead(1 31) == HIGH)
    {
      count = count + 1;
      init_password(ti-2, 4);
      while(digitalRead(11) == HIGH){} 
    }
   }
   delay(10);
}

void init_password(int x, int y){
 
  if(count == 1 && keypad[x-1][y-1] == '*'){ 
      count = count - 1; 
      mode = 2; 
      Serial.println(" Change Passowrd "); 
    }

  if(mode == 1 || mode == 2) check_password(x, y);
  if(mode == 3) chanche_password(x,y); 
}

void check_password(int x, int y)
{
       int verify_password = 0;
       lcd.setCursor(count-1, 1);
       lcd.print(keypad[x-1][y-1]);
       Serial.print(keypad[x-1][y-1]);
       if(count<=6){
          input_password[count-1] = keypad[x-1][y-1];
       }
       if(count>=6){

        for(int i = 0; i<6; i++){
          if(password[i] != input_password[i]) verify_password = verify_password - 1;
        }
        
        if(verify_password == 0) {  
          Serial.println(" "); 
          Serial.println("Door Open"); 
          if(mode==1){
              lcd.clear();
              lcd.print("Aberto.");
              tone(13,1500);
              delay(500);
              noTone(13);
              delay(500);
              tone(13,1500);
              delay(500);
              noTone(13);
              delay(2000); 
          }
          count = 0;
          if(mode == 2) mode = 3;
         }
        else {  
          Serial.println(" "); 
          Serial.println("Wrong Password!"); 
          lcd.clear();
          lcd.print("Senha Incorreta.");
          count = 0; 
          delay(2000); 
          }
        }
        
       delay(10);
}

void chanche_password(int x, int y){
  
       Serial.print(keypad[x-1][y-1]);
       if(count<=6){
          lcd.setCursor(count-1, 1);
          lcd.print(keypad[x-1][y-1]);
          password[count-1] = keypad[x-1][y-1];
       }

       if(count>=6){
          count = 0;
          mode = 1;
          Serial.println("Done!");
       }

}

