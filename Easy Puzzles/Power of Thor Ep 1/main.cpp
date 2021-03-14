#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum Direction{ E, W, N, NE, NW, S, SE, SW};

int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();

    // game loop
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();

        int xVal = initialTX - lightX;
        int yVal = initialTY - lightY;
        int final = 0;

        if(yVal > 0) final += 2;
        if(yVal < 0 && (initialTY < 18)){final += 5;}
        if(yVal == 0) final-=1;
        

        if(xVal < 0) final += 1;
        if(xVal > 0) final += 2;

        switch(final){
            case 0: cout << "E" << endl; initialTX += 1; break;
            case 1: cout << "W" << endl; initialTX -= 1; break;
            case 2: cout << "N" << endl; initialTY -= 1; break;
            case 3: cout << "NE" << endl; initialTY -= 1; initialTX += 1; break;
            case 4: cout << "NW" << endl; initialTY -= 1; initialTX -= 1; break;
            case 5: cout << "S" << endl; initialTY += 1; break;
            case 6: cout << "SE" << endl; initialTY += 1; initialTX += 1; break;
            case 7: cout << "SW" << endl; initialTY += 1; initialTX -= 1; break;
            default: break;
        }
    }
}
