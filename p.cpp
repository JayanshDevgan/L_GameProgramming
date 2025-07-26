#include <iostream>

template<typename T>
void print(T value)
{
	std::cout << value << std::endl;
}

template<typename T1, typename... Args>
void print(T1 a, Args... others)
{
	std::cout << a << std::endl;
	print(others...);
}

int main()
{
	print("FUCK", 242, 24141.0);
	return 0;
}
