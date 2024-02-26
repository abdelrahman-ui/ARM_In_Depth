/*
    @file   application.c
    @author Abelrahman Yassen
*/

typedef unsigned int uint32_t;

typedef struct
{
  volatile uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  volatile uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  volatile uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  volatile uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  volatile uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  volatile uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  volatile uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  volatile uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  volatile uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_TypeDef;

typedef struct
{
  volatile uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  volatile uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  volatile uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  volatile uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  volatile uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  volatile uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  volatile uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t          RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  volatile uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  volatile uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t          RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  volatile uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  volatile uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  volatile uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t          RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  volatile uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  volatile uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t          RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  volatile uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  volatile uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  volatile uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t          RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  volatile uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  volatile uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t          RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  volatile uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  volatile uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t          RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  volatile uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  volatile uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
} RCC_TypeDef;

#define SET_BIT(REG, BIT) ((REG) |= (BIT))

#define PERIPH_BASE                0x40000000UL /*!< Peripheral base address in the alias region                                */
#define AHB1PERIPH_BASE            (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE                   (AHB1PERIPH_BASE + 0x3800UL)
#define RCC                        ((RCC_TypeDef *) RCC_BASE)

#define GPIOD_BASE                 (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOD                      ((GPIO_TypeDef *) GPIOD_BASE)

#define RCC_AHB1ENR_GPIODEN_Pos    (3U)                                
#define RCC_AHB1ENR_GPIODEN_Msk    (0x1UL << RCC_AHB1ENR_GPIODEN_Pos)   /*!< 0x00000008 */
#define RCC_AHB1ENR_GPIODEN        RCC_AHB1ENR_GPIODEN_Msk  

#define __HAL_RCC_GPIOD_CLK_ENABLE() SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN)

uint32_t Counter1 = 5;
uint32_t Counter2 = 10;

uint32_t Counter3 = 0;
uint32_t Counter4;

int main(void){
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIOD->MODER |= (1 << 24); /* General purpose output mode */
    GPIOD->MODER |= (1 << 26); /* General purpose output mode */
    GPIOD->MODER |= (1 << 28); /* General purpose output mode */
    GPIOD->MODER |= (1 << 30); /* General purpose output mode */
    while(1){
        for(uint32_t counter = 0; counter < 5; counter++){
            GPIOD->ODR |= (1 << 12);
            GPIOD->ODR |= (1 << 13);
            GPIOD->ODR |= (1 << 14);
            GPIOD->ODR |= (1 << 15);
            for(uint32_t i = 0 ; i < 156250 ; i++);
            GPIOD->ODR &= ~(1 << 12);
            GPIOD->ODR &= ~(1 << 13);
            GPIOD->ODR &= ~(1 << 14);
            GPIOD->ODR &= ~(1 << 15);
            for(uint32_t i = 0 ; i < 156250 ; i++);
        }
        Counter1++;
        Counter2++;
        if(Counter1 == 10){
            Counter3 = 9;
            Counter4 = 8;
        }
    }
}
