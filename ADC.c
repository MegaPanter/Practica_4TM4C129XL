/*
 * ADC.c
 *
 *  Created on: 04/11/2019
 *      Author: ravenelco
 */
#include "lib/include.h"

extern void Configura_Reg_ADC0(void)
{
    /*
    Habilitar el modulo 0 del ADC con dos canales analogicos 
    en el puerto E a una velocidad de conversion de 250ksps
    dandole la mayor prioridad al secuenciador 2 con evento
    de procesador 
    */
     //Pag 396 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC = (1<<0); 
    //Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(1<<3)|(0<<2)|(1<<1)|(1<<0)|(1<<12)|(1<<8);
    //Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    GPIOB_AHB->DIR = (0<<5);
    GPIOD_AHB->DIR = (0<<7) | (0<<6);
    GPIOE_AHB->DIR = (0<<0) | (0<<2)| (0<<4); //PE5 y PE4
    //(GPIOAFSEL) pag.770 Enable alternate función para que el modulo analógico tenga control de esos pines
    GPIOB_AHB->AFSEL = (1<<5);
    GPIOD_AHB->AFSEL = (1<<7) | (1<<6);
    GPIOE_AHB->AFSEL=  (1<<0) | (1<<2) | (1<<4);
    //GPIOE_AHB->AFSEL =  (1<<4) | (1<<5);
    //(GPIODEN) pag.781 desabilita el modo digital
    //GPIOE_AHB->DEN = (0<<4) | (0<<5 );
    GPIOB_AHB->DEN = (0<<5);
    GPIOD_AHB->DEN = (0<<7) | (0<<6);
    GPIOE_AHB->DEN = (0<<0) | (0<<2)| (0<<4);
    //Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
    //GPIOE_AHB->PCTL = GPIOE_AHB->PCTL & (0xFF00FFFF);
    //----------------------------------(0X76543210)
    GPIOB_AHB->PCTL = GPIOB_AHB->PCTL & (0xFF0FFFFF);
    GPIOD_AHB->PCTL = GPIOD_AHB->PCTL & (0x00FFFFFF);
    GPIOE_AHB->PCTL = GPIOE_AHB->PCTL & (0xFFF0F0F0);
    //(GPIOAMSEL) pag.786 habilitar analogico
    //GPIOE_AHB->AMSEL = (1<<5) | (1<<4);
    GPIOB_AHB->AMSEL = (1<<5);
    GPIOD_AHB->AMSEL = (1<<7) | (1<<6);
    GPIOE_AHB->AMSEL= (1<<0) | (1<<2)| (1<<4);
    
    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC0->PC = 0x1;//250ksps
    //Pag 1099 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores
    //PRIORIDAD ss3/ss2/ss1/ss0  mayor 0-----3 menor 
    ADC0->SSPRI = 0x3012;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX  = (0x0<<8)|(0x0<<4);
    //Pag 1129 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    
    
    
    ADC0->SSMUX2 = (1<<0)|(3<<4)|(4<<8); 
                           //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
    ADC0->SSMUX1 = (5<<0)|(11<<4)|(9<<8); 
    ADC0->SSCTL2 = (1<<1) | (1<<2)| (1<<5) | (1<<6)|(1<<9) | (1<<10);
    ADC0->SSCTL1 = (1<<1) | (1<<2)|(1<<5) | (1<<6)|(1<<9) | (1<<10);
    /* Enable ADC Interrupt */
    ADC0->IM = (0<<2)|(0<<1); /* Unmask ADC0 sequence 2 interrupt pag 1082*/
    //NVIC->PRI4 = (NVICPRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC->EN0 = 0x00010000;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS = (0<<3) | (1<<2) | (1<<1) | (0<<0);
    
}

