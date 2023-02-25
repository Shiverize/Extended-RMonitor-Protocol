/*******************************************************************************
 * 
 * File: RMonitor_Framework.c
 * 
 * Authors: Borna Loncaric
 * 
 * Description:
 * 
 * Framework created for Microchip products to work with AMB RMonitor timing
 * protocol. 
 *
 ******************************************************************************/

#include "app.h"

/******************************************************************************/

// Index counters
int n = 0;
int infoNo = 0;
uint8_t lapC;
static bool newMsg;

int tempNum;
uint8_t tempLet;
bool sameMsg;

int lapBuff[5];
uint8_t infoBuff[6];
// Timer buffers
uint8_t ttgBuff[6];
uint8_t todBuff[6];
uint8_t rtBuff[6];

uint8_t flag;
int lapsLeft;


/*******************************************************************************
 * Lap calculation function
 ******************************************************************************/

void calculateLapsLeft() {

    switch (lapC)
    {
        case 0:
            break;
        case 1:
            lapsLeft = lapBuff[0];
            break;
        case 2:
            lapsLeft = ((lapBuff[0])*10) + (lapBuff[1]);
            break;
        case 3:
            lapsLeft = (lapBuff[0]*100) + (lapBuff[1]*10) + lapBuff[2];
            break;
        case 4:
            lapsLeft = (lapBuff[0]*1000) + (lapBuff[1]*100) 
            + (lapBuff[2]*10) + lapBuff[3];
            break;
        case 5:
            lapsLeft = (lapBuff[0]*10000) + (lapBuff[1]*1000) 
            + (lapBuff[2]*100) + (lapBuff[3]*10) + lapBuff[4];
            break;
        default:
            break;
    }

    lapsGlobal = lapsLeft;

}

/*******************************************************************************
 * Time-to-go and race time filling methods
 ******************************************************************************/
void fill_ttg() {
    ttg_vrijeme.sat = (ttgBuff[0]-'0')*10 + ttgBuff[1]-'0';
    ttg_vrijeme.minuta = (ttgBuff[2]-'0')*10 + ttgBuff[3]-'0';
    ttg_vrijeme.sekunda = (ttgBuff[4]-'0')*10 + ttgBuff[5]-'0';
}
/******************************************************************************/
void fill_racetime() {
    racetime.sat = (rtBuff[0]-'0')*10 + rtBuff[1]-'0';
    racetime.minuta = (rtBuff[2]-'0')*10 + rtBuff[2]-'0';
    racetime.sekunda = (rtBuff[4]-'0')*10 + rtBuff[5]-'0';
}

/*******************************************************************************
 * 
 *                             HEARTBEAT METHOD
 * 
 ******************************************************************************/

void checkHeartbeat(uint8_t * f) {

    int i = 0;

    while (getMsgRead()) {
        if (f[i]==',') {
            infoNo++;
            n=0;
        }

        if (f[i]==0x0A || f[i]==0x0D) {
            setMsgRead(false);
            infoNo = 0;
        }
        
        switch (infoNo) {
            case 1: // Laps to go
                if (isNum(f[i])==true) {
                        // tempNum is inside 'isNum' method
                    lapBuff[lapC] = tempNum;//returnNumber();

                        // At the end increment n
                    lapC++;
                }
                break;
            case 2: // Time to go
                calculateLapsLeft();
                if (isNum(f[i])==true) {
                    
                    ttgBuff[n] = f[i];
                        // At the end increment n
                    n++;
                }
                break;
            case 3: // Time of day
                lapC = 0;   // reset lap digit count
                fill_ttg();
                if (isNum(f[i])==true) {
                        
                    todBuff[n] = f[i];
                        // At the end increment n
                    n++;
                }
                break;
            case 4: // Race time
                if (isNum(f[i])==true) {
                    
                    rtBuff[n] = f[i];
                        // At the end increment n
                    n++;
                }
                break;
            case 5: // Flag status
                fill_racetime();
                if (isLetter(f[i])==true) {
                    switch (f[i])
                    {
                        // Fixed 6 char length
                    case 'G':   // "Green "
                    case 'Y':   // "Yellow"
                    case 'R':   // "Red   "
                    case 'F':   // "Finish"
                        flag = f[i];
                        break;
                    default:
                        break;
                    }
                }
                break;
            default:                
                break;
        }
            // Move forward
        i++;
    }
}
