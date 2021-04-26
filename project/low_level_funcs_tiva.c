/* low_level_funcs_tiva.c
 * 
 * Set of functions at the bottom level for the 3662 calculator mini-project.
 * These are the hardware drivers.
 * 
 * For documentation, see the documentation in the corresponding .h file.
 * 
 * Dr Chris Trayner, 2019 September
 */

#include "TExaS.h"
#include "low_level_funcs_tiva.h"

// =========================== CONSTANTS ============================

/* ----- What you need to do with these #define constants -----
 * 
 * You will need to define many hardware-specific #define constants 
 * to make your program work with the Tiva. They should all be 
 * defined here.
 * 
 * It is your job to decide which constants you need to define.
 * Any which you do define must have the names given here. This is 
 * the same as asking you to use specified names for functions. 
 * Rather than giving you a list of required names, you are given 
 * the definitions but without the values entered. In fact, they 
 * all have a value entered (0x0) to make sure the module will 
 * compile.
 * 
 * The port allocations (i.e. what bit of what port does what job) 
 * are given in Appendix C of the Mini-project Handout. For your 
 * convenience they are copied into the comment at the start of each 
 * port below.
 * 
 * For Ports A, B, D and E and the clocks, all the constants have 
 * been listed for you. This is simpler than deciding which you 
 * will use in your program. For definitions you don't need, 
 * just leave them as they are (with value 0x0) - it's not worth 
 * deleting them. Unused #define definitions do no harm.
 * 
 * These port and clock constants have been given the standard 
 * names, so there is no explanation of what they mean.
 * There are also some special LCD-related definitions which are 
 * not Tiva standards. These are at the end of these constants 
 * and have comments explaining what they are.
 */

// --------------------------- Ports -------------------------

// Port A (bit 2 is EN, bit 3 is RS):
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_PDR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x0))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x0))

// Port B (PORTB[2:5] are LCD DB4 to DB7):
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_PDR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x0))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x0))

// Port D (PORTD[0:3] are the outputs to the columns):
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_PDR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x0))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x0))

// Port E (PORTE[0:3] are the inputs from the rows):
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x0))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x0))


// --------------------------- Clocks --------------------------
#if 0
/* You are not asked to define the following because they are defined 
 * in PLL.h, which is #included by TExaS.h, which is #included above.
 */

//PLL related Defines
#define SYSCTL_RIS_R		(*((volatile unsigned long *)0x0))	
#define SYSCTL_RCC_R		(*((volatile unsigned long *)0x0))
#define SYSCTL_RCC2_R		(*((volatile unsigned long *)0x0))	
#define SYSCTL_RCGC1_R		(*((volatile unsigned long *)0x0))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x0))

//SysTick related Defines	
#define NVIC_ST_CTRL_R        	(*((volatile unsigned long *)0x0))
#define NVIC_ST_RELOAD_R      	(*((volatile unsigned long *)0x0))
#define NVIC_ST_CURRENT_R     	(*((volatile unsigned long *)0x0))
#endif

// ------------------- Special definitions ----------------------

/* LCD-related definitions
 * 
 * These are explained in Appendix C of the Mini-project Handout;
 * before you write this code you should re-read that part of 
 * that Appendix. The port allocations are copied into the 
 * comments at the start of each port above.
 * These have all been defined here with the simple value 0 (so the 
 * program will compile), but you should think carefully about 
 * them. For instance, if you need to access bit 6 of a port, 
 * should you define the value to be 6? Or should you write a 
 * definition like (*((volatile unsigned long *) ... )) to make 
 * the port access this bit directly? It is your decision.
 */

#define LCD_RS			0 /* 
			 * The single port bit connected to the 
			 * RS (Register Select) pin of the LCD.
			 */
#define LCD_EN			0 /* 
			 * The single port bit connected to the 
			 * EN (ENable data transfer) pin of the LCD.
			 */
#define LCD_DATA		0 /*
			 * The set of four adjacent bits connected 
			 * to the four data transfer bits (DB4 to 
			 * DB7) of the LCD. */

/* Incidentlly, a  comment on C-writing technique:
 * You will have noticed that the comments above use to old C 
 * comment form starting with slash-star and ending with 
 * star-slash, rather than the newer slash-slash. This is because 
 * a slash-slash comment ends at the line end. When you edit a 
 * program, it is an easy mistake to copy and paste something in the 
 * middle of a comment. It compiles, but the comment now refers to 
 * the wrong lines of code. But with the old form it probably won't 
 * compile, so you find the problem.
 * This is also why the comments above start on the same line as 
 * the #define, even though there is only room for the opening 
 * slash-star. (At least, there would only be room for that if you 
 * used the (*((volatile unsigned long *) ... )) form.)
 * This is one of the personal tricks I have invented over the years 
 * to stop me making mistaakes.
 */

// =========================== FUNCTIONS ============================

// ------------------------ Keyboard functions ------------------------

void InitKeyboardPorts( void )
{
	// Write your code here.
} // InitKeyboardPorts

void WriteKeyboardCol( unsigned char nibble )
{
	// Write your code here.
} // WriteKeyboardCol

unsigned char ReadKeyboardRow( void )
{
	// Write your code here.
} // ReadKeyboardRow


// ------------------------ Display functions ------------------------

void SendDisplayNibble( unsigned char byte, unsigned char instruction_or_data )
{
	// Write your code here.
} // SendDisplayInstruction

void SendDisplayByte( unsigned char byte, unsigned char instruction_or_data )
{
	// Write your code here.
} // SendDisplayInstruction

void InitDisplayPort( void )
{
	// Write your code here.
} // InitDisplayPort

void ClearDisplay()
{
	// Write your code here.
} // ClearDisplay

void TurnCursorOnOff( short int On )
{
	// Write your code here.
} // TurnCursorOnOff

void SetPrintPosition( short int line, short int char_pos )
{
	// Write your code here.
 // SetPrintPosition
}

void PrintChar( char ch )
{
	// Write your code here.
} // PrintChar


// ------------------------ Flash memory functions ------------------------

void InitFlash()
{
	// Write your code here.
} // InitFlash

void WriteDoubleToFlash( double number )
{
	// Write your code here.
} // WriteFloatToFlash

double ReadDoubleFromFlash()
{
	// Write your code here.
} // ReadFloatFromFlash


// ------------------------ Sundry functions ------------------------

void InitAllOther()
{
	// Write your code here.
} // InitAllOther

void InitAllHardware()
{
	// Write your code here.
} // InitAllHardware

void WaitMicrosec( long int wait_microsecs )
{
	// Write your code here.
} // WaitMicrosec


