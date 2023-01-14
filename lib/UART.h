#ifndef UART_UART_H_
#define UART_UART_H_

extern void Configurar_UART1(void);
extern void interrupcion(void);
extern void transmisor(char *string);
extern void trans_char(char c);
extern void UARTS_ISR(void);




extern void Configurar_SysTick(void);
extern void SysTick_espera(float delay);
extern void SysTick_1ms(uint16_t delay);


#endif /* UART_UART_H_ */