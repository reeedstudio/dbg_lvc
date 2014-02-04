
#include <Arduino.h>
#include "dbg_lvc.h"

void dbg_lvc::init()
{
    dtaGet = 0;
    dtaLen = 0;
}

bool dbg_lvc::isGetNum()                    // if get num
{
    if(0 == dtaGet)return 0;

    for(int i=0; i<dtaLen-2; i++)
    {
        if((dtaUart[i] != '-') && (dtaUart[i] < '0' || dtaUart[i] > '9'))
        {
            dtaGet = 0;                     // clear flag
            dtaLen = 0;                     // clear length
            return 0;
        }
    }

    return 1;
    
}

bool dbg_lvc::getNum(long *dta)
{
    if(!isGetNum())return 0;
    
    long sum = 0;

    long __pow[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
    
    int _offset = 0;
    
    _offset = dtaUart[0] == '-' ? 1 : 0;
    dtaLen = dtaUart[0] == '-' ? dtaLen - 3 : dtaLen -2;
    
    
    for(int i=0; i<dtaLen; i++)
    {
        sum += (dtaUart[i+_offset] - '0') * __pow[dtaLen-i-1];
    }
    
    sum = (dtaUart[0] == '-') ? 0-sum : sum;
    
    *dta = sum;
    
    dtaLen = 0;                             // clear len
    dtaGet = 0;                             // clear flag
    
    return 1;
    
}


void dbg_lvc::timer_isr_dbg_lvc()
{
    if(1 == dtaGet)
    {
        while(Serial.available())
        {
            Serial.read();
        }
        return;
    }
    
    while(Serial.available())
    {
        dtaUart[dtaLen++] = (char)Serial.read();
        
        if(dtaUart[dtaLen-1] == '\n')
        {
            dtaGet = 1;
        }

    }
}

dbg_lvc DBG;