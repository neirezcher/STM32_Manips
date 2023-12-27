/*********************************************************************************/
/* OO STM32 Library : xxPinAsOutput CLASS DECLARATION To configure GPIO Pins as Input 
	 E.D - INSAT Nov 2021
	      Default Constructor: Push Pull
 
        Use:  PinAsOutput  ObjectName (PA_i) , 
              where X is for GPIOX (A, B, C or D)
			        i is the pin Number (0 to 15)

		Example:  PinAsOutput MyLed (PB_5;
************************************************************************************/

#include <stm32_wrapper_gpio.h>

namespace OOlayer {

class PinAsOutput {

		  /*Used as Atribute to save PinName + use read Object (Pin) state (gpio_read()).  */
		PinName thepin;
	
public:

    /** Create a PinAsOutput connected to the specified pin
     *
     *  @param pin PinAsOutput pin to connect to
     */
		PinAsOutput  (PinName pin) :thepin(pin) { 
				gpio_init_out_def  (pin); 
		}
    

/***** Create a PinAsOutput connected to the specified pin
     *
     *  @param pin PinAsOutput pin to connect to
     *  @param mode the initial mode of the pin
     */
    PinAsOutput (PinName pin, PinOutMode mode):thepin(pin) {
        gpio_init_out (pin, mode);
    }

/***** Create a PinAsOutput connected to the specified pin
     *
     *  @param pin PinAsOutput pin to connect to
     *  @param mode the initial mode of the pin
     */
    PinAsOutput (PinName pin, PinOutMode mode, PinSpeed speed):thepin(pin) {
        gpio_init_out_ex (pin, mode, speed);
    }

/***** Read the input, represented as 0 or 1 (int)
     *
     *  @returns
     *    An integer representing the state of the input pin,
     *    0 for logical 0, 1 for logical 1
     */
    int read() {
        return gpio_read_out(thepin);
    }	

		/***** An operator shorthand for read(): overload (=) for value = object
--> To Read an Input, use only The object Name
		Example:  int BtnState = MyButton;
     */
    operator int() {
        return read();
    }		
		
/***** Write to the output pin, represented as 0 or 1
     *
     *  @returns
     *    An integer representing the state of the input pin,
     *    0 for logical 0, 1 for logical 1
     */		
		    void write(int value) {
					gpio_write(thepin,value);
				}
				
				
				// Ci-dessous: Les 2 sucrcharges (de l'opérateur =) à compléter 
		
/**** A shorthand for write(): overload (= operator) for object = value
*/
    /* void operator= (//complete code )
			{
        //complete code
    }*/

				
				
/***** A shorthand for write(): overload (= operator) for object = object
*/		
				
    /*void operator= (//complete code) {
        //complete code);
    }*/



}; //Class End

} //namespace
