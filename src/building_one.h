#ifndef BUILDING_ONE_H
#define BUILDING_ONE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "dd_exception.h"
#include "destler_doubloon.h"
#include "rng.h"

/**
 * Building 1, also known as the George Eastman building, is the financial
 * home of RIT.  Deep in the basement is a secret vault that holds
 * the favored campus currency, Destler Doubloons.
 *
 * @author Sean Strout @ RIT CS
 */
class BuildingOne {
public:
    /** seed to use for random number generator */
    static constexpr int SEED = 0;

    /**
     * Create the administration building with an empty vault of doubloons.
     */
    BuildingOne();

    /**
     * Increase the value of each doubloon in the vault by value.
     *
     * @param value amount to increase by
     */
    void bull_market(double value);

    /**
     * Decrease the value of each doubloon in the vault by value.
     *
     * @param value amount to decrease by
     */
    void bear_market(double value);

    /**
     * Return a doubloon that was previously withdrawn back to the vault.
     *
     * @param dd the doubloon to add
     */
    void deposit(DestlerDoubloon&& dd);

    /**
     * Destroy a doubloon in the vault.
     *
     * @param id id of doubloon to destroy
     * @throws DDException if the doubloon is not in the vault
     */
    void destroy(unsigned long long id);

    /**
     * Get a doubloon from the vault for lookup.
     *
     * @param id id of doubloon to get
     * @throws DDException if the doubloon is not in the vault
     * @return the doubloon, if present
     */
    const DestlerDoubloon& doubloon(unsigned long long id) const;

    /**
     * Create a new collection of doubloons and store them in the vault.
     *
     * @param num_doubloons the number of doubloons to create
     */
    void mint(unsigned int num_doubloons);

    /**
     * How many doubloons are currently in the vault?
     *
     * return # doubloons in vault
     */
    size_t num_doubloons() const;

    /**
     * Get the total worth of all doubloons in the vault.
     *
     * @return total worth
     */
    double total_worth() const;

    /**
     * Take a doubloon, by id, out of the vault and pass it to the caller.
     *
     * @param id the id of the doubloon
     * @throws DDException if the doubloon is not in the vault
     * @return the doubloon
     */
    DestlerDoubloon withdraw(unsigned long long id);

    /**
     * Sends all the doubloons in the vault, to the output stream, in the
     * format of one doubloon per line, where id is the doubloon's id, and
     * value is the current worth of the doubloon.
     *
     * DD: 0x{id}, value: {value}
     *
     * @param os the output stream to insert into
     * @param b1 the admin building
     * @return the output stream (for chaining)
     */
    friend std::ostream& operator<<(std::ostream& os, const BuildingOne& b1);

private:
    /** the random number generator */
    RNG rng_;

    /** the vault of doubloons */
    std::unordered_map<unsigned long long, DestlerDoubloon> vault_;

    /** id's of doubloons that are currently withdrawn to the wallet */
    std::unordered_set<unsigned long long> withdrawn_ids_;
};

#endif // BUILDING_ONE_H
