#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int enumDir(string dir){
    if(dir == "U") return 0;
    if(dir == "L") return 1;
    if(dir == "R") return 2;
    if(dir == "D") return 3;
    if(dir == "DR") return 4;
    if(dir == "DL") return 5;
    if(dir == "UR") return 6;
    if(dir == "UL") return 7;
    return 8;
}

bool enumUp(string dir){
    if(dir == "U" || dir == "UR" || dir == "UL") return true;
    return false;
}

bool enumRight(string dir){
    if(dir == "UR" || dir == "R" || dir == "DR") return true;
    return false;
}

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();

    int X, Y;
    cin >> X >> Y; cin.ignore();

    int xL = 0, yL = 0;
    int xR = W - 1;
    int yR = H - 1;

    while(1){
        string dir;
        cin >> dir; cin.ignore();

        switch(enumDir(dir)){
            case 0: //U
                yR = Y;
                Y = Y - ceil((yR - yL) / 2.0);
                break;
            case 1: //L
                xR = X;
                X = X - ceil((xR - xL) / 2.0);
                break;
            case 2: // R
                xL = X;
                X = X + ceil((xR - xL) / 2.0);
                break;
            case 3: // D
                yL = Y;
                Y = Y + ceil((yR - yL) / 2.0);    
                break;
            case 4: //DR
                xL = X;
                X = X + ceil((xR - xL) / 2.0);
                yL = Y;
                Y = Y + ceil((yR - yL) / 2.0);     
                break;
            case 5: // DL
                yL = Y;
                Y = Y + ceil((yR - yL) / 2.0);       
                xR = X;
                X = X - ceil((xR - xL) / 2.0);    
                break; 
            case 6: // UR
                yR = Y;
                Y = Y - ceil((yR - yL) / 2.0);
                xL = X;
                X = X + ceil((xR - xL) / 2.0);
                break;                 
            case 7: // UL
                xR = X;
                X = X - ceil((xR - xL) / 2.0);
                yR = Y;
                Y = Y - ceil((yR - yL) / 2.0);
                break; 
            default: break;
        }
        cout << X << " " << Y << endl;
    }

}
