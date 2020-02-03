/*******************************************************************************
 * 
 * File: RMonitor_Framework.c
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

/******************************************************************************/

// Index counters
int n = 0;
int infoNo = 0;

int tempNum;
char tempLet;
bool sameMsg;

uint8_t lapBuff[5];
char infoBuff[6];
// Timer buffers
int ttgBuff[6];
int todBuff[6];
int rtBuff[6];

char flag;
int lapsLeft;

/******************************************************************************/

static bool isNum(char input) {
    
    switch(input) {
            case '0':
                tempNum = 0;
                return true;
                break;
            case '1':
                tempNum = 1;
                return true;
                break;
            case '2':
                tempNum = 2;
                return true;
                break;
            case '3':
                tempNum = 3;
                return true;
                break;
            case '4':
                tempNum = 4;
                return true;
                break;
            case '5':
                tempNum = 5;
                return true;
                break;
            case '6':
                tempNum = 6;
                return true;
                break;
            case '7':
                tempNum = 7;
                return true;
                break;
            case '8':
                tempNum = 8;
                return true;
                break;
            case '9':
                tempNum = 9;
                return true;
                break;
            default:
                return false;
                break;
        }
}

/******************************************************************************/

static bool isLetter(char input) {

    switch(input) {
                // Uppercase
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                // Lowercase
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                tempLet = input;
                return true;
                break;
            default:
                return false;
                break;
        }

}

/******************************************************************************/

    // Return letter
char returnLetter() {
    return tempLet;
}
    // Return number
int8_t returnNumber() {
    return tempNum;
}

/******************************************************************************/

int8_t calculateLapsLeft() {
    
    int m = 0;

    switch (n)
    {
        case 1:
            lapsLeft = lapBuff[0];
            break;
        case 2:
            lapsLeft = (lapBuff[0]*10) + lapBuff[1];
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

    return lapsLeft;

}

/******************************************************************************/
        // OBSOLETE

/*void checkInfo(uint8_t * txBuff) {

    infoNo = 0;
    n=0;
    
        // First, check if the character is a number
    if (isNum(txBuff)==true) {
        
        

        // Then check if it's a letter
    } else if (isLetter(txBuff==true)) {
            
        infoBuff[j] = returnLetter();
        j++;

        // If it's a ',' character
    } else if (tx_buffer[i] == ',') {
        // ',' marks the end of one and progress to another information inside of the protocol
        infoNo++;
    } else {
        // Do nothing, just wait for count
    }
}*/

/******************************************************************************/

void checkHeartbeat(uint8_t * f) {

    int i = 0;

    do {
        if (f[i]==',') {
            infoNo++;
            n=0;
        }

        if (f[i]==0x0A || f[i]==0x0D) {
            sameMsg = false;
        }
        
        switch (infoNo) {
            case 1: // Laps to go
                if (isNum(f[i])==true) {
                        // tempNum je varijabla unutar 'isNum' metode
                    lapBuff[n] = returnNumber();

                        // At the end increment n
                    n++;
                }
                break;
            case 2: // Time to go
                if (isNum(f[i])==true) {
                        // tempNum je varijabla unutar 'isNum' metode
                    ttgBuff[n] = returnNumber();

                        // At the end increment n
                    n++;
                }
                break;
            case 3: // Time of day
                if (isNum(f[i])==true) {
                        // tempNum je varijabla unutar 'isNum' metode
                    todBuff[n] = returnNumber();

                        // At the end increment n
                    n++;
                }
                break;
            case 4: // Race time
                if (isNum(f[i])==true) {
                        // tempNum je varijabla unutar 'isNum' metode
                    rtBuff[n] = returnNumber();

                        // At the end increment n
                    n++;
                }
                break;
            case 5: // Flag status
                if (isLetter(f[i])==true) {
                    char tempLet = f[i];
                    switch (tempLet)
                    {
                        // Fixed 6 char length
                    case 'G':
                        flag = tempLet;     // "Green "
                        break;
                    case 'Y':
                        flag = tempLet;     // "Yellow"
                        break;
                    case 'R':
                        flag = tempLet;     // "Red   "
                        break;
                    case 'F':
                        flag = tempLet;     // "Finish"
                        break;
                    default:
                        break;
                    }
                }
                    // Has to end after the flag
                sameMsg = false;
                break;
            default:                
                break;
        }

            // Move forward
        i++;
    } while (sameMsg==true);

        // Reset the message state after LF/CR
    sameMsg = true;

}