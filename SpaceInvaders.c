
// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total

#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "tm4c123gh6pm.h"
#include "UART.h"

//imgs
const unsigned char cell[] = {
0x42,0x4d,0x8e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x00,0x00,0x00,0x28,0x00,
0x00,0x00,0x08,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x01,0x00,0x04,0x00,0x00,0x00,
0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x80,
0x00,0x00,0x00,0x80,0x80,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x80,
0x00,0x00,0x80,0x80,0x80,0x00,0xc0,0xc0,0xc0,0x00,0x00,0x00,0xff,0x00,0x00,0xff,
0x00,0x00,0x00,0xff,0xff,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x0f,0xf0,0x00,0x00,0x0f
,0xf0,0x00,0x00,0x0f,0xf0,0x00,0x00,0x0f,0xff,0xff,0xff,0xff   
};

const unsigned char oo[] ={
 0x42, 0x4D, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xF8, 0x00, 0x8F, 0x00, 0xF0, 0x00,
 0x0F, 0x00, 0xF0, 0x00, 0x0F, 0x00, 0xF8, 0x00, 0x8F, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,

};

const unsigned char xx[] ={
 0x42, 0x4D, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x23, 0x2E, 0x00, 0x00, 0x23, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x08, 0xFF, 0x80, 0x00, 0x80, 0x88, 0x08, 0x00, 0xF8, 0x00,
 0x8F, 0x00, 0xF8, 0x00, 0x8F, 0x00, 0x80, 0x88, 0x08, 0x00, 0x08, 0xFF, 0x80, 0x00, 0xFF,

};
const unsigned char empty[] = {
0x42,0x4d,0x8e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x00,0x00,0x00,0x28,0x00,
0x00,0x00,0x08,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x01,0x00,0x04,0x00,0x00,0x00,
0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x80,
0x00,0x00,0x00,0x80,0x80,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x80,
0x00,0x00,0x80,0x80,0x80,0x00,0xc0,0xc0,0xc0,0x00,0x00,0x00,0xff,0x00,0x00,0xff,
0x00,0x00,0x00,0xff,0xff,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


char matrix[8]={0};
char input[43];
int PlayOut = 0;
int EVA = 0;
int provocation = 0;
void PortF_Init(void);
void Delay(void);
void EnableInterrupts(void);
int playPosition (char z);
//ai
int GetValue(int t);
int AIManager(void);
int NegaMax(int Depth);
int winning(void);
void computer(void);
void player(void);
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}
void PortB_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTB_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTB_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTB_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTB_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTB_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}

void UART_Init(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
//                 switching from PC5,PC4 to PA1,PA0
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port A
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 520;                    // IBRD = int(80,000,000 / (16 * 9600)) = int(520.8333)
  UART0_FBRD_R = 53;                    // FBRD = round(0.83333 * 64) = 53
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1,PA0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1,PA0
                                        // configure PA1,PA0 as UART0
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA1,PA0
}

unsigned char UART_InChar(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART1_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART1_DR_R&0xFF));
}


unsigned char UART_InCharNonBlocking(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  if((UART1_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART1_DR_R&0xFF));
  } else{
    return 0;
  }
}

void UART_OutString(unsigned char buffer[]){
   
	while(*buffer)
	{
		UART_OutChar(*buffer);
		buffer++;
	}

}
void UART_OutChar(unsigned char data){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART1_FR_R&UART_FR_TXFF) != 0);
  UART1_DR_R = data;
}

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Timer2_Init(unsigned long period);
void Delay100ms(unsigned long count); // time delay in 0.1 seconds
unsigned long TimerCount;
unsigned long Semaphore;
void startScreen(void);

	#include <stdio.h>
	#include <stdlib.h>
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

