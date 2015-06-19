/**
 * CS Exercise 5.4
 * Title: calendar
 * Author: Martin Giger
 * Date: 19.06.2015
 */

#include <iostream>
#include <string>

using namespace std;

const unsigned int DAYS_PER_WEEK = 7;
const unsigned int DAYS_PER_YEAR = 365;
const unsigned int REFERENCE_DAY_CORRECTION = 6;

bool isLeapYear(const unsigned int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

unsigned int getDaysOfYear(const unsigned int year) {
    return DAYS_PER_YEAR + (isLeapYear(year) ? 1 : 0);
}

unsigned int getDaysUntilYear(const unsigned int year) {
    unsigned int ret = REFERENCE_DAY_CORRECTION;
    for(unsigned int i = 1; i < year; ++i) {
        ret += getDaysOfYear(i);
    }
    return ret;
}

// I'd prefer to const the month length more, but I'm not really sure how...
unsigned int getDaysOfMonth(const unsigned int month, const unsigned int year) {
    if(month == 2) {
        return 28 + (isLeapYear(year) ? 1 : 0);
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

unsigned int getDaysOfPassedMonths(const unsigned int month, const unsigned int year) {
    unsigned int ret = 0;
    for(unsigned int i = 1; i < month; ++i) {
        ret += getDaysOfMonth(i, year);
    }
    
    return ret;
}

unsigned int getWeekdaysSinceReference(const unsigned int day, const unsigned int month, const unsigned int year) {
    return day + getDaysOfPassedMonths(month, year) + getDaysUntilYear(year);
}

unsigned int getWeekdayCode(const unsigned int day, const unsigned int month, const unsigned int year) {
    return getWeekdaysSinceReference(day, month, year) % DAYS_PER_WEEK;
}

string getWeekday(const unsigned int day, const unsigned int month, const unsigned int year) {
    switch(getWeekdayCode(day, month, year)) {
        case 0: return "Monday";
        case 1: return "Tuesday";
        case 2: return "Wednesday";
        case 3: return "Thursday";
        case 4: return "Friday";
        case 5: return "Saturday";
        default: return "Sunday";
    }
}

int main(void) {
    unsigned int day, month, year;
    cout << "Day? ";
    cin >> day;
    cout << "Month? ";
    cin >> month;
    cout << "Year? ";
    cin >> year;
    
    cout << getWeekday(day, month, year) << endl;
    
    return 0;
}
