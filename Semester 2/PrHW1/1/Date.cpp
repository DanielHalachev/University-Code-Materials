/**
* Solution to homework assignment 1
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 1
* @compiler GCC
*/


#include <iostream>
#include "Date.hpp"

//standard functions
bool isLeap(int year) {
    if (year % 100 != 0 && year % 4 == 0 || year % 400 == 0) {
        return true;
    }
    return false;
}

unsigned int dateToDayOfYear(Date date) {
    // this function returns the number of days
    // that have passed since the beginning of the year
    unsigned int daysAfterStart = date.getDay();
    switch (date.getMonth()) {
        case 12:
            daysAfterStart = daysAfterStart + 30;
        case 11:
            daysAfterStart = daysAfterStart + 31;
        case 10:
            daysAfterStart = daysAfterStart + 30;
        case 9:
            daysAfterStart = daysAfterStart + 31;
        case 8:
            daysAfterStart = daysAfterStart + 31;
        case 7:
            daysAfterStart = daysAfterStart + 30;
        case 6:
            daysAfterStart = daysAfterStart + 31;
        case 5:
            daysAfterStart = daysAfterStart + 30;
        case 4:
            daysAfterStart = daysAfterStart + 31;
        case 3:
            daysAfterStart = daysAfterStart + 28;
        case 2:
            daysAfterStart = daysAfterStart + 31;
    }
    if (isLeap(date.getYear()) && date.getMonth() > 2) {
        daysAfterStart++;
    }
    return daysAfterStart;
}

void dayOfYearToDate(unsigned int &offset, unsigned int &month, int &year) {
    //this function converts the day of the year to a date
    int months[12] = {31, (isLeap(year)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i = 1;
    for (; i < 12; i++) {
        if (offset <= months[i]) {
            break;
        }
        offset = offset - months[i];
    }
    month = i;
}

//Date Class functions
Date::Date() {
    year = 2000;
    month = 1;
    day = 1;
}

Date::Date(unsigned short day, unsigned short month, int year) {
    //initialize year - works with years B.C included
    this->year = year;

    //initialize month
    if (month == 0) {
        month = 1;
        std::cout << "Error. A month can't be zero. Month is set to 1" << std::endl;
    }
    while (month > 12) {
        month = month - 12;
        std::cout << "Error. A month can't be bigger than 12. Month is set to " << month << std::endl;
    }
    this->month = month;

    //initialize day
    if (day < 0) {
        day = -day;
        std::cout << "Error. A day of the month can't be negative. Day is set to " << day << std::endl;
    } else if (day == 0) {
        day = 1;
        std::cout << "Error. A day of the month can't be zero. Day is set to 1." << std::endl;
    }
    switch (month) {
        case 12:
        case 10:
        case 8:
        case 7:
        case 5:
        case 3:
        case 1:
            if (day > 31) {
                day = day % 31;
                std::cout << "Error. A day of the month can't be >31. Day is set to " << day << std::endl;
            }
            break;
        case 11:
        case 9:
        case 6:
        case 4:
            if (day > 30) {
                day = day % 30;
                std::cout << "Error. A day of the month can't be > 30. Day is set to " << day << std::endl;
            }
            break;
        case 2:
            if (isLeap(year)) {
                if (day > 28) {
                    day = day % 28;
                    std::cout << "Error. February in a Leap Year is 28 days. Day is set to " << day << std::endl;
                }
            } else {
                if (day > 29) {
                    day = day % 29;
                    std::cout << "Error. February is 29 days. Day is set to " << day << std::endl;
                }
            }
        default:
            break;
    }
    this->day = day;
}

void Date::addDays(unsigned int n) {
    //find which day of the year the date is
    unsigned int daysAfterStart = dateToDayOfYear(*this);

    //calculate new daysAfterStart
    unsigned int remainingDays;
    if (isLeap(year)) {
        remainingDays = 366 - daysAfterStart;
    } else {
        remainingDays = 365 - daysAfterStart;
    }
    if (n < remainingDays) {
        daysAfterStart = daysAfterStart + n;
    } else {
        this->year++;
        n = n - remainingDays;
        unsigned int daysOfNextYear = (isLeap(year)) ? 366 : 365;
        while (n > daysOfNextYear) {
            n = n - daysOfNextYear;
            this->year++;
            daysOfNextYear = (isLeap(year)) ? 366 : 365;
        }
        daysAfterStart = n;
    }

    //find date by the changed daysAfterStart
    unsigned int newMonth;
    dayOfYearToDate(daysAfterStart, newMonth, year);
    this->day = daysAfterStart;
    this->month = newMonth;
}

void Date::removeDays(unsigned int n) {
    //find which day of the year the date is
    unsigned int daysAfterStart = dateToDayOfYear(*this);

    //calculate new daysAfterStart
    if (n < daysAfterStart) {
        daysAfterStart = daysAfterStart - n;
    } else {
        this->year--;
        n = n - daysAfterStart;
        unsigned int daysOfNextYear = (isLeap(year)) ? 366 : 365;
        while (n > daysOfNextYear) {
            n = n - daysOfNextYear;
            this->year--;
            daysOfNextYear = (isLeap(year)) ? 366 : 365;
        }
        daysAfterStart = daysOfNextYear - n;
    }

    //find date by the changed daysAfterStart
    unsigned int newMonth;
    dayOfYearToDate(daysAfterStart, newMonth, year);
    this->day = daysAfterStart;
    this->month = newMonth;
}

bool Date::isLeapYear() const {
    return isLeap(this->year);
}

bool Date::isLaterThan(const Date date) const {
    if (this->year > date.year) {
        return true;
    } else if (this->year == date.year) {
        if (this->month > date.month) {
            return true;
        } else if (this->month == date.month) {
            return (this->day > date.day);
        }
        return false;
    }
    return false;
}

unsigned int Date::daysToEvent(const Date eventDate) const {
    //daysAfterStart1 = dateToDayOfYear(*this);;
    unsigned int daysAfterStart2 = dateToDayOfYear(eventDate);
    if (!this->isLaterThan(eventDate)) {
        for (int i = this->year; i < eventDate.year; i++) {
            if (isLeap(i)) {
                daysAfterStart2 = daysAfterStart2 + 366;
            } else {
                daysAfterStart2 = daysAfterStart2 + 365;
            }
        }
        return daysAfterStart2 - dateToDayOfYear(*this);
    }
    std::cout << "Error. Event already happened." << std::endl;
    return 0;
}

unsigned int Date::daysToXmas() const {
    return daysToEvent(Date(25, 12, this->year));
}

unsigned int Date::daysToNewYear() const {
    return daysToEvent(Date(1, 1, this->year + 1));
}

//convenient functions which aren't required but are useful
int Date::getYear() const {
    return year;
}

unsigned short Date::getMonth() const {
    return month;
}

unsigned short Date::getDay() const {
    return day;
}

void Date::setYear(int newYear) {
    this->year = newYear;
}

void Date::setMonth(unsigned short newMonth) {
    this->month = newMonth;
}

void Date::setDay(unsigned short newDay) {
    this->day = newDay;
}

void Date::printDate() const {
    std::cout << day << "." << month << "." << year << std::endl;
}