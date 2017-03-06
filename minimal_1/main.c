/*******************************
 * stm32 minimal example main.c
 *******************************/

#include <stdint.h>

/* memory and peripheral start addresses */
#define FLASH_BASE      0x08000000
#define SRAM_BASE       0x20000000
#define PERIPH_BASE     0x40000000

/* work out end of RAM address as initial stack pointer */
/* STM32F103RB has 20 Kbye of RAM */
#define SRAM_SIZE       20*1024     
#define SRAM_END        (SRAM_BASE + SRAM_SIZE)

/* LED connected to PIN 8 of GPIOA */
#define LED_PIN         12
/* output mode: push-pull + 50MHz */
#define OUTPUT_MODE     (0x10|0x03) 

/* RCC peripheral addresses applicable to GPIOA */
#define RCC_BASE        (PERIPH_BASE + 0x21000)
#define RCC_APB2ENR     (*(volatile unsigned long*)(RCC_BASE + 0x18))

/* GPIOA peripheral addresses */
#define GPIOA_BASE      (PERIPH_BASE + 0x10800)
#define GPIOA_CRL       (*(volatile unsigned long*)(GPIOA_BASE + 0x00))
#define GPIOA_CRH       (*(volatile unsigned long*)(GPIOA_BASE + 0x04))
#define GPIOA_ODR       (*(volatile unsigned long*)(GPIOA_BASE + 0x0C))
#define GPIOA_BSRR      (*(volatile unsigned long*)(GPIOA_BASE + 0x10))
#define GPIOA_BRR       (*(volatile unsigned long*)(GPIOA_BASE + 0x14))

#define GPIOB_BASE      (PERIPH_BASE + 0x10C00)
#define GPIOB_CRL       (*(volatile unsigned long*)(GPIOB_BASE + 0x00))
#define GPIOB_CRH       (*(volatile unsigned long*)(GPIOB_BASE + 0x04))
#define GPIOB_ODR       (*(volatile unsigned long*)(GPIOA_BASE + 0x0C))
#define GPIOB_BSRR      (*(volatile unsigned long*)(GPIOB_BASE + 0x10))
#define GPIOB_BRR       (*(volatile unsigned long*)(GPIOB_BASE + 0x14))

/* user functions */
int main(void);
void delay(unsigned long count);

int main()
{
    /* enable clock on GPIOA peripheral */
    RCC_APB2ENR |= (1u << 2u);
    /* enable clock on GPIOB peripheral */
    RCC_APB2ENR |= (1u << 3u);
    

    /* set LED pin output mode */
    /*
    GPIOA_CRL |= OUTPUT_MODE << ((LED_PIN) << 2); // if pins 0 to 7
    GPIOB_CRH |= OUTPUT_MODE << ((LED_PIN-8) << 2); // if pins 8 to 15
    */

    GPIOB_CRH |= (0x2 << 16u); // MODE: 0x2 = 2MHz
    GPIOB_CRH |= (0x0 << 18u); // CNF: 0x0 = general purpose push / pull
    
    while(1)
    {
	GPIOB_ODR = (1u << LED_PIN);  // set LED pin high
	delay(200000);
	
	GPIOB_ODR &= ~(1u << LED_PIN);  // clear LED pin (low)
	delay(200000);
    }
}

void delay(unsigned long count)
{
    volatile uint32_t c = count;
    
    while(c--);
}
