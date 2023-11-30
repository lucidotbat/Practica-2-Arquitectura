#include "ripes_system.h"
#include <stdio.h>

#define SW0 (0x01)
#define SW1 (0x02)
#define SW2 (0x04)
#define SW3 (0x08)
volatile unsigned int * led_base = (volatile unsigned int *) LED_MATRIX_0_BASE;
volatile unsigned int * manzana  = (volatile unsigned int *) LED_MATRIX_0_BASE;
volatile unsigned int * bordeLados  = (volatile unsigned int *) LED_MATRIX_0_BASE;
volatile unsigned int * bordeArriba  = (volatile unsigned int *) LED_MATRIX_0_BASE;
volatile unsigned int * d_pad_up = (volatile unsigned int *) D_PAD_0_UP;
volatile unsigned int * d_pad_do = (volatile unsigned int *) D_PAD_0_DOWN;
volatile unsigned int * d_pad_le = (volatile unsigned int *) D_PAD_0_LEFT;
volatile unsigned int * d_pad_ri = (volatile unsigned int *) D_PAD_0_RIGHT;
volatile unsigned int * led_cola = (volatile unsigned int *) LED_MATRIX_0_BASE;



void main()
{
    
    int snake[LED_MATRIX_0_WIDTH * LED_MATRIX_0_HEIGHT] = {0};
    int frente = 4;
    int cola = 0;
    
    unsigned int mask = 0;

    int score = 0;
    int i = 0, a, f = 0;

    for(int i = 0; i < LED_MATRIX_0_WIDTH; i++)
    {
        *bordeLados = 0xFA8072;
        bordeLados += 35 * 24;
        *bordeLados = 0xFA8072;
        bordeLados -= 35 * 24;
        bordeLados++;
    }
    
    
    for(int h = 0; h < LED_MATRIX_0_HEIGHT; h++)
    {
        *bordeArriba = 0xFA8072;
        bordeArriba += 34;
        *bordeArriba = 0xFA8072;
        bordeArriba -= 34;
        bordeArriba += 35;
    }


    led_base += 2;
    led_base += 3 * 35;
    led_cola += 2;
    led_cola += 3 * 35;

    manzana += 7;
    manzana += 2 * 35;
    *manzana = 0x008000;

    int contador = 0;

    int movimiento1 = 1, movimiento2 =1;
    while(1)
    {
        for(int j = 0; j < 1000; j++)
            a = j;
        
        if(manzana == led_base)
        {
            if(manzana >= 805)
                contador = 37;
            if (movimiento1 == 1)
            {
                led_base += 1;
                snake[frente] = 1;
            }
            else if (movimiento1 == -1)
            {
                led_base -= 1;
                snake[frente] = -1;
            }
            else if (movimiento1 == -LED_MATRIX_0_WIDTH)
            {
                led_base -= LED_MATRIX_0_WIDTH;
                snake[frente ] = -35;
            }
            else 
            {
                led_base += LED_MATRIX_0_WIDTH;
                snake[frente] = 35;
            }
            frente++;
            *led_base = 0xFFD700;
            score ++;
            int mamanzana = 0;
            int contador = 0;
        
            while (mamanzana != 1) 
            {
                manzana += contador;
                if (*manzana != 0xFFD700 && *manzana != 0xFA8072)
                {
                    *manzana = 0x008000;
                    mamanzana = 1;
                } 
                else 
                    contador++;
            }
        }
        if(*d_pad_up == 1)
        {
            movimiento1 = -LED_MATRIX_0_WIDTH;
            movimiento2 = -35;
        }
        if(*d_pad_do == 1)
        {
            movimiento1= LED_MATRIX_0_WIDTH;
            movimiento2 = 35;
        }
        if(*d_pad_le == 1)
        {
            movimiento1= -1;
            movimiento2 = -1;
        }
        if(*d_pad_ri == 1)
        {
            movimiento1 = 1;
            movimiento2 = 1;
        }
    
        led_base += movimiento1;
        snake[frente] = movimiento2;
        frente++;
        led_cola += snake[cola];
        cola++;
        f++;
    
        for (int w = 0; w < 1000; w++)
        w+w;

    
        if((*led_base == 0xFFD700) && (f == 1))
            break;
        else if((*led_base == 0xFA8072) && (f == 1))
            break;
        else
        {
            *led_cola = 0x000000;
            *led_base = 0xFFD700; 
        }
  
        f = 0;

    }

    printf("PUNTOS: %i", score);
    return 0;

}
