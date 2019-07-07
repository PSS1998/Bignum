#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include "bignum.h"

using namespace std;


BigNum::BigNum(void) {
	number = "0";
	sign = 1;
	decimal_point = 0;
}

BigNum::BigNum(double _n) {
	stringstream strs;
	strs << _n;
	number = strs.str();
	sign = 1;
	if (number[0] == '-') {
		number.erase(number.begin());
		sign = -1;
	}
	decimal_point = 0;
	for (int i = 0; i<number.size(); i++)
		if (number[i] == '.') {
			decimal_point = i;
			break;
		}
	if (decimal_point != 1) {
		for (int i = 0; i < number.size(); i) {
			if (number[i] == '0')
				number.erase(number.begin());
			else
				break;
		}
	}
	if (decimal_point) {
		for (int i = number.size() - 1; i >= 0; i--) {
			if (number[i] == '0')
				number.erase(number.end() - 1);
			else
				break;
		}
		if ((number.size() - 1) == decimal_point) {
			number.erase(number.end() - 1);
			decimal_point = 0;
		}
	}
	if (number == "")
		number = "0";
}

BigNum::BigNum(string _number) {
//error check
	vector<int> count(2);
	bool not_digit = 0;
	for (int i = 0; i < _number.size(); i++) {
		if (_number[i] == '-')
			count[0]++;
		if(_number[i] == '.')
			count[1]++;
		if (_number[i] > '9')
			not_digit == 1;
		if (_number[i] < '0' && _number[i] != '-' && _number[i] != '.')
			not_digit == 1;
	}
	if (count[0] > 1 || count[1] > 1 || not_digit)
		throw not_a_number();
//error check	
	number = _number;
	sign = 1;
	if (number[0] == '-') {
		number.erase(number.begin());
		sign = -1;
	}
	decimal_point = 0;
	for (int i = 0; i<number.size(); i++)
		if (number[i] == '.') {
			decimal_point = i;
			break;
		}
	if (decimal_point != 1) {
		for (int i = 0; i < number.size(); i) {
			if (number[i] == '0')
				number.erase(number.begin());
			else
				break;
		}
	}
	if (decimal_point) {
		for (int i = number.size() - 1; i >= 0; i--) {
			if (number[i] == '0')
				number.erase(number.end() - 1);
			else
				break;
		}
		if ((number.size() - 1) == decimal_point) {
			number.erase(number.end() - 1);
			decimal_point = 0;
		}
	}
	if (number == "")
		number = "0";
}

