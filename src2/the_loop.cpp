#include "the_loop.h"

#include <iomanip>
#include <memory>
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

    /*
     * debug - toggle debugging of the doubloons
     */
    commands_["debug"] = []() {
        DestlerDoubloon::DEBUG = !(DestlerDoubloon::DEBUG);
    };

    /*
     * deposit- deposit doubloon into building 1 vault (from front of wallet)
     */
    commands_["deposit"] = [this]() {
        this->b1_.deposit(std::move(wallet_.front()));
        this->wallet_.pop_front();
    };

    /*
     * doubloon id - list a doubloon in the building 1 vault by id
     */
    commands_["doubloon"] = [this]() {
        unsigned long long int id_;
        in_>>std::hex>>id_>>std::dec;
        try {
            std::cout << (this->b1_.doubloon(id_)) << std::endl;
        }catch(DDException& nd){
            std::cout<<nd.what()<<std::endl;
        }
    };

    /*
     * fedora #- fedoras song: decrease value of all coins in vault by #
     */
    commands_["fedora"] = [this]() {
        double value_;
        in_>>value_;
        this->b1_.bear_market(value_);
    };

    /*gun id
     *  - prelude to gunbrella: destroy a coin in vault by id*/
    commands_["gun"] = [this]() {
        unsigned long long int id_;
        in_>>std::hex>>id_>>std::dec;
        try {
            this->b1_.destroy(id_);
        }catch(DDException& nd){
            std::cout<<nd.what()<<std::endl;
        }
    };

    /*ritchie #
    	- ritchie's lullaby: increase value of all coins in vault by #*/
    commands_["ritchie"] = [this]() {
        double value_;
        in_>>value_;
        this->b1_.bull_market(value_);
    };

    /*sos #
    	- song of storms: mint # coins*/
    commands_["sos"] = [this]() {
        unsigned int num_;
        in_>>num_;
        this->b1_.mint(num_);
    };

    /*vault
        - display all doubloons in building 1 vault*/
    commands_["vault"] = [this]() {
        std::cout<<this->b1_;
    };

    /*wallet
        - display all doubloons in wallet*/
    commands_["wallet"] = [this]() {
        if(this->wallet_.size()==0){
            std::cout<<"wallet is empty!"<<std::endl;
        }else {
            for (auto it = this->wallet_.begin(); it != wallet_.end(); it++) {
                cout << *(*(it)) << std::endl;
            }
        }
    };

    /*withdraw id
        - withdraw a doubloon from building 1 vault (into back of wallet)*/
    commands_["withdraw"] = [this]() {
        unsigned long long int id_;
        in_ >> std::hex >> id_ >> std::dec;
        if (this->b1_.num_doubloons() == 0) {
            std::cout << "the vault is empty!" << std::endl;
        }
        else {
            try {
                this->wallet_.push_back(this->b1_.withdraw(id_));
            } catch (DDException &nd) {
                std::cout << nd.what() << std::endl;
            }
        }
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
    //return all doubloon from wallet to vault
    unsigned long long int w_coins= this->wallet_.size();
    if(w_coins>0){
        std::cout<<"returning doubloons in wallet to bank!\n";
    }
    for(unsigned long long int i=0; i<w_coins;i++){
        this->b1_.deposit(std::move(wallet_.front()));
        this->wallet_.pop_front();
    }
    // display the vault statistics
    std::cout<<"doubloons in vault: "<<(this->b1_.num_doubloons())<<std::endl;
    std::cout<<"total worth: "<<this->b1_.total_worth()<<std::endl;
}
