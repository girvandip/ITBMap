#ifndef USERINPUT_H
#define USERINPUT_H

#include <thread>

class UserInput {
    public:
        UserInput();
        ~UserInput();
        bool getKeyPress(int c);

    private:
        void inputHandler();
        std::thread inputThread;
        bool keyStates[255];
        bool active;
};

#endif
