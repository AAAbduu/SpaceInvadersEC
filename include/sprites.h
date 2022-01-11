#ifndef _sprites
#define _sprites
/**********************************************************
 * sprites.h
 **********************************************************/

extern u16* gfx_laser_cannon;
extern u16* gfx_crab_alien;

extern void init_sprite_memory();

extern void set_main_palette();
extern void set_secondary_palette();

extern void alloc_sprites_in_memory();

extern void movimiento_general_aleatorio();

extern void display_laser_cannon(int x, int y);
extern void remove_laser_cannon(int x, int y);

extern void display_crab_alien(int index, int x, int y);
extern void remove_crab_alien(int index, int x, int y);

extern void display_projectile(int index, int x, int y);
extern void remove_projectile(int index, int x, int y);

#endif
