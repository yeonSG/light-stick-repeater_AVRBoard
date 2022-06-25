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
#define F_CPU 8000000UL    // 8MHz

#define HIGH 1
#define LOW 0

// 기본 SPI 핀
#define SPI_DDR DDRB        // Data Direction, 데이터 방향 레지스터
#define SPI_PORT PORTB      // SPI Port
#define SPI_PIN PINB        // Pin Address, 핀 주소, 값 읽어올때 사용
#define SS 0x01            // SlaveSelect(Chip Select)
#define SCK 0x02           // Clock
#define MOSI 0x80          // MasterOut 

// #define MISO 0x08          // MasterInput * NOTUSE

// 추가 핀
#define LCD_DDR DDRE
#define LCD_DC 0x80
#define LCD_DC_Port PORTE
#define LCD_BUSY 0x20
#define LCD_BUSY_Pin PINE
#define LCD_BUSY_Port PORTE
#define LCD_RST 0x40            
#define LCD_RST_Port PORTE      
#define LCD_BS 0x10
#define LCD_BS_Port PORTE


#define SET_CLK SPI_PORT |= SCK  
#define CLR_CLK SPI_PORT &= ~SCK 
#define SET_DAT SPI_PORT |= MOSI 
#define CLR_DAT SPI_PORT &= ~MOSI


/**
 * @brief Do delay
 */
void HAL_Delay(uint32_t Delay);
void HAL_Delay_us(uint32_t _us);


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