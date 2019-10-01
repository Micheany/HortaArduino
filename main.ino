
#include<LiquidCrystal.h> //adicionando a biblioteca do display
#define pino_sinal_analogico A0 //pinagem do arduino conectado com o sensor
#define Rele 13                  // pinagem do rele
int valor_analogico;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //pinagem do LCD
int a=0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(pino_sinal_analogico, INPUT);  //o pino do sensor recebe corrente
  pinMode(Rele,OUTPUT);                 // pino do rele é de saida de corrente
  digitalWrite(Rele,HIGH);
  lcd.begin(16,2);                      // inicializa o lcd de 16x2
  lcd.clear();
}

void loop()
{
  lcd.clear(); 
  //Le o valor do pino A0 do sensor
  
  valor_analogico = analogRead(pino_sinal_analogico); 
  digitalWrite(Rele,HIGH);
  
   //////LCD/////
   Serial.print("..");
   Serial.print(valor_analogico);
   Serial.println("..");
  a=map(valor_analogico,0,1024,100,0);     //porcentagem
  Serial.println(a);
  lcd.clear();                       //limpa o display
  lcd.setCursor(3, 0);               //coluna,linha (1=segunda linha)
  lcd.print("UMIDADE A: ");           //printa
  lcd.setCursor(3,1);                
  lcd.print(a);
  lcd.setCursor(5,1);
  lcd.print("%");
  delay(5000);   

//Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
   
  //Rolagem para a direita
  for (int posicao = 0; posicao < 6; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }
  
 ///// RELE /////
  
  //Solo umido, nao liga o rele
  if (valor_analogico >= 0 && valor_analogico < 600)
  {
  Serial.print("\no solo ja esta umido, nao ha necessidade de mais água-high\n");
  Serial.print(valor_analogico);
  digitalWrite(Rele,HIGH);
  }
  //Solo com umidade moderada, liga o rele por 2segundos
  if (valor_analogico >= 600 && valor_analogico < 800)
  {
    Serial.print("\numidade moderada, acionando o rele-low--high\n");
    Serial.print(valor_analogico);
    digitalWrite(Rele,LOW); //liga rele
    delay(5000);              //tempo ligado em milisegundos
    digitalWrite(Rele,HIGH); //desliga rele
    delay(200);   //tempo desligado em milisegundos
  }
  //solo seco, liga o rele por 5 segundos
  if (valor_analogico >= 800 && valor_analogico <= 1024)
  {
    Serial.print("\numidade baixa, acionando o rele--low--high\n");
    Serial.print(valor_analogico);
    digitalWrite(Rele,LOW);
    delay(5000);
    digitalWrite(Rele,HIGH);
    delay(200);
  }
}
