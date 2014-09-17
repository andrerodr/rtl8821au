/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __RTW_EFUSE_H__
#define __RTW_EFUSE_H__


#define	EFUSE_ERROE_HANDLE		1

#define	PG_STATE_HEADER 		0x01
#define	PG_STATE_WORD_0		0x02
#define	PG_STATE_WORD_1		0x04
#define	PG_STATE_WORD_2		0x08
#define	PG_STATE_WORD_3		0x10
#define	PG_STATE_DATA			0x20

#define	PG_SWBYTE_H			0x01
#define	PG_SWBYTE_L			0x02

#define	PGPKT_DATA_SIZE		8

#define	EFUSE_WIFI				0
#define	EFUSE_BT				1

enum _EFUSE_DEF_TYPE {
	TYPE_EFUSE_MAX_SECTION				= 0,
	TYPE_EFUSE_REAL_CONTENT_LEN			= 1,
	TYPE_AVAILABLE_EFUSE_BYTES_BANK		= 2,
	TYPE_AVAILABLE_EFUSE_BYTES_TOTAL	= 3,
	TYPE_EFUSE_MAP_LEN					= 4,
	TYPE_EFUSE_PROTECT_BYTES_BANK		= 5,
	TYPE_EFUSE_CONTENT_LEN_BANK			= 6,
};

#define		EFUSE_MAX_MAP_LEN		256
#define		EFUSE_MAX_HW_SIZE		512
#define		EFUSE_MAX_SECTION_BASE	16

#define EXT_HEADER(header) ((header & 0x1F ) == 0x0F)
#define ALL_WORDS_DISABLED(wde)	((wde & 0x0F) == 0x0F)
#define GET_HDR_OFFSET_2_0(header) ( (header & 0xE0) >> 5)

#define		EFUSE_REPEAT_THRESHOLD_			3

//=============================================
//	The following is for BT Efuse definition
//=============================================
#define		EFUSE_BT_MAX_MAP_LEN		1024
#define		EFUSE_MAX_BANK			4
#define		EFUSE_MAX_BT_BANK		(EFUSE_MAX_BANK-1)
//=============================================
/*--------------------------Define Parameters-------------------------------*/
#define		EFUSE_MAX_WORD_UNIT			4

/*------------------------------Define structure----------------------------*/
typedef struct PG_PKT_STRUCT_A{
	uint8_t offset;
	uint8_t word_en;
	uint8_t data[8];
	uint8_t word_cnts;
}PGPKT_STRUCT,*PPGPKT_STRUCT;

/*------------------------------Define structure----------------------------*/
typedef struct _EFUSE_HAL{
	uint8_t	fakeEfuseBank;
	u32	fakeEfuseUsedBytes;
	uint8_t	fakeEfuseContent[EFUSE_MAX_HW_SIZE];
	uint8_t	fakeEfuseInitMap[EFUSE_MAX_MAP_LEN];
	uint8_t	fakeEfuseModifiedMap[EFUSE_MAX_MAP_LEN];

	u16	BTEfuseUsedBytes;
	uint8_t	BTEfuseUsedPercentage;
	uint8_t	BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
	uint8_t	BTEfuseInitMap[EFUSE_BT_MAX_MAP_LEN];
	uint8_t	BTEfuseModifiedMap[EFUSE_BT_MAX_MAP_LEN];

	u16	fakeBTEfuseUsedBytes;
	uint8_t	fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
	uint8_t	fakeBTEfuseInitMap[EFUSE_BT_MAX_MAP_LEN];
	uint8_t	fakeBTEfuseModifiedMap[EFUSE_BT_MAX_MAP_LEN];
}EFUSE_HAL, *PEFUSE_HAL;


/*------------------------Export global variable----------------------------*/
extern uint8_t fakeEfuseBank;
extern u32 fakeEfuseUsedBytes;
extern uint8_t fakeEfuseContent[];
extern uint8_t fakeEfuseInitMap[];
extern uint8_t fakeEfuseModifiedMap[];

extern u32 BTEfuseUsedBytes;
extern uint8_t BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
extern uint8_t BTEfuseInitMap[];
extern uint8_t BTEfuseModifiedMap[];

extern u32 fakeBTEfuseUsedBytes;
extern uint8_t fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
extern uint8_t fakeBTEfuseInitMap[];
extern uint8_t fakeBTEfuseModifiedMap[];
/*------------------------Export global variable----------------------------*/

uint8_t	efuse_GetCurrentSize(PADAPTER padapter, u16 *size);
u16	efuse_GetMaxSize(PADAPTER padapter);
uint8_t	rtw_efuse_access(PADAPTER padapter, uint8_t bRead, u16 start_addr, u16 cnts, uint8_t *data);
uint8_t	rtw_efuse_map_read(PADAPTER padapter, u16 addr, u16 cnts, uint8_t *data);
uint8_t	rtw_efuse_map_write(PADAPTER padapter, u16 addr, u16 cnts, uint8_t *data);
uint8_t	rtw_BT_efuse_map_read(PADAPTER padapter, u16 addr, u16 cnts, uint8_t *data);
uint8_t 	rtw_BT_efuse_map_write(PADAPTER padapter, u16 addr, u16 cnts, uint8_t *data);

u16	Efuse_GetCurrentSize(PADAPTER pAdapter, uint8_t efuseType, BOOLEAN bPseudoTest);
uint8_t	Efuse_CalculateWordCnts(uint8_t word_en);
void	ReadEFuseByte(PADAPTER Adapter, u16 _offset, uint8_t *pbuf, BOOLEAN bPseudoTest) ;
void	EFUSE_GetEfuseDefinition(PADAPTER pAdapter, uint8_t efuseType, uint8_t type, void *pOut);
uint8_t	efuse_OneByteRead(PADAPTER pAdapter, u16 addr, uint8_t *data, BOOLEAN	 bPseudoTest);
uint8_t	efuse_OneByteWrite(PADAPTER pAdapter, u16 addr, uint8_t data, BOOLEAN	 bPseudoTest);

void	Efuse_PowerSwitch(PADAPTER pAdapter,uint8_t	bWrite,uint8_t	 PwrState);
int 	Efuse_PgPacketRead(PADAPTER pAdapter, uint8_t offset, uint8_t *data, BOOLEAN bPseudoTest);
int 	Efuse_PgPacketWrite(PADAPTER pAdapter, uint8_t offset, uint8_t word_en, uint8_t *data, BOOLEAN bPseudoTest);
void	efuse_WordEnableDataRead(uint8_t word_en, uint8_t *sourdata, uint8_t *targetdata);
uint8_t	Efuse_WordEnableDataWrite(PADAPTER pAdapter, u16 efuse_addr, uint8_t word_en, uint8_t *data, BOOLEAN bPseudoTest);

uint8_t	EFUSE_Read1Byte(PADAPTER pAdapter, u16 Address);
void	EFUSE_ShadowMapUpdate(PADAPTER pAdapter, uint8_t efuseType, BOOLEAN bPseudoTest);
void	EFUSE_ShadowRead(PADAPTER pAdapter, uint8_t Type, u16 Offset, u32 *Value);
#endif

