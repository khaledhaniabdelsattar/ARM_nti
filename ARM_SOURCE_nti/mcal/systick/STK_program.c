#include	"stdTypes.h"
#include	"BITMATH.h"

#include	"STK_interface.h"

#include	"STK_config.h"
#include	"STK_private.h"


#ifndef		NULL
#define		NULL		(void *)0
#endif

/*****   Global variable   *****/
u32 global_u32Clk       = 0 ;
u8  Global_u8SingleFlag = 0 ;
static void (* functionCallBack)(void) = NULL;


void STK_voidInit(void)
{
	/*  choosing clk for the SysTick  */
	#if   STK_CLK_SOURCE  ==  AHB
		SET_BIT (STK->CTRL , STK_CTRL_CLKSOURCE);
		global_u32Clk = STK_AHB_CLK ;

	#elif STK_CLK_SOURCE  ==  AHB_BY_8
		CLR_BIT (STK->CTRL , STK_CTRL_CLKSOURCE);
		global_u32Clk = STK_AHB_CLK / 8  ;

	#else
		#error (" configuration error")
	#endif
}

void STK_voidSetBusyWait( u32 Copy_u32Time , STK_time_t copy_unit )
{
	u32 local_u32Load = 0 ;
	STK->VAL = 0 ;
	/* Calculate and load the load value */
	switch (copy_unit){
		case TIME_MS :
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000) ;
			STK->LOAD     = local_u32Load ;
			break;

		case TIME_US :
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000000) ;
			STK->LOAD     = local_u32Load ;
			break ;
		default :    /* Should not be here */      break;
	}

	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);

	/* Wait for the flag */
	while ( !(GET_BIT (STK->CTRL , STK_CTRL_COUNTFLAG)));

	/* Stop timer */
	CLR_BIT(STK->CTRL , STK_CTRL_ENABLE);
}
void STK_voidSetIntervalPeriodic( u32 Copy_u32Time , STK_time_t copy_unit, void (*Copy_func)(void)){
	u32 local_u32Load = 0 ;
	STK->VAL = 0 ;
	/* Calculate and load the load value */
	switch (copy_unit){
		case TIME_MS :
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000) ;
			STK->LOAD     = local_u32Load ;
			break;

		case TIME_US :
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000000) ;
			STK->LOAD     = local_u32Load ;
			break ;
		default :    /* Should not be here */      break;
	}

	/* To pass the function to ISR */
	functionCallBack = Copy_func ;

	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);

	/* Enable STK interrupt */
	SET_BIT(STK->CTRL , STK_CTRL_TICKINT);
}

void STK_voidSetIntervalSingle( u32 Copy_u32Time , STK_time_t copy_unit, void (*Copy_func)(void)){
	u32 local_u32Load = 0 ;
	CLEAR_BIT(STK->CTRL , STK_CTRL_ENABLE);
	STK->VAL = 0 ;
	/* Calculate and load the load value */
	switch (copy_unit){
		case TIME_MS :
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000) ;
			STK->LOAD     = local_u32Load ;
			break;

		case TIME_US :
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000000) ;
			STK->LOAD     = local_u32Load ;
			break ;
		default :    /* Should not be here */      break;
	}

	/* To pass the function to ISR */
	functionCallBack = Copy_func ;

	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);

	/* Enable interrupt */
	SET_BIT(STK->CTRL , STK_CTRL_TICKINT);

	/* Set single flag */
	Global_u8SingleFlag = 1 ;
}

void STK_voidStop(void)
{
	/* Stop timer */
	CLEAR_BIT(STK->CTRL , STK_CTRL_ENABLE);

	/* Disable interrupt */
	CLEAR_BIT(STK->CTRL , STK_CTRL_TICKINT);
}

void STK_voidResume(void)
{
	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);

	/* Enable interrupt */
	SET_BIT(STK->CTRL , STK_CTRL_TICKINT);
}

void STK_voidStart(void)
{
	/* Zero the val rigester */
	STK->VAL = 0 ;

	/* Load value with max value */
	STK->LOAD = 0xFFFFFF;

	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);
}


u32 STK_u32GetElapsedTime(STK_time_t copy_unit)
{
	u32 local_u32Value =  STK->LOAD - STK->VAL ;
	u32 local_u32ElapsedTime = 0 ;
	/* Calculate the elabsed time in ms or us */
	switch (copy_unit){
		case TIME_MS :
			local_u32ElapsedTime = local_u32Value / (global_u32Clk / 1000) ;
			break;

		case TIME_US :
			local_u32ElapsedTime = local_u32Value / (global_u32Clk / 1000000) ;
			break ;
		default :    /* Should not be here */      break;
	}
	return local_u32ElapsedTime ;
}


