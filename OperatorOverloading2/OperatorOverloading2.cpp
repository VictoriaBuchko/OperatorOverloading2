#include <iostream>
using namespace std;

class MyString
{
	char* str;
	int size;
	static int count;//статическое поле 

public:


	MyString() : MyString(80) {}//конструктор по умолчанию

	MyString(int length) : size(length)//используем инициализатор
	{
		str = new char[size + 1];
		strcpy_s(str, size + 1, "");
		count++;
	}

	MyString(const char* Str) : MyString(strlen(Str))//при делегировании мы вызываем 2 коструктор
		//где определяем длину строки и выделяем под нее динамическую память и инициализирует ее пустой строкой
	{
		strcpy_s(str, size + 1, Str);//копирует содержимое строки Str в созданную строку(мы поручили создание этой строки коструктору 2)
		cout << "The copy constructor worked" << endl;
	}

	MyString(const MyString& string) : MyString(string.size)//использую делегирование, так как было предупреждение про неинициализированный размер
	{
		strcpy_s(str, size + 1, string.str);
	}


	void StrInput() {

		cout << "Enter a string: ";
		cin.getline(str, size + 1);
	}

	void Output()
	{
		cout << "String: " << str << endl;
	}

	static int GetCount()
	{
		return count;
	}

	MyString operator++ () {

		int newSize = size + 1;
		char* newStr = new char[newSize + 1];

		strcpy_s(newStr, newSize + 1, str);

		newStr[size] = 'x';
		newStr[newSize] = '\0';

		MyString newString(newStr);

		delete[] newStr;

		return newString;
	}

	MyString operator-- () {

		if (size > 0) {

			int newSize = size - 1;
			char* newStr = new char[newSize + 1];

			strncpy_s(newStr, newSize + 1, str, newSize);
			newStr[newSize] = '\0';
			MyString newString(newStr);

			delete[] newStr;
			return newString;
		}
		else {
			return *this;
		}
	}

	MyString operator+(int number) const {

		if (number < 0) {
			return *this;
		}

		int newSize = size + number;
		char* newStr = new char[newSize + 1];

		strcpy_s(newStr, newSize + 1, str);

		for (int i = size; i < newSize; ++i) {

			newStr[i] = 'x';
		}
		newStr[newSize] = '\0';

		MyString newString(newStr);

		delete[] newStr;

		return newString;

	}
	MyString operator-(int number) const {

		if (number <= 0 || number > size) {
			return *this;
		}
		
		int newSize = size - number;
		char* newStr = new char[newSize + 1];

		strncpy_s(newStr, newSize + 1, str, newSize);

		newStr[newSize] = '\0';

		MyString newString(newStr);

		delete[] newStr;
		return newString;
	}


	~MyString() {

		delete[] str;
		count--;
	}
};

int MyString::count = 0;

int main()
{
	MyString str1;
	str1.StrInput();

	MyString str2(20);
	str2.StrInput();

	MyString str3("Hello");

	cout << "\nObjects str: \n\n";

	str1.Output();
	str2.Output();
	str3.Output();

	MyString str4 = str3;
	str4.Output();

	MyString increment = ++str3;
	increment.Output();

	MyString decrement = --str3;
	decrement.Output();

	MyString plus = str3+4;
	plus.Output();


	MyString minus = str3-2;
	minus.Output();

	cout << "\nNumber of objects created " << MyString::GetCount() << endl;
	return 0;
}

