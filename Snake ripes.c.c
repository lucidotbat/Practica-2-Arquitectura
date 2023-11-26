#include "ripes_system.h"
#include <stdio.h>

#define SW0 (0x01)
#define SW1 (0x02)
#define SW2 (0x04)
#define SW3 (0x08)
volatile unsigned int * led_base = (volatile unsigned int *) LED_MATRIX_0_BASE;
volatile unsigned int * manzana  = (volatile unsigned int *) LED_MATRIX_0_BASE;
volatile unsigned int * borde  = (volatile unsigned int *) LED_MATRIX_0_BASE;
volatile unsigned int * d_pad_up = (volatile unsigned int *) D_PAD_0_UP;
volatile unsigned int * d_pad_do = (volatile unsigned int *) D_PAD_0_DOWN;
volatile unsigned int * d_pad_le = (volatile unsigned int *) D_PAD_0_LEFT;
volatile unsigned int * d_pad_ri = (volatile unsigned int *) D_PAD_0_RIGHT;

void PrintFrame(int a,int x,int y,int orientacion,int length){
    

    if(a == 1){
    borde += x;
    borde += y * 35;
    }
    
    for(int i = 0;i < length; i++){
    *borde = 0xFA8072;
    if(orientacion == 1){ // arriba es -=
        
        borde -= LED_MATRIX_0_WIDTH;
        
    }else if(orientacion == 2){ // abajo es +=
        
        borde += LED_MATRIX_0_WIDTH;
        
    }else if(orientacion == 3){ // izquierda es -=1
        
        borde -= 1;
        
    }else{ // derecha es +=1
        
        borde += 1; 
    
    }

        
    }

    
    
    


    
}

void main()
{
unsigned int mask = 0;

int score = 0;
int i = 0, a, f = 0;

PrintFrame(1,0,0,4,35);
PrintFrame(0,0,0,2,25);
//PrintFrame(35,25,1,25);
//PrintFrame(35,25,3,25);


led_base += 0;

led_base += 2;
led_base += 3 * 35;

manzana += 7;
manzana += 7 * 15;
*manzana = 0x008000;

while(1)
{
    for(int j = 0; j < 1000; j++)
        a = j;
        
    if(manzana == led_base)
    {
        led_base += 1;
        score ++;
    }

    if(*d_pad_up == 1)
    {
        led_base -= LED_MATRIX_0_WIDTH;
        f++;
    }

    if(*d_pad_do == 1)
    {
        led_base += LED_MATRIX_0_WIDTH;
        f++;
    }

    if(*d_pad_le == 1)
    {
        led_base -= 1;
        f++;
    }
    
    if(*d_pad_ri == 1)
    {
        led_base += 1;
        f++;
    }
    
    if((*led_base == 0xFFD700) && (f == 1))
        break;
    else if((*led_base == 0xFA8072) && (f == 1))
        break;
    else
       *led_base = 0xFFD700; 
  
     f = 0;

}

printf("Tu puntuación es %i", score);

}
