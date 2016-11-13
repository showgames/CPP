#include <iostream>
#include <cstdlib>
#include "game.hpp"
using namespace std;

int
inputDirection()
{
    char d;
    while(1) {
        cout << "up: w down: z left: a right: s" << endl;
        cin >> d;

        switch(d) {
            case 'w': return 0;
            break;
            case 'z': return 1;
            break;
            case 'a': return 2;
            break;
            case 's': return 3;
            break;
            default: continue;
            break;
        }
    }
    return 0;
}

int
main(int argc, char* argv[])
{ 
    int height = 5;
    int width = 8;
    char stageData[] = "#########..p   ##oo    ##      #########";

    int direction;
    STAGE stage;

    stage.init(height, width, stageData);
    while(1) {
        stage.draw();
        stage.update(inputDirection());
        system("reset");
        if (stage.checkClear()) {
            stage.draw();
            cout << "Clear!" << endl;
            return 0;
        }
    }
    return 0;
}