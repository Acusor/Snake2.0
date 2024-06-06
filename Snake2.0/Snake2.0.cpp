#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include "Sarpe.h"
#include "Fruct.h"
#include <ctime>
#include <vector>
#include <string>

#define WIDTH 50
#define HEIGHT 25

using namespace std;

int score = 0;

string username;
bool game_started = false;  

Sarpe sarpe({ WIDTH / 2, HEIGHT / 2 }, 1);
Fruct fruct;

void board()
{
    COORD sarpe_pos = sarpe.get_pos();
    COORD fruct_pos = fruct.get_pos();
    cout << "Scor: " << score << endl;

    vector<COORD> sarpe_corp = sarpe.get_corp();
    for (int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for (int j = 0; j < WIDTH - 2; j++)
        {
            if (i == 0 || i == HEIGHT - 1) cout << '#';
            else if (i == sarpe_pos.Y && j + 1 == sarpe_pos.X) cout << 'O';
            else if (i == fruct_pos.Y && j + 1 == fruct_pos.X) cout << "@";
            else
            {
                bool ParteCorp = false;
                for (int k = 0; k < sarpe_corp.size() - 1; k++)
                {
                    if (i == sarpe_corp[k].Y && j + 1 == sarpe_corp[k].X)
                    {
                        cout << 'o';
                        ParteCorp = true;
                        break;
                    }
                }
                if (!ParteCorp) cout << ' ';
            }
        }
        cout << "#\n";
    }
}

void save_score()
{
    ofstream file("score.txt", ios::app);
    if (file.is_open())
    {
        file << "Nume utilizator: " << username << " - Scor: " << score << endl;
        file.close();
    }
    else
    {
        cerr << "Unable to open file for writing!" << endl;
    }
}

void save_game_state()
{
    ofstream file("game_state.txt");
    if (file.is_open())
    {
        file << username << endl;
        file << score << endl;

        COORD pos = sarpe.get_pos();
        file << pos.X << " " << pos.Y << endl;

        file << sarpe.get_len() << endl;

        vector<COORD> sarpe_corp = sarpe.get_corp();
        for (COORD segment : sarpe_corp)
        {
            file << segment.X << " " << segment.Y << " ";
        }
        file << endl;

        COORD fruct_pos = fruct.get_pos();
        file << fruct_pos.X << " " << fruct_pos.Y << endl;

        file.close();
    }
    else
    {
        cerr << "Nu se poate deschide fisierul pentru scriere!" << endl;
    }
}

bool load_game_state()
{
    ifstream file("game_state.txt");
    if (file.is_open())
    {
        file >> username;
        file >> score;

        COORD pos;
        file >> pos.X >> pos.Y;
        sarpe.set_pos(pos);

        int len;
        file >> len;
        sarpe.set_len(len);

        vector<COORD> sarpe_corp;
        COORD segment;
        while (file >> segment.X >> segment.Y)
        {
            sarpe_corp.push_back(segment);
        }
        sarpe.set_corp(sarpe_corp);

        COORD fruct_pos;
        file >> fruct_pos.X >> fruct_pos.Y;
        fruct.set_pos(fruct_pos);

        file.close();
        return true;
    }
    else
    {
        cerr << "Nu s-a gasit joc salvat!" << endl;
        return false;
    }
}



void game()
{
    srand(time(NULL));
    fruct.gen_fruct();
    while (true)
    {
     
        board();

        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w': sarpe.schimba_dir('u'); break;
            case 's': sarpe.schimba_dir('d'); break;
            case 'a': sarpe.schimba_dir('l'); break;
            case 'd': sarpe.schimba_dir('r'); break;
            case 'p':
                save_game_state();
                cout << "Pauza joc.Apasa o tasta pentru a reveni in meniu..\n";
                _getch();
                return;
            }
        }
        if (sarpe.coliziune())
        {
            cout << "Sfarsit de joc!" << endl;
 
            save_score();
            game_started = false;  
            system("pause");
            return;
        }

        if (sarpe.mancat(fruct.get_pos()))
        {
            fruct.gen_fruct();
            sarpe.crestere();
            score++;
        }

        sarpe.mutare_sarpe();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
        Sleep(50);
    }
}

void display_info()
{
    system("cls");
    cout << "\n\n\n\t\tInformatii Joc Snake\n";
    cout << "\t\t----------------------\n";
    cout << "\t\tComenzi:\n";
    cout << "\t\tW - Deplasare in sus\n";
    cout << "\t\tS - Deplasare in jos\n";
    cout << "\t\tA - Deplasare in stanga\n";
    cout << "\t\tD - Deplasare in dreapta\n";
    cout << "\t\tP - Pune jocul in pauza";
    cout << "\t\t\n";
    cout << "\t\tObiectiv:\n";
    cout << "\t\tMananca fructele (@) pentru a creste si a iti mari scorul.\n";
    cout << "\t\tEvita sa lovesti peretii sau sa te lovesti de tine pentru a continua jocul. \n";
    cout << "\t\t\n";
    cout << "\t\tInfo autor:Zavate Panait Iustin,grupa 3121b\n";
    cout << "\t\t\n";
    cout << "\t\tIntrodu o tasta pentru a reveni in meniu.\n";
    _getch();
}

void display_scores()
{
    system("cls");
    ifstream file("score.txt");
    if (file.is_open())
    {
        string line;
        cout << "\n\n\n\t\tScoruri jucatori\n";
        cout << "\t\t-----------\n";
        while (getline(file, line))
        {
            cout << "\t\t" << line << endl;
        }
        file.close();
    }
    else
    {
        cerr << "Nu se poate deschide fisierul!" << endl;
    }
    cout << "\n\t\tIntrodu o tasta pentru a reveni in meniu.\n";
    _getch();
}


void menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    char optiune;
    while (true)
    {
        system("cls");

        int x = columns / 2 - 10;
        int y = rows / 2 - 6; 

        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)y });
        cout << "***Snake Game***\n";

        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)(y + 1) }); 
        if (!game_started) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "1. Incepe joc\n";
        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "1. Incepe joc (In Progres)\n";
        }

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)(y + 2) }); 

        if (!game_started) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        }
        cout << "2. Continua jocul\n";

        
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)(y + 3) });
        cout << "3. Info\n";
        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)(y + 4) });
        cout << "4. Vizualizeaza scoruri\n";
        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)(y + 5) });
        cout << "5. Iesire\n";
        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)(y + 6) });
        cout << "Introduceti o optiune: ";
        optiune = _getch();

        switch (optiune)
        {
        case '1':
            system("cls");
            cout << "Introdu nume utilizator: ";
            cin >> username;
            system("cls");
            sarpe = Sarpe({ WIDTH / 2, HEIGHT / 2 }, 1);
            fruct = Fruct();
            score = 0;
            game_started = true;
            game();
            break;
        case '2':
            if (game_started)
            {
                if (load_game_state()) {
                    system("cls");
                    game();
                }
                else {
                    cout << "Nu s-a gasit joc salvat!" << endl;
                    system("pause");
                }
            }
            else {
                cout << "Nu s-a inceput jocul!" << endl;
                system("pause");
            }
            break;
        case '3':
            display_info();
            break;
        case '4':
            display_scores();
            break;
        case '5':
            system("cls");
            cout << "Ati ales sa parasiti programul...";
            exit(0);
        default:
            cout << "\n\t\tAlegere invalida,incearca din nou!\n";
            system("pause");
        }
    }
}







int main()
{
    game_started = false;
    menu();
    return 0;
}
