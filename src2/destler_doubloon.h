#ifndef DESTLER_DOUBLOON_H
#define DESTLER_DOUBLOON_H

#include <bitset>
#include <iostream>
#include <string>

/**
 * The DestlerDoubloon is the hot new crypto currency at RIT.  Each doubloon
 * that is minted has a unique 64 bit integer id, along with a monetary
 * value.  Being a currency, it is very important that the only class
 * authorized to create doubloons is BuildingOne.
 *
 * @author Sean Strout @ RIT CS
 */
class DestlerDoubloon {
public:
    /** BuildingOne is a friend.  They are the only class that is allowed
     * to create */
    friend class BuildingOne;

    /** A flag used when debugging.  If it is true the creation and
     * moving of doubloons will be displayed to standard output. */
    static bool DEBUG;

    /**
     * Copy construction is forbidden by all
     */
    DestlerDoubloon(const DestlerDoubloon& other) = delete;

    /**
     * Copy assignment is forbidden by all.
     */
    DestlerDoubloon& operator=(const DestlerDoubloon& other) = delete;

    /**
     * Move construction is forbidden by all
     */
    DestlerDoubloon(DestlerDoubloon&& other)= delete;

    /**
     * Move assignment is forbidden by all.
     */
    DestlerDoubloon& operator=(DestlerDoubloon&& other) = delete;

    /**
     * Destruct a doubloon.  If debugging is enabled it should print:
     *
     * {this doubloon} being destroyed!
     */
    ~DestlerDoubloon();

    /**
     * Two doubloons are the same if they have the same id.
     *
     * @param other the other doubloon to compare against
     * @return whether they are equal or not
     */
    bool operator==(const DestlerDoubloon& other) const;

    /**
     * Get the id of the doubloon.
     *
     * @return the id
     */
    unsigned long long id() const;

    /**
     * Get the monetary value of the doubloon.
     *
     * @return the value
     */
    double value() const;

    /**
     * Send the doubloon to the output stream.  It should send the string:
     *
     * DD: 0x{id}, value: {value}
     *
     * For consistency sake, all doubloon id's should print out with all
     * 16 hex values, padded with leading 0's if necessary.
     *
     * @param os the output stream
     * @param dd the doubloon
     * @return the output stream, for chaining
     */
    friend std::ostream& operator<<(std::ostream& os, const DestlerDoubloon& dd);

private:
    /**
     * Create a new doubloon, with a unique 64 bit id and a value of 1.
     * If debugging is enabled it should print:
     *
     * {doubloon} being created!
     *
     * @param id the id
     * @param value the value
     */
    DestlerDoubloon(unsigned long long id, double value);


    /**
     * Increase the worth of this doubloon.
     *
     * @param value amount to increase by
     */
    void increase_value(double value);

    /**
     * Decrease the worth of this doubloon, but don't allow it to go below 0.
     *
     * @param value amount to decrease by
     */
    void decrease_value(double value);

    /** the id is stored in a bitset to improve lookup speed */
    std::bitset<64> id_;

    /** the value of the doubloon */
    double value_;
};

// specialize hash<DestlerDoubloon>
namespace std {
    template<>
    struct hash<DestlerDoubloon> {
        /**
         * The id of the doubloon is used as the hash code.
         *
         * @param dd the doubloon
         * @return the id
         */
        size_t operator()(const DestlerDoubloon& dd) const {
            return dd.id();
        }
    };
}

#endif // DESTLER_DOUBLOON_H
