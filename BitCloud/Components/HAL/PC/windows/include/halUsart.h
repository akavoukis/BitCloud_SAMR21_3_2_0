/*****************************************************************************//**
\file  halUsart.h

\brief Declarations of usart hardware-dependent module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    06/08/12 N. Fomin - Created
**********************************************************************************/
#ifndef _HAL_USART_H
#define _HAL_USART_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysTypes.h>
#include <Windows.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define USART_CHANNEL_FAKE 1

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct
{
  volatile uint16_t rxPointOfRead;
  volatile uint16_t rxPointOfWrite;
  volatile uint16_t rxBytesInBuffer;
} HalUsartService_t;

typedef enum
{
  COM1   = 1,
  COM2   = 2,
  COM3   = 3,
  COM4   = 4,
  COM5   = 5,
  COM6   = 6,
  COM7   = 7,
  COM8   = 8,
  COM9   = 9,
  COM10  = 10,
  COM11  = 11,
  COM12  = 12,
  COM13  = 13,
  COM14  = 14,
  COM15  = 15,
  COM16  = 16,
  COM17  = 17,
  COM18  = 18,
  COM19  = 19,
  COM20  = 20,
  COM21  = 21,
  COM22  = 22,
  COM23  = 23,
  COM24  = 24,
  COM25  = 25,
  COM26  = 26,
  COM27  = 27,
  COM28  = 28,
  COM29  = 29,
  COM30  = 30,
  COM31  = 31,
  COM32  = 32,
  COM33  = 33,
  COM34  = 34,
  COM35  = 35,
  COM36  = 36,
  COM37  = 37,
  COM38  = 38,
  COM39  = 39,
  COM40  = 40,
  COM41  = 41,
  COM42  = 42,
  COM43  = 43,
  COM44  = 44,
  COM45  = 45,
  COM46  = 46,
  COM47  = 47,
  COM48  = 48,
  COM49  = 49,
  COM50  = 50,
  COM51  = 51,
  COM52  = 52,
  COM53  = 53,
  COM54  = 54,
  COM55  = 55,
  COM56  = 56,
  COM57  = 57,
  COM58  = 58,
  COM59  = 59,
  COM60  = 60,
  COM61  = 61,
  COM62  = 62,
  COM63  = 63,
  COM64  = 64,
  COM65  = 65,
  COM66  = 66,
  COM67  = 67,
  COM68  = 68,
  COM69  = 69,
  COM70  = 70,
  COM71  = 71,
  COM72  = 72,
  COM73  = 73,
  COM74  = 74,
  COM75  = 75,
  COM76  = 76,
  COM77  = 77,
  COM78  = 78,
  COM79  = 79,
  COM80  = 80,
  COM81  = 81,
  COM82  = 82,
  COM83  = 83,
  COM84  = 84,
  COM85  = 85,
  COM86  = 86,
  COM87  = 87,
  COM88  = 88,
  COM89  = 89,
  COM90  = 90,
  COM91  = 91,
  COM92  = 92,
  COM93  = 93,
  COM94  = 94,
  COM95  = 95,
  COM96  = 96,
  COM97  = 97,
  COM98  = 98,
  COM99  = 99,
  COM100 = 100,
  COM101 = 101,
  COM102 = 102,
  COM103 = 103,
  COM104 = 104,
  COM105 = 105,
  COM106 = 106,
  COM107 = 107,
  COM108 = 108,
  COM109 = 109,
  COM110 = 110,
  COM111 = 111,
  COM112 = 112,
  COM113 = 113,
  COM114 = 114,
  COM115 = 115,
  COM116 = 116,
  COM117 = 117,
  COM118 = 118,
  COM119 = 119,
  COM120 = 120,
  COM121 = 121,
  COM122 = 122,
  COM123 = 123,
  COM124 = 124,
  COM125 = 125,
  COM126 = 126,
  COM127 = 127,
  COM128 = 128,
  COM129 = 129,
  COM130 = 130,
  COM131 = 131,
  COM132 = 132,
  COM133 = 133,
  COM134 = 134,
  COM135 = 135,
  COM136 = 136,
  COM137 = 137,
  COM138 = 138,
  COM139 = 139,
  COM140 = 140,
  COM141 = 141,
  COM142 = 142,
  COM143 = 143,
  COM144 = 144,
  COM145 = 145,
  COM146 = 146,
  COM147 = 147,
  COM148 = 148,
  COM149 = 149,
  COM150 = 150,
  COM151 = 151,
  COM152 = 152,
  COM153 = 153,
  COM154 = 154,
  COM155 = 155,
  COM156 = 156,
  COM157 = 157,
  COM158 = 158,
  COM159 = 159,
  COM160 = 160,
  COM161 = 161,
  COM162 = 162,
  COM163 = 163,
  COM164 = 164,
  COM165 = 165,
  COM166 = 166,
  COM167 = 167,
  COM168 = 168,
  COM169 = 169,
  COM170 = 170,
  COM171 = 171,
  COM172 = 172,
  COM173 = 173,
  COM174 = 174,
  COM175 = 175,
  COM176 = 176,
  COM177 = 177,
  COM178 = 178,
  COM179 = 179,
  COM180 = 180,
  COM181 = 181,
  COM182 = 182,
  COM183 = 183,
  COM184 = 184,
  COM185 = 185,
  COM186 = 186,
  COM187 = 187,
  COM188 = 188,
  COM189 = 189,
  COM190 = 190,
  COM191 = 191,
  COM192 = 192,
  COM193 = 193,
  COM194 = 194,
  COM195 = 195,
  COM196 = 196,
  COM197 = 197,
  COM198 = 198,
  COM199 = 199,
  COM200 = 200,
  COM201 = 201,
  COM202 = 202,
  COM203 = 203,
  COM204 = 204,
  COM205 = 205,
  COM206 = 206,
  COM207 = 207,
  COM208 = 208,
  COM209 = 209,
  COM210 = 210,
  COM211 = 211,
  COM212 = 212,
  COM213 = 213,
  COM214 = 214,
  COM215 = 215,
  COM216 = 216,
  COM217 = 217,
  COM218 = 218,
  COM219 = 219,
  COM220 = 220,
  COM221 = 221,
  COM222 = 222,
  COM223 = 223,
  COM224 = 224,
  COM225 = 225,
  COM226 = 226,
  COM227 = 227,
  COM228 = 228,
  COM229 = 229,
  COM230 = 230,
  COM231 = 231,
  COM232 = 232,
  COM233 = 233,
  COM234 = 234,
  COM235 = 235,
  COM236 = 236,
  COM237 = 237,
  COM238 = 238,
  COM239 = 239,
  COM240 = 240,
  COM241 = 241,
  COM242 = 242,
  COM243 = 243,
  COM244 = 244,
  COM245 = 245,
  COM246 = 246,
  COM247 = 247,
  COM248 = 248,
  COM249 = 249,
  COM250 = 250,
  COM251 = 251,
  COM252 = 252,
  COM253 = 253,
  COM254 = 254,
  COM255 = 255
} UsartChannel_t;

