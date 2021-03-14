#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 #define EPSILON 0.0001

struct tLight{
    int dur, dist;
};

bool compDouble(double a, double b){
    return (fabs(a-b) < EPSILON);
}

int main()
{
    int speed;
    cin >> speed; cin.ignore();
    int lightCount;
    cin >> lightCount; cin.ignore();

    vector<tLight> lights;
    for(int i = 0; i < lightCount; i++) {
        int distance;
        int duration;
        cin >> distance >> duration; cin.ignore();

        tLight tempIn;
        tempIn.dist = distance;
        tempIn.dur = duration;
        lights.push_back(tempIn);
    }

    int answer = 0;
    while(answer == 0){
        for(int i = 0; i < lights.size(); i++){
            double timeSec = lights[i].dist / (double) speed / 1000  * 60 * 60;
        
            double numRounds = fmod(timeSec / lights[i].dur,2);
            bool passLight = false;

            if(numRounds < 1) passLight = true;
            if(compDouble(numRounds, (double)2)) passLight = true;

            if(!passLight) break;
            if( (i + 1) == lights.size() ) answer = speed;
        }
        speed--;
    }
    
    cout << answer << endl;
}
