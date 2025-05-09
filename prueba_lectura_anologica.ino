byte Tx[9];//8 bytes para canales análogos, 1 byte para los digitales
int InDigital[] = {4, 5, 6, 7};//Pines digitales a usar

void setup() {
  Serial.begin(9600,SERIAL_8E1);
 
 for(int i=0;i<=3;i++){
  pinMode(InDigital[i],INPUT);//Asignación de pines digitales
  }

  // put your setup code here, to run once:

}

void loop() {
//Lectura Canales Analógicos
for(int i=0;i<5;i++){
Tx[2*i]=analogRead(i);//Lectura y asignacion de primer byte de entrada análoga 2*i
Tx[2*i+1]=analogRead(i)>>8;//Lectura y asignacion de segundo byte de entrada análoga 2*i+1
}

//Lectura Digital Input
  for(int i=0;i<=3;i++){
  bitWrite(Tx[8], i, digitalRead(InDigital[i]));//Escritura en el Byte 8 de pines digitales, segun el vector InDigital  
  }

//Transmisión canales analógicos
for(int i=0;i<5;i++){
Serial.write(Tx[2*i+1]);
Serial.write(Tx[2*i]);//Escritura de en puerto serial de entradas análogas
}

Serial.write(Tx[8]);//Escritura de en puerto serial de entradas digitales

delay(700);
 

}