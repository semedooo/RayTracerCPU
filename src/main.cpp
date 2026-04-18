#include <iostream>
#include <limits>
#include "Menu.h"
#include "RenderTests.h"

using namespace std;

int main() {
    int op;
    op = -1;

    while (op!=0) {
        printMenu();
        cin >> op;

        if (cin.fail()) {
            cout << "Error: invalid input!" << endl;
            return 1;
        }

        switch (op) {
            case 1: {
                runCenteredSphereRenderTest();
                break;
            }
            case 2: {
                runGroundPlaneRenderTest();
                break;
            }
            case 3: {
                runThreeSpheresRenderTest();
                break;
            }
            case 4: {
                runSphereAndPlaneRenderTest();
                break;
            }
            case 5: {
                runCustomSceneRenderTest();
                break;
            }
            case 0:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Error: invalid operation!" << endl;
                break;
        }
        if (op != 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press Enter to continue...";
            cin.get();
            cout << endl;
        }
    }

    return 0;
}
