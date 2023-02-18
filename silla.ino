//Pines de Canal A
#define EN_CA 8
#define RPWM_CA 11
#define LPWM_CA 10

//Pines Canal B
#define EN_CB 7
#define RPWM_CB 6
#define LPWM_CB 5

//Pines de Lectura de Joysctick
#define LEC_X A0
#define LEC_Y A1

//Estos valores corresponden a los valores de operación del joystick
#define MAX_X 921
#define MIN_X 100
#define MAX_Y 921
#define MIN_Y 100

#define CMAX_X 610
#define CMAX_Y 610
#define CMIN_X 490
#define CMIN_Y 490

//Aqui se calcula los valores de la pendiente para cada funcion, son 4 funciones a las cuales se les calcula la pendiente y el desfase
#define M_X_POS  (255/(CMAX_X - MAX_X))
#define M_X_NEG  (-255/(CMIN_X - MIN_X))
#define M_Y_POS  (255/(CMAX_Y - MAX_Y))
#define M_Y_NEG  (-255/(CMIN_Y - MIN_Y))

//Aqui se calcula el valor de los desfases de las funcones
#define THETA_
#define THETA_
#define THETA_
#define THETA_

void setup() {
  pinMode(EN_CA, OUTPUT);
  pinMode(RPWM_CA, OUTPUT);
  pinMode(LPWM_CA, OUTPUT);

  pinMode(EN_CB, OUTPUT);
  pinMode(RPWM_CB, OUTPUT);
  pinMode(LPWM_CB, OUTPUT);

  pinMode(LEC_X, INPUT);
  pinMode(LEC_Y, INPUT);

  //Al iniciar la Silla, debemos de arrancar con todo frenado Por seguridad, por ende, llamamos a la funcion frenar silla

  frenar_silla(EN_CA, RPWM_CA, LPWM_CA);  
  frenar_silla(EN_CB, RPWM_CB, LPWM_CB);
}

void loop() {
  // put your main code here, to run repeatedly:

}


// Funcion de frenado, El driver de control de motores tiene dos funciones de parado de motores.
// Esta funicones parará los motores y ademas los frenará por seguridad

void frenar_silla(int EN, int RPWM, int LPWM){
  digitalWrite(EN, HIGH);
  digitalWrite(RPWM,HIGH);
  digitalWrite(LPWM,HIGH);
}
 

//Esta funcion hace que los motores arranquen deacuerdo una intensidad que pasa como parametro hacia adelante
void adelante(int EN, int RPWM, int LPWM, int PWM){
  digitalWrite(EN, HIGH);
  digitalWrite(LPWM, HIGH);
  analogWrite(RPWM, PWM);
}

//Esta funcion hace que los motores arranquen deacuerdo una intensidad que pasa como parametro en reversa
void reversa(int EN, int RPWM, int LPWM, int PWM){
  digitalWrite(EN, HIGH);
  digitalWrite(RPWM, HIGH);
  analogWrite(LPWM, PWM);
}

//Estas funciones se encarga de calcular los PWM deacuerdo al cuadrante en el que se encuentra el joystick.
// Existen dos funciones lineales que describen la intensidad del pwm. hay que recordar que el PWM va desde
// 0 hasta 255, siendo 0 un PWM de 0% y 255 un PWM de 100%.
// Esta funcion maneja unas zonas muertas, en el centro, esta zona corresponde a los valores de lectura
// del sensor del Joystick cuando este se encuentra en reposo. Esta zona corresponde especificamente a los
// valores de 490 a 610, recordar que el ADC tiene 1024 niveles.

int pendiente(){

}

















