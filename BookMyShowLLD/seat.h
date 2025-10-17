// 4

#pragma once

#include <string>

using namespace std;

enum class SeatType {
    BASIC,
    STANDARD,
    PREMIUM
};

enum class SeatStatus {
    AVAILABLE,
    BOOKED
};

class Seat {
private:
    string id;
    int row;
    int column;
    SeatType type;
    double price;
    SeatStatus status;

public:
    Seat(const string& id, int row, int column, SeatType type, double price)
        : id(id), row(row), column(column), type(type), price(price), status(SeatStatus::AVAILABLE) {}

    string getId() const {
        return id;
    }

    double getPrice() const {
        return price;
    }

    int getColumn() const {
        return column;
    }

    SeatStatus getStatus() const {
        return status;
    }

    SeatType getType() const {
        return type;
    }

    int getRow() const {
        return row;
    }
};
