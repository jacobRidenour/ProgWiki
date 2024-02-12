// An enum datatype for the months of the year

#include <string>
#include <iostream>
#include <ctime>

using string = std::string;

enum MonthsOfTheYear {
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

// A struct to represent calendar dates
struct dmy {
    int day;
    MonthsOfTheYear month;
    int year;
};

// not fully implemented, compiler warns it's unsafe, probably best to do this another way

struct dmy getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    struct dmy currentDate {};
    currentDate.month = static_cast<MonthsOfTheYear>(ltm->tm_mon);

}

// A Function to map the name of a month to an enum value
string getMonthName(MonthsOfTheYear month) {
    string months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return months[month - 1];
}inline void printMonthsFromNow(struct dmy& date) {
    int monthsFromNow = abs((date.month - 2) % 12);
    std::cout << "The given date is in " << getMonthName(date.month) << " which is " << monthsFromNow << " months from now!\n";
}

inline void printDate(struct dmy& date) {
    std::cout << getMonthName(date.month) << " " << date.day << ", " << date.year << "\n";
}

int main() {
    // Declare and initialize date1
    struct dmy date1 {};
    date1.day = 13;
    date1.month = February;
    date1.year = 1927;

    // Declare and allocate date2
    struct dmy* date2 = new struct dmy;

    // Initialize the fields of myDatePtr
    date2->day = 11;
    date2->month = November;
    date2->year = 2024;

    // Print the dates in the given format
    printDate(date1);
    printDate(*date2);

    // Compute and Print results
    printMonthsFromNow(*date2);

    // free memory
    delete date2;

    return 0;
}