#ifndef SARPE_H
#define SARPE_H

#include <vector>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 25

using namespace std;

class Sarpe
{
private:
    COORD pos;
    int len;
    int vel;
    char direction;
    vector<COORD> corp;
    

public:
    Sarpe(COORD pos, int vel);
    void crestere();
    void schimba_dir(char dir);
    void mutare_sarpe();
    vector<COORD> get_corp();
    bool coliziune();
    bool mancat(COORD fruct_pos);
    COORD get_pos();
    int get_len() const {
        return len;
    }
    
    void set_pos(const COORD& new_pos) {
        pos = new_pos;
    }
    void set_len(int new_len) {
        len = new_len;
    }
    void set_corp(const vector<COORD>& new_corp) {
        corp = new_corp;
    }


};

#endif // SARPE_H


