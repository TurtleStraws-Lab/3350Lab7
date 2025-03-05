//
// Original author: Gordon Griesel
//            Date: Spring 2024
//         Purpose: Calculate days between dates
//
// Days between dates is calculated by incrementing the earlier date
// one day at a time until it reaches the later date, and counting
// the increments.
//
// To be a leap year, the year number must be divisible by four – except for
// end-of-century years, which must be divisible by 400. This means that the
// year 2000 was a leap year, although 1900 was not. 2024, 2028, 2032 and
// 2036 are all leap years.
//
//SECOND AUTHOR: MOISES GONZALEZ
//DATE: 3/4/2025
//PURPOSE: FIX PROGRAM
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const char mname[][16] = {"Jan","Feb","Mar","Apr","May","Jun",
    "Jul","Aug","Sep","Oct","Nov","Dec"};
/*const*/ int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

class Date
{
    private:
        int month;
        int day;
        int year;
    public:
        Date() {
            //The default constructor is not used.
        }
        Date(const char *date)
        {
            //date format: "mm-dd-yyyy"
            //Use it like this: Date d1("11-05-2024");
            month = (date[0]-'0')*10 + date[1]-'0';
            day   = (date[3]-'0')*10 + date[4]-'0';
            year  = (date[6]-'0')*1000 + (date[7]-'0')*100 +
                (date[8]-'0')*10 + (date[9]-'0');
        }
        Date operator++()
        {
            bool leapyear = false;
            if(leapyear == false){
            if(year % 4 == 0)
            {
                leapyear = true;
                days[1] = 29;
            }
            if (year % 100 == 0)
            {
                leapyear = false;
            }
            if (year % 400 == 0)
            {
                leapyear = true;
                days[1] = 29;
            }
            }
            //prefix (pre increment)
            day += 1;
            if(day > days[month-1]){
                day = 1; 
                month += 1;
            }
            if(month == 13){
                month = 1;
                day = 1;
                year += 1;
                days[1] = 28;
            }

            return *this;
        }
        Date operator++(int)
        {
            //postfix (post increment)
            Date tmp;
            day += 1;

            if(day > days[month-1]){
                day = 1; 
                month += 1;
            }
            if(month == 13){
                month = 1;
                day = 1;
                year += 1;
                days[1] = 28;

            }
            return tmp;
        }
        bool operator==(const Date &d)
        {
            return (day == d.day && month == d.month && year == d.year);
        }
        friend ostream &operator<<(ostream &, const Date &);
};

ostream &operator<<(ostream &strm, const Date &obj)
{
    strm << mname[obj.month-1] << " " << setw(2) << obj.day << ", " << obj.year;
    return strm;
}

//function prototypes
int twoDates(const char *d1, const char *d2);
int daysBetweenDates(Date d1, Date d2);

//some test data
char testdates[][16] = {
    "03-04-2025", "03-04-2025",  // from today until today
    "03-04-2025", "03-05-2025",  // from today until tomorrow
    "03-01-2025", "03-31-2025",  // from mar-1 to mar-31
    "03-01-2025", "04-01-2025",  // from mar-1 to apr-1
    "01-01-2024", "01-01-2025",  // 1 year
    "01-01-2025", "01-01-2026",  // 1 year
    "03-04-2025", "03-02-2025",  // 2 days (backwards)
    "",           ""
};



//========================================================
// main function is here
//========================================================
int main(int argc, char **argv)
{
    if (argc >= 3){
        Date date1(argv[1]);
        Date date2(argv[2]);
        int count2 = 0;
        cout << "Days between " << (Date)argv[1] << " and " << (Date)argv[2] << " is: "; 
            count2 = twoDates(argv[1], argv[2]);     
            if (count2 >= 4000000) {
            count2 = twoDates(argv[2], argv[1]);
            cout << count2 << " (Backwards)" <<endl;
            //++noverflows;
            //cout << "  <--- error ";
            exit(0);
        }
            else{
            count2 = twoDates(argv[1], argv[2]);    
            cout << count2 << endl;
            exit(0);
    }
    } 
    cout << "\nCalculate days between dates.\n" << endl;
    char d1[100], d2[100];
    int noverflows = 0;
    int i = 0;
    while (strlen(testdates[i*2]) > 0) {
        strcpy(d1, testdates[i*2+0]);
        strcpy(d2, testdates[i*2+1]);
        cout << "Days between " << (Date)d1 << " and " << (Date)d2 << " is: ";
        // which date is earlier?
        Date date1(d1);
        Date date2(d2);
        int count;
           
            count = twoDates(d1, d2);     
            if (count >= 4000000) {
            count = twoDates(d2, d1);
            cout << count << " (Backwards)";
            //++noverflows;
            //cout << "  <--- error ";
        }
            else{
            count = twoDates(d1, d2);    
            cout << count << "";
            }
        cout << endl;
        ++i;
    }
    if (noverflows)
        cout << noverflows << " errors occured." << endl;
    cout << endl;
    return 0;
}

int twoDates(const char *d1, const char *d2)
{
    // ============================
    // Do not modify this function.
    // ============================
    Date date1(d1);
    Date date2(d2);
    int count = daysBetweenDates(date1, date2);
    return count;
}   

int daysBetweenDates(Date d1, Date d2)
{
    // ============================
    // Do not modify this function.
    // ============================
    // Start the count at 0.
    // Example: The days between Thursday and Friday
    //          will be one day not two days.
    int count = 0;
    while (!(d1 == d2)) {
        ++d1;
        ++count;
        //safety exit
        if (count >= 4000000)
            break;
    }
    return count;
}














