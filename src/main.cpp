#include <iostream>
#include <limits>
#include <string>
#include "Menu.h"
#include "RenderTests.h"

using namespace std;

namespace {
bool tryParseMenuOption(const std::string& text, int& value) {
    if (text.empty()) {
        return false;
    }

    size_t parsedChars = 0;
    try {
        int parsed = std::stoi(text, &parsedChars);
        if (parsedChars != text.size()) {
            return false;
        }
        value = parsed;
        return true;
    } catch (...) {
        return false;
    }
}

void discardPendingInputLines() {
    std::cin.clear();
    while (std::cin.rdbuf()->in_avail() > 0) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
}

int main() {
    int op = -1;

    while (op != 0) {
        printMenu();

        std::string optionText;
        if (!std::getline(std::cin, optionText)) {
            std::cout << "Error: failed to read input!" << std::endl;
            return 1;
        }

        if (!tryParseMenuOption(optionText, op)) {
            std::cout << "Error: invalid input!" << std::endl;
            continue;
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
            // Drop any keys typed while the SFML window was focused.
            discardPendingInputLines();
            cout << "Press Enter to continue...";
            std::string pauseLine;
            std::getline(std::cin, pauseLine);
            cout << endl;
        }
    }

    return 0;
}
