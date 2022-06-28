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
#include <avr/io.h>
#include <avr/interrupt.h>

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
    // E2213HS091_DrawBmp(0,50,104,41,BLACK,WHITE,BmpImage);		// width=104, heigh=41
    E2213HS091_ShowCharStr(0,100,"UID:5572380",FONT_1608,BLACK,WHITE);  
    E2213HS091_ShowCharStr(20,116,"Designed",FONT_1608,BLACK,WHITE);
    E2213HS091_ShowCharStr(44,132,"By",FONT_1608,BLACK,WHITE);
    E2213HS091_ShowCharStr(40,148,"szongen",FONT_1608,BLACK,WHITE);
    E2213HS091_SendImageData();
    E2213HS091_SendUpdateCmd();
    E2213HS091_TurnOffDCDC();
}

void showLogo() {
	E2213HS091_SetHYBELogoFrame();
	E2213HS091_SendImageData();
    E2213HS091_SendUpdateCmd();
    // E2213HS091_TurnOffDCDC();
	return;
}

void example_text() {
    E2213HS091_ClearFullScreen(BLACK);
    E2213HS091_DrawLine(0,1,212,HORIZONTAL,WHITE);
	E2213HS091_DrawLine(0,3,212,HORIZONTAL,WHITE);	
    E2213HS091_ShowCharStr(0,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",FONT_1608,WHITE,BLACK);
    E2213HS091_ShowCharStr(0,30,"01234567890",FONT_1608,WHITE,BLACK);
    E2213HS091_ShowCharStr(0,50,"!@#$^&*()~:;",FONT_1608,WHITE,BLACK);
    E2213HS091_DrawLine(0,99,212,HORIZONTAL,WHITE);
	E2213HS091_DrawLine(0,101,212,HORIZONTAL,WHITE);
    E2213HS091_SendImageData();
    E2213HS091_SendUpdateCmd();
    E2213HS091_TurnOffDCDC();
}

volatile unsigned char rx;

/* 초기화 참고 : https://wowon.tistory.com/75 */
void UART0_init() {	// 0번 수신 (PC->)
	UCSR0A = 0x00;

	// RXCIE0: 수신완료 인터럽트 허용비트.
	// RXEN0 : 수신 허용 비트.
	UCSR0B |= (1<<RXCIE0) | (1<<RXEN0);

	// 비동기, 페리티=none, stop=1bit,  data=8비트 사용
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);

	// 9600 보율
	UBRR0H = 0x00;	
	UBRR0L = 103;
}

void UART1_init() {	// 1번 송신 (->RF MCU)
	UCSR1A = 0x00;
	
	// TXEN1 : 송신 허용 비트
	UCSR1B |= (1<<TXEN1);
	
	// 비동기, 페리티=none, stop=1bit,  data=8비트 사용
	UCSR1C |= (1<<UCSZ11) | (1<<UCSZ10);

	// 9600 보율
	UBRR1H = 0x00;
	UBRR1L = 103;
}

void UART_Init() {
	UART0_init();	// (PC -> )
	UART1_init();	// ( -> RF MCU)
	SREG = 0x80; 	// 인터럽트 활성화
}

/* 0번 UART에서 데이터를 받으면 1번 UART 송신 인터럽트를 활성화 하여 받은 데이터를 바이페스 합니다. */
ISR(USART0_RX_vect)	{  // UART0 수신완료 인터럽트
	rx = UDR0;
	UCSR1B |= (1<<UDRIE1);	// 송신 준비완료 인터럽트 인에이블 비트 Set
}

ISR(USART1_UDRE_vect) {	 // UART1 송신 준비완료 인터럽트
	UDR1 = rx;
	UCSR1B &= ~(1<<UDRIE1);  // 송신 준비완료 인터럽트 인에이블 비트 Clear
}

/* 임의 데이터 전송해야 할 때 사용, 만약 사용할 경우 인터럽트 인에이블 비트 Clear 후 사용. */
void UART1_PutChar(char data) {
	while ((UCSR1A &(1<<UDRE)) == 0);
	UDR1 = data;	
}
void UART1_PutStream(char *stream, int len) {
	while (len > 0) {
		UART1_PutChar(*stream++);
		len--;
	}
}

int main(void)
{
	/* Init */
    init_spi_master();
    init_GPIO();
	E2213HS091_Init();
	
	UART_Init();

	/* Loop */
	while (1)
	{
		showLogo();
		HAL_Delay(3000);
		example_text();
		HAL_Delay(3000);
		E2213HS091_ReverseFrame();
    	E2213HS091_SendImageData();
    	E2213HS091_SendUpdateCmd();
    	E2213HS091_TurnOffDCDC();
		HAL_Delay(3000);
	}
}
