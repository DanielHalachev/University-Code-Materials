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

#ifndef ZADACHA1_DATE_HPP
#define ZADACHA1_DATE_HPP


class Date {
private:
    int year;
    unsigned short month;
    unsigned short day;
public:
    Date();

    Date(unsigned short day, unsigned short month, int year);

    void addDays(unsigned int n);

    void removeDays(unsigned int n);

    bool isLeapYear() const;

    bool isLaterThan(Date date) const;

    unsigned int daysToXmas() const;

    unsigned int daysToNewYear() const;

    unsigned int daysToEvent(Date eventDate) const;

    //utility functions which aren't required but are useful
    int getYear() const;

    unsigned short getMonth() const;

    unsigned short getDay() const;

    void setYear(int newYear);

    void setMonth(unsigned short newMonth);

    void setDay(unsigned short newDay);

    void printDate() const;
};


#endif //ZADACHA1_DATE_HPP
