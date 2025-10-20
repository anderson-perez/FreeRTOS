#ifndef USER_APP_H
#define	USER_APP_H

#define EXAMPLE_1   0
#define FILOSOFOS   0
#define EXAMPLE_2   0
#define EXAMPLE_3   0
#define EXAMPLE_4   0
#define ALARME      1

#if EXAMPLE_1 == 1

void config_user_app();
void task_1();
void task_2();

#elif FILOSOFOS == 1

void config_user_app();
void f_0();
void f_1();
void f_2();
void f_3();
void f_4();

void pensar();
void comer(int f_id);

#elif EXAMPLE_2 == 1

void config_user_app();
void task_1();
void task_2();

#elif EXAMPLE_3 == 1

void config_user_app();
void task_1();
void task_2();

#elif EXAMPLE_4 == 1

void config_user_app();
void task_1();
void task_2();

#elif ALARME == 1

void config_user_app();
void task_sensor();
void task_lampada();
void task_speaker();

#endif

#endif	/* USER_APP_H */

