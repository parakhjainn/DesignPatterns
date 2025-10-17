// 5

#pragma once

#include <iostream>
#include <string>
#include "show.h"
#include "user.h"
#include "seat.h"

using namespace std;

enum class BookingStatus {
    PENDING, CONFIRMED
};

class Booking {
    int bookingId;
    User user;
    Show show;
    BookingStatus status;
    vector<Seat*> seats;

public:
    Booking(int bookingId, BookingStatus status, const vector<Seat*>& seats)
        : bookingId(bookingId), status(status), seats(seats) {}

    BookingStatus getBookingStatus() {
        return status;
    }
    
};
