#include <iostream>
#include <thread>
#include <chrono>

//#include "spdlog/spdlog.h"

#include "index/Indexer.h"
#include "Engine.h"

using namespace std;
//using namespace spdlog;

int main (int argc, char *argv[]) {
    Engine e;

    e.start ();

    this_thread::sleep_for (chrono::seconds (10));

    e.stop ();

    return 0;
}
