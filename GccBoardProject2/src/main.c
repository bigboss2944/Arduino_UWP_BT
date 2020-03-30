/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define delay(ms)

#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>

unsigned int Ctemp;
unsigned int Ftemp;


void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void ){
	
	while ( !(UCSR0A & (1<<RXC0)) )
	;/* Get and return received data from buffer */
	return UDR0;
	}

void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	}
	
double GetTemp(void)
{
	ADMUX = (3 << REFS0) | (8 << MUX0); // 1.1V REF, channel#8 is temperature
	ADCSRA |= (1 << ADEN) | (6 << ADPS0);       // enable the ADC div64
	delay(20);                  // wait for voltages to become stable.
	ADCSRA |= (1 << ADSC);      // Start the ADC

	while (ADCSRA & (1 << ADSC));       // Detect end-of-conversion
	// The offset of 324.31 could be wrong. It is just an indication.
	// The returned temperature is in degrees Celcius.
	return (ADCW - 324.31) / 1.22;
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	USART_Init(MYUBRR);

	board_init();
	
	DDRB |= (1<<DDB5); //Configure le pin 5 du port B en sortie, le reste en entrée
	DDRB |= (1<<DDB4);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB2);
	
	unsigned char carac;
	double temp;
	//DDRB = 0x3A;
	
	while(1){
		
		
		carac=USART_Receive();
		USART_Transmit(carac);
		
		if(carac=='1')
		{
			PORTB=0x20;
			
			
			
		}
		else if(carac=='2'){
			PORTB=0x30;
			
			
			
		}
		else if(carac=='3'){
			PORTB=0x38;
			
			
			
		}
		else if(carac=='4'){
			PORTB=0x3C;
			
			
			
		}
		else if(carac=='0'){
			PORTB=0x00;
			
			
			
		}
	
		
			
		
	}

	
}
