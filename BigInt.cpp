#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "BigInt.h"
#define MAX 10000 // for strings

// Empty Constructor initializtion with zero
BigInt::BigInt()
{
	number = "0";
	sign = false;
}

// String Constructor
BigInt::BigInt(string s)
{
	if(isdigit(s[0]))
	{
		setNumber(s);
		sign = false;
	}
	else
	{
		setNumber(s.substr(1));
		setSign( s[0]=='-' );
	}
}

// String Constructor with sign
BigInt::BigInt(string s, bool sign)
{
	setNumber(s);
	setSign(sign);
}

// Int constructor
BigInt::BigInt(int no)
{
	stringstream ss;
	string s;
	ss << no;
	ss >> s;

	if(isdigit(s[0]))
	{
		setNumber(s);
		setSign(false);
	}
	else
	{
		setNumber(s.substr(1));
		setSign( s[1]=='-' );
	}
}

void BigInt:: setNumber(string s)
{
	number = s;
}

const string& BigInt:: getNumber()
{
	return number;
}

void BigInt:: setSign(bool b)
{
	sign = b;
}

const bool& BigInt:: getSign()
{
	return sign;
}

// Return Absolute Value
BigInt BigInt::absolute()
{
	return BigInt( getNumber() ); // +ve by default
}


// Operator Overloading
void BigInt::operator = (BigInt b)
{
	setNumber(b);
	setSign(b.getSign());
}

bool BigInt::operator == (BigInt b)
{
	return equals(*this, b);
}

bool BigInt::operator != (BigInt b)
{
	return !equals(*this, b);
}

bool BigInt::operator > (BigInt b)
{
	return greater(*this, b);
}

bool BigInt::operator < (BigInt b)
{
	return less(*this, b);
}

bool BigInt::operator >= (BigInt b)
{
	return equals(*this, b) || greater(*this, b);
}

bool BigInt::operator <=  (BigInt b)
{
	return equals(*this, b) || less(*this, b);
}

// Increment the value by one and return the value
// Prefix
BigInt& BigInt::operator ++()
{
	(*this) = (*this) + 1;
	return (*this);
}

// Return the value, and then increment
// Postfix

BigInt BigInt::operator ++(int)
{
	BigInt before = (*this);
	(*this) = (*this) + 1;
	return before;
}

BigInt& BigInt::operator --()
{
	(*this) = (*this) - 1;
	return (*this);
}

BigInt BigInt::operator --(int)
{
	BigInt before = (*this);
	(*this) = (*this) - 1;
	return before;
} 

BigInt BigInt::operator + (BigInt b)
{
	BigInt addition;

	if( getSign() == b.getSign())	// Both are +ve or -ve
	{
		addition.setNumber(add(getNumber(), b.getNumber()));
		addition.setSign(getSign());
	}
	else	// Different Sign
	{
		if( absolute() > b.absolute())
		{
			addition.setNumber( subtract( getNumber(), b.getNumber()));
			addition.setSign( getSign() );
		}
		else
		{
			addition.setNumber( subtract(b.getNumber(), getNumber()));
			addition.setSign( b.getSign() );
		}
	}
	if(addition.getNumber()=="0")	// to avoid -0
			addition.setSign(false);

	return addition;
}

BigInt BigInt::operator - (BigInt b)
{
	b.setSign( !getSign() );
	return (*this) + b;
}

BigInt BigInt::operator * (BigInt b)
{
	BigInt mul;
	mul.setNumber( multiply(getNumber(), b.getNumber()));
	mul.setSign( getSign()!=b.getSign() );

	if(mul.getNumber()=="0") // to avoid -0
		mul.setSign(false);

	return mul;
}

BigInt BigInt:: operator / (BigInt b)
{
	long long den = toInt( b.getNumber() );
	BigInt div;

	div.setNumber( divide(getNumber(), den).first );
	div.setSign( getSign() != b.getSign() );

	if(div.getNumber() == "0") // avoid (-0) problem
		div.setSign(false);

	return div;
}


BigInt BigInt::operator % (BigInt b)
{
	long long den = toInt( b.getNumber() );

	BigInt rem;
	long long rem_int = divide(number, den).second;
	rem.setNumber( toString(rem_int) );
	rem.setSign( getSign() != b.getSign() );

	if(rem.getNumber() == "0") // avoid (-0) problem
		rem.setSign(false);

	return rem;
}

BigInt& BigInt::operator += (BigInt b)
{
	(*this) = (*this) + b;
	return (*this);
}

BigInt& BigInt::operator -= (BigInt b)
{
	(*this) = (*this) - b;
	return (*this);
}

BigInt& BigInt::operator *= (BigInt b)
{
	(*this) = (*this) * b;
	return (*this);
}

