#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
class Date
{
private:
    int _year;
    int _month;
    int _day;
    
    //判断是否为闰年
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
    //获取某年某月的天数
    int getMonthDays(int year, int month) const {
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return month_days[month];
    }
    
    //检查日期是否有效
    bool checkDate(int year, int month, int day) const {
        if (year < 1900) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > getMonthDays(year, month)) return false;
        return true;
    }
    
public:
    //构造函数
    Date() {
        _year = 1900;
        _month = 1;
        _day = 1;
    }
    
    Date(int yy, int mm, int dd) {
        if (checkDate(yy, mm, dd)) {
            _year = yy;
            _month = mm;
            _day = dd;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }
    
    //前置++
    Date& operator++() {
        _day++;
        if (_day > getMonthDays(_year, _month)) {
            _day = 1;
            _month++;
            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
        return *this;
    }
    
    //后置++
    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }
    
    //前置--
    Date& operator--() {
        _day--;
        if (_day < 1) {
            _month--;
            if (_month < 1) {
                _month = 12;
                _year--;
            }
            _day = getMonthDays(_year, _month);
        }
        return *this;
    }
    
    //后置--
    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }
    
    //一个日期加上一个天数
    Date operator+(int days) const {
        Date result = *this;
        for (int i = 0; i < days; i++) {
            ++result;
        }
        return result;
    }
    
    //一个日期减去一个天数
    Date operator-(int days) const {
        Date result = *this;
        for (int i = 0; i < days; i++) {
            --result;
        }
        return result;
    }
    
    //日期减日期
    int operator-(const Date& other) const {
        Date d1 = *this;
        Date d2 = other;
        int diff = 0;
        
        if (d1 < d2) {
            Date temp = d1;
            d1 = d2;
            d2 = temp;
        }
        
        while (d2 < d1) {
            ++d2;
            diff++;
        }
        
        return diff;
    }
    
    //<重载
    int operator<(const Date& other) const {
        if (_year != other._year) return (_year < other._year) ? 1 : 0;
        if (_month != other._month) return (_month < other._month) ? 1 : 0;
        return (_day < other._day) ? 1 : 0;
    }
    
    //重载输出运算符
    friend ostream& operator<<(ostream& os, const Date& date);
    
    //备用输出函数
    void out() const {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

//重载输出运算符
ostream& operator<<(ostream& os, const Date& date) {
    os << date._year << "-" << date._month << "-" << date._day;
    return os;
}

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}
int main()
{
    Test();
    return 0;
}