/*
* file: pin.h
*
* Atmel mega88/168/328 DIP  
* digital read/write Library for use in AVR Studio
*
* Created: 12/25/2012 00:59:20
* muchiri john
*
**/ 


#ifndef PIN_H_
#define PIN_H_

#include <avr/io.h>
#include <inttypes.h>



#ifdef __cplusplus
	extern "C"{
#endif


/************************************************************************
* structure to hold registers and bit number.                                                                      
************************************************************************/
struct reg_bit{
	volatile uint8_t* DDRx;
	volatile uint8_t* PORTx;
	volatile uint8_t* PINx;
	uint8_t bit; 
};

/************************************************************************
* enumeration to hold bit set/reset values or write mode. 
************************************************************************/
enum{ 
	LOW, HIGH, INPUT=0, OUTPUT
};

/************************************************************************
* enumeration to hold warefab dev board port registers.
************************************************************************/
enum{
	D0, D1, D2, D3, D4, D5, D6, D7,
	B0, B1, B2, B3, B4, B5, B6, B7,
	C0, C1, C2, C3, C4, C5, C6
};
/************************************************************************
* port registers and bit number.
* DDRx - data direction register.
* PORTx - write register.
* PINx - read register.       
************************************************************************/
static const struct reg_bit pins_def[]  = {
		//portd
	{ &DDRD, &PORTD, &PIND, PIND0 }, //30
	{ &DDRD, &PORTD, &PIND, PIND1 }, //31
	{ &DDRD, &PORTD, &PIND, PIND2 }, //32
	{ &DDRD, &PORTD, &PIND, PIND3 }, //1
	{ &DDRD, &PORTD, &PIND, PIND4 }, //2
	{ &DDRD, &PORTD, &PIND, PIND5 }, //9
	{ &DDRD, &PORTD, &PIND, PIND6 }, //10
	{ &DDRD, &PORTD, &PIND, PIND7 }, //11
		//portb
	{ &DDRB, &PORTB, &PINB, PINB0 }, //12
	{ &DDRB, &PORTB, &PINB, PINB1 }, //13
	{ &DDRB, &PORTB, &PINB, PINB2 }, //14
	{ &DDRB, &PORTB, &PINB, PINB3 }, //15
	{ &DDRB, &PORTB, &PINB, PINB4 }, //16
	{ &DDRB, &PORTB, &PINB, PINB5 }, //17
	{ &DDRB, &PORTB, &PINB, PINB6 }, //7
	{ &DDRB, &PORTB, &PINB, PINB7 }, //8
		//portc
	{ &DDRC, &PORTC, &PINC, PINC0 }, //23
	{ &DDRC, &PORTC, &PINC, PINC1 }, //24
	{ &DDRC, &PORTC, &PINC, PINC2 }, //25
	{ &DDRC, &PORTC, &PINC, PINC3 }, //26
	{ &DDRC, &PORTC, &PINC, PINC4 }, //27
	{ &DDRC, &PORTC, &PINC, PINC5 }, //28
	{ &DDRC, &PORTC, &PINC, PINC6 }, //29
};


/************************************************************************
* declare number of physical pins
************************************************************************/
static const uint8_t pins = C6 + 1;

/************************************************************************
* check port pin direction.
* pin - physical pin number on the AVR.                                             
* e.g pinStatus(6);
      checks the status of PORTB5 - B5 whether an input or output. 
************************************************************************/
static inline uint8_t pinStatus(uint8_t pin) {
	if (pin < pins) {
		return (*pins_def[pin].DDRx >> pins_def[pin].bit) & 1;
	} else { return 0;  }
}		

/************************************************************************
* sets i/o direction of a port pin.
* pin - physical pin on the AVR.
* mode - set i/o mode of port bit, 1/0, OUTPUT/INPUT.
* e.g pinSet(6, 1); 
      sets PORTB5 - B5  as output.                                                                      
************************************************************************/
static inline void pinSet(uint8_t pin, uint8_t mode) {
	if (pin < pins) {
		if (mode) {
			*pins_def[pin].DDRx |=  _BV(pins_def[pin].bit);
		} else {
			*pins_def[pin].DDRx &= ~ _BV(pins_def[pin].bit);
		}
	} else {}
}

/************************************************************************
* read bit.
* pin - physical pin number on the AVR.
* e.g pinRead(6);
      reads the bit value of PORTB5 bit.                                                                    
************************************************************************/
static inline uint8_t pinRead(uint8_t pin) {
	if (pin < pins) {
		return (*pins_def[pin].PINx >> pins_def[pin].bit) & 1;
	} else { return 0; }
}

/************************************************************************
* set/reset bit.
* pin - physical pin number on the AVR.
* Value - set/ reset value , 0/1, HIGH/LOW.
* e.g pinWrite(6, 1); 
      sets the bit of PORTB5 - B5 .                                                                 
************************************************************************/
static inline void pinWrite(uint8_t pin, uint8_t value) {
	if (pin < pins) {
		if (value) {
			*pins_def[pin].PORTx |= _BV(pins_def[pin].bit);
		} else {
			*pins_def[pin].PORTx &= ~ _BV(pins_def[pin].bit);
		}
	}
}
/************************************************************************
* toggle bit.
* pin - physical pin number on the AVR.                              
* e.g pinToggle(6, 1);
      toggles bit 5 of PORTB - B5. 
************************************************************************/
static inline uint8_t pinToggle(uint8_t pin) {
	if (pin < pins) {
		return *pins_def[pin].PORTx ^= _BV(pins_def[pin].bit);
	} else { return 0; }
}
/************************************************************************
* set i/o mode of many pins at once
* *p - pointer to an array of pins.
* mode - either OUTPUT/INPUT, 1/0.
* uint8_t ar[3] = {4, 5, 6};
* e.g pinMultiSet(ar, 1); 
      sets pins 4, 5 and 6 as outputs.                                                                      
************************************************************************/
static inline void pinsMultiSet(const uint8_t *p, uint8_t mode){
	while(*p){
		mode ? pinSet(*p++, 1) : pinSet(*p++, 0);
	}
}
/************************************************************************
* write many pins at once
* *p - pointer to an array of pins.
* mode - either HIGH/LOW, 1/0.
* uint8_t ar[3] = {4, 5, 6};
* e.g pinMultiWrite(ar, 1); 
      sets pins 4, 5 and 6 High.                                                                      
************************************************************************/
static inline void pinsMultiWrite(const uint8_t *p, uint8_t mode){
	while(*p){
			mode ? pinWrite(*p++, 1) : pinWrite(*p++, 0);
	}
}

/************************************************************************
 * activate pull-up resistor on an input pin  
 * pin - port pin to activate pull-up. 
 *e.g activatePullUp(3);
      activates internal pull up resistor on pin 3                     
************************************************************************/
static inline void activatePullUp(uint8_t pin){
	pinSet(pin, INPUT);
	pinWrite(pin, HIGH);
}
/**************************************************************************
variable to set the pin array
e.g
	multiPins outPins[4] = { 2,3,4,5 };
	pinsMultiWrite(outPins, HIGH);
	set pins 2,3,4,5 high.
**************************************************************************/
typedef uint8_t multiPins;

//enum to hold ports
enum ports
{
	B, C, D
};
//enum to write value to full port
static inline void portSet(uint8_t port, uint8_t value)
{
	if(port == B) DDRB = value;
	if(port == C) DDRC = value;
	if(port == D) DDRD = value;
}
/*
 * write to a value to port
 * port - port to write to.
 * value - value to be written
 * e.g portWrite(C, 0xFF);
 * writes 0xFF to whole of PORTC
*/

static inline void portWrite(uint8_t port, uint8_t value)
{
	if(port == B) PORTB = value;
	if(port == C) PORTC = value;
	if(port == D) PORTD = value;
}

static inline uint8_t portRead(uint8_t port)
{
	if(port == B) return (PINB & 0xFF);
	if(port == C) return (PINC & 0xFF);
	if(port == D) return (PIND & 0xFF);
}

#ifdef __cplusplus
}
#endif

#endif /* PIN_H_ */
