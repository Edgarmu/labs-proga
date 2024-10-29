#pragma once

#include <stdexcept>

struct VectorHasInconsistentDimensions : public std::logic_error {
    using std::logic_error::logic_error;
};