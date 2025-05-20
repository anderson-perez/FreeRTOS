#ifndef USER_APP_H
#define	USER_APP_H

#include "FreeRTOS.h"
#include "task.h"
#include "xc.h"
#include "FreeRTOSConfig.h"
#include "queue.h"

void config_user_app();

void tarefa_teste();
void tarefa_teste_2();

void tarefa_escritor();
void tarefa_leitor();

// Exemplo conversor AD
void config_adc();
void tarefa_potenciometro();
void tarefa_led();
uint16_t le_adc();

#endif	/* USER_APP_H */

