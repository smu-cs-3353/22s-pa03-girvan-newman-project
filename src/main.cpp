#include "GirvanNewman.h"
#include "LabelPropagationAlgo.h"
#include <chrono>

int main(int argc, char** argv) {
    GirvanNewman firstAlgo;
    firstAlgo.runAlgo(argv[1]);

    LabelPropagationAlgo secondAlgo;
    secondAlgo.runAlgo(argv[1]);
}