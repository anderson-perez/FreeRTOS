#include "user_app.h"
#include "queue.h"
#include "semphr.h"

SemaphoreHandle_t s;
QueueHandle_t fila;

void config_user_app()
{
    TRISDbits.TRISD0    = 0;
    TRISDbits.TRISD1    = 0;
    TRISDbits.TRISD2    = 0;
    
    s = xSemaphoreCreateBinary();
    
    fila = xQueueCreate(5, sizeof(char));
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


void tarefa_escritor()
{
    char comando[] = {'L', 'D'};
    //int idx_comando = 0;
    
    while (1) {
        PORTDbits.RD0 = 1;
        if (PORTDbits.RD3 == 1)
            xQueueSend(fila, &comando[0], portMAX_DELAY);
        else 
            xQueueSend(fila, &comando[1], portMAX_DELAY);
        //idx_comando = (idx_comando+1) % 2;
        vTaskDelay(50);
        PORTDbits.RD0 = 0;
        vTaskDelay(50);
    }
}

void tarefa_leitor()
{
    char cmd;
    
    while (1) {
        PORTDbits.RD1 = 1;
        xSemaphoreTake(s, portMAX_DELAY);
        xQueueReceive(fila, &cmd, portMAX_DELAY);
        // Testa comando recebido
        switch (cmd) {
            
            case 'L': PORTDbits.RD2 = 1;
                      break;
            
            case 'D': PORTDbits.RD2 = 0;
                      break;
        }
        vTaskDelay(50);
        PORTDbits.RD1 = 0;
        vTaskDelay(50);
    }
}
