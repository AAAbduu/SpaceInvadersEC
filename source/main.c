/**********************************************************
 * main.c
 *
 * Este codigo se ha implementado basandose en el ejemplo
 * "Simple sprite demo" de dovoto y otro de Jaeden Amero
 **********************************************************/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	    // srand, rand,...
#include <unistd.h>
#include <time.h>       // time

#include "backgrounds.h"
#include "controllers.h"
#include "defines.h"
#include "keypad_screen.h"
#include "sprites.h"
#include "timers.h"
#include "game.h"

/*
 * Variables globales
 **/
  int posX = 115;
  int puntuacion = 0;
  int posY=170;
  int aliens_muertos =0;
  int num_aliens = 10;
  int velocidad = 0;
  int pr_act=0;
  t_crab_alien *tc;
  int tiempo_pasado =0;


  int num_pr = 3;
  int state;
  int tiempo_de_juego;
  int seg = 0;
  int nivel = 1;
  t_projectile pr[3];


/*
 * main()
 **/

int main() {

    /*
 	 * Poner en marcha el motor grafico 2D.
 	 **/
    powerOn(POWER_ALL_2D); // <nds.h>

    /*
     * Establecer la pantalla inferior como principal, inicializar
     * el sistema grafico y configurar el sistema de fondos.
     **/
    lcdMainOnBottom(); // <nds.h>
    init_video();
    init_background();

    /*
 	 * Inicializar memoria de sprites y guardar en ella los sprites.
 	 **/
    init_sprite_memory();
    alloc_sprites_in_memory();

    /*
 	 * Establecer las paletas para los sprites.
 	 **/
    set_main_palette();
    set_secondary_palette();

    /* Inicializa la consola (superior) de texto.
     * Nota.- Para borrar la pantalla existe la funcion consoleClear()
     **/
    consoleDemoInit(); // <nds.h>

    /*
     * Para inicializar el generador de numeros aleatorios en funcion de una semilla,
	 * en este caso time(NULL). srand() solo se suele activar una vez por ejecucion y
	 * no devuelve ningun valor.
	 * La funcion para generar valores aleatorios en el resto del programa es rand()
	 **/
    srand(time(NULL));

    /*
     * Mostrar fondos en pantalla.
     **/
    //display_back01();
    state = INICIO;

    /*
     * Incluimos la siguiente cabecera para que cada grupo la modifique con
     * su numero de grupo "xxx" en "ECxxx".


	interrupts_setting();




    while(1) {

      switch (state) {
        case INICIO:
        consoleClear();
        display_back01();
        while(!is_the_screen_touched()){
        iprintf("\x1b[00;00H  +--------------------------+  ");
        iprintf("\x1b[01;00H  : KE-EC 20/21      EC107   :  ");
        iprintf("\x1b[02;00H  +--------------------------+  ");

        iprintf("\x1b[04;00H  +--------------------------+  ");
        iprintf("\x1b[05;00H  : Judith Antelo Lacalle    :  ");
        iprintf("\x1b[06;00H  : Silvia Arenales Munoz    :  ");
        iprintf("\x1b[07;00H  : Abdu Ali                 :  ");
        iprintf("\x1b[08;00H  +--------------------------+  ");

        iprintf("\x1b[18;00H Toca la pantalla para comenzar");
         if(is_the_screen_touched()){
            nivel = 1;
            iniciar_juego();
            state = JUGAR;
          }
        }
          break;


        case JUGAR:
        iprintf("\x1b[00;00H  +--------------------------+  ");
        iprintf("\x1b[01;00H  : KE-EC 20/21      EC107   :  ");
        iprintf("\x1b[02;00H  +--------------------------+  ");
        iprintf("\x1b[16;00H Puntuacion: %d", puntuacion);
        iprintf("\x1b[18;00H Estas en el nivel: %d", nivel);
        iprintf("\x1b[20;00H Te quedan: %d segundos", tiempo_de_juego );

          movimiento();
            if(aliens_muertos == num_aliens){
              tiempo_pasado = 0;
              tiempo_pasado = 120-tiempo_de_juego;
                consoleClear();
                if(nivel==5){
                  state = FIN;
                  break;
                }
                state = SIGNIVEL;

            }
            if(tiempo_de_juego==0){
              consoleClear();
              free(tc);
              state = GAMEOVER;
            }




            if(tiempo_de_juego%10 == 0){
              iprintf("\x1b[20;00H Te quedan: %d segundos", tiempo_de_juego );
            }

            if(alien_llega()){
              consoleClear();
              free(tc);
              tiempo_pasado = 0;
              tiempo_pasado = 120-tiempo_de_juego;
              state = GAMEOVER;

            }

            break;

            case SIGNIVEL:

            iprintf("\x1b[01;00H Tiempo transcurrido: %d", tiempo_pasado);
              iprintf("\x1b[03;00H PASAS DE NIVEL ");
              iprintf("\x1b[05;00H Puntuacion: %d", puntuacion);
              iprintf("\x1b[07;00H TOCA LA PANTALLA PARA CONTINUAR ");
              if(is_the_screen_touched()){
                nivel++;
                num_aliens = num_aliens + 2;
                free(tc);
              iniciar_juego();
              state = JUGAR;}
            break;

            case GAMEOVER:
            clean_screen();
            consoleClear();
            while(!is_the_screen_touched()){

              iprintf("\x1b[08;00H Tiempo transcurrido: %d", tiempo_pasado);
              iprintf("\x1b[10;00H OH NO! PERDISTE! ");
              iprintf("\x1b[18;00H Para volver a jugar ");
              iprintf("\x1b[19;00H pulsa la pantalla ");
              display_back02();
              if(is_the_screen_touched()){
                num_aliens = 10;
                nivel = 1;
                iniciar_juego();
                state = JUGAR;
              }
            }
            break;

            case FIN:
            iprintf("\x1b[00;00H  +--------------------------+  ");
            iprintf("\x1b[01;00H  : KE-EC 20/21      EC107   :  ");
            iprintf("\x1b[02;00H  +--------------------------+  ");
            iprintf("\x1b[04;00H  +--------------------------+  ");
            iprintf("\x1b[05;00H  : Judith Antelo Lacalle    :  ");
            iprintf("\x1b[06;00H  : Silvia Arenales Munoz    :  ");
            iprintf("\x1b[07;00H  : Abdu Ali                 :  ");
            iprintf("\x1b[08;00H  +--------------------------+  ");
            iprintf("\x1b[18;00H Enhorabuena, te lo has pasado! ");
            iprintf("\x1b[20;00H Pulsa START para jugar otra vez");

            break;
          }


        }
}// while

 // main()
