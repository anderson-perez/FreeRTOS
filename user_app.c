#include <p24FJ128GA010.h>

#include "user_app.h"
#include "FreeRTOS.h"
#include "task.h"
#include <xc.h>
#include "semphr.h"

#if EXAMPLE_1 == 1

SemaphoreHandle_t s;


void config_user_app()
{
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    s = xSemaphoreCreateBinary();
}

void task_1()
{
    while (1) {
        LATDbits.LATD0 = ~PORTDbits.RD0;
        xSemaphoreTake(s, portMAX_DELAY);    
    }
}

void task_2()
{
    while (1) {
        LATDbits.LATD1 = ~PORTDbits.RD1;
        //vTaskDelay(10);
        xSemaphoreGive(s);
    }
}

#elif FILOSOFOS == 1

#define QTD 5

// vetor de garfos
SemaphoreHandle_t garfos[QTD];

void config_user_app()
{
    for (int i = 0; i < QTD; i++) {
        garfos[i] = xSemaphoreCreateBinary();   // Cria semáforo
        xSemaphoreGive(garfos[i]);              // Seta em 1
    }
    
    // Configuração de portas dos leds que irão representar os filósofos
    
}

void f_0()
{
    while (1) {
        pensar();
        comer(0);
    }
}

void f_1()
{
    
}

void f_2()
{
    
}

void f_3()
{
    
}

void f_4()
{
    
}

void pensar()
{
    vTaskDelay(50);
}

void comer(int f_id)
{
    // Garfo da esquerda
    xSemaphoreTake(garfos[f_id], portMAX_DELAY);
    // Garfo da direita
    xSemaphoreTake(garfos[(f_id+1) % QTD], portMAX_DELAY);    
}

#endif