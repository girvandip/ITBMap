#include "UserInput.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>

void enableRawMode() {
    termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
}

void disableRawMode() {
    termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

int _kbhit(void) {
    int bytesWaiting;
    ioctl(0, FIONREAD, &bytesWaiting);
    return bytesWaiting > 0;
}

UserInput::UserInput() {
    for (unsigned char i = 0; i < 255; i++) {
        keyStates[i] = false;
    }
    active = true;
    enableRawMode();
    inputThread = std::thread(&UserInput::inputHandler, this);
}

UserInput::~UserInput() {
    active = false;
    inputThread.join();
    disableRawMode();
}

bool UserInput::getKeyPress(int c) {
    if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
        if (keyStates[c]) {
            keyStates[c] = false;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void UserInput::inputHandler() {
    while (active) {
        if (_kbhit()) {
            int c = getchar();
            if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
                keyStates[c] = true;
            }
        }
        usleep(1);
    }
}
