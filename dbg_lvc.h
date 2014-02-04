#ifndef __DBG_LVC_H__
#define __DBG_LVC_H__

class dbg_lvc{

private:

    char dtaUart[20];
    char dtaLen;
    char dtaGet;


public:
    
    void init();
    bool isGetNum();                            // if get num
    bool getNum(long *dta);                     // get num
    
    void timer_isr_dbg_lvc();

};


extern dbg_lvc DBG;

#endif