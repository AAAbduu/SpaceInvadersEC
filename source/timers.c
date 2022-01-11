/**********************************************************
 * timers.c
 **********************************************************/

/*
 * Añadir los includes que sean necesarios
 **/
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

/*
 * Rutina de atención a la interrupción del temporizador
 **/
 void handler_t2_disparar(){
	 for(int x = 0; x<num_pr; x++){
 		if(pr[x].state == 1){
 		disparar(pr[x],x);
				}
 		}
}


 void movimiento_handler_t1(){
	 movimiento_general_aleatorio();
	 //for(int i = 0; i<num_aliens;i++){
 		//if((tc[i].state == 1)){
 			//display_crab_alien(tc[i].id,tc[i].x,tc[i].y);
 		//}
		//POR SI SE SALEN FUERA DE PANTALLA, LOS VUELVO A METER DENTRO.
		for(int i =0;i<num_aliens;i++){
			if(tc[i].x>220){
				tc[i].x = tc[i].x - 15;
			}else if(tc[i].x<0){
				tc[i].x = tc[i].x + 15;
			}
		}

 	//}
	 if(seg==10){
	 	for(int i = 0; i<num_aliens;i++){
	 		if((tc[i].state == 1)){			//MUEVO TODOS HACIA ABAJO TRAS 10 SEGUNDOS
	 			remove_crab_alien(tc[i].id,tc[i].x,tc[i].y);
	 			tc[i].y = tc[i].y+10;
	 			display_crab_alien(tc[i].id,tc[i].x,tc[i].y);
	 			seg =0;
	 				}
	 			}
	 	}
 }



void timer_handler() {
seg++;
tiempo_de_juego--;

}
 // timer_handler()
