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

/******************************************************************************/

#include "app.h"

static bool isNum(uint8_t input) {
    
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

static bool isLetter(uint8_t input) {

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