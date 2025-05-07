#include "user_app.h"
#include "queue.h"
#include "semphr.h"

SemaphoreHandle_t s;

void config_user_app()
{
    TRISDbits.TRISD0    = 0;
    TRISDbits.TRISD1    = 0;
    TRISDbits.TRISD2    = 0;
    
    s = xSemaphoreCreateBinary();
}

void tarefa_teste()
{
    while (1) {                
        PORTDbits.RD0 = ~PORTDbits.RD0;
        xSemaphoreTake(s, portMAX_DELAY);
        //vTaskDelay(20);       
        //taskYIELD();
        
    }
}

void tarefa_teste_2()
{
    while (1) {        
        PORTDbits.RD1 = ~PORTDbits.RD1;
        //vTaskDelay(20);        
    }
}
