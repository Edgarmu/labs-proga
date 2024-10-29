#pragma once

struct Dimension {
    int rows;
    int columns;

    bool operator==(const Dimension& other) const {
        return rows == other.rows && columns == other.columns;
    }
    bool operator!=(const Dimension& other) const {
        return !(*this == other);
    }

    static bool canMultiply(const Dimension& left, const Dimension& right) {
        return left.columns == right.rows;
    }
};