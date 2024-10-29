#pragma once

#include <exception>

struct NegativeSize : public std::logic_error {
    using std::logic_error::logic_error;
};