int count;
int main(void){
  TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	 PortF_Init();        // Call initialization of port PF4 PF2 
 //PortB_Init();	
  EnableInterrupts();  // The grader uses interrupts
  Random_Init(1);
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	
	Nokia5110_SetCursor(3,2);
	Nokia5110_OutString("START");
	while((GPIO_PORTF_DATA_R&0x10)!=0);
  Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	
	int i;
	for(i=0;i<44;i++)
	input[i]=' ';
	Nokia5110_SetCursor(0,1);
	Nokia5110_OutString("1player->sw1");
	Nokia5110_SetCursor(0,3);
	Nokia5110_OutString("2players>sw2");
	
	
	//while((GPIO_PORTF_DATA_R&0x01)==1&&(GPIO_PORTF_DATA_R&0x10)==1);
	
		//Delay();
		while(1)
		{
			/*Nokia5110_ClearBuffer();Nokia5110_DisplayBuffer();
			Nokia5110_OutString("1player->sw1");
	Nokia5110_SetCursor(0,3);
	Nokia5110_OutString("2players>sw2");*/
			
			Delay();
			if((GPIO_PORTF_DATA_R&0x01)==0)
	{
		Nokia5110_DisplayBuffer();
	  Nokia5110_ClearBuffer();
	  Nokia5110_Clear();
		startScreen(); 
		player();
		
	
	}
	else if((GPIO_PORTF_DATA_R&0x10)==0)
	{
		 
		
			
		Nokia5110_DisplayBuffer();
	  Nokia5110_ClearBuffer();
	  Nokia5110_Clear();
		startScreen();
		computer();
	
	}
	for(i=0;i<44;i++)
	    input[i]=' ';
}
}

//startUpOfscreen
void startScreen()
{
	int ii=47,jj,yy=0,kk;
	for( kk=0; kk<6; ii++)
	{
		yy=7;
		for(jj=0; jj<7; jj++)
		{
			Nokia5110_PrintBMP(yy, ii, cell,0);
	    Nokia5110_DisplayBuffer(); 
			yy+=7;
		}
		ii-=8; kk++;
	} 
	Nokia5110_PrintBMP(0, 6,oo ,0);
	Nokia5110_DisplayBuffer(); 
}



