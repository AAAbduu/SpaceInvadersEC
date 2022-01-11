/**********************************************************
 * keypad_screen.c
 **********************************************************/

/*
 * Añadir los includes que sean necesarios
 **/
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

/*
 * Esta función consulta si se ha tocado la pantalla táctil
 **/
int is_the_screen_touched() {
touchPosition screen_pos;
	touchRead(&screen_pos);
  	return !(screen_pos.px==0 && screen_pos.py==0);
} // is_the_screen_touched()


/*
 * Esta función tiene que devolver el valor de la tecla pulsada
 **/
int pressed_key_value() {
    /*
 	 * Devuelve el valor asociado a la tecla pulsada:
 	 * A=0;    B=1;  SELECT=2; START=3; RIGHT=4;
 	 * LEFT=5; UP=6; DOWN=7;   R=8;     L=9
 	 * -1 en otros casos
 	 **/
if((KEYS_DAT&0X0001)==0) return 0;//return A
else if((KEYS_DAT&0X0002)==0) return 1; //return B
else if((KEYS_DAT&0X0004)==0) return 2; //return SELECT
else if((KEYS_DAT&0X0008)==0) return 3; //return START
else if((KEYS_DAT&0X0010)==0) return 4; //return Right
else if((KEYS_DAT&0X0020)==0) return 5; //return IZQD
else if((KEYS_DAT&0X0040)==0) return 6; //return ARRIBA
else if((KEYS_DAT&0X0080)==0) return 7; //return ABAJO
else if((KEYS_DAT&0X0100)==0) return 8; //return R
else if((KEYS_DAT&0X0200)==0) return 9; //return L
else return -1;

} // pressed_key_value()


/*
 * Rutina de atención a la interrupción del teclado
 **/

//Metodo que se encarga en atender la interrupcion al disparar con la tecla B.
void keypad_handler() {
if(pressed_key_value()==1){
if(pr_act<num_pr){
	pr[pr_act].x = posX;
	pr[pr_act].y = posY-10;
	pr[pr_act].state = 1;
	pr[pr_act].id = pr_act;
	pr_act++;
	if(pr_act==num_pr){
		pr_act=0;

		}
	}

}else if(pressed_key_value()==3){
	if(state == JUGAR || state ==FIN){
	num_aliens = 10;
	nivel = 1;
	free(tc);				//START POR INTERRUPCION TAMBIEN PORQUE ASI LO ACORDAMOS
	clean_screen();
	consoleClear();
	iniciar_juego();
	state = JUGAR;
	}
}else if(pressed_key_value()==0){
	if(state == JUGAR){
	consoleClear();
	free(tc);								//A POR INTERRUPCION PORQUE ASI LO ACORDAMOS CON IÑAKI
	nivel = 1;
	state = GAMEOVER;
	}
}else if(pressed_key_value()==2){
	if(state == JUGAR){
	free(tc);				//SELECT POR INTERRUPCION TAMBIEN PORQUE ASI LO ACORDAMOS
	clean_screen();
	nivel = 1;
	consoleClear();
	state = INICIO;
		}
	}
}

//Metodo que se encarga de mover el cañon por encuesta
	void movimiento(){
		if(pressed_key_value()==4) {
			velocidad++;
			if((posX > 1) && (posX <235)){
				if(velocidad == 10){
				remove_laser_cannon(posX,posY);
				posX=posX+1;
				display_laser_cannon(posX,posY);
				velocidad = 0;}
			}else{
				remove_laser_cannon(posX,posY);
				posX=posX-4;
				display_laser_cannon(posX,posY);

			}

		}else if(pressed_key_value()==5){
			velocidad++;
			if((posX > 1) && (posX <240)){
				if(velocidad==10){
	 remove_laser_cannon(posX,posY);
	 posX=posX-1;
	 display_laser_cannon(posX,posY);
	velocidad=0;}}else{
		remove_laser_cannon(posX,posY);
		posX=posX+4;
		display_laser_cannon(posX,posY);
	}}
	}
