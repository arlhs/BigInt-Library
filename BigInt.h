#include<string>
#define MAX 10000 // Max size
using namespace std;

class BigInt
{
private:
	string number;
	bool sign;
	bool equals(BigInt n1, BigInt n2);
	bool less(BigInt n1, BigInt n2);
	bool greater(BigInt n1, BigInt n2);
	string add(string number1, string number2);
	string subtract(string number1, string number2);
	string multiply(string n1, string n2);
	pair<string, long long> divide(string n, long long den);
	string toString(long long n);
	long long toInt(string s);	

public:
	BigInt();	// Empty Constructor for intiliazing zero
	BigInt(string s);	// initializing with string
	BigInt(string s, bool sin);	// initializing with string ans sign
	BigInt(int s);		// initializing with int
	void setNumber(string s);
	const string& getNumber(); // retrieves the number
	void setSign(bool s);
	const bool& getSign();
	BigInt absolute(); // returns the absolute value
	void operator = (BigInt b);
	bool operator == (BigInt b);
	bool operator != (BigInt b);
	bool operator > (BigInt b);
	bool operator < (BigInt b);
	bool operator >= (BigInt b);
	bool operator <= (BigInt b);
	BigInt& operator ++(); // prefix
	BigInt  operator ++(int); // postfix
	BigInt& operator --(); // prefix
	BigInt  operator --(int); // postfix
	BigInt operator + (BigInt b);
	BigInt operator - (BigInt b);
	BigInt operator * (BigInt b);
	BigInt operator / (BigInt b);
	BigInt operator % (BigInt b);
	BigInt& operator += (BigInt b);
	BigInt& operator -= (BigInt b);
	BigInt& operator *= (BigInt b);
	BigInt& operator /= (BigInt b);
	BigInt& operator %= (BigInt b);
	BigInt& operator [] (int n);
	BigInt operator -(); // unary minus sign
	operator string(); // for conversion from BigInt to string
};