typedef enum
{
  USART_MODE_ASYNC = 1
} UsartMode_t;
typedef enum
{
  USART_BAUDRATE_1200   = CBR_1200,
  USART_BAUDRATE_2400   = CBR_2400,
  USART_BAUDRATE_4800   = CBR_4800,
  USART_BAUDRATE_9600   = CBR_9600,
  USART_BAUDRATE_19200  = CBR_19200,
  USART_BAUDRATE_38400  = CBR_38400,
  USART_BAUDRATE_57600  = CBR_57600,
  USART_BAUDRATE_115200 = CBR_115200
} UsartBaudRate_t;
typedef enum
{
  USART_DATA8 = 8
} UsartData_t;
typedef enum
{
  USART_PARITY_NONE  = NOPARITY,
  USART_PARITY_EVEN  = EVENPARITY,
  USART_PARITY_ODD   = ODDPARITY,
  USART_PARITY_SPACE = SPACEPARITY,
  USART_PARITY_MARK  = MARKPARITY
} UsartParity_t;
typedef enum
{
  USART_STOPBIT_1  = ONESTOPBIT,
  USART_STOPBIT_15 = ONE5STOPBITS,
  USART_STOPBIT_2  = TWOSTOPBITS
} UsartStopBits_t;
typedef enum
{
  USART_EDGE_MODE_FALLING = 0,
  USART_EDGE_MODE_RISING  = 1
} UsartEdgeMode_t;
typedef uint8_t UsartClkMode_t;
typedef enum
{
  HAL_USART_TASK_USART_TXC,
  HAL_USART_TASK_USART_RXC,
  HAL_USART_TASKS_NUMBER
} HalUsartTaskId_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Opens Usart interface

\param[in] baud     - usart's baud rate;
\param[in] size     - amount of bits in a byte;
\param[in] stopBits - amount of stopbits;
\param[in] parity   - usart's parity
\param[in] channel  - usart's channel
******************************************************************************/
void halOpenUsart(UsartBaudRate_t baud, UsartData_t size, UsartStopBits_t stopBits, UsartParity_t parity, UsartChannel_t channel);

/**************************************************************************//**
\brief Writes data to Usart interface

\param[in] buffer - pointer to buffer with data to be sent;
\param[in] length - amount of bytes in a buffer
******************************************************************************/
void halWriteUsartData(uint8_t *buffer, uint16_t length);

/**************************************************************************//**
\brief Puts received bytes to the cyclic buffer

\param[in] data   - data to put;
\param[in] length - channel number
******************************************************************************/
void halUsartRxBufferFiller(uint8_t *data, uint16_t length);
#endif //_HAL_USART_H
//eof halUsart.h
