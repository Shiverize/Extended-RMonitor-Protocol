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
//bool isNum(char* input);
//bool isLetter(char* input);

PT_THREAD(app_rMon(pt_t *pt));

// Return value functions
char returnLetter();
uint8_t returnNumber();
uint8_t calculateLapsLeft();

// Message reading functions
void checkHeartbeat(uint8_t * f);   // $F