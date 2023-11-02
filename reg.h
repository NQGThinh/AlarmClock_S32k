#define uint32 unsigned int



//#define PCC_base    (0x40065000)
//#define PCC_PORTC   *((volatile uint32*) (PCC_base + 0x12C))
//#define PCC_PORTD   *((volatile uint32*) (PCC_base + 0x130))
//#define PCC_LPUART1 *((volatile uint32*) (PCC_base+0x1AC)) 
//	
/** PCC - Size of Registers Arrays */
#define PCC_PCCn_COUNT                           122u

/** PCC - Register Layout Typedef */
typedef struct {
  volatile unsigned int PCCn[PCC_PCCn_COUNT];              /**< PCC Reserved Register 0..PCC CMP0 Register, array offset: 0x0, array step: 0x4 */
} PCC_Type;


/** Peripheral PCC base address */
#define PCC_base_address                                 (0x40065000u)
/** Peripheral PCC base pointer */
#define PCC                                      ((PCC_Type *)PCC_base_address)


#define PCC_LPSPI0_INDEX                         44
#define PCC_LPSPI1_INDEX                         45
#define PCC_LPSPI2_INDEX                         46
#define PCC_LPIT_INDEX                           55
#define PCC_PORTA_INDEX                          73
#define PCC_PORTB_INDEX                          74
#define PCC_PORTC_INDEX                          75
#define PCC_PORTD_INDEX                          76
#define PCC_PORTE_INDEX                          77
#define PCC_LPUART1_INDEX                        107


typedef struct
{
		volatile unsigned int VERID;
		volatile unsigned int PARAM;
		volatile unsigned int GLOBAL;
		volatile unsigned int PINCFG;
		volatile unsigned int BAUD;
		volatile unsigned int STAT;
		volatile unsigned int CTRL;
		volatile unsigned int DATA;
		volatile unsigned int MATCH;
		volatile unsigned int MODIR;
		volatile unsigned int FIFO;
		volatile unsigned int WATER;
}LPUART_type;

#define LPUART1_base (0x4006B000)
#define LPUART1 ((LPUART_type*) LPUART1_base)


typedef struct 
{
    volatile const unsigned int VERID;                            
    volatile const unsigned int PARAM;
    volatile unsigned int dummy1[2];    
    volatile const unsigned int CSR;                            
    volatile unsigned int RCCR;                              
    volatile unsigned int VCCR;                              
    volatile unsigned int HCCR;                              
    volatile unsigned int CLKOUTCNFG;
    volatile unsigned int dummy2[55];                       
    volatile unsigned int SOSCCSR;                           
    volatile unsigned int SOSCDIV;                           
    volatile unsigned int SOSCCFG;
    volatile unsigned int dummy3[61]; 
    volatile unsigned int SIRCCSR;                           
    volatile unsigned int SIRCDIV;                           
    volatile unsigned int SIRCCFG;  
    volatile unsigned int dummy4[61];
    volatile unsigned int FIRCCSR;                          
    volatile unsigned int FIRCDIV;                          
    volatile unsigned int FIRCCFG;
    volatile unsigned int dummy5[189];
    volatile unsigned int SPLLCSR;                           
    volatile unsigned int SPLLDIV;                           
    volatile unsigned int SPLLCFG;   
}SCG_type;

#define SCG_base (0x40064000)
#define SCG ((SCG_type*) SCG_base)


#define PCR_num 34
typedef struct 
{
    volatile uint32 PCR[PCR_num];
    /* data */
}PORT_type;


#define PORTB_base (0x4004A000u)
#define PORTB ((PORT_type*)  PORTB_base)
#define PORTC_base 0x4004B000
#define PORTC ((PORT_type*)  PORTC_base)
#define PORTD_base 0x4004C000
#define PORTD ((PORT_type*)  PORTD_base)


///* NVIC register */

//#define ISER_COUNT 8
//#define ICER_COUNT 8
//#define ISPR_COUNT 8
//#define ICPR_COUNT 8
//#define IABR_COUNT 8
//#define IPR_COUNT 60

//typedef struct 
//{
//    volatile uint32 ISER[ISER_COUNT];
//    volatile uint32 dummy1[24];
//    volatile uint32 ICER[ICER_COUNT];
//    volatile uint32 dummy2[24];
//    volatile uint32 ISPR[ISPR_COUNT];
//    volatile uint32 dummy3[24];
//    volatile uint32 ICPR[ICPR_COUNT];
//    volatile uint32 dummy4[24];
//    volatile uint32 IABR[IABR_COUNT];
//    volatile uint32 dummy5[56];
//    volatile uint32 IPR[IPR_COUNT];
//    volatile unsigned char dummy6[2573];
//    volatile uint32 STIR;

//}NVIC_type;

//#define NVIC_base (0xE000E100u)
//#define NVIC ((NVIC_type*) NVIC_base)

/** S32_NVIC - Size of Registers Arrays */
#define S32_NVIC_ISER_COUNT                      8u
#define S32_NVIC_ICER_COUNT                      8u
#define S32_NVIC_ISPR_COUNT                      8u
#define S32_NVIC_ICPR_COUNT                      8u
#define S32_NVIC_IABR_COUNT                      8u
#define S32_NVIC_IP_COUNT                        240u

