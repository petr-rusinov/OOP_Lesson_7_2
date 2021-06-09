#include <iostream>
#include <cassert>
#include <iomanip>
#include <memory>
using namespace std;
// 1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям.
// Перегрузите оператор вывода для данного класса.Создайте два "умных" указателя today и date.
// Первому присвойте значение сегодняшней даты.Для него вызовите по отдельности методы доступа к 
// полям класса Date, а также выведите на экран данные всего объекта с помощью перегруженного 
// оператора вывода.Затем переместите ресурс, которым владеет указатель today в указатель date.
// Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.
// 

class Date
{
private:
	uint8_t m_day;
	uint8_t m_month;
	uint16_t m_year;
public:
	Date() : Date(1, 1, 2021) { }
	Date(uint8_t day, uint8_t month, uint16_t year) : m_day(day), m_month(month), m_year(year) { }

	void setDay(uint8_t day) 
	{
		assert(day <= 31);
		m_day = day; 
	}
	uint8_t getDay() const { return m_day; }
	
	void setMonth(uint8_t month)
	{
		assert(month <= 12);
		m_month = month;
	}
	uint8_t getMonth() const { return m_month; }

	void setYear(uint16_t year) { m_year = year; }
	uint16_t getYear() const { return m_year; }
	friend ostream& operator  << (ostream& out, const Date& date);
};

ostream& operator << (ostream& out, const Date& date)
{
	out << setfill('0') << setw(2) << static_cast<unsigned>(date.getDay()) << "." \
		<< setfill('0') << setw(2) << static_cast<unsigned>(date.getMonth()) << "." \
		<< static_cast<unsigned>(date.getYear());
	return out;
}


// 2. По условию предыдущей задачи создайте два умных указателя date1 и date2. 
// Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и 
// сравнивает их между собой(сравнение происходит по датам).Функция должна вернуть более позднюю дату.
// Создайте функцию, которая обменивает ресурсами(датами) два умных указателя, переданных в функцию в качестве параметров.
// Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.
// 

unique_ptr<Date>& compareDates(unique_ptr<Date>& date1, unique_ptr<Date>& date2)
{
	if (date1->getYear() > date2->getYear())
	{
		return date1;
	}
	else if (date2->getYear() > date1->getYear())
	{
		return date2;
	}
	else if (date1->getMonth() > date2->getMonth())
	{
		return date1;
	}
	else if (date2->getMonth() > date1->getMonth())
	{
		return date2;
	}
	else if (date1->getDay() > date2->getDay())
	{
		return date1;
	}
	else if (date2->getDay() > date1->getDay())
	{
		return date2;
	}
	else
	{
		return date1; //даты равны.
	}


}

void swapDates(unique_ptr<Date>& date1, unique_ptr<Date>& date2)
{
	unique_ptr<Date> temp = make_unique<Date>();
	temp = move(date1);
	date1 = move(date2);
	date2 = move(temp);
}

int main()
{
	cout << "---------------- TASK 1 ----------------" << endl;
	unique_ptr<Date> today = make_unique<Date>();
	today->setDay(8);
	today->setMonth(06);
	today->setYear(2021);
	cout << "today is " << *today << endl;
	unique_ptr<Date> date = make_unique<Date>();
	date = move(today);
	if (today)
		cout << "today is " << *today << endl;
	else
		cout << "today is nullptr" << endl;
	if (date)
		cout << "date is " << *date << endl;
	else
		cout << "date is nullptr" << endl;

	cout << "---------------- TASK 2 ----------------" << endl;
	unique_ptr<Date> date1 = make_unique<Date>();
	date1->setDay(1);
	date1->setMonth(5);
	date1->setYear(2021);
	cout <<"Date 1 is " << *date1 << endl;
	unique_ptr<Date> date2 = make_unique<Date>();
	date2->setDay(2);
	date2->setMonth(4);
	date2->setYear(2020);
	cout << "Date 2 is " << *date2 << endl;

	cout << "The most recent date is  " << *compareDates(date1, date2) << endl;
	cout << endl;

	cout << "----- Before Swap ------" << endl;
	cout << "Date 1: " << *date1 << ", Date 2: " << *date2 << endl;
	swap(date1, date2);
	cout << "----- After Swap ------" << endl;
	cout << "Date 1: " << *date1 << ", Date 2: " << *date2 << endl;

}
