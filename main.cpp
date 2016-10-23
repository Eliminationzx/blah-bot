#include <iostream>
#include <thread>
#include <chrono>

//#include "spdlog/spdlog.h"

#include "src/index/Worker.h"
#include "Engine.h"

using namespace std;
//using namespace spdlog;

int main (int argc, char *argv[]) {
    cout << "Hello, world!\n";

    Engine e;

    e.start ();

    this_thread::sleep_for (chrono::seconds (3)):

    e.stop ();

    return 0;
}
