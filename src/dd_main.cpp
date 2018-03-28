#include <iostream>
#include <fstream>

#include "the_loop.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ios_base;
using std::istream;
using std::filebuf;

/**
 * The main program for Destler Doubloons.  It is run on the command line as:
 *
 * $ dd_main [input-file]
 *
 * If an input file is specified, the commands are read from it.  Otherwise
 * standard input is used to read the commands.
 *
 * @author Sean Strout @ RIT CS
 *
 * @param argc number of command line arguments
 * @param argv the command line arguments
 * @return 0
 */
int main(int argc, char* argv[]) {
    filebuf inbuf;

    // check if an input file was specified
    if (argc > 2) {
        cerr << "Usage: dd_main [input-file]" << endl;
        return 0;
    } else if (argc == 2) {
        if (!inbuf.open(argv[1], ios_base::in)) {
            cerr << "Error opening file " << argv[1] << endl;
            return 0;
        }
    }

    // create input stream from input file or cin
    istream is(inbuf.is_open() ? &inbuf : cin.rdbuf());

    // create the loop and enter the main loop
    TheLoop the_loop(is, !inbuf.is_open());
    the_loop.main_loop();

    return 0;
}