BigInt& BigInt::operator /= (BigInt b)
{
	(*this) = (*this) / b;
	return (*this);
}

BigInt& BigInt::operator %= (BigInt b)
{
	(*this) = (*this) % b;
	return (*this);
}

BigInt& BigInt::operator [] (int n)
{
	return *(this + (n*sizeof(BigInt)));
}

BigInt BigInt::operator -() // unary minus sign
{
	return (*this) * -1;
}

//-------------------------------------------------------------

BigInt::operator string() // for conversion from BigInt to string
{
	string signedString = ( getSign() ) ? "-" : ""; // if +ve, don't print + sign
	signedString += number;
	return signedString;
}

bool BigInt::equals(BigInt n1, BigInt n2)
{
	return n1.getNumber() == n2.getNumber() &&
			n1.getSign() == n2.getSign();
}

bool BigInt::less(BigInt n1, BigInt n2)
{
	bool sign1 = n1.getSign();
	bool sign2 = n2.getSign();

	// n1 is negative and n2 is positive
	if(sign1 && !sign2)
	{
		return true;
	}
	// n1 is positive and n2 is negative
	else if(!sign1 && sign)
	{
		return false;
	}
	// Both positve number
	else if( !sign1 )
	{
		if( n1.getNumber().length() > n2.getNumber().length() )
			return false;
		else if( n1.getNumber().length() < n2.getNumber().length() )
			return true;
		return n1.getNumber()<n2.getNumber();
	}
	else
	{
		if( n1.getNumber().length() > n2.getNumber().length() )
			return true;
		else if(n1.getNumber().length() < n2.getNumber().length())
			return false;
		// greater with -ve sign is LESS
		return n1.getNumber().compare( n2.getNumber() ) > 0; 
	}
}

bool BigInt:: greater(BigInt n1, BigInt n2)
{
	return !equals(n1, n2) && !less(n1, n2);
}

string BigInt::add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ?  number1 : number2;
	char carry = '0';
	int differenceInLength = abs( (int) (number1.size() - number2.size()) );

	if(number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0'); // put zeros from left

	else// if(number1.size() < number2.size())
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.size()-1; i>=0; --i)
	{
		add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

		if(i != 0)
		{	
			if(add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if(add[0] > '9')
	{
		add[0]-= 10;
		add.insert(0,1,'1');
	}
	return add;
}

//-------------------------------------------------------------
// subtracts two strings and returns their sum in as a string
string BigInt::subtract(string number1, string number2)
{
	string sub = (number1.length()>number2.length())? number1 : number2;
	int differenceInLength = abs( (int)(number1.size() - number2.size()) );

	if(number1.size() > number2.size())	
		number2.insert(0, differenceInLength, '0');

	else
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.length()-1; i>=0; --i)
	{
		if(number1[i] < number2[i])
		{
			number1[i] += 10;
			number1[i-1]--;
		}
		sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
	}

	while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
		sub.erase(0,1);

	return sub;
}

//-------------------------------------------------------------
// multiplies two strings and returns their sum in as a string
string BigInt::multiply(string n1, string n2)
{
	if(n1.length() > n2.length()) 
		n1.swap(n2);

	string res = "0";
	for(int i=n1.length()-1; i>=0; --i)
	{
		string temp = n2;
		int currentDigit = n1[i]-'0';
		int carry = 0;

		for(int j=temp.length()-1; j>=0; --j)
		{
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;

			if(temp[j] > 9)
			{
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			}
			else
				carry = 0;

			temp[j] += '0'; // back to string mood
		}

		if(carry > 0)
			temp.insert(0, 1, (carry+'0'));
		
		temp.append((n1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

		res = add(res, temp); // O(n)
	}

	while(res[0] == '0' && res.length()!=1) // erase leading zeros
		res.erase(0,1);

	return res;
}

// divides string on long long, returns pair(qutiont, remainder)
pair<string, long long> BigInt::divide(string n, long long den)
{
	long long rem = 0;
	string result; result.resize(MAX);
	
	for(int indx=0, len = n.length(); indx<len; ++indx)
	{
		rem = (rem * 10) + (n[indx] - '0');
		result[indx] = rem / den + '0';
		rem %= den;
	}
	result.resize( n.length() );

	while( result[0] == '0' && result.length() != 1)
		result.erase(0,1);

	if(result.length() == 0)
		result = "0";

	return make_pair(result, rem);
}

// Convert to string
string BigInt::toString(long long n)
{
	stringstream ss;
	string s;

	ss << n;
	ss >> s;

	return s;
}

// Convert string to long long
long long BigInt::toInt(string s)
{
	long long no = 0;

	for(int i=0; i<s.length(); i++)
	{
		no = no*10 + (s[i]-'0');
	}

	return no;
}

#endif


