/*
 * GccApplication1.c
 *
 * Created: 4/04/2023 7:42:15 p. m.
 * Author : Edgar Alfonso Paez Barros
 * E-mail : paezbedgar@gmail.com
 
 Este proyecto contendrá el firmware para el control de un silla de ruedas electricas, el microcontrolador(uC) a usar será el AVR ATMEGA328P
 
 En este uC se usaran los siguientes pines, pero antes se indicará los dispositivos a usar:
		*Puerto H dual de 50A.
		*Regulador DC-DC LM2560.
		*Joystiick industrial analogico
		
	los pines de uC que se usaran seran:
	Como entrada analogica x : ADC0 En el puerto C
	Como entrada analógica y : ADC4 En el puerto C
	
	como salidas PWM se usaran:
	RPWMA:OCR0A
	RPWMB:OCR2A
	LPWMA:OCR0B
	LPWMB:OCR2B
	
	El ENABLE del canal A será el pin 1 del puerto C
	El Enable del canal B será el pin 5 del puerto C 
 */ 
					/* ESPACIO DE LLAMADO DE LIBRERIAS */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>


					/*		ESPACIO DE DECLARACIÓN DE VARIABLES */
volatile uint8_t derecho = 0;
volatile uint8_t valor_sensor_izquierdo = 0, valor_sensor_derecho = 0;


					/*		ESPACIO DE CREACION DE PROTOTIPO DE FUNCIONES		*/
ISR(ADC_vect);
void pins_configurations_init(void);
void ADC_init(void);
void pwm_0AB_2AB(uint8_t pwm_broad_A, uint8_t pwm_broad_B);
void PWM_OC0AB_init(void);
void PWM_OC2AB_init(void);
void adelante_A(int valor_pwm);
void adelante_B(int valor_pwm);
void atras_A(int valor_pwm);
void atras_B(int valor_pwm);


					/*		Espacio de definiciones								*/
#define RPWMA OCR0A
#define RPWMB OCR2A
#define LPWMA OCR0B
#define LPWMB OCR2B
#define EN_A 0b00000010
#define EN_B 0b00100000
#define F_CPU 800000UL



int main(void)
{
	pins_configurations_init();
	ADC_init();
	PWM_OC0AB_init();
	PWM_OC2AB_init();
	while (1)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
			adelante_A(valor_sensor_derecho);
			adelante_B(valor_sensor_izquierdo);
		}
		PORTC = 0x00F;
		_delay_ms(1000);   //hay que eliminar los delays. hay que terminar el firmware
		
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
			atras_A(valor_sensor_derecho);
			atras_B(valor_sensor_izquierdo);
		}
		
		_delay_ms(1000);
		
	}
}



ISR(ADC_vect)
{
	if (derecho){
		ADMUX = 0<<REFS1| 1<<REFS0| 1<<ADLAR| 0<<MUX3| 1<<MUX2| 0<<MUX1| 0<<MUX0;
		derecho = 0;
		valor_sensor_derecho = ADCH;
	}else{
		ADMUX = 0<<REFS1| 1<<REFS0| 1<<ADLAR| 0<<MUX3| 0<<MUX2| 0<<MUX1| 0<<MUX0;
		derecho = 1;
		valor_sensor_izquierdo = ADCH;
	}
	ADCSRA |= 1<<ADSC;
}

void pins_configurations_init(void){
	DIDR0 = 0xFF;			//Este registro desactiva las entradas digitales de todos los ADCs, con esto se ahorra energia.
	DDRC = 0b11101110;			//Se configura los pines 0 y 4 como entrada, el resto como salida
	PORTC = 0x00;		//Se configura la resistencia de pull-up; esto ahorra energia y protege las entradas del uC
	DDRD = 0xFF;			// se configura el puerto como salida
	DDRB = 0xFF;			//se configura el puerto como salida
}

void ADC_init(void){
	ADMUX = (0<<REFS1| 1<<REFS0| 1<<ADLAR| 0<<MUX3| 1<<MUX2| 0<<MUX1| 0<<MUX0); /* Se
	*configura inicialmente el puerto PC4 como entrada analogica
	*se configura como voltaje de referencia AVcc con capacitor externo
	*se realiza el ajuste de hacia la izquierda del registro de resultado del ADC*/
	
	ADCSRA |= (0<<ADATE |1<< ADIE| 1<<ADPS2|1<< ADPS1|1<< ADPS0);/*
	*Se deshabilita el auto-trigger
	*Se habilita la interrupciones del ADC
	*Se habilita el prescaler del ADC en el maximo */
	sei();/* Se habilitan las interrupciones globales del microcontrolador*/
	ADCSRA |= (1<<ADEN |1<<ADSC);/*
	*Se habilita el ADC, se enciende
	*Se inicia la conversion del ADC*/
	
}

void PWM_OC0AB_init(void){
	TCCR0A = 1<< COM0A1 | 0<< COM0A0 |1<< COM0B1| 0<<COM0B0 |1<<WGM01|1<< WGM00 ;
	TCCR0B =  0<<WGM02| 1<<CS02 |0<<CS01|0<< CS00;  //prescaler a 256
	OCR0A = 0;
	OCR0B = 0;
}

void PWM_OC2AB_init(void){
	TCCR2A = 1<< COM2A1 | 0<<COM2A0	|1<< COM2B1|0<< COM2B0 |1<< WGM21| 1<<WGM20;
	TCCR2B |= 0<<WGM22|1<< CS22|1<< CS21|0<< CS20;
	OCR2A = 0;
	OCR2B = 0;
}

void adelante_A(int valor_pwm){
	PORTC |= EN_A ;
	RPWMA = valor_pwm;
	LPWMA = 0xFF;	
}
void adelante_B(int valor_pwm){
	PORTC |= EN_B;
	RPWMB = valor_pwm;
	LPWMB = 0xFF;
}

void atras_A(int valor_pwm){
	PORTC |= EN_A;
	RPWMA = 0xFF;
	LPWMA = valor_pwm;
}

void atras_B(int valor_pwm){
	PORTC |= EN_B;
	RPWMB = 0xFF;
	LPWMB = valor_pwm;
}
