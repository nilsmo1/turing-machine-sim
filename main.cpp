#include "TuringMachine.h"

int main(int argc, char** argv) {
    if (argc < 3) return 1;
    TuringMachine t(argv[1]);
    t.read_tape(argv[2]);
    bool step = (argc > 3) && (argv[3][0] == 'r');
    t.run(step);
    return 0;
}
