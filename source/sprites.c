/**********************************************************
 * sprites.c
 *
 * Este codigo se ha implementado basandose en el ejemplo
 * "Simple sprite demo" de dovoto y otro de Jaeden Amero
 **********************************************************/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sprites.h"
#include "defines.h"

u16* gfx_laser_cannon;
u16* gfx_crab_alien;
u16* gfx_projectile;

/*
 * Dibujado de un sprite de 16x16 pixels
 * Debido al funcionamiento de los bancos de memoria, las primeras cuatro filas
 * forman el cuadrante superior izquiero, las siguientes, el cuadrante superior
 * derecho, las siguientes el cuadrante inferior izquierdo y las últimas cuatro
 * filas, el cuadrante inferior derecho, como se muestra al lado.
 */

u8 laser_cannon[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,12,0,0,0,0,0,0,12,12, 				// 0000000000000000
	0,0,0,0,0,0,12,12,0,12,12,12,12,12,12,12, 			// 0000000000000000

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 00000001200000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000001212120000000
	0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0, 					// 0000001212120000000
	12,0,0,0,0,0,0,0,12,12,12,12,12,12,0,0, 			// 01212121212121212121212121200

	12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12, 	// 1212121212121212121212121212120
	12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,	// 1212121212121212121212121212120
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 1212121212121212121212121212120
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 1212121212121212121212121212120

	12,12,12,12,12,12,12,0,12,12,12,12,12,12,12,0, 		// 0000000000000000
	12,12,12,12,12,12,12,0,12,12,12,12,12,12,12,0, 		// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
};

u8 crab_alien[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,4,0,0,0,0,0,0,0,0,4,0,0, 					// 0000000000000000
	0,0,0,0,4,4,4,4,0,0,0,4,4,0,4,4, 					// 0000000000000000

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000400000400000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000040004000000
	0,0,4,0,0,0,0,0,0,4,0,0,0,0,0,0, 					// 0000444444400000
	4,4,4,0,0,0,0,0,4,0,4,4,0,0,0,0, 					// 0004404440440000

	0,0,4,4,4,4,4,4,0,0,4,0,4,4,4,4, 					// 0044444444444000
	0,0,4,0,4,0,0,0,0,0,0,0,0,4,4,0, 					// 0040444444404000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0040400000404000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000044044000000

	4,4,4,4,4,0,0,0,4,4,4,0,4,0,0,0, 					// 0000000000000000
	0,0,4,0,4,0,0,0,4,4,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
};

u8 projectile[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,12,0,0,0,0,0,0,12,0, 					// 0000000000000000
	0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0, 					// 0000000000000000

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 00000001200000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 00000012000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 00000001200000000
	0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0, 					// 00000000120000000

	0,0,0,0,0,0,0,12,0,0,0,0,0,0,12,0, 					// 00000001200000000
	0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0, 					// 00000012000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 00000001200000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 					// 0000000000000000
};

/*
 * Inicializar la memoria de sprites.
 **/
void init_sprite_memory() {
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	gfx_laser_cannon = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfx_crab_alien   = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfx_projectile   = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);

} // init_sprite_memory()


/*
 * Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */

