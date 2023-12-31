#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"RCC_interface.h"
#include	"RCC_private.h"
#include	"RCC_config.h"

void		RCC_voidSysClkInt(void)
{
  #if RCC_SYS_CLK == RCC_PLL
    
	#if PLL_CLK  ==  PLL_HSE
	SET_BIT(RCC_CFGR , RCC_CFGR_PLLSRC) ;
	#if  PLL_PRE  ==  x1
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x2
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE) ;
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x3
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE) ;
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x4
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE) ;
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x5
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE) ;
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#else  #warning  "wrong choose PLL  prescaler"
	#endif 
	#elif PLL_CLK  ==  PLL_HSI
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLSRC) ;
	#if  PLL_PRE  ==  x1
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x2
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
	    SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x3
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x4
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x5
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#else  #warning  "wrong choose PLL  prescaler"
	#endif 
	#else 
		#error "Error wrong choose PLL CLK "
	#endif 
	
	SET_BIT(RCC_CR , RCC_CR_PLLON) ;
	while(!GET_BIT(RCC_CR , RCC_CR_PLLRDY))	;
	
	CLR_BIT(RCC_CFGR , RCC_CFGR_SW0);
	SET_BIT(RCC_CFGR , RCC_CFGR_SW1);
	
	#elif RCC_SYS_CLK == RCC_HSI 
	SET_BIT(RCC_CR , RCC_CR_HSION) ;
    while(!GET_BIT(RCC_CR , RCC_CR_HSIRDY))	;
	
	CLR_BIT(RCC_CFGR , RCC_CFGR_SW0);
	CLR_BIT(RCC_CFGR , RCC_CFGR_SW1);
	
	#elif RCC_SYS_CLK == RCC_HSE
	SET_BIT(RCC_CR , RCC_CR_HSEON) ;
    while(!GET_BIT(RCC_CR , RCC_CR_HSERDY))	;
	
	#if  HSE_BYP   == ON   
	 SET_BIT(RCC_CR, RCC_CR_HSEBYP) ;
	 #elif  HSE_BYP == OFF   
	 CLR_BIT(RCC_CR, RCC_CR_HSEBYP) ;
	 #else  
         #error  "error wrong choose bypass fillter"
    #endif	 
	SET_BIT(RCC_CFGR , RCC_CFGR_SW0);
	CLR_BIT(RCC_CFGR , RCC_CFGR_SW1);
	#else   
		#error "Error wrong choose CLK system"
	#endif

    #if     MCO == NO_CLK     
	CLR_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	CLR_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	CLR_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	
    #elif 	MCO == SYS_CLK
	CLR_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	CLR_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	#elif 	MCO == HSI_CLK
	SET_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	CLR_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	#elif 	MCO == HSE_CLK 
	CLR_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	#elif 	MCO == PLL_CLK_DEV2
	SET_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	#else 
		#error "wrong choose MCO "
	#endif 
     
}
void		RCC_voidEnablePerClk(u8 BusId , u8 PerId)
{
	/*		Range Check							*/
	if(PerId < 32)
	{
		switch(BusId)
		{
			case	RCC_AHB		:	SET_BIT(RCC_AHBENR,PerId) ;	break;
			case	RCC_APB1	:	SET_BIT(RCC_APB1ENR,PerId);	break;
			case	RCC_APB2	:	SET_BIT(RCC_APB2ENR,PerId);	break;
		}
		
	}
	else{	/*	Return Error "Out Of The Range"		*/	}
	
}
void		RCC_voidDisablePerClk(u8 BusId , u8 PerId)
{
	/*		Range Check							*/
	if(PerId < 32)
	{
		switch(BusId)
		{
			case	RCC_AHB		:	CLR_BIT(RCC_AHBENR,PerId) ;	break;
			case	RCC_APB1	:	CLR_BIT(RCC_APB1ENR,PerId);	break;
			case	RCC_APB2	:	CLR_BIT(RCC_APB2ENR,PerId);	break;
		}
		
	}
	else{	/*	Return Error "Out Of The Range"		*/	}	

#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"RCC_interface.h"
#include	"RCC_private.h"
#include	"RCC_config.h"

void		RCC_voidSysClkInt(void)
{
  #if RCC_SYS_CLK == RCC_PLL
    
	#if PLL_CLK  ==  PLL_HSE
	SET_BIT(RCC_CFGR , RCC_CFGR_PLLSRC) ;
	#if  PLL_PRE  ==  x1
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x2
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE) ;
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x3
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE) ;
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x4
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE) ;
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x5
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLXTPRE) ;
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#else  #warning  "wrong choose PLL  prescaler"
	#endif 
	#elif PLL_CLK  ==  PLL_HSI
	CLR_BIT(RCC_CFGR , RCC_CFGR_PLLSRC) ;
	#if  PLL_PRE  ==  x1
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x2
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
	    SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
	    CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x3
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x4
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#elif PLL_PRE ==  x5
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL1);
		CLR_BIT(RCC_CFGR , RCC_CFGR_PLLMUL2);
		SET_BIT(RCC_CFGR , RCC_CFGR_PLLMUL3);
	#else  #warning  "wrong choose PLL  prescaler"
	#endif 
	#else 
		#error "Error wrong choose PLL CLK "
	#endif 
	
	SET_BIT(RCC_CR , RCC_CR_PLLON) ;
	while(!GET_BIT(RCC_CR , RCC_CR_PLLRDY))	;
	
	CLR_BIT(RCC_CFGR , RCC_CFGR_SW0);
	SET_BIT(RCC_CFGR , RCC_CFGR_SW1);
	
	#elif RCC_SYS_CLK == RCC_HSI 
	SET_BIT(RCC_CR , RCC_CR_HSION) ;
    while(!GET_BIT(RCC_CR , RCC_CR_HSIRDY))	;
	
	CLR_BIT(RCC_CFGR , RCC_CFGR_SW0);
	CLR_BIT(RCC_CFGR , RCC_CFGR_SW1);
	
	#elif RCC_SYS_CLK == RCC_HSE
	SET_BIT(RCC_CR , RCC_CR_HSEON) ;
    while(!GET_BIT(RCC_CR , RCC_CR_HSERDY))	;
	
	#if  HSE_BYP   == ON   
	 SET_BIT(RCC_CR, RCC_CR_HSEBYP) ;
	 #elif  HSE_BYP == OFF   
	 CLR_BIT(RCC_CR, RCC_CR_HSEBYP) ;
	 #else  
         #error  "error wrong choose bypass fillter"
    #endif	 
	SET_BIT(RCC_CFGR , RCC_CFGR_SW0);
	CLR_BIT(RCC_CFGR , RCC_CFGR_SW1);
	#else   
		#error "Error wrong choose CLK system"
	#endif

    #if     MCO == NO_CLK     
	CLR_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	CLR_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	CLR_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	
    #elif 	MCO == SYS_CLK
	CLR_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	CLR_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	#elif 	MCO == HSI_CLK
	SET_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	CLR_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	#elif 	MCO == HSE_CLK 
	CLR_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	#elif 	MCO == PLL_CLK_DEV2
	SET_BIT(RCC_CFGR,RCC_CFGR_MCO) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC1) ;
	SET_BIT(RCC_CFGR,RCC_CFGR_MC2) ;
	#else 
		#error "wrong choose MCO "
	#endif 
     
}
void		RCC_voidEnablePerClk(u8 BusId , u8 PerId)
{
	/*		Range Check							*/
	if(PerId < 32)
	{
		switch(BusId)
		{
			case	RCC_AHB		:	SET_BIT(RCC_AHBENR,PerId) ;	break;
			case	RCC_APB1	:	SET_BIT(RCC_APB1ENR,PerId);	break;
			case	RCC_APB2	:	SET_BIT(RCC_APB2ENR,PerId);	break;
		}
		
	}
	else{	/*	Return Error "Out Of The Range"		*/	}
	
}
void		RCC_voidDisablePerClk(u8 BusId , u8 PerId)
{
	/*		Range Check							*/
	if(PerId < 32)
	{
		switch(BusId)
		{
			case	RCC_AHB		:	CLR_BIT(RCC_AHBENR,PerId) ;	break;
			case	RCC_APB1	:	CLR_BIT(RCC_APB1ENR,PerId);	break;
			case	RCC_APB2	:	CLR_BIT(RCC_APB2ENR,PerId);	break;
		}
		
	}
	else{	/*	Return Error "Out Of The Range"		*/	}	

}