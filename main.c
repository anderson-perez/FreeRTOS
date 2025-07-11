/*
 * FreeRTOS Kernel V11.1.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
 * This is a simple main that will start the FreeRTOS-Kernel and run a periodic task
 * that only delays if compiled with the template port, this project will do nothing.
 * For more information on getting started please look here:
 * https://freertos.org/FreeRTOS-quick-start-guide.html
 */

/* FreeRTOS includes. */
#include "user_app.h"

void main( void )
{
    config_user_app();
  
    //xTaskCreate(tarefa_teste, "T", configMINIMAL_STACK_SIZE, NULL, 7, NULL); 
    //xTaskCreate(tarefa_teste_2, "T", configMINIMAL_STACK_SIZE, NULL, 7, NULL); 
    
    //xTaskCreate(tarefa_escritor, "E", configMINIMAL_STACK_SIZE, NULL, 5, NULL); 
    //xTaskCreate(tarefa_leitor, "L", configMINIMAL_STACK_SIZE, NULL, 5, NULL); 
    
    xTaskCreate(tarefa_potenciometro, "P", configMINIMAL_STACK_SIZE, NULL, 5, NULL); 
    //xTaskCreate(tarefa_led, "L", configMINIMAL_STACK_SIZE, NULL, 5, NULL); 
    
    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
        /* Should not reach here. */
    }
}
