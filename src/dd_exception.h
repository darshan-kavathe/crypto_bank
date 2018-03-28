#ifndef DD_EXCEPTION_H
#define DD_EXCEPTION_H

#include <stdexcept>

/**
 * A class to represents exceptions that can happen while working
 * with DestlerDoublooons, e.g. withdrawing a Doubloon when there
 * are none left in Building 1's vault.
 */
class DDException : public std::runtime_error {
public:
    /**
     * Construct this exception.
     *
     * @param msg the exception message
     */
    DDException(const std::string& msg) : runtime_error(msg.c_str()) {}

    /**
     * Get a string containing information about the exception.
     *
     * @return exception message
     */
    virtual const char* what() const throw() {
        return std::runtime_error::what();
    }
}; // DDException

#endif // DD_EXCEPTION_H
