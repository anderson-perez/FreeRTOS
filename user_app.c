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
    
    // Configura conversor AD
    config_adc();
}

// Exemplo conversor AD
void config_adc()
{
    // Configuração do conversor AD
    
    AD1CON3bits.ADRC    = 1;            // Clock interno
    AD1CON3bits.SAMC    = 0b11111;      // Tad = 31
    AD1CON3bits.ADCS    = 0b00111111;   //  64 * TCY
    AD1CHSbits.CH0SA    = 0b0000;
    AD1CON2bits.VCFG    = 0b011;
    AD1CON1bits.SAMP    = 0;  
    AD1CON1bits.ADON    = 1;            // Liga conversor AD
}

uint16_t le_adc()
{
    AD1CON1bits.SAMP   = 1;
    vTaskDelay(1);
    AD1CON1bits.SAMP   = 0;
    
    while (!AD1CON1bits.DONE);
    
    return ADC1BUF0;
}

void tarefa_potenciometro()
{
    uint16_t vlr_lido = 0;
    
    while (1) {
        vlr_lido = le_adc();
        
        if (vlr_lido > 100) {
            LATDbits.LATD2 = 1; // Liga o led
        }
        else {
            LATDbits.LATD2 = 0; // Desliga o led
        }
        
        vTaskDelay(30);
    }
}

void tarefa_led()
{
    while (1) {
        LATDbits.LATD2 = ~PORTDbits.RD2;
        vTaskDelay(100);
    }
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
