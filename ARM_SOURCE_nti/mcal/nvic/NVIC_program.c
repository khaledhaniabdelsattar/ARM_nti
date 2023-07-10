#include	"stdTypes.h"
//#include	"Bit_Math.h"



#include	"NVIC_config.h"
#include	"NVIC_private.h"

// delay function
void _delay_ms(u32 ticks)
{
	u32 i;
	for( i = 0; i < (ticks * 500) ; i++)
		{
			asm("NOP");
		}
}



void		NVIC_voidInit()
{
	/*		How many Groups and Sub Group used in the system  //dh peripheral tani 5ales mafrod na3mlo driver w ma7tagen nst5dmo f bsor3a mmkn na3ml kda	*/
	#ifndef			SCB_AIRCR
		#define		SCB_BASE_ADD		(0xE000ED00)
		#define		SCB_AIRCR			*((u32 *)(SCB_BASE_ADD+0x0C))
	#endif

	SCB_AIRCR = NVIC_NUM_GRP_SUB;
}


/*IntNum refer to number of interrrupts you have and you know them from vector table of medium STMF103C8C6"they are 59 so we need about 64 bits"*/
void		NVIC_voidEnablePerInt(u8 IntNum)
{
	/*		Range Check			*/
	if(IntNum<32) // because we have different registers every one  cosists of 32 bits only
	{
		//SET_BIT(NVIC_ISER0,IntNum); Read Modify Write
		NVIC_ISER0 = (1 << IntNum) ; //write only as we have register for set and another register for clear

	}else if(IntNum<64)
	{
		IntNum -= 32;
		NVIC_ISER1 = (1 << IntNum) ; //write only
	}

}

void		NVIC_voidDisablePerInt(u8 IntNum)
{
	/*		Range Check			*/
	if(IntNum<32)
	{
		NVIC_ICER0 = (1 << IntNum) ;

	}else if(IntNum<64)
	{
		IntNum -= 32;
		NVIC_ICER1 = (1 << IntNum) ;
	}

}

void		NVIC_voidSetPendingFlag(u8 IntNum)
{
	/*		Range Check			*/
	if(IntNum<32)
	{
		NVIC_ISPR0 = (1 << IntNum) ;

	}else if(IntNum<64)
	{
		IntNum -= 32;
		NVIC_ISPR1 = (1 << IntNum) ;
	}

}

void		NVIC_voidClrPendingFlag(u8 IntNum)
{
	/*		Range Check			*/
	if(IntNum<32)
	{
		NVIC_ICPR0 = (1 << IntNum) ;

	}else if(IntNum<64)
	{
		IntNum -= 32;
		NVIC_ICPR1 = (1 << IntNum) ;
	}

}


u8			NVIC_u8ReadActiveFlag(u8 IntNum)
{
	u8	Local_u8ActiveFlg = 0x55 ; //any value except 0 and 1 as error check
	/*		Range Check			*/
	if(IntNum<32)
	{
		Local_u8ActiveFlg = GET_BIT(NVIC_IABR0,IntNum);

	}else if(IntNum<64)
	{
		IntNum -= 32;
		Local_u8ActiveFlg = GET_BIT(NVIC_IABR1,IntNum);
	}
	return	Local_u8ActiveFlg;
}

/*		4 Groups and 4 sub Groups , EXTI0 int Num = 6 ===> Group = 1, Sub = 2 	*/
/*NVIC_voidSetSwIntPriority(6,0b0110);*/

void		NVIC_voidSetSwIntPriority(u8 IntNum , u8 priority)
{

	/*		Range Check			*/
	if(IntNum<32)
	{
		NVIC_IPR[IntNum] &= ~(0b1111 <<4);
		NVIC_IPR[IntNum] |= (priority << 4);
	}

	else if(IntNum<64)
	{
		IntNum -= 32;
		NVIC_IPR[IntNum] &= ~(0b1111 <<4);
		NVIC_IPR[IntNum] |= (priority << 4);
	}


}