void set_main_palette() {
                                         // 0: TRANSPARENTE
   SPRITE_PALETTE[1]  = RGB15(31,0,0);   // ROJO:           RGB24={FF,00,00}
   SPRITE_PALETTE[2]  = RGB15(31,31,0);  // AMARILLO:       RGB24={FF,FF,00}
   SPRITE_PALETTE[3]  = RGB15(31,31,31); // BLANCO:         RGB24={FF,FF,FF}
   SPRITE_PALETTE[4]  = RGB15(0,31,0);   // VERDE:          RGB24={00,FF,00}
   SPRITE_PALETTE[5]  = RGB15(0,0,31);   // AZUL:           RGB24={00,00,FF}
   SPRITE_PALETTE[6]  = RGB15(0,0,0);    // NEGRO:          RGB24={00,00,00}
   SPRITE_PALETTE[7]  = RGB15(0,31,31);  // CYAN:           RGB24={00,FF,FF}
   SPRITE_PALETTE[8]  = RGB15(31,0,31);  // MAGENTA:        RGB24={FF,00,FF}
   SPRITE_PALETTE[9]  = RGB15(16,16,16); // GRIS:           RGB24={80,80,80}
   SPRITE_PALETTE[10] = RGB15(25,25,25); // GRIS CLARO:     RGB24={D0,D0,D0}
   SPRITE_PALETTE[11] = RGB15(8,8,8);    // GRIS OSCURO:    RGB24={40,40,40}
   SPRITE_PALETTE[12] = RGB15(31,19,0);  // NARANJA:        RGB24={FF,99,00}
   SPRITE_PALETTE[13] = RGB15(19,0,4);   // GRANATE:        RGB24={99,00,21}
   SPRITE_PALETTE[14] = RGB15(25,0,0);   // MARRON:         RGB24={66,00,00}
   SPRITE_PALETTE[15] = RGB15(16,0,16);  // MORADO:         RGB24={80,00,80}
   SPRITE_PALETTE[16] = RGB15(25,19,31); // LILA:           RGB24={CC,99,FF}
   SPRITE_PALETTE[17] = RGB15(31,19,25); // ROSA:           RGB24={FF,99,CC}
   SPRITE_PALETTE[18] = RGB15(23,21,21); // AZUL CLARO:     RGB24={BB,FF,FF}
   SPRITE_PALETTE[19] = RGB15(0,0,16);   // AZUL MARINO:    RGB24={00,00,80}
   SPRITE_PALETTE[20] = RGB15(0,16,16);  // VERDE AZULADO:  RGB24={00,80,80}
   SPRITE_PALETTE[21] = RGB15(0,12,0);   // VERDE OSCURO:   RGB24={00,66,00}
   SPRITE_PALETTE[22] = RGB15(16,16,0);  // VERDE OLIVA:    RGB24={80,80,00}
   SPRITE_PALETTE[23] = RGB15(19,31,19); // VERDE CLARO:    RGB24={99,FF,99}
   SPRITE_PALETTE[24] = RGB15(31,31,19); // AMARILLO CLARO: RGB24={FF,FF,99}
} // set_main_palette()

/*
 * Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256
 * colores posibles en la pantalla secundaria. El 0 es transparente y los no definidos son negros.
 */

void set_secondary_palette() {
   SPRITE_PALETTE_SUB[1] = RGB15(0,31,0);   // los pixels a 1 se mostrarán verdes
   SPRITE_PALETTE_SUB[2] = RGB15(31,31,31); // los pixels a 1 se mostrarán blancos
   SPRITE_PALETTE_SUB[3] = RGB15(31,31,0);  // los pixels a 1 se mostrarán amarillos
} // set_secondary_palette()


/*
 *Para guardar los sprites en memoria y luego poder usarlos.
 **/
void alloc_sprites_in_memory() {
  int i;
  for(i = 0; i < 16 * 16 / 2; i++){ //muestra un cuadrado en la memoria de la pantalla principal
     gfx_crab_alien[i]   = crab_alien[i*2]   | (crab_alien[(i*2)+1]<<8);
     gfx_laser_cannon[i] = laser_cannon[i*2] | (laser_cannon[(i*2)+1]<<8);
     gfx_projectile[i]   = projectile[i*2]   | (projectile[(i*2)+1]<<8);
  }
} // alloc_sprites_in_memory()



/*
 * Funciones especificas para manejar los sprites.
 **/

void display_laser_cannon(int x, int y) {
	oamSet(&oamMain, 	//main graphics engine context
		127,     		//oam index (0 to 127)
		x, y,    		//x and y pixel location of the sprite
		0,       		//priority, lower renders last (on top)
		0,	 			//this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_laser_cannon,	//+16*16/2,	//pointer to the loaded graphics
		-1,             //sprite rotation data
		false,          //double the size when rotating?
		false,			//hide the sprite?
		false, false, 	//vflip, hflip
		false			//apply mosaic
	);
	oamUpdate(&oamMain);
} // display_laser_cannon()

