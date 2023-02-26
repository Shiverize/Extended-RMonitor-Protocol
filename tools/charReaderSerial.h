/*******************************************************************************
 * 
 * File: RMonitor_Framework.c
 * 
 * Authors: Borna Loncaric
 * 
 * Description:
 * 
 * Character reading functions for serial data.
 *
 ******************************************************************************/

#include "app.h"

static bool isNum(uint8_t input);
static bool isLetter(uint8_t input);