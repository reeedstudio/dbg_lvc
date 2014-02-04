#include <Streaming.h>
#include <dbg_lvc.h>

void setup()
{
    Serial.begin(115200);
    
    DBG.init();
    cout << "hello world" << endl;
    
    Serial.println("nihao");
}

void loop()
{
    DBG.timer_isr_dbg_lvc();
    
    if(DBG.isGetNum())
    {
        long num = 0;
        
        if(DBG.getNum(&num))
        {
            cout << num << endl;
        }
    }
    
    delay(1);
}