void remove_laser_cannon(int x, int y) {
	oamSet(&oamMain, 	//main graphics engine context
		127,     		//oam index (0 to 127)
		x, y,    		//x and y pixel location of the sprite
		0,       		//priority, lower renders last (on top)
		0,	 			//this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_laser_cannon,	//+16*16/2,	//pointer to the loaded graphics
		-1,             //sprite rotation data
		false,          //double the size when rotating?
		true,			//hide the sprite?
		false, false, 	//vflip, hflip
		false			//apply mosaic
	);
	oamUpdate(&oamMain);
} // remove_laser_cannon()

void display_crab_alien(int index, int x, int y) {
	oamSet(&oamMain, 	//main graphics engine context
		index,  		//oam index (0 to 127)
		x, y,    		//x and y pixel location of the sprite
		0,       		//priority, lower renders last (on top)
		0,	 			//this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_crab_alien,		//+16*16/2, 	//pointer to the loaded graphics
		-1,             //sprite rotation data
		false,          //double the size when rotating?
		false,			//hide the sprite?
		false, false, 	//vflip, hflip
		false			//apply mosaic
	);
	oamUpdate(&oamMain);
} // display_crab_alien()

void remove_crab_alien(int index, int x, int y) {
	oamSet(&oamMain, 	//main graphics engine context
		index,  		//oam index (0 to 127)
		x, y,    		//x and y pixel location of the sprite
		0,       		//priority, lower renders last (on top)
		0,	 			//this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_crab_alien,		//+16*16/2, 	//pointer to the loaded graphics
		-1,            	//sprite rotation data
		false,         	//double the size when rotating?
		true,			//hide the sprite?
		false, false, 	//vflip, hflip
		false			//apply mosaic
	);
	oamUpdate(&oamMain);
} // remove_crab_alien()

void display_projectile(int index, int x, int y) {
	oamSet(&oamMain, 	//main graphics engine context
		index,  		//oam index (0 to 127)
		x, y,    		//x and y pixel location of the sprite
		0,       		//priority, lower renders last (on top)
		0,	 			//this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_projectile,		//+16*16/2, 	//pointer to the loaded graphics
		-1,             //sprite rotation data
		false,          //double the size when rotating?
		false,			//hide the sprite?
		false, false, 	//vflip, hflip
		false			//apply mosaic
	);
	oamUpdate(&oamMain);
} // display_projectile()

void remove_projectile(int index, int x, int y) {
	oamSet(&oamMain, 	//main graphics engine context
		index,  		//oam index (0 to 127)
		x, y,    		//x and y pixel location of the sprite
		0,       		//priority, lower renders last (on top)
		0,	 			//this is the palette index if multiple palettes or the alpha value if bmp sprite
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_projectile,		//+16*16/2, 	//pointer to the loaded graphics
		-1,            	//sprite rotation data
		false,         	//double the size when rotating?
		true,			//hide the sprite?
		false, false, 	//vflip, hflip
		false			//apply mosaic
	);
	oamUpdate(&oamMain);
} // remove_projectile()

//Metodo que se encarga de mover aleatoriamente los aliens al interrumpir el timer.
void movimiento_general_aleatorio(){
	for(int i = 0; i<num_aliens;i++){
		int x = rand () % (3-1+1) + 1;
		switch (x) {
			case 1: //DERECHA
				if((0<tc[i].x<230) && (tc[i].state == 1)){
					remove_crab_alien(tc[i].id,tc[i].x,tc[i].y);
					tc[i].x = tc[i].x +2;
					display_crab_alien(tc[i].id,tc[i].x,tc[i].y);

				}break;
				case 2: //IZQUIERDA
					if((0<tc[i].x<230) && (tc[i].state == 1)){
						remove_crab_alien(tc[i].id,tc[i].x,tc[i].y);
						tc[i].x = tc[i].x -2;
						display_crab_alien(tc[i].id,tc[i].x,tc[i].y);

					}break;
					case 3: //ABAJO
						if((0<tc[i].x<230)&&(0<tc[i].y<160)&& (tc[i].state == 1)){
							remove_crab_alien(tc[i].id,tc[i].x,tc[i].y);
							tc[i].y = tc[i].y +2;
							display_crab_alien(tc[i].id,tc[i].x,tc[i].y);

						}break;

		}

	}
}
