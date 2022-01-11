/**********************************************************
 * controllers.c
 **********************************************************/

/*
 * Añadir los includes que sean necesarios
 **/
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "keypad_screen.h"
#include "timers.h"


/*
 * Habilitar las interrupciones. En el Controlador de Interrupciones
 **/
void enable_interrupts() {

  /*
   * Primero se inhiben todas las interrupciones
   **/
	IME = 0;

  // Escribir un 1 en el bit correspondiente
	// 3322|2222|2222|1111|1111|1000|0000|0000
	// 1098|7654|3210|9876|5432|1098|7654|3210
	// 0000|0000|0000|0000|0001|0000|0000|1000
	//   0    0    0    0    1    0    0    8



  /*
   * Escribir un 1 en el bit correspondiente
   **/
	IE = (IE | 0x00001038);


  /*
   * Se vuelven a habilitar todas las interrupciones
   **/
	 IME = 1;


} // enable_interrupts()


/*
 * Programar los registros de control. Aquí es donde se configuran los
 * registros de control de los periféricos.
 **/
void configure_control_registers() {

  /*
   * Registro de Control del Teclado
   **/


  /*
   * Registro de Control de los Temporizadores
   *   TIMER0_CNT
   *     El temporizador se activa poniendo un 1 en el bit 7.
   *     El temporizador interrumpirá al desbordarse el contador,
   *        si hay un 1 en el bit 6.
   *     Los dos bits de menos peso indican lo siguiente:
   *        00 frecuencia 33554432 hz
   *        01 frecuencia 33554432/64 hz
   *        10 frecuencia 33554432/256 hz
   *        11 frecuencia 33554432/1024 hz
   *   TIMER0_DAT
   *     Se utiliza para indicar a partir de que valor tiene que empezar
   *        a contar (latch)
   **/



//Interrumpo 1 vez por segundo t0: Para calcular el timer_DAT se hace esta operacion: x = 65536 - (1/VECESporSegundoQueInterrumpo)*(FrecuenciaAsignada en TIEMR_CNT)
    TIMER0_DAT =  32768;
		TIMER0_CNT = (TIMER0_CNT | 0x00C3);
//Interrumpo 2 vez por segundo t1:
		TIMER1_DAT=54613;
		TIMER1_CNT = (TIMER1_CNT | 0x00C3);
//Interrumpo 3 vez por segundo t2:
		TIMER2_DAT=54613;
		TIMER2_CNT = (TIMER2_CNT | 0x00C3);

    KEYS_CNT = (KEYS_CNT|0x400F);
}

 // configure_control_registers()



/*
 * Este procedimiento inicializa el vector de interrupciones para que
 * el gestor de interrupciones sepa que rutina de atencion tiene que
 * ejecutar cuando le llega una peticion de interrupcion.
 **/
void define_interrupt_vector_table() {

  /*
   * Rutina de Atencion al Teclado
   **/ irqSet(IRQ_KEYS, keypad_handler);


  /*
   * Rutinas de Atencion a los Temporizadores
   **///
  irqSet(IRQ_TIMER0, timer_handler);
	irqSet(IRQ_TIMER1,movimiento_handler_t1);
	irqSet(IRQ_TIMER2,handler_t2_disparar);


} // DefinirVectorInterrupciones()


/*
 * Inhibe las interrupciones. En el Controlador de Interrupciones
 **/
void disable_interrupts() {

  /*
   * Primero se inhiben todas las interrupciones
   **/
  IME = 0;


  /*
   * Escribir un 0 en el bit correspondiente
   **/

IE = (IE & 0xFFFFEFC7);

  /*
   * Se vuelven a habilitar todas las interrupciones
   **/

   IME = 1;

} // disable_interrupts()



void interrupts_setting() {

  enable_interrupts();
  configure_control_registers();
  define_interrupt_vector_table();

}  // interrupts_setting()
