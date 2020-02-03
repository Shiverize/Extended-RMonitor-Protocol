/*******************************************************************************
 * 
 * File: cmdRMonitor.c
 * 
 * Authors: Borna Loncaric
 * 
 * Device name: EDS153
 * Ver: S-Race (v1.0)
 * 
 * Description:
 * 
 * Citanje RS232/485 podataka te konverzija u podatke suvisle semaforu.
 *
 ******************************************************************************/

#include <app.h>

/******************************************************************************/

int i = 0;

static uint8_t tx_buffer[200];  // 200 is a randomly defined number
    // izmjenjeno sa uint8_t na char_t


//strcpy ((char*) tx_buffer, (const char*) buffConvert);

/******************************************************************************
 * Petlja za iscitavanje serijskih podataka
 *  - potrebno staviti u PT
 *****************************************************************************/

PT_THREAD (app_rMon(pt_t * pt)) {

    PT_BEGIN(pt);
    
    for (;;) {

            // $F is a 1st level message
        if (0U == strncmp("$F,", (char*) &tx_buffer[0], 3)) {

            checkHeartbeat(tx_buffer);
            
        /************ Proceeding to 2nd & 3rd level messages ****************/
            // Competitor information
        } else if (0U == strncmp("$A,", (char*) &tx_buffer[0], 3)) {

            // Competitor information
        } else if (0U == strncmp("$COMP,", (char*) &tx_buffer[0], 6)) {

            // Run information
        } else if (0U == strncmp("$B,", (char*) &tx_buffer[0], 3)) {

            // Class information
        } else if (0U == strncmp("$C,", (char*) &tx_buffer[0], 3)) {

            // Setting information
        } else if (0U == strncmp("$E,", (char*) &tx_buffer[0], 3)) {

            // Race information
        } else if (0U == strncmp("$G,", (char*) &tx_buffer[0], 3)) {

            // Practice/qualifying information
        } else if (0U == strncmp("$H,", (char*) &tx_buffer[0], 3)) {

            // Init record (clear scoreboard)
        } else if (0U == strncmp("$I,", (char*) &tx_buffer[0], 3)) {

            // Passing information
        } else if (0U == strncmp("$J,", (char*) &tx_buffer[0], 3)) {

            /************ ENCHANCED RMon commands and codes ****************/
            // Line crossing message
        } else if (0U == strncmp("$L,", (char*) &tx_buffer[0], 3)) {

            // Track description message
        } else if (0U == strncmp("$T,", (char*) &tx_buffer[0], 3)) {
            
        }        
        
        if (sys_t1_ser2ticks_tout_end() == true) {
                INT_LOCK;
                //gpsWIx = 0U; // reset buffer write index
                INT_UNLOCK;
            }
            PT_YIELD(pt);
        }
        PT_END(pt);
    //}
}

