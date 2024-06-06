#include "Fruct.h"

#define WIDTH 50
#define HEIGHT 25

void Fruct::gen_fruct()
{
	pos.X = (rand() % (WIDTH - 2)) + 1;
	pos.Y = (rand() % (HEIGHT - 2)) + 1;
}

COORD Fruct::get_pos() {return pos;}
