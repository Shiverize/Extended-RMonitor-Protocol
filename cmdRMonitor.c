/*******************************************************************************
 * 
 * File: cmdRMonitor.c
 * 
 * Authors: Borna Loncaric
 * 
 * Description:
 * 
 * Reading RS232/485 serial data and semaphore conversion.
 *
 ******************************************************************************/

#include "app.h"

/******************************************************************************/

int i = 0;
int j = 0;
bool msgEnd;
bool msgRead;

static uint8_t tx_buffer[200];  // 200 is a randomly defined number

/*******************************************************************************
 * Buffer fill & clear operations
 ******************************************************************************/

void rmon_buff_fill(uint8_t tx) {
    if (tx != 0x0A) {   // If line feed (LF) is summoned
        tx_buffer[j] = tx;
        j++;
        msgEnd = false;
        msgRead = false;
    } else {
        j = 0;
        msgEnd = true;
        msgRead = true;
    }
}

void rmon_buff_clear() {
    int i = 0;
    
    for (i=0; i<sizeof(tx_buffer); i++) {
        tx_buffer[i] = NULL;
    }
}

/*******************************************************************************
 * Message read checks
 ******************************************************************************/

void setMsgRead(bool in) {
    msgRead = in;
}

bool getMsgRead() {
    return msgRead;
}

/******************************************************************************
 * Loop for reading incoming serial data
 *****************************************************************************/

PT_THREAD (app_rMon(pt_t * pt)) {

    PT_BEGIN(pt);
    
    for (;;) {

        if (msgRead == true) {
                // $F is a 1st level message
            if (0U == strncmp("$F,", (char*) &tx_buffer[0], 3)) {

                checkHeartbeat(&tx_buffer);
                

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

                // Check if there was an RMon message so the clock
                // switches to the lap counter mode immediately and starts
                // The 10 minute countdown
            if (0U == strncmp("$F,", (char*) &tx_buffer[0], 3) || 
                    0U == strncmp("$A,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$COMP,", (char*) &tx_buffer[0], 6) ||
                    0U == strncmp("$B,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$C,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$E,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$G,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$H,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$I,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$J,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$L,", (char*) &tx_buffer[0], 3) ||
                    0U == strncmp("$T,", (char*) &tx_buffer[0], 3)                
                    ){
                setClockRMon();
                rmon_buff_clear();
            }
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