void Delay(void){unsigned long volatile time;
  time = 727240*200/91;  // 0.1sec
  while(time){
		time--;
  }
}
void computer(void)
{
	 TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	 PortF_Init();        // Call initialization of port PF4 PF2    
  EnableInterrupts();  // The grader uses interrupts
  Random_Init(1);
  Nokia5110_Init();
	int w;
	 while(1){
		w=AIManager();
		while(input[w-7]==' '&&w>7)
		{w-=7;}
		input[w]='O';
		Nokia5110_PrintBMP(7*((w%7)+1), 12+(7*(5-(w/7))),oo ,0);   //col->w%7   row-->5-w/7
   	Nokia5110_DisplayBuffer(); 
		/*Nokia5110_SetCursor((w%7),5-(w/7));   
    Nokia5110_OutChar('O');*/
		Delay();
		char winningtemp = winning();
        if(winningtemp != 0)
        {
            if(winningtemp == 1)
						{
							Nokia5110_SetCursor(8,3);
							Nokia5110_OutString("win");
							break;
						}
            else if (winningtemp == 2)  //player1-->computer won
						{
							Nokia5110_SetCursor(8,3);
							Nokia5110_OutString("lose");
							Nokia5110_SetCursor(8,4);
							Nokia5110_OutString("er");
							break;
						}
            else if (winningtemp == 3)   //tie
						{
							Nokia5110_SetCursor(11,3);  
							Nokia5110_OutChar('0');
							break;
						}
        }
				
        else
				{
					Nokia5110_PrintBMP(0, 6,oo ,0);
	        Nokia5110_DisplayBuffer();
					int x=  playPosition('X');
					while(x==-1)
					{
						Nokia5110_PrintBMP(0, 6,oo ,0);
	Nokia5110_DisplayBuffer();
					 x=  playPosition('X');
					}
          x=x/7;
					Nokia5110_PrintBMP((count+1)*7, 12+(7*(5-x)), xx ,0);   
   	      Nokia5110_DisplayBuffer(); 
// Nokia5110_SetCursor(count,5-x);   //col-->count   row-->5-x
// Nokia5110_OutChar('X');
					char winningtemp2= winning();
        if(winningtemp2 != 0)
        {
            if(winningtemp2 == 1)
						{
							Nokia5110_SetCursor(8,3);
							Nokia5110_OutString("win");
							break;
						}
            else if (winningtemp2 == 2)  //player1-->computer won
						{
							Nokia5110_SetCursor(8,3);
							Nokia5110_OutString("lose");
							Nokia5110_SetCursor(8,4);
							Nokia5110_OutString("er");
							break;
						}
            else if (winningtemp2 == 3)   //tie
						{
							Nokia5110_SetCursor(11,3);  
							Nokia5110_OutChar('0');
							break;
						}
        }

				}
	
}
}
void player(void)
{
	// TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	// PortF_Init();        // Call initialization of port PF4 PF2  
  // PortB_Init();  
 // EnableInterrupts();  // The grader uses interrupts
  Random_Init(1);
 // Nokia5110_Init();
	UART_Init();
  Nokia5110_ClearBuffer();
	startScreen();
	//while(GPIO_PORTB_DATA_R&0x00==0);
	char r= rand ();
	//char r='2';
	UART_OutChar(r);
	while((GPIO_PORTB_DATA_R&0x00)==0);
	char a=UART_InChar();
	Delay();
	if(r>a)
	{
		while(1)
		{ 	
			Nokia5110_PrintBMP(0, 6,oo ,0);
	    Nokia5110_DisplayBuffer();
			
			int x=  playPosition('X');
					while(x==-1)
					{
						Nokia5110_PrintBMP(0, 6,oo ,0);
	          Nokia5110_DisplayBuffer();
 					 x=  playPosition('X');
					}
					UART_OutChar(count+1);
          x=x/7;
					Nokia5110_PrintBMP((count+1)*7, 12+(7*(5-x)), xx ,0);   
   	      Nokia5110_DisplayBuffer(); 
         // Nokia5110_SetCursor(count,x);
         // Nokia5110_OutChar('X');
						char winningtemp = winning();
        if(winningtemp != 0)
        {
            if(winningtemp == 1)
						{
							Nokia5110_SetCursor(11,3);
							Nokia5110_OutChar('2');
							break;
						}
            else if (winningtemp == 2)  //player1-->computer won
						{
							Nokia5110_SetCursor(11,3);
							Nokia5110_OutChar('1');
							break;
						}
            else if (winningtemp == 3)   //tie
						{
							Nokia5110_SetCursor(11,3);  
							Nokia5110_OutChar('0');
							break;
						}
        }
				else
				{
					while((GPIO_PORTB_DATA_R&0x00)==0);
					char a=UART_InChar();
					int x=GetValue(a-1);
         while(x==-1) 
          {
						while((GPIO_PORTB_DATA_R&0x00)==0);
	          char a=UART_InChar();
						int x=GetValue(a-1);
          }
	while(input[x-7]==' '&&x>0)
		{x-=7;}
		input[x]='O';
		Nokia5110_PrintBMP(7*a, 12+(7*(5-x)), oo ,0);   
    Nokia5110_DisplayBuffer(); 
		//Nokia5110_SetCursor(a-1,x);
   // Nokia5110_OutChar('O');
char winningtemp2= winning();
        if(winningtemp2 != 0)
        {
            if(winningtemp2 == 1)
						{
							Nokia5110_SetCursor(8,3);
							Nokia5110_OutString("win");
							break;
						}
            else if (winningtemp2 == 2)  //player1-->computer won
						{
							Nokia5110_SetCursor(8,3);
							Nokia5110_OutString("lose");
							Nokia5110_SetCursor(8,4);
							Nokia5110_OutString("er");
							break;
						}
            else if (winningtemp2 == 3)   //tie
						{
							Nokia5110_SetCursor(11,3);  
							Nokia5110_OutChar('0');
							break;
						}
        }
				}
		}
	}
	else
	{ 
		while(1)
		{
				while((GPIO_PORTB_DATA_R&0x00)==0);
					char a=UART_InChar();
					int x=GetValue(a-1);
         while(x==-1) 
          {
							while((GPIO_PORTB_DATA_R&0x00)==0);
	          char a=UART_InChar();
						int x=GetValue(a-1);
          }
	while(input[x-7]==' '&&x>0)
		{x-=7;}
		input[x]='O';
		Nokia5110_PrintBMP(a*7, 12+(7*(5-x)),oo ,0);   
    Nokia5110_DisplayBuffer(); 
		//Nokia5110_SetCursor(a-1,x);
    //Nokia5110_OutChar('O');
		char winningtemp = winning();
        if(winningtemp != 0)
        {
            if(winningtemp == 1)
						{
							Nokia5110_SetCursor(11,3);
							Nokia5110_OutChar('2');
							break;
						}
            else if (winningtemp == 2)  //player1-->computer won
						{
							Nokia5110_SetCursor(11,3);
							Nokia5110_OutChar('1');
							break;
						}
            else if (winningtemp == 3)   //tie
						{
							Nokia5110_SetCursor(11,3);  
							Nokia5110_OutChar('0');
							break;
						}
        }
       else
			 {
				 Nokia5110_PrintBMP(0, 6,oo ,0);
	Nokia5110_DisplayBuffer();
				 int x=  playPosition('X');
					while(x==-1)
					{
						Nokia5110_PrintBMP(0, 6,oo ,0);
	Nokia5110_DisplayBuffer();
					 x=  playPosition('X');
					}
					UART_OutChar(count+1);
          x=x/7;
					Nokia5110_PrintBMP((count+1)*7, 12+(7*(5-x)), xx ,0);   
   	      Nokia5110_DisplayBuffer(); 
         // Nokia5110_SetCursor(count,x);
          //Nokia5110_OutChar('X');
					char winningtemp2 = winning();
        if(winningtemp2 != 0)
        {
            if(winningtemp2 == 1)
						{
							Nokia5110_SetCursor(8,3);
							Nokia5110_OutString("win");
							break;
						}
            else if (winningtemp2 == 2)  //player1-->computer won
						{
							Nokia5110_SetCursor(8,3);
							Nokia5110_OutString("lose");
							Nokia5110_SetCursor(8,4);
							Nokia5110_OutString("er");
							break;
						}
            else if (winningtemp2 == 3)   //tie
						{
							Nokia5110_SetCursor(11,3);  
							Nokia5110_OutChar('0');
							break;
						}
        }
			 }				 
		}
	}
}
int playPosition(char z)
{ 
	char x;
	 count=-1;
	Nokia5110_PrintBMP(0, 6,oo ,0);
	Nokia5110_DisplayBuffer();
	while(1)
	{
		
	while((GPIO_PORTF_DATA_R&0x01)==1)
	{
		int a=GPIO_PORTF_DATA_R&0x10;
		if(a==0)
	{
		if(count<6)
		{
			count++;
			Nokia5110_PrintBMP((count+1)*7, 6,oo ,0);
			
			Nokia5110_PrintBMP((count)*7, 6, empty ,0);
	    Nokia5110_DisplayBuffer(); 
		}
		else
		{
			Nokia5110_PrintBMP((count+1)*7, 6, empty ,0);
			count=-1; 
			Nokia5110_PrintBMP(0, 6,oo ,0);
	    Nokia5110_DisplayBuffer(); 
		}
		
Delay();		
	
} 
	}
	Nokia5110_PrintBMP((count+1)*7, 6, empty ,0);
		Nokia5110_PrintBMP(0, 6,oo ,0);
	  Nokia5110_DisplayBuffer(); 
	x=GetValue(count);
 if(x==-1) 
 {
	return -1;
 }
 
	while(input[x-7]==' '&&x>6)
		{x-=7;}
		input[x]=z;
 break;

}
					return x;

}


