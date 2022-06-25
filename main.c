/*
 * avrMCU.c
 *
 * Created: 2022-06-07 오후 10:04:16
 * Author : YS
 */ 

#include "main.h"
#include "util/delay.h"
#include "Appication/HardDrivers/E2213HS091.h"
#include "Appication/HardDrivers/image.h"

void HAL_Delay_us(uint32_t _us) {
	while (0 < _us)
	{
		_delay_us(1);
		--_us;
	}
}

void HAL_Delay(uint32_t Delay) {
	while (0 < Delay)
	{
		_delay_ms(1);
		--Delay;
	}
}

 void init_spi_master() {

    // SPI_DDR |= (1 << SS);	
	// SPI_DDR |= (1 << MOSI);
	// SPI_DDR |= (1 << SCK);
	// SPI_DDR = 0x0B;
	SPI_DDR = 0x83;
	CLR_CLK;
	CLR_DAT;
 }

 void init_GPIO() {
    // LCD_DDR &= ~(1 << LCD_BUSY);   // input
	// LCD_DDR |= (1 << LCD_DC);     // output
	// LCD_DDR |= (1 << LCD_RST); 
	// LCD_DDR |= (1 << LCD_BS);
	// LCD_DDR = 0xD1;		// 1101_0001
	LCD_DDR = 0xD0;		// 1101_0001

    LCD_BS_Port &= ~LCD_BS; // BS pin Clear.

	/*  */
	setPin_DC(1);
	setPin_RST(1);
	setPin_CS(1);
 }

void spiTransferByte_c(unsigned char data)
{	
	CLR_CLK;asm("nop");
	if (data&128) SET_DAT; else CLR_DAT;
	SET_CLK;
	asm("nop");

	CLR_CLK;asm("nop");
	if (data&64) SET_DAT; else CLR_DAT;
	SET_CLK;
	asm("nop");

	CLR_CLK;asm("nop");
	if (data&32) SET_DAT; else CLR_DAT;
	SET_CLK;
	asm("nop");

	CLR_CLK;asm("nop");
	if (data&16) SET_DAT; else CLR_DAT;
	SET_CLK;
	asm("nop");

	CLR_CLK;asm("nop");
	if (data&8) SET_DAT; else CLR_DAT;
	SET_CLK;
	asm("nop");

	CLR_CLK;asm("nop");
	if (data&4) SET_DAT; else CLR_DAT;
	SET_CLK;
	asm("nop");

	CLR_CLK;asm("nop");
	if (data&2) SET_DAT; else CLR_DAT;
	SET_CLK;
	asm("nop");

	CLR_CLK;asm("nop");
	if (data&1) SET_DAT; else CLR_DAT;
	SET_CLK;
	asm("nop");
	
	CLR_CLK;

	data=0;
}

void SPI_master_write(uint8_t data) {
    spiTransferByte_c(data);
}

void setPin_CS(int set) {
    if (set)
        SPI_PORT |= SS;
    else
        SPI_PORT &= ~SS;
}
void setPin_DC(int set) {
    if (set)
        LCD_DC_Port |= LCD_DC;
    else
        LCD_DC_Port &= ~LCD_DC;
}
void setPin_RST(int set) {		// 네거티브니까 0으로 해야 리셋
    if (set)
        LCD_RST_Port |= LCD_RST;
    else
        LCD_RST_Port &= ~LCD_RST;
}
int readPin_BUSY() {
	if ((LCD_BUSY_Pin & LCD_BUSY) == LCD_BUSY)
		return HIGH;
	else
		return LOW;
}

void example() {
    // HAL_Delay(50);
    // E2213HS091_Init();		// ok
    /* 显示图片测试 */
    // E2213HS091_DrawImage(0,0,104,212,gImage_1);
    E2213HS091_ClearFullScreen(BLACK);
    E2213HS091_SendImageData();
    E2213HS091_SendUpdateCmd();
    E2213HS091_TurnOffDCDC();
    HAL_Delay(1000);
    /* 显示点�?�线、矩形�?�字符�?�bpm图片测试 */
    E2213HS091_ClearFullScreen(WHITE);
    E2213HS091_DrawPoint(0,0,BLACK);
    E2213HS091_DrawLine(0,2,10,HORIZONTAL,BLACK);
    E2213HS091_DrawLine(0,3,215,HORIZONTAL,BLACK);
    E2213HS091_DrawLine(0,4,10,VERTICAL,BLACK);    
    E2213HS091_DrawRectangle(0,16,10,10,SOLID,BLACK,WHITE);   
    E2213HS091_DrawRectangle(20,16,10,10,HOLLOW,BLACK,WHITE);          
    E2213HS091_ShowCharStr(0,30,"FONT TEST",FONT_1608,BLACK,WHITE);
    E2213HS091_ShowCharStr(0,30,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",FONT_1608,BLACK,WHITE);
    E2213HS091_DrawBmp(0,50,104,41,BLACK,WHITE,BmpImage);		// width=104, heigh=41
    E2213HS091_ShowCharStr(0,100,"UID:5572380",FONT_1608,BLACK,WHITE);  
    E2213HS091_ShowCharStr(20,116,"Designed",FONT_1608,BLACK,WHITE);
    E2213HS091_ShowCharStr(44,132,"By",FONT_1608,BLACK,WHITE);
    E2213HS091_ShowCharStr(40,148,"szongen",FONT_1608,BLACK,WHITE);
    E2213HS091_SendImageData();
    E2213HS091_SendUpdateCmd();
    E2213HS091_TurnOffDCDC();
}

int main(void)
{
	/* 테스트 */
	// LCD_DDR = ~LCD_BUSY;
	// while(1) {
	// 	LCD_BUSY_Port = LCD_BUSY;
	// 	HAL_Delay(1000);
	// 	LCD_BUSY_Port = 0x00;
	// 	HAL_Delay(1000);
	// }
	
    /* 본 코드 */
    init_spi_master();
    init_GPIO();	
	E2213HS091_Init();

	// while(1) {
	// 	SET_CLK;
	// 	SET_DAT;
	// 	HAL_Delay(3000);
	// 	CLR_CLK;
	// 	CLR_DAT;
	// 	HAL_Delay(3000);
	// }

	example();
	while (1)
	{
		;
	}
	
	DDRA = 0xFF;
    while (1) 
    {
	    PORTA = 0xFF;
		E2213HS091_ClearFullScreen(BLACK);
		E2213HS091_SendImageData();

		E2213HS091_SendUpdateCmd();
		// E2213HS091_TurnOffDCDC();
		HAL_Delay(3000);
		
		PORTA = 0x00;
		E2213HS091_ClearFullScreen(WHITE);
		E2213HS091_SendImageData();
		
		E2213HS091_SendUpdateCmd();
		// E2213HS091_TurnOffDCDC();
	    HAL_Delay(3000);
    }
}

