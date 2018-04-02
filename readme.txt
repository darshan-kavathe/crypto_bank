Description:
============
This project contain sample code for bank-wallet system with following functionality:
(doubloon is a imaginary crypto-coin and building 1 is a bank)
By implementation, all coins have unique id and can be only moved and not copied.

Here are the full list of commands:
    debug
        - toggle debugging of the doubloons. gets you in and out of debug mode.
    deposit
    	- deposit doubloon into building 1 vault (from front of wallet)
    doubloon id
    	- list a doubloon in the building 1 vault by id
    fedora #
    	- fedoras song: decrease value of all coins in vault by #
    gun id
    	- prelude to gunbrella: destroy a coin in vault by id
    help
    	- this help message
    quit
    	- end program
    ritchie #
    	- ritchie's lullaby: increase value of all coins in vault by #
    sos #
    	- song of storms: mint # coins
    vault
        - display all doubloons in building 1 vault
    wallet
        - display all doubloons in wallet
    withdraw id
        - withdraw a doubloon from building 1 vault (into back of wallet)

Instruction:
============
1.change directory to ../src$:
2.compile:
g++ -g -gdwarf-2 -Wall -Wextra -Weffc++ -pedantic -std=c++17 -c dd_main.cpp the_loop.cpp building_one.cpp destler_doubloon.cpp rng.cpp
3.Executable:
g++ -o dd_main dd_main.o the_loop.o building_one.o destler_doubloon.o rng.o
run:
./dd_main ../output/input1.txt > my_output1.txt

cross-check with test files:
diff my_output1.txt ../output/output1.txt

Remove object files and executable
rm *.o 
rm dd_main
