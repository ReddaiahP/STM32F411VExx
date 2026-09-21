#define PERIPH_BASE       0x40000000UL
#define APB1PERIPH_BASE   0x40000000UL
#define APB2PERIPH_BASE   0x40010000UL
#define AHB1PERIPH_BASE   0x40020000UL
#define AHB2PERIPH_BASE   0x50000000UL


#define GPIOA_BASE    (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE    (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE    (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE    (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE    (AHB1PERIPH_BASE + 0x1000UL)
#define RCC_BASE      (AHB1PERIPH_BASE + 0x3800UL)

typedef struct{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
}GPIO_Reg_Def_t;


#define GPIOA ((volatile GPIO_Reg_Def_t *)GPIOA_BASE)
#define GPIOB ((volatile GPIO_Reg_Def_t *)GPIOB_BASE)
#define GPIOC ((volatile GPIO_Reg_Def_t *)GPIOC_BASE)
#define GPIOD ((volatile GPIO_Reg_Def_t *)GPIOD_BASE)
#define GPIOE ((volatile GPIO_Reg_Def_t *)GPIOE_BASE)

#define RCC   ((volatile Rcc_Reg_Def_t *)RCC_BASE)



typedef struct
{
    volatile uint32_t CR;           // 0x00
    volatile uint32_t PLLCFGR;      // 0x04
    volatile uint32_t CFGR;         // 0x08
    volatile uint32_t CIR;          // 0x0C

    volatile uint32_t AHB1RSTR;     // 0x10
    volatile uint32_t AHB2RSTR;     // 0x14

    volatile uint32_t RESV0[2];     // 0x18, 0x1C

    volatile uint32_t APB1RSTR;     // 0x20
    volatile uint32_t APB2RSTR;     // 0x24

    volatile uint32_t RESV1[2];     // 0x28, 0x2C

    volatile uint32_t AHB1ENR;      // 0x30
    volatile uint32_t AHB2ENR;      // 0x34

    volatile uint32_t RESV2[2];     // 0x38, 0x3C

    volatile uint32_t APB1ENR;      // 0x40
    volatile uint32_t APB2ENR;      // 0x44

    volatile uint32_t RESV3[2];     // 0x48, 0x4C

    volatile uint32_t AHB1LPENR;    // 0x50
    volatile uint32_t AHB2LPENR;    // 0x54

    volatile uint32_t RESV4[2];     // 0x58, 0x5C

    volatile uint32_t APB1LPENR;    // 0x60
    volatile uint32_t APB2LPENR;    // 0x64

    volatile uint32_t RESV5[2];     // 0x68, 0x6C

    volatile uint32_t BDCR;         // 0x70
    volatile uint32_t CSR;          // 0x74

    volatile uint32_t RESV6[2];     // 0x78, 0x7C

    volatile uint32_t SSCGR;        // 0x80
    volatile uint32_t PLLI2SCFGR;   // 0x84

    volatile uint32_t RESV7;        // 0x88
    volatile uint32_t DCKCFGR;      // 0x8C

} Rcc_Reg_Def_t;


//offsetof(Rcc_Reg_Def_t, AHB1ENR) later for reference