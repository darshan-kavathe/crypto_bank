#ifndef THE_LOOP_H
#define THE_LOOP_H

#include <deque>
#include <functional>
#include <iostream>

#include "building_one.h"

/**
 * The loop is where RIT community members get a chance to interact with
 * Destler Doubloons.
 */
class TheLoop {
public:
    /**
     * Create the loop.
     *
     * @param is the input stream, either stdin or a file
     * @param std_in true if stdin was specified, false if a file
     */
    TheLoop(std::istream& is, bool std_in);

    /**
     * The main loop.
     */
    void main_loop();

private:
    /** the input stream */
    std::istream& in_;

    /** whether input is from stdin or not */
    bool stdin_;

    /** the admin building */
    BuildingOne b1_;

    /** a wallet to store doubloons from the vault */
    std::deque<DestlerDoubloon> wallet_;

    /** a map of command strings to lambda expressions to call when
     * invoking the command. */
    std::unordered_map<std::string, std::function<void ()>> commands_;
};

#endif // THE_LOOP_H
