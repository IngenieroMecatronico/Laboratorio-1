/*
 * Prelaboratorio.c
 *
 * Created: 28/01/2025 22:22:16
 * Author : Juan Fernando Maldonado Menéndez - 22449
 * Catedrático: Katha Senn
 * Descripción: Programa de juego de carreras en contadores binarios.
 */ 


//*********************************************************************************************
//Librerias
//*********************************************************************************************

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include "botones/botones.h"

//*********************************************************************************************
//Prototipos de función
//*********************************************************************************************

 void initports(void); //Inicializo mis funciones a utilizar en el código.
 void botones(uint8_t numboton); //Esta función me ayudará a verificar que botón se oprimió.
 //uint8_t contador1;
 //uint8_t contador2;
 
 uint8_t bandera; //Esta variable me limitará las veces que se enciende el display de 7 segmentos.
 uint8_t juego;  //Esta bandera me permitirá poder iniciar el juego.
 uint8_t ciclo; //Esta bandera limitará nuevamente las veces que se enciende el display.
 uint8_t numboton; //Esta variable me dirá que botón se oprimió.
//*********************************************************************************************
//Variables globales
//*********************************************************************************************


//*********************************************************************************************
//Código principal
//*********************************************************************************************

int main(void)
{
	initports(); //Inicializo mi función de puertos.
	// Habilitamos las interrupciones globales.
	sei();
    while (1) 
    {
		//PORTD = 0b00000000;
		if (bandera == 1 && ciclo == 0 )  //Si se oprimió el botón de iniciar juego y no se ha repetido el ciclo, entonces ejecutar el display.
		{
				PORTD = 0b0010010;  //Número 5 según mi cableado en ánodo común.
				_delay_ms(1000);
				PORTD = 0b0011001; //Número 4 según mi cableado en ánodo común.
				_delay_ms(1000);
				PORTD = 0b0110000;//Número 3 según mi cableado en ánodo común.
				_delay_ms(1000);
				PORTD = 0b0100100;//Número 2 según mi cableado en ánodo común.
				_delay_ms(1000);
				PORTD = 0b1111001;//Número 1 según mi cableado en ánodo común.
				_delay_ms(1000);
				PORTD = 0b1000000;//Número 0 según mi cableado en ánodo común.
				_delay_ms(1000);
				juego = 1;
				ciclo = 1;
				
		}
			
		//initDisplay(contador);
    }
}

//*********************************************************************************************
//Subrutinas
//*********************************************************************************************
void initports(void){
	//Inicializamos los puertos de interés:
	UCSR0B = 0;
	//Todo el puerto D es salida debido a que todos los leds están alli.
	DDRD = 0xFF;
	//Apago todos los leds del display.
	PORTD = 0xFF;
	//Todo el puerto C como salida, debido a que est+an los leds allí.
	DDRC = 0xFF;
	//Apago todos los leds
	PORTC = 0;
	//PB0 es salida, lo de más es entrada.
	DDRB = 0;
	DDRB |= (1<<PORTB0);
	//Configurar los botones como downs, pero se conecta con pullup.
	PORTB &= ~(1<<PORTC1)|~(1<<PORTC2)|~(1<<PORTC3);
	//Vamos a habilitar la interrupción de los puertos B.
	PCICR |= (1<<PCIE0);
	//Habilitamos la máscara.
	PCMSK0 |= (1<<PCINT1)|(1<<PCINT2)|(1<<PCINT3);
	}
//*********************************************************************************************
//ISR
//*********************************************************************************************
ISR(PCINT0_vect){
	if (!(PINB & (1<<PORTB1)))   //Si se detecta un cambio en PINB y fué en el puerto PB1, encender la bandera para ejecutar el display.
	{
		
		//contador++;
		bandera = 1;
	}
	if (!(PINB & (1<<PORTB2))) //Si se detecta cambio en PINB y fué Puerto PB2, preguntar si ya se ejecutó el ciclo del display.
	{
		if (juego == 1) //SI ya se ejecutó el ciclo del display, nombrar la variable numboton para saber que botón se apachó.
		{
		numboton = 1;
		botones(numboton);
		}
	}
	if (!(PINB & (1<<PORTB3))) //Si se detecta cambio en PINB y fué Puerto PB2¿3, preguntar si ya se ejecutó el ciclo del display.
	{
		if (juego == 1) //SI ya se ejecutó el ciclo del display, nombrar la variable numboton para saber que botón se apachó.
		{
			numboton = 2;
			botones(numboton);
		}
	}
}
