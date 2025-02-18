/*
 * botonesc.c
 *
 * Created: 1/02/2025 21:04:23
 *  Author: ferma
 */
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
uint8_t contador1;
uint8_t contador2;
uint8_t Ledmspdc1;
uint8_t Ledmspb1;
uint8_t prueba;
uint8_t ganador;
uint8_t ledscont2;
#include "botones.h"
void botones(uint8_t numboton){
	switch(ganador){   //Este switch me ayudará a pausar el juego a la hora que haya un ganador, por lo que al inicío entra al ciclo.
	case 0:
		switch(numboton){  
		case 1:
			if (contador1 <= 15) //SI apaché el botón y fué la bandera de numboton en 1, aumento mi contador 1.
			{
			contador1++;
			//Necesito led en PD7, menos significativo, por lo que solo asignaré al puerto D7 el valor menos significativo.
			Ledmspdc1 = contador1 & 0b00000001;
			PORTD = (Ledmspdc1<<PORTD7);
			//Necesito led en PB0, segundo menos significativo, por lo que haré un AND para obtener el segundo menos significativo.
			Ledmspb1 = ((contador1 & 0b00000010) >> 1);
			PORTB = (Ledmspb1<<PORTB0); //Distribuyo los valores del contador dependiendo de donde conecté cada led.
			prueba = ((contador1 & 0b00001100) >> 2);
			}
		break;
		case 2:
			if (contador2 <= 15)
			{
				contador2++;
				ledscont2 = ((contador2 & 0b00001111)); //Si numboton fué 2 y el contador2 es menor o igual a 15, entonces hago un and del contador para desplegarlo en el puerto.
			}
		break;
		} //Hago la distribución de leds en el puerto C debido a que PC0 Y PC1 son del primer contador y PC2-PC5 son del segundo contador.
		PORTC = ((prueba & 0b00000001)<<PORTC0)|(((prueba & 0b00000010)>>1)<<PORTC1)|((ledscont2 & 0b00000001)<<PORTC2)|(((ledscont2 & 0b00000010)>>1)<<PORTC3)|(((ledscont2 & 0b00000100)>>2)<<PORTC4)|(((ledscont2 & 0b00001000)>>3)<<PORTC5);
		if ((numboton == 1) & (contador1 == 15))  //Si ya se llegó a los 15 en el contador1 y se oprimió el botón, entonces pongo mi bandera de ganador en 1 para saber que J1 ganó.
		{
			//contador2 = 0;
			contador1 = 14;
			ganador = 1;
		}
		else if ((numboton == 2) & (contador2 == 15)) //Si ya se llegó a los 15 en el contador2 y se oprimió el botón, entonces pongo mi bandera de ganador en 2 para saber que J2 ganó.
		{
			//contador1 = 0;
			contador2 = 14;
			ganador = 2;
		}
	break;
	case 1: //Si mi variable ganador está en 1, despliego el 1 en el display y borro el contador 2.
		PORTD = 0b1111001;
		PORTC = (0<<PORTC2)|(0<<PORTC3)|(0<<PORTC4)|(0<<PORTC5);
		PORTC = (1<<PORTC0)|(1<<PORTC1);
		PORTD |= (1<<PORTD7);
		PORTB |= (1<<PORTB0);
		
	break;
	case 2: //Si mi variable ganador está en 2, despliego el 2 en el display y borro el contador 1.
		PORTD = 0b0100100;
		PORTC = (0<<PORTC0)|(0<<PORTC1);
		PORTD &= ~(1<<PORTD7);
		PORTB &= ~(1<<PORTB0);
		PORTC = (1<<PORTC2)|(1<<PORTC3)|(1<<PORTC4)|(1<<PORTC5);
		
	break;
	}
}