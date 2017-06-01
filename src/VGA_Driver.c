#include <stdint-gcc.h>
#include "strfuncs.h"
#define START 0xb8000
#define WIDTH 80
#define HEIGHT 25


typedef struct display_character {
   char character;
   uint8_t t_color:4;
   uint8_t bg_color:3;
   uint8_t blink:1;
}__attribute__((packed)) display_character;

int cursor = 0;

int VGA_row_count() {
   return HEIGHT;
}

int VGA_col_count() {
   return WIDTH;
}

void next_line() {
   cursor = cursor + 80 - (cursor % 80);
}

extern void VGA_clear(void) {
   display_character *screen = (display_character *) START;
   int i = 0;

   for (i=0; i < WIDTH * HEIGHT; i++) {
      screen[i].character = ' ';
      screen[i].bg_color = 0;
      screen[i].t_color = 0xD;
   }
}

void find_space() {
   display_character *screen = (display_character *) START;
   display_character screencpy[WIDTH * (HEIGHT - 1)];
   int i;

   if (cursor >= WIDTH * HEIGHT) {
      for (i = 0; i < (WIDTH * (HEIGHT - 1)); i++) {
         screencpy[i] = screen[i + WIDTH];
      }
      VGA_clear();

      for (i = 0; i < (WIDTH * (HEIGHT - 1)); i++) {
         screen[i] = screencpy[i];
      }

      cursor = WIDTH * (HEIGHT - 1);

   }
}

extern void VGA_display_char(char inc) {
   display_character *screen = (display_character *) START;

   if (inc == '\n') {
      next_line();
   }
   else {
      screen[cursor].character = inc;
      cursor++;
   }
   find_space();
}

extern void VGA_display_str(char *s) {
   int count = strlen(s);
   char *temp = s;
   while (count--) {
      VGA_display_char(*temp);
      temp++;
   }
}

void VGA_display_attr_char(int x, int y, char c, int fg, int bg) {
   display_character *screen = (display_character *) START;
   
   int loc = y*WIDTH + x;
   screen[loc].character = c;
   screen[loc].t_color = fg;
   screen[loc].bg_color = bg;
}

