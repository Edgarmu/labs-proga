#pragma once

#include <stdexcept>

struct MatrixHasInconsistentDimensions : public std::logic_error {
    using std::logic_error::logic_error;
};