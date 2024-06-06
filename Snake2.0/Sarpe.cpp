#include "Sarpe.h"
#include <vector>
Sarpe::Sarpe(COORD pos, int vel)
{
    this->pos = pos;
    this->vel = vel;
    len = 1;
    direction = 'n';

    corp.push_back(pos);
}

void Sarpe::schimba_dir(char dir) { direction = dir; }
void Sarpe::crestere() { len++; }
COORD Sarpe::get_pos() { return pos; }

vector <COORD> Sarpe::get_corp() { return corp; }

void Sarpe::mutare_sarpe()
{
    switch (direction)
    {
    case 'u':pos.Y -= vel; break;
    case 'd':pos.Y += vel; break;
    case 'l':pos.X -= vel; break;
    case 'r':pos.X += vel; break;

    }

    
    corp.push_back(pos);
    if (corp.size() > len) corp.erase(corp.begin());
}



bool Sarpe::mancat(COORD fruct_pos)
{
    if (fruct_pos.X == pos.X && fruct_pos.Y == pos.Y) return true;
    return false;
}


bool Sarpe::coliziune()
{
    if (pos.X<1 || pos.X>WIDTH-2 || pos.Y<1 || pos.Y>HEIGHT-2) return true;
    
    for (int i = 0; i < len - 1; i++)
    {
        if (pos.X == corp[i].X && pos.Y == corp[i].Y) return true;


    }
    return false;
}
