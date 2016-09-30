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

        // load the queues from the db

        cout << ">>> ";
        cin >> input;

        if (input == "quit") {
            stop ();
        }

    }
}

void Engine::stop () {
    logger->debug  (__PRETTY_FUNCTION__);

    running = false;
}



