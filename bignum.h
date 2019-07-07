#include<vector>

class proxy_bracket;

class BigNum {
public:
	BigNum();
	BigNum(double _n);
	BigNum(std::string _number);

	BigNum operator+(BigNum& b);
	BigNum operator+(double d);
	BigNum& operator+=(BigNum& b);
	BigNum operator++();
	BigNum operator++(int);
	void operator=(BigNum &b);
	proxy_bracket operator[](int x);
	bool operator==(BigNum& b);
	bool operator<(BigNum& b);
	BigNum operator-();

	friend std::ostream& operator<<(std::ostream& out, BigNum& b);
	friend std::istream& operator >> (std::istream& in, BigNum& b);

	std::string get_number() { return number; }
private:
	int sign;
	std::string number;
	int decimal_point;
};

BigNum operator+(const double d, BigNum& b);

std::ostream& operator<<(std::ostream& out, BigNum& b);
std::istream& operator >> (std::istream& in, BigNum& b);

class proxy_bracket {
public:
	proxy_bracket(char& c) : number_char(&c), digit_char(*number_char) {}
	void operator=(const int& n);
	friend std::ostream& operator<<(std::ostream& out, proxy_bracket& c);
private:
	char* number_char;
	char digit_char;
};

std::ostream& operator<<(std::ostream& out, proxy_bracket& c);


class not_a_number {};