u32 STK_u32GetRemainingTime(STK_time_t copy_unit)
{
	u32 local_u32Value = STK->VAL ;
	u32 local_u32RemainingTime = 0 ;
	/* Calculate remaining time in ms or us */
	switch (copy_unit){
		case TIME_MS :
			local_u32RemainingTime = local_u32Value / (global_u32Clk / 1000) ;
			break;

		case TIME_US :
			local_u32RemainingTime = local_u32Value / (global_u32Clk / 1000000) ;
			break ;
		default :    /* Should not be here */      break;
	}
	return local_u32RemainingTime ;
}

void SysTick_Handler(void)
{
	/* In case of using single interval*/
	if (Global_u8SingleFlag){
		/* Stop timer */
		CLR_BIT(STK->CTRL , STK_CTRL_ENABLE);
		/* Disable interrupt */
		CLR_BIT(STK->CTRL , STK_CTRL_TICKINT);
	}
	functionCallBack();
}


/*************itt1**************/
//static	void	(*STK_CallBack)	(void)	=	NULL;
//static	u8		STK_u8ModeOfInterval;
//
//void	STK_voidInit()
//{
//		/*		RCC == HSI		*/
//		#if		STK_CLK_SRC	==	STK_AHB_DIV_8
//			STk -> CTRL = 0x00000000;
//		#elif	STK_CLK_SRC	==	STK_AHB
//			STk -> CTRL = 0x00000004;
//		#else	#error	"Wrong choice of SysTick Clock Source!"
//		#endif
//}
//void	STK_voidSetBusyWait(u32	Ticks)
//{
//	/*	Load ticks to Load Register 	*/
//	STK -> LOAD = Ticks;
//	/*	Start the timer 				*/
//	SET_BIT(STK -> CTRL , 0);
//	/*	Wait till the flag is raised 	*/
//	while((GET_BIT(STK -> CTRL , 16 ))==0)
//	{
//		asm("NOP");
//	}
//	/*	Stop the timer					*/
//	CLR_BIT(STK -> CTRL , 0);
//	STK ->	LOAD	=	0;
//	STK ->	VAL		=	0;
//}
//void	STK_voidSetIntervalSingle(u32	Ticks, void (*Pf)(void))
//{
//	/*	Load ticks to Load Register 	*/
//	STK -> LOAD = Ticks;
//	/*	Start the timer 				*/
//	SET_BIT(STK -> CTRL , 0);
//	/*	Save Call Back Function		 	*/
//	STK_CallBack =	Pf;
//	/*	Enable STK Interrupt		 	*/
//	SET_BIT(STK -> CTRL , 1);
//	/*	Set the mode single Intervale	*/
//	STK_u8ModeOfInterval = STK_SINGLE_INTERVAL;
//}
//void	STK_voidSetIntervalPeriodic(u32	Ticks, void (*Pf)(void))
//{
//		/*	Load ticks to Load Register 	*/
//	STK -> LOAD = Ticks;
//	/*	Start the timer 				*/
//	SET_BIT(STK -> CTRL , 0);
//	/*	Save Call Back Function		 	*/
//	STK_CallBack =	Pf;
//	/*	Enable STK Interrupt		 	*/
//	SET_BIT(STK -> CTRL , 1);
//	/*	Set the mode single Intervale	*/
//	STK_u8ModeOfInterval = STK_PERIOD_INTERVAL;
//}
//void	STK_voidStopInterval()
//{
//		/*	Disable The Interrupt			*/
//		CLR_BIT(STK -> CTRL , 1);
//		/*	Stop the timer					*/
//		CLR_BIT(STK -> CTRL , 0);
//		STK ->	LOAD	=	0;
//		STK ->	VAL		=	0;
//}
//u32		STK_u32GetElapsedTime()
//{
//	u32	Local_u32ElapsedTime;
//	Local_u32ElapsedTime	=	((STK -> LOAD)-(STK -> VAL));
//	return	Local_u32ElapsedTime;
//}
//u32		STK_u32GetRemainingTime()
//{
//	u32	Local_u32Remaining;
//	Local_u32Remaining	=	STK -> VAL;
//	return	Local_u32Remaining;
//}
//
//
//void	SysTick_Handler()
//{
//	u8 Local_u8Temp;
//	if(STK_u8ModeOfInterval == STK_SINGLE_INTERVAL)
//	{
//		/*	Disable The Interrupt			*/
//		CLR_BIT(STK -> CTRL , 1);
//		/*	Stop the timer					*/
//		CLR_BIT(STK -> CTRL , 0);
//		STK ->	LOAD	=	0;
//		STK ->	VAL		=	0;
//	}
//	STK_CallBack();
//	/*	to clear the timer flsg just read it */
//	Local_u8Temp	=	GET_BIT(STK -> CTRL,16);
//}





