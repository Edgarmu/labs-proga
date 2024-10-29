#pragma once

#include <exception>

struct InconsistentBounds : public std::logic_error {
    using std::logic_error::logic_error;
};
