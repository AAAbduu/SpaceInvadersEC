/**********************************************************
 * game.c
 *
 *Este archivo contiene los metodos propios del juego para
 *tenerlo mejor organizado.
 **********************************************************/


#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sprites.h"
#include "defines.h"

//Metodo que se encarga de iniciar el juego y los niveles a medida que avanzas.
void iniciar_juego() {
  tc =  (t_crab_alien *)malloc(num_aliens* sizeof(t_crab_alien)); //USAR FREE(tc) AL ACABAR EL JUEGO SIEMPRE
  for(int i =0; i<num_pr;i++){
    pr[i].state = 0; //state 0, no lanzado, state 1 lanzado.
  }
  aliens_muertos=0;
  tiempo_de_juego=120; 
  num_pr=3;
  puntuacion = 0;
  consoleClear();
  display_back02();
  display_laser_cannon(posX,posY);
  for(int x =0; x<num_aliens;x++){
    tc[x].x = rand () % (230-0+1) + 0;
    tc[x].y = rand () % (60-0+1) + 0;
    tc[x].id = x;
    tc[x].state = 1;
    display_crab_alien(tc[x].id,tc[x].x,tc[x].y);
  }}
//funcion que permite conocer si un alien esta suficientemente cerca para acabar el juego.
int alien_llega(){
  for(int x =0; x<num_aliens;x++){
    if((tc[x].y > 155) && (tc[x].state==1)){
      return 1;
    }
  }return 0;
}

//Metodo que se encarga de disparar los proyectiles y en caso de colision con un alien, hace desaparecer ambos y aumenta la puntuacion del jugador.
void disparar(t_projectile ePr, int h){

    if(pr[h].y>0){
      for(int x=16; x>0;x--){
          remove_projectile(ePr.id, ePr.x, ePr.y);
          ePr.y = ePr.y -1;
          display_projectile(ePr.id, ePr.x, ePr.y);
              pr[h].x = ePr.x;
              pr[h].y = ePr.y;
              if(ePr.state==0){
                remove_projectile(ePr.id, ePr.x, ePr.y);
              }
          for(int i = 0; i<num_aliens; i++){
  			       for(int f = 0; f<7; f++){
			              if(((tc[i].y==ePr.y)&&(tc[i].state==1))&&((tc[i].x==ePr.x)|| (tc[i].x==ePr.x-f)|| (tc[i].x==ePr.x+f))) {
				                      remove_crab_alien(tc[i].id,tc[i].x,tc[i].y);
                              remove_projectile(pr[h].id, pr[h].x, pr[h].x);
                              remove_projectile(ePr.id, ePr.x, ePr.y);
                              ePr.state=0;
                              aliens_muertos++;
                              puntuacion=puntuacion+10;
				                      tc[i].state = 0;
                              pr[h].state = 0;
                              }
                            }
                          }

                      }
      }else if(ePr.y<=0){
            pr[h].state = 0;

            remove_projectile(pr[h].id, pr[h].x, pr[h].y);

          }
}



//Metodo que limpia la pantalla de abajo.
void clean_screen(){
  remove_laser_cannon(posX,posY);

  for(int i = 0; i<num_aliens;i++){
    tc[i].state = 0;
    remove_crab_alien(tc[i].id,tc[i].x,tc[i].y);
  }

}
