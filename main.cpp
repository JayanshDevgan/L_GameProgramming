/*#include <iostream>
#include <memory>

// SMART POINTERS

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> bptr;
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::weak_ptr<A> aptr; // use weak_ptr to avoid cycle
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();

    a->bptr = b;
    b->aptr = a;

    return 0;
}


// COPY & MOVE CONSTRUCTOR


#include <iostream>
#include <cstring>
#include <string>


class Texture
{
private:
	unsigned char* data;
	size_t size;
	std::string name;

public:
	Texture(const std::string& fileName, size_t dataSize) : size(dataSize), name(fileName)
	{
		data = new unsigned char[size];
		std::memset(data, 255, size);
		std::cout << "Loaded Texture: " << name << std::endl;
	}

	// Copy Constructor
	Texture(const Texture& other) : size(other.size), name(other.name + "_copy")
	{
		data = new unsigned char[size];
		std::memcpy(data, other.data, size);
		std::cout << "Copied Texture: " << name << std::endl;
	}

	// Move Constructor
	Texture(Texture&& other) noexcept : data(other.data), size(other.size), name(std::move(other.name))
	{
		other.data = nullptr;
		other.size = 0;
		std::cout << "Moved Texture: " << name << std::endl;
	}

	~Texture()
	{
		delete[] data;
		std::cout << "Destroyed Texture: " << name << std::endl;
	}
};


Texture loadTexture()
{
	Texture t("enemy_diffuse.png", 1024 * 1024);
	return t;
}

int main(void)
{
	Texture a("hero_diffuse.png", 512 * 512);
	Texture b = a;
	Texture c = loadTexture();
	return 0;
} */


// Multithreading & Concurrency

#include <iostream>
#include <thread>

void printHello(std::string name)
{
	std::cout << "Hello, " << name << std::endl;
}

int main(void)
{
	//std::thread t(printHello, "JAYANSH");
	//t.join();
	std::thread t([](std::string name) {
		std::cout << "Hello, " << name << std::endl;
		}, "JAYANSH");
	t.join();
	return 0;
}