/** S32_NVIC - Register Layout Typedef */
typedef struct {
  volatile unsigned int ISER[S32_NVIC_ISER_COUNT];         /**< Interrupt Set Enable Register n, array offset: 0x0, array step: 0x4 */
					 unsigned int RESERVED_0[24];
  volatile unsigned int ICER[S32_NVIC_ICER_COUNT];         /**< Interrupt Clear Enable Register n, array offset: 0x80, array step: 0x4 */
           unsigned int RESERVED_1[24];
  volatile unsigned int ISPR[S32_NVIC_ISPR_COUNT];         /**< Interrupt Set Pending Register n, array offset: 0x100, array step: 0x4 */
           unsigned int RESERVED_2[24];
  volatile unsigned int ICPR[S32_NVIC_ICPR_COUNT];         /**< Interrupt Clear Pending Register n, array offset: 0x180, array step: 0x4 */
           unsigned int RESERVED_3[24];
  volatile unsigned int IABR[S32_NVIC_IABR_COUNT];         /**< Interrupt Active bit Register n, array offset: 0x200, array step: 0x4 */
       unsigned char RESERVED_4[224];
  volatile unsigned char IP[S32_NVIC_IP_COUNT];              /**< Interrupt Priority Register n, array offset: 0x300, array step: 0x1 */
       unsigned char RESERVED_5[2576];
  volatile  unsigned int STIR;                              /**< Software Trigger Interrupt Register, offset: 0xE00 */
} NVIC_Type;

/* S32_NVIC - Peripheral instance base addresses */
/** Peripheral S32_NVIC base address */
#define NVIC_BASE                            (0xE000E100u)
/** Peripheral S32_NVIC base pointer */
#define NVIC                                 ((NVIC_Type *)NVIC_BASE)

typedef struct
{
    volatile unsigned int PDOR;                              /**< Port Data Output Register, offset: 0x0 */
    volatile  unsigned int PSOR;                             /**< Port Set Output Register, offset: 0x4 */
    volatile  unsigned int PCOR;                             /**< Port Clear Output Register, offset: 0x8 */
    volatile  unsigned int PTOR;                             /**< Port Toggle Output Register, offset: 0xC */
    volatile const  unsigned int PDIR;                       /**< Port Data Input Register, offset: 0x10 */
    volatile unsigned int PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
    volatile unsigned int PIDR;                              /**< Port Input Disable Register, offset: 0x18 */
}GPIO_type;

#define GPIOD_base (0x400FF0C0)
#define GPIOD ((GPIO_type *) (GPIOD_base))
#define GPIOC_base (0x400FF080)
#define GPIOC ((GPIO_type *) (GPIOC_base))

/*---------------------------------*/
/*---------LSPI register----------*/
/*---------------------------------*/
typedef struct {
  volatile const  unsigned int VERID;                             /**< Version ID Register, offset: 0x0 */
  volatile const  unsigned int PARAM;                             /**< Parameter Register, offset: 0x4 */
       unsigned char RESERVED_0[8];
  volatile unsigned int CR;                                /**< Control Register, offset: 0x10 */
  volatile unsigned int SR;                                /**< Status Register, offset: 0x14 */
  volatile unsigned int IER;                               /**< Interrupt Enable Register, offset: 0x18 */
  volatile unsigned int DER;                               /**< DMA Enable Register, offset: 0x1C */
  volatile unsigned int CFGR0;                             /**< Configuration Register 0, offset: 0x20 */
  volatile unsigned int CFGR1;                             /**< Configuration Register 1, offset: 0x24 */
       unsigned char RESERVED_1[8];
  volatile unsigned int DMR0;                              /**< Data Match Register 0, offset: 0x30 */
  volatile unsigned int DMR1;                              /**< Data Match Register 1, offset: 0x34 */
       unsigned char RESERVED_2[8];
  volatile unsigned int CCR;                               /**< Clock Configuration Register, offset: 0x40 */
       unsigned char RESERVED_3[20];
  volatile unsigned int FCR;                               /**< FIFO Control Register, offset: 0x58 */
  volatile const  unsigned int FSR;                               /**< FIFO Status Register, offset: 0x5C */
  volatile unsigned int TCR;                               /**< Transmit Command Register, offset: 0x60 */
  volatile  unsigned int TDR;                               /**< Transmit Data Register, offset: 0x64 */
       unsigned char RESERVED_4[8];
  volatile const  unsigned int RSR;                               /**< Receive Status Register, offset: 0x70 */
  volatile const  unsigned int RDR;                               /**< Receive Data Register, offset: 0x74 */
} LPSPI_Type;
/** Peripheral LPSPI base address */
#define LPSPI0_base_address  (0x4002C000u)
#define LPSPI1_base_address  (0x4002D000u)
#define LPSPI2_base_address  (0x4002E000u)

#define LPSPI0                                   ((LPSPI_Type *)LPSPI0_base_address)
#define LPSPI1                                   ((LPSPI_Type *)LPSPI1_base_address)
#define LPSPI2                                   ((LPSPI_Type *)LPSPI2_base_address)


typedef struct
{
	volatile unsigned int SYST_CSR;
	volatile unsigned int SYST_RVR;
	volatile unsigned int SYST_CVR;
	volatile unsigned int SYST_CALIB;
}SYST_Type;

#define SYST_BASE 0xE000E010
#define SYST  ((SYST_Type *)SYST_BASE)

