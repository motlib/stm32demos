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
#define LED_PIN         0
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
#define GPIOB_ODR       (*(volatile unsigned long*)(GPIOB_BASE + 0x0C))
#define GPIOB_BSRR      (*(volatile unsigned long*)(GPIOB_BASE + 0x10))
#define GPIOB_BRR       (*(volatile unsigned long*)(GPIOB_BASE + 0x14))

#define STACK_TOP 0x20000800   // just a tiny stack for demo


/* user functions */
void delay();
static void nmi_handler(void);
static void hardfault_handler(void);
int main(void);

// Define the vector table
unsigned int *myvectors[4] __attribute__ ((section("vectors"))) = {
    (unsigned int *) STACK_TOP,         // stack pointer
    (unsigned int *) main,              // code entry point
    (unsigned int *) nmi_handler,       // NMI handler (not really)
    (unsigned int *) hardfault_handler  // hard fault handler
};


int main()
{
    /* enable clock on GPIOA peripheral */
    RCC_APB2ENR |= (1u << 2u);
    /* enable clock on GPIOB peripheral */
    RCC_APB2ENR |= (1u << 3u);
    

    /* set LED pin output mode */
    
//    GPIOA_CRL |= OUTPUT_MODE << ((LED_PIN) << 2); // if pins 0 to 7
//    GPIOA_CRL |= 
    //GPIOB_CRH |= OUTPUT_MODE << ((LED_PIN-8) << 2); // if pins 8 to 15
    
    GPIOA_CRL = (0x2 << 0u); // MODE: 0x2 = 2MHz
    //GPIOA_CRL |= (0x0 << 18u); // CNF: 0x0 = general purpose push / pull

    //GPIOB_CRH |= (0x2 << 16u); // MODE: 0x2 = 2MHz
    //GPIOB_CRH |= (0x0 << 18u); // CNF: 0x0 = general purpose push / pull
    
    while(1)
    {
	GPIOA_ODR |= (1u << LED_PIN);  // set LED pin high
	delay();
	
	GPIOA_ODR &= ~(1u << LED_PIN);  // clear LED pin (low)
	delay();
    }
}


void delay(void)
{
    volatile unsigned int i;

    for (i = 0; i < 20000; i++)
	;
}

void nmi_handler(void)
{
    for(;;);
}

void hardfault_handler(void)
{
    for(;;);
}
