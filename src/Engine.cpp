//
// Created by ololosh on 9/29/16.
//

#include <thread>
//#include <chrono>
#include <iostream>
#include <string>

#include "Engine.h"

using namespace std;

// TODO: init implementation
void Engine::start () {
    logger->debug (__PRETTY_FUNCTION__);

    running = true;

    string input;

    while (running) {
        this_thread::sleep_for (chrono::seconds (1));

        cout << ">>> ";
        cin >> input;

        if (input == "quit") {
            stop ();
        }

        // TODO:: threads start up
    }
}

void Engine::stop () {
    logger->debug  (__PRETTY_FUNCTION__);

    running = false;
}



