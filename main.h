/*
 * main.h
 *
 * Created: 2022-06-07 오후 10:30:57
 *  Author: YS
 *  brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>

//0. Clock - 외부 크리스탈과 동일한 값 정의홤.
#define F_CPU 16000000UL    // 16MHz

 //1. baud rate를 선택
#define USART_BAUDRATE 9600
 
 //2.시스템 클록과 원하는 baud rate를 이용하여 UBRR 값을 계산한다.
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// 기본 SPI 핀
#define SPI_DDR DDRB        // Data Direction, 데이터 방향 레지스터
#define SPI_PORT PORTB      // SPI Port
#define SPI_PIN PINB        // Pin Address, 핀 주소, 값 읽어올때 사용
#define SS 0x01            // SlaveSelect(Chip Select)
#define SCK 0x02           // Clock
#define MOSI 0x04          // MasterOut
#define MISO 0x08          // MasterInput

// 추가 핀
#define SPI_DC_Pin 0x10
#define SPI_DC_Port PORTB
#define SPI_BUSY_Pin 0x20
#define SPI_BUSY_Port PORTB
#define SPI_RST_Pin 0x40            
#define SPI_RST_Port PORTB
#define SPI_BS_Pin 0x80
#define SPI_BS_Port PORTB

  

// #define DI_SCREEN_BUSY_Pin GPIO_PIN_1   // BUSY GPIO의 핀 (BUSY)        : Busy
// #define DI_SCREEN_BUSY_GPIO_Port GPIOA  // BUSY GPIO의 포트
// #define DO_SCREEN_DC_Pin GPIO_PIN_2     // DC   GPIO의 핀 (DC)          : Data/Command Control
// #define DO_SCREEN_DC_GPIO_Port GPIOA    // DC   GPIO의 포트
// #define DO_SCREEN_RST_Pin GPIO_PIN_3    // RST  GPIO의 핀 (RST, RST)    : Reset
// #define DO_SCREEN_RST_GPIO_Port GPIOA   // RST  GPIO의 포트
// #define DO_SCREEN_CS_Pin GPIO_PIN_4     // CS   GPIO의 핀 (CSB, SCS)    : Chip Select
// #define DO_SCREEN_CS_GPIO_Port GPIOA    // CS   GPIO의 포트
// #define DO_SCREEN_CLK_Pin GPIO_PIN_5    // CLK  GPIO의 핀 (SCL, SCLK)   : Clock(SPI)
// #define DO_SCREEN_CLK_GPIO_Port GPIOA   // CLK  GPIO의 포트 
// #define MO_SCREEN_MOSI_Pin GPIO_PIN_7   // MOSI GPIO의 핀 (SDA, SI)     : Data(SPI)
// #define MO_SCREEN_MOSI_GPIO_Port GPIOA  // MOSI GPIO의 포트 


/**
 * @brief Do delay
 */
void HAL_Delay(uint32_t Delay);


/**
 * @brief SPI Init
 */
void init_spi_master();

/**
 * @brief SPI로 데이터 전송함
 */
void SPI_master_write(uint8_t data);

/**
 * @brief Set/Clear ChipSelect pin
 */
void setPin_CS(int set);
/**
 * @brief Set/Clear Data/Command Control pin
 */
void setPin_DC(int set);
/**
 * @brief Set/Clear Reset pin
 */
void setPin_RST(int set);
/**
 * @brief Read Busy Pin
 */
int readPin_BUSY();


#endif /* MAIN_H_ */