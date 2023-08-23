// #include "test.hpp"
#include <iostream>

typedef std::string str_t;

typedef std::string (*testLevel) (void);

class Testing
{
	private:
	public:
		Testing();
		~Testing();
		str_t test1(void);
		str_t test2(void);
		str_t (Testing::*tl(int lvl))(void);
};

Testing::Testing() { }

Testing::~Testing() { }

str_t Testing::test1(void)
{
	return ("test 1");
}

str_t	Testing::test2(void)
{
	return ("test 2");
}

str_t	(Testing::*Testing::tl(int lvl)) (void)
{
	str_t	(Testing::*t) (void);

	if (lvl == 1)
		t = &Testing::test1;
	else if (lvl == 2)
		t = &Testing::test2;
	else
		t = NULL;
	return (t);
}

int main(void)
{
	Testing t;
	str_t	(Testing::*selected)(void);

	selected = t.tl(2);
	if (selected)
		std::cout << (t.*selected)() <<std::endl;
	else
		std::cout << "Invalid command!" << std::endl;
	return (0);
}
