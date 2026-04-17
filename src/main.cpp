#include <iostream>
#include <unistd.h>
#include "Menu.h"
#include "VectorTests.h"
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
            case 1: case 2: case 3: case 4: case 5: case 6:{
                runVectorBinaryTest(op);
                break;
            }
            case 7: case 8: {
                runVectorUnaryTest(op);
                break;
            }
            case 9: {
                runGradientRenderTest();
                break;
            }
            case 10: {
                runSkyRenderTest();
                break;
            }
            case 11: {
                runSphereIntersectionRenderTest();
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
            sleep(1);
            cin.ignore(10000, '\n'); // limpa o \n residual do cin >> op
            cout << "Press Enter to continue...";
            cin.get();
            cout << endl;
        }
    }

    return 0;
}
