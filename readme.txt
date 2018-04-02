compile:
g++ -g -gdwarf-2 -Wall -Wextra -Weffc++ -pedantic -std=c++17 -c dd_main.cpp the_loop.cpp building_one.cpp destler_doubloon.cpp rng.cpp
Executable:
g++ -o dd_main dd_main.o the_loop.o building_one.o destler_doubloon.o rng.o
run:
./dd_main ../output/input1.txt > my_output1.txt

cross-check with test files:
diff my_output1.txt ../output/output1.txt