BigNum BigNum::operator+(BigNum& b) {
	BigNum a = *this;
	int addition_sign = 0;
	int negative = 0;
	if (sign*b.sign == -1)
		addition_sign = -1;
	if (addition_sign == -1 && sign == -1)
		if ((-(*this)) < b) {
			negative = 1;
			a.sign = -a.sign;
			b.sign = -b.sign;
		}
	int carry = 0;
	char num1;
	char num2;
	string new_number;
	int size1 = a.number.size();
	int size2 = b.number.size();
	int size_dif;
	int size;
	int bigger_number;
	if (size1 > size2) {
		size = size1;
		size_dif = size1 - size2;
		bigger_number = 1;
	}
	else {
		size = size2;
		size_dif = size2 - size1;
		bigger_number = 2;
	}
	if (a.decimal_point) {
		if (b.decimal_point) {
			int i = 0;
			for (i = 0; i<min(a.number.size() - a.decimal_point, b.number.size() - b.decimal_point) - 1; i++) {
				num1 = a.number[a.number.size() - 1 - i];
				num2 = b.number[b.number.size() - 1 - i];
				int digit = atoi(&num1) + atoi(&num2)*addition_sign;
				digit += carry;
				if (digit >= 0) {
					carry = digit / 10;
					digit -= (carry * 10);
				}
				else {
					carry = -1;
					digit += 10;
				}
				stringstream convert;
				convert << digit;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
			new_number.insert(0, ".");
			i++;
			for (i; i<min(a.number.size(), b.number.size()); i++) {
				num1 = a.number[a.number.size() - 1 - i];
				num2 = b.number[b.number.size() - 1 - i];
				int digit = atoi(&num1) + atoi(&num2)*addition_sign;
				digit += carry;
				if (digit >= 0) {
					carry = digit / 10;
					digit -= (carry * 10);
				}
				else {
					carry = -1;
					digit += 10;
				}
				stringstream convert;
				convert << digit;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
			if (bigger_number == 1) {
				for (i; i<a.number.size(); i++) {
					num1 = a.number[a.number.size() - 1 - i];
					int digit = atoi(&num1);
					digit += carry;
					if (digit >= 0) {
						carry = digit / 10;
						digit -= (carry * 10);
					}
					else {
						carry = -1;
						digit += 10;
					}
					stringstream convert;
					convert << digit;
					string Result = convert.str();
					new_number.insert(0, Result);
				}
			}
			else {

				for (i; i<b.number.size(); i++) {
					num2 = b.number[b.number.size() - 1 - i];
					int digit = atoi(&num2);
					digit += carry;
					if (digit >= 0) {
						carry = digit / 10;
						digit -= (carry * 10);
					}
					else {
						carry = -1;
						digit += 10;
					}
					stringstream convert;
					convert << digit;
					string Result = convert.str();
					new_number.insert(0, Result);
				}
			}
			if (carry) {
				stringstream convert;
				convert << carry;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
		}
		else {
			for (int i = 0; i<a.number.size() - a.decimal_point; i++) {
				num1 = a.number[a.number.size() - 1 - i];
				new_number.insert(0, 1, num1);
			}
			int size_rest;
			if (a.decimal_point > b.number.size()) {
				bigger_number = 1;
				size_rest = b.number.size();
			}
			else {
				bigger_number = 2;
				size_rest = a.decimal_point;
			}
			int i = 0;
			for (i = 0; i<size_rest; i++) {
				num1 = a.number[a.number.size() - 1 - i - (a.number.size() - a.decimal_point)];
				num2 = b.number[b.number.size() - 1 - i];
				int digit = atoi(&num1) + atoi(&num2)*addition_sign;
				digit += carry;
				if (digit >= 0) {
					carry = digit / 10;
					digit -= (carry * 10);
				}
				else {
					carry = -1;
					digit += 10;
				}
				stringstream convert;
				convert << digit;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
			if (bigger_number == 1) {
				for (i; i<a.decimal_point; i++) {
					num1 = a.number[a.number.size() - 1 - i - (a.number.size() - a.decimal_point)];
					int digit = atoi(&num1);
					digit += carry;
					if (digit >= 0) {
						carry = digit / 10;
						digit -= (carry * 10);
					}
					else {
						carry = -1;
						digit += 10;
					}
					stringstream convert;
					convert << digit;
					string Result = convert.str();
					new_number.insert(0, Result);
				}
			}
			else {
				for (i; i<b.number.size(); i++) {
					num2 = b.number[b.number.size() - 1 - i];
					int digit = atoi(&num2);
					digit += carry;
					if (digit >= 0) {
						carry = digit / 10;
						digit -= (carry * 10);
					}
					else {
						carry = -1;
						digit += 10;
					}
					stringstream convert;
					convert << digit;
					string Result = convert.str();
					new_number.insert(0, Result);
				}
			}
			if (carry) {
				stringstream convert;
				convert << carry;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
		}
	}
	else {
		if (b.decimal_point) {
			for (int i = 0; i<b.number.size() - b.decimal_point; i++) {
				num2 = b.number[b.number.size() - 1 - i];
				new_number.insert(0, 1, num2);
			}
			int size_rest;
			if (b.decimal_point > a.number.size()) {
				bigger_number = 2;
				size_rest = a.number.size();
			}
			else {
				bigger_number = 1;
				size_rest = b.decimal_point;
			}
			int i = 0;
			for (i = 0; i<size_rest; i++) {
				num1 = a.number[a.number.size() - 1 - i];
				num2 = b.number[b.number.size() - 1 - i - (b.number.size() - b.decimal_point)];
				int digit = atoi(&num1) + atoi(&num2)*addition_sign;
				digit += carry;
				if (digit >= 0) {
					carry = digit / 10;
					digit -= (carry * 10);
				}
				else {
					carry = -1;
					digit += 10;
				}
				stringstream convert;
				convert << digit;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
			if (bigger_number == 2) {
				for (i; i<b.decimal_point; i++) {
					num2 = b.number[b.number.size() - 1 - i - (b.number.size() - b.decimal_point)];
					int digit = atoi(&num2);
					digit += carry;
					if (digit >= 0) {
						carry = digit / 10;
						digit -= (carry * 10);
					}
					else {
						carry = -1;
						digit += 10;
					}
					stringstream convert;
					convert << digit;
					string Result = convert.str();
					new_number.insert(0, Result);
				}
			}
			else {
				for (i; i<a.number.size(); i++) {
					num1 = a.number[a.number.size() - 1 - i];
					int digit = atoi(&num1);
					digit += carry;
					if (digit >= 0) {
						carry = digit / 10;
						digit -= (carry * 10);
					}
					else {
						carry = -1;
						digit += 10;
					}
					stringstream convert;
					convert << digit;
					string Result = convert.str();
					new_number.insert(0, Result);
				}
			}
			if (carry) {
				stringstream convert;
				convert << carry;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
		}
		else {
			int i = 0;
			for (i = 0; i<size - size_dif; i++) {
				num1 = a.number[a.number.size() - 1 - i];
				num2 = b.number[b.number.size() - 1 - i];
				int digit = atoi(&num1) + atoi(&num2)*addition_sign;
				digit += carry;
				if (digit >= 0) {
					carry = digit / 10;
					digit -= (carry * 10);
				}
				else {
					carry = -1;
					digit += 10;
				}
				stringstream convert;
				convert << digit;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
			if (bigger_number == 1) {
				for (i; i<size; i++) {
					num1 = a.number[a.number.size() - 1 - i];
					int digit = atoi(&num1);
					digit += carry;
					if (digit >= 0) {
						carry = digit / 10;
						digit -= (carry * 10);
					}
					else {
						carry = -1;
						digit += 10;
					}
					stringstream convert;
					convert << digit;
					string Result = convert.str();
					new_number.insert(0, Result);
				}
			}
			else {
				for (i; i<size; i++) {
					num2 = b.number[b.number.size() - 1 - i];
					int digit = atoi(&num2);
					digit += carry;
					if (digit >= 0) {
						carry = digit / 10;
						digit -= (carry * 10);
					}
					else {
						carry = -1;
						digit += 10;
					}
					stringstream convert;
					convert << digit;
					string Result = convert.str();
					new_number.insert(0, Result);
				}
			}
			if (carry) {
				stringstream convert;
				convert << carry;
				string Result = convert.str();
				new_number.insert(0, Result);
			}
		}
	}

	if (a.sign == -1 && b.sign == -1)
		new_number.insert(0, "-");
	if (negative) {
		new_number.insert(0, "-");
		b.sign = -b.sign;
	}

	return BigNum(new_number);
}

BigNum& BigNum::operator+=(BigNum& b) {
	BigNum new_number = *this + b;
	number = new_number.number;
	decimal_point = new_number.decimal_point;
	return *this;
}

BigNum BigNum::operator++() {
	BigNum new_number = *this + 1.0;
	*this = new_number;
	return new_number;
}

BigNum BigNum::operator++(int) {
	BigNum old_number(number);
	BigNum new_number = *this + 1.0;
	*this = new_number;
	return old_number;
}

void BigNum::operator=(BigNum & b) {
	number = b.number;
	decimal_point = b.decimal_point;
	sign = b.sign;
}

proxy_bracket BigNum::operator[](int x) {
	BigNum zero("0");
	if (x >= 0) {
		if (x >= decimal_point)
			return proxy_bracket(zero.number[0]);
		return proxy_bracket(number[decimal_point - 1 - x]);
	}
	else {
		return proxy_bracket(number[decimal_point - x]);
	}
}

bool BigNum::operator==(BigNum& b) {
	if (number == b.number && sign == b.sign)
		return true;
	return false;
}

bool BigNum::operator<(BigNum & b) {
	int size1 = 0;
	int size2 = 0;
	if (decimal_point)
		size1 = decimal_point;
	if (b.decimal_point)
		size2 = b.decimal_point;
	if (!decimal_point)
		size1 = number.size();
	if (!b.decimal_point)
		size2 = b.number.size();
	if (sign < b.sign)
		return true;
	if (sign > b.sign)
		return false;
	if (size1 < size2)
		return true;
	if (size1 > size2)
		return false;
	if (size1 == size2) {
		int i = 0;
		while (true) {
			if (number[i] < b.number[i])
				return true;
			if (number[i] > b.number[i])
				return false;
			if (number[i] == b.number[i])
				i++;
		}
	}
	return false;
}

BigNum BigNum::operator-() {
	string num = number;
	BigNum new_num(num);
	new_num.sign *= -1;
	return new_num;
}

BigNum BigNum::operator+(double d) {
	BigNum double_number(d);
	BigNum new_number = *this + double_number;
	return BigNum(new_number);
}

BigNum operator+(const double d, BigNum& b) {
	BigNum double_number(d);
	BigNum new_number = b + double_number;
	return new_number;
}

ostream& operator<<(ostream& out, BigNum& b) {
	if (b.decimal_point != 1) {
		for (int i = 0; i < b.number.size(); i) {
			if (b.number[i] == '0')
				b.number.erase(b.number.begin());
			else
				break;
		}
	}
	if (b.decimal_point) {
		for (int i = b.number.size() - 1; i >= 0; i--) {
			if (b.number[i] == '0')
				b.number.erase(b.number.end() - 1);
			else
				break;
		}
		if ((b.number.size() - 1) == b.decimal_point) {
			b.number.erase(b.number.end() - 1);
			b.decimal_point = 0;
		}
	}

	if (b.sign == -1)
		out << "-";
	out << b.number;
	return out;
}

istream& operator >> (std::istream& in, BigNum& b) {
	string input_number;
	in >> input_number;
	b.number = input_number;
	b.sign = 1;
	if (b.number[0] == '-') {
		b.number.erase(b.number.begin());
		b.sign = -1;
	}
	b.decimal_point = 0;
	for (int i = 0; i<b.number.size(); i++)
		if (b.number[i] == '.') {
			b.decimal_point = i;
			break;
		}
	if (b.decimal_point != 1) {
		for (int i = 0; i < b.number.size(); i) {
			if (b.number[i] == '0')
				b.number.erase(b.number.begin());
			else
				break;
		}
	}
	if (b.decimal_point) {
		for (int i = b.number.size() - 1; i >= 0; i--) {
			if (b.number[i] == '0')
				b.number.erase(b.number.end() - 1);
			else
				break;
		}
		if ((b.number.size() - 1) == b.decimal_point) {
			b.number.erase(b.number.end() - 1);
			b.decimal_point = 0;
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream & out, proxy_bracket & c) {
	out << c.digit_char;
	return out;
}

void proxy_bracket::operator=(const int& n) {
	int m = n;
	m = m + '0';
	if (m > '9' || m < '0') {
		throw not_a_number();
	}
	*number_char = m;
	digit_char = m;
}