// ai

int GetValue(int column) // pass this function a column that you want to play in and it will return its value in input array ..
{
	int i;
	int n;
	if(column > 7)
        return -1;
	if(column == 0) {
		if(input[0]==' ')
			return 0;
		else if(input[7]==' ')
			return 7;
		else if(input[14]==' ')
			return 14;
		else if(input[21]==' ')
			return 21;
		else if(input[28]==' ')
			return 28;
		else  if(input[35]==' ')
			return 35;
		else 
			return -1;
	}
  for( i = 0 ; i<= 6 ; i++)
  {
      if( input[column+7*i] == ' '  )
      {
          n = column+7*i;
          break;
      }
  }
  if ( n >42 )
      return -1;
    return n;
}

int AIManager() // AI Algorithm
{
int column;  
float temp; 
int PlayNumber;	
float chance[2] = {9999999 , 0 };
    for( column = 0 ; column <7 ; column ++)
    {
        PlayOut = 0;
        EVA=0;
        PlayNumber = GetValue(column);
        if( PlayNumber != -1)
        {

            input[PlayNumber] = 'O';
            if(winning()==2)
               {
                   input[PlayNumber]=' ';
                   return PlayNumber ;
               }
            temp = -(100*NegaMax(1));
            if(PlayOut != 0)
                temp -= ((100*EVA)/PlayOut);
            if(-temp >= 100)
                provocation = 1;
            if( chance[0] > temp  )
            {
                chance[0] = temp  ;
                chance[1] = PlayNumber;
            }
            input[PlayNumber] = ' ';
        }
    }
    return chance[1];
}
int NegaMax(int Depth) // MiniMax algorithm in NegaMax form
{
    char XO;
int column;    
int PlayNumber[8] = {0,0,0,0,0,0,0,0}; // The values of the input[] for every column
    int chance=0;
    if(Depth % 2 != 0)
        XO='X';
    else
        XO='O';
		
    for( column = 0 ; column < 7 ; column ++)
        PlayNumber[column]=GetValue(column);
    for( column = 0 ; column < 7 ; column++)
    {
        if(PlayNumber[column] != 0)
        {
            input[PlayNumber[column]]=XO;
            if( winning() != 0 )
            {
                PlayOut ++;
                if(XO=='O')
                    EVA ++;
                else
                    EVA --;
                input[PlayNumber[column]]=' ';
                return -1;
            }
            input[PlayNumber[column]]=' ';
        }
    }
    if(Depth <= 3)
    {
			int column;
        for( column = 0 ; column < 7 ; column ++)
        {
            int temp=0;
            if( PlayNumber[column] != 0 )
            {
                input[PlayNumber[column]]=XO;
                if( winning() != 0 )
                {
                    PlayOut++;
                    if(XO=='O')
                        EVA++;
                    else
                        EVA--;
                    input[PlayNumber[column]]=' ';
                    return -1;
                }
                temp = NegaMax(Depth+1);
                if(column == 1)
                    chance = temp;
                if(chance < temp)
                    chance = temp;
                input[PlayNumber[column]]=' ';
            }
        }
    }
    return -chance;


}

int winning() // Winning algorithm
{
     int temp=0;
	int i ;
    for( i = 0 ; i<= 42 ; i++)
    {
        if(input[i] != ' ')
        {
					int var = (int)(i/7) ;
            temp++;
            if( i - var* 7 <= 3  )
                if( input[i] == input [i+1] && input[i] == input[i+2] && input[i] == input[i+3] )	{
								if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
									}
            if( i <= 21 )
                if ( input[i] == input[i+7] && input[i] == input[i+14] && input[i] == input[i+21]  ) {
								if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
									}
            if( i - var* 7 <= 3 && i<=18  )
                if(input[i] == input[i+8] && input[i] == input[i+16] && input[i]==input[i+24])	{
                    if(input[i] == 'X'  )
                        return 1 ;
                    else
                        return 2;
									}
            if( i - var* 7 >= 3 && i <= 21   )
                if(input[i] == input[i+6] && input[i] == input[i+12] && input[i]==input[i+18]) {
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
									}
        }

    }
    if (temp == 42)
        return 3;
    return 0;
}





// You can use this timer only if you learn how it works
void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}
void Timer2A_Handler(void){ 
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout

}
void Delay100ms(unsigned long count){unsigned long volatile time;
  while(count>0){
    time = 727240/20;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

