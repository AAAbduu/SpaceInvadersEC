#ifndef _defines
#define _defines
/**********************************************************
 * defines.h
 **********************************************************/

#include <nds.h>
#include <stdio.h>

/*
 * Aquí se definen los registros del gestor de interrupciones
 **/
#define IME		(*(vuint16*)0x04000208) //Interrupt Master Enable - Habilita o deshabilita todas las interrupciones
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable - Activa o desactiva las interrupciones una a una
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag - Guarda las peticiones de interrupcion

/*
 * Aquí se definen algunas funciones para el tratamiento de las interrupciones
 **/
#define enable_ints() 	IME=1 //Habilita todas las interrupciones
#define disable_ints() 	IME=0 //Inhibe todas las interrupciones

/*
 * Aquí se definen los registros del teclado
 **/
#define KEYS_DAT	(*(vuint16*)0x4000130) //Registro de datos del teclado
#define KEYS_CNT	(*(vuint16*)0x4000132) //Registro de control del teclado

/*
 * Aquí se definen los registros del temporizador
 **/
#define TIMER0_CNT  (*(vuint16*)0x04000102) //Registro de control del temporizador
#define TIMER1_CNT (*(vuint16*)0x04000106)//Registro de control del temporizador 1
#define TIMER2_CNT (*(vuint16*)0x0400010A)//Registro de control del temporizador 2
    /*
     * El temporizador se activa poniendo un 1 en el bit 7.
     * El temporizador interrumpirá al desbordarse el contador, si hay un 1 en el bit 6.
     * Los dos bits de menos peso indican lo siguiente:
     *		00 frecuencia 33554432 hz
     *		01 frecuencia 33554432/64 hz
     *		10 frecuencia 33554432/256 hz
     *		11 frecuencia 33554432/1024 hz
     **/
#define TIMER0_DAT  (*(vuint16*)0x04000100) //Registro de datos del temporizador
#define TIMER1_DAT (*(vuint16*)0x04000104)//Registro de datos del temporizador 1
#define TIMER2_DAT (*(vuint16*)0x04000108)//Registro de datos del temporizador 2
    /*
     * Se utiliza para indicar a partir de qué valor tiene que empezar a contar
     **/

/*
 * Asignar un identificador a cada tecla
 **/
#define A		0
#define B		1
#define SELECT		2
#define START		3
#define RIGHT		4
#define LEFT		5
#define UP		6
#define DOWN		7
#define R		8
#define L		9

/*
* Aqui se crean estructuras de datos
**/

typedef struct t_crab_alien{
 int x;
 int y;
 int id;
 int state;
} t_crab_alien;


typedef struct t_projectile{
 int x;
 int y;
 int id;
 int state;  // 0 si no esta lanzado, 1 si esta lanzado
} t_projectile;


/*
 * Asignar un identificador a cada estado
 **/
#define INICIO 0
#define JUGAR 1
#define SIGNIVEL 2
#define GAMEOVER 3
#define FIN 4


/*
 * Variables globales
 **/
extern int seg;
extern int puntuacion;
extern int pr_act;
extern int num_pr;
extern int velocidad;
extern int num_aliens;
extern int aliens_muertos;
extern int state;
extern int nivel;
extern int tiempo_de_juego;
extern t_crab_alien *tc;
extern t_projectile pr[3];
extern int posX ;
extern int posY ;


#endif
