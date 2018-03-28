#include "the_loop.h"

#include <iomanip>

using std::cout;
using std::endl;
using std::flush;
using std::function;
using std::hex;
using std::ios;
using std::istream;
using std::move;
using std::streampos;
using std::string;
using std::ws;

TheLoop::TheLoop(istream& is, bool std_in) :
        in_{is},
        stdin_{std_in},
        b1_{},
        wallet_{},
        commands_{} {

    commands_["help"] = []() {
        cout <<
             "debug\n" <<
             "\t- toggle debugging of the Doubloons\n" <<
             "deposit\n" <<
             "\t- deposit Doubloon into building 1 vault (from front of wallet)\n" <<
             "Doubloon id\n" <<
             "\t- list a Doubloon in the building 1 vault by id\n" <<
             "fedora #\n" <<
             "\t- fedoras song: decrease value of all coins in vault by #\n" <<
             "gun id\n" <<
             "\t- prelude to gunbrella: destroy a coin in vault by id\n" <<
             "help\n" <<
             "\t- this help message" <<
             "quit\n" <<
             "\t- end program\n" <<
             "ritchie #\n" <<
             "\t- ritchie's lullaby: increase value of all coins in vault by #\n" <<
             "sos #\n" <<
             "\t- song of storms: mint # coins\n" <<
             "vault\n" <<
             "\t- display all Doubloons in building 1 vault\n" <<
             "wallet\n" <<
             "\t- display all Doubloons in wallet\n" <<
             "withdraw id\n" <<
             "\t- withdraw a Doubloon from building 1 vault (into back of wallet)\n";
    };
    // TODO implement lambda expressions for remaining commands here
    /*
     * debug - toggle debugging of the doubloons
     */
    commands_["debug"] = []() {
        DestlerDoubloon::DEBUG = !(DestlerDoubloon::DEBUG);
    };
    /*
     * deposit- deposit doubloon into building 1 vault (from front of wallet)
     */
    commands_["deposit"] = []() {

    };
    /*
     * doubloon id - list a doubloon in the building 1 vault by id
     */
    commands_["doubloon id"] = []() {

    };
    /*
     * fedora #- fedoras song: decrease value of all coins in vault by #
     */
    commands_["fedora"] = []() {

    };
    /*gun id
     *  - prelude to gunbrella: destroy a coin in vault by id*/
    commands_["gun id"] = []() {

    };
    /*quit
    	- end program*/
    commands_["quit"] = []() {

    };
    /*ritchie #
    	- ritchie's lullaby: increase value of all coins in vault by #*/
    commands_["ritchie"] = []() {

    };
    /*sos #
    	- song of storms: mint # coins*/
    commands_["debug"] = []() {

    };
    /*vault
        - display all doubloons in building 1 vault*/
    commands_["vault"] = []() {

    };
    /*wallet
        - display all doubloons in wallet*/
    commands_["wallet"] = []() {

    };
    /*withdraw id
        - withdraw a doubloon from building 1 vault (into back of wallet)*/
    commands_["withdraw id"] = []() {

    };
}

void TheLoop::main_loop() {
    string cmd;
    while (true) {
        if (stdin_) {
            cout << "$ " << flush;
        } else {
            // do this stream manipulation so we can print the entire line
            // if the command is coming from a file, but we want to reset
            // it before the command is read in later
            in_ >> ws;
            streampos pos{in_.tellg()};
            string line{};
            getline(in_, line);
            cout << "$ " << line << endl;
            in_.seekg(pos);
        }

        in_ >> cmd;
        if (cmd == "quit") {
            break;
        } else if (commands_.count(cmd) == 1) {
            commands_[cmd]();
        } else {
            cout << "unrecognized command!" << endl;
            // consume rest of line
            string tmp;
            getline(in_, tmp);
        }
    }

    // TODO move any Doubloons in wallet back to the vault

    // TODO display the vault statistics
}
