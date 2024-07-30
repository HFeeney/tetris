#include "PlayerController.hh"
#include "curses.h"

Action PlayerController::getAction(unsigned int maxTime) {
    timeout(maxTime);
    int input = getch();

    switch (input) {
        case KEY_LEFT:
            return LEFT;
        case KEY_RIGHT:
            return RIGHT;
        case KEY_DOWN:
            return DOWN;
        case (int) 'd':
            return ROTATE_LEFT;
        case (int) 'f':
            return ROTATE_RIGHT;
        case ERR:
        default:
            return NONE;
    }
}