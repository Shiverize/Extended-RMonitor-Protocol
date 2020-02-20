/*******************************************************************************
 * 
 * File: RMonitor_Framework.h
 * 
 * Authors: Borna Loncaric
 * 
 * Device name: EDS153
 * Ver: S-Race (v1.0)
 * 
 * Description:
 * 
 * Framework created for Microchip products to work with AMB RMonitor timing
 * protocol. 
 *
 ******************************************************************************/

#include <app.h>

// Letter/number checks
int lapsGlobal;
datumvrijeme_t ttg_vrijeme;
datumvrijeme_t racetime;

PT_THREAD(app_rMon(pt_t *pt));

// Return value functions
uint8_t returnLetter();
uint8_t returnNumber();
void calculateLapsLeft();

// Message reading functions
void checkHeartbeat(uint8_t * f);   // $F

/* cmdRMonitor.c */
void setMsgRead(bool in);   // 6.2.2020.
bool getMsgRead();          // -||-
void rmon_buff_clear();