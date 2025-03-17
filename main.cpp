#include <iostream>
#include <memory>
#include <vector>

// ENCAPSULATION: START

class Player
{
private:
	int m_health;
	int m_stamina;

public:
	Player(int health, int stamina) : m_health(health), m_stamina(stamina) {}

	void TakeDamage(int damage)
	{
		m_health -= damage;
		if (m_health < 0)
			m_health = 0;
	}

	int GetHealth() const { return m_health; }
};

// ENCAPSULATION: END


// INHERITANCE: START

class BaseCharacter
{
protected:
	std::string m_name;
	int m_health;

public:
	BaseCharacter(std::string name, int health) : m_name(name), m_health(health) {}
	virtual void Speak() { std::cout << m_name << " say hello! \n"; }
};

class NPC : public BaseCharacter
{
public:
	NPC(std::string name, int health) : BaseCharacter(name, health) {}
	void Speak() override { std::cout << m_name << " (NPC) says: welcome traveler! \n"; }
};

// INHERITANCE: END

// POLYMORPHISM: START

void Interact(BaseCharacter* character)
{
	character->Speak();
}

// POLYMORPHISM: END

// ABSTRACTION: START

class GameObject
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	void CommonFunction()
	{
		std::cout << "All GameObjects have a Common function" << std::endl;
	}

	virtual ~GameObject() {}
};

class Cube : public GameObject 
{
public:
	void Update() override
	{
		std::cout << "Cube Update" << std::endl;
	}

	void Render() override
	{
		std::cout << "Cube Render" << std::endl;
	}
};

class Enemy : public GameObject
{
public:
	void Update() override
	{
		std::cout << "Enemy Update" << std::endl;
	}

	void Render() override
	{
		std::cout << "Enemy Render" << std::endl;
	}
};

// ABSTRACTION: END

// RAW POINTERS: START
class Weapon
{
public:
	void Fire() { std::cout << "Weapon Fired!" << std::endl; };
};
// RAW POINTERS: END

// SMART POINTERS: START
class Gun
{
public:
	void Shoot() { std::cout << "Bang bang!" << std::endl; };
};

class Character
{
public:
	std::shared_ptr<int> m_health;
	Character(std::shared_ptr<int> health) : m_health(health) {};
	void ShowHealth() { std::cout << "Health: " << *m_health << std::endl; }
};

class PowerUp
{
public:
	std::string m_type;
	PowerUp(std::string type) : m_type(type) {}
	void Activate() { std::cout << "Power Up Activated: " << m_type << std::endl; }
	~PowerUp() { std::cout << m_type << " Power-Up Destroyed!" << std::endl; }
};

class Car
{
public:
	std::weak_ptr<PowerUp> activePowerUp;

	void UsePowerUp()
	{
		if (auto powerUp = activePowerUp.lock())
		{
			powerUp->Activate();
		}
		else
		{
			std::cout << "Power-Up no longer avaliable! \n";
		}
	}
};

// SMART POINTERS: END

// STACK VS HEAP: START
static void Stack() // FAST, auto deallocation
{
	int a = 4;
}

static void Heap() // SLOW, manual deallocation
{
	int* a = new int(4);
	delete a;
}
// STACK VS HEAP: END

// OBJECT POOLING: START
class Bullet {
public:
	bool active = false;
	void Fire() { active = true; std::cout << "FIRED!"; }
	void Reset() { active = false; }
};

class BulletPool {
	std::vector<Bullet> bullets;
public:
	BulletPool(int size) { bullets.resize(size); }

	Bullet* GetBullet() {
		for (Bullet& b : bullets) {
			if (!b.active) return &b;
		}
		return nullptr;
	}
};

// OBJECT POOLING: END

int main()
{
	// ENCAPSULATION_CALL START
	Player player(100, 50);
	player.TakeDamage(50);
	std::cout << player.GetHealth() << std::endl;
	// ENCAPSULATION_CALL END

	// INHERITANCE_CALL START
	NPC npc("Bob", 100);
	npc.Speak();
	// INHERITANCE_CALL END

	// POLYMORPHISM_CALL START
	Interact(&npc);
	// POLYMORPHISM_CALL END

	// ABSTRACTION_CALL START
	GameObject* cube = new Cube();
	GameObject* enemy = new Enemy();

	cube->Update();
	enemy->Render();

	delete cube;
	delete enemy;
	// ABSTRACTION_CALL END

	// RAW POINTERS_CALL START
	Weapon* Bullet = new Weapon();
	Bullet->Fire();
	delete Bullet;
	// RAW POINTERS_CALL END

	// SMART POINTERS_CALL START
	std::unique_ptr<Gun> pistol = std::make_unique<Gun>();
	pistol->Shoot();

	std::shared_ptr<int> health = std::make_shared<int>(100);
	Character IronMan(health);
	Character Thanos(health);

	IronMan.ShowHealth();
	*health -= 50;
	Thanos.ShowHealth();

	Car car;
	{
		std::shared_ptr<PowerUp> speedBoost = std::make_shared<PowerUp>("Speed Boost");
		car.activePowerUp = speedBoost;

		car.UsePowerUp();
	}
	car.UsePowerUp();
	// SMART POINTERS_CALL END

	// STACK VS HEAP_CALL START
	Stack();
	Heap();
	// STACK VS HEAP_CALL END'

	// OBJECT POOLING_CALL START
	BulletPool bulletPool(10);

	auto bullet1 = bulletPool.GetBullet();
	
	if (bullet1) {
		bullet1->Fire();
		std::cout << "Bullet 1 fired!" << std::endl;
	}
	else {
		std::cout << "No available bullets!" << std::endl;
	}

	auto bullet2 = bulletPool.GetBullet();

	if (bullet2) {
		bullet2->Fire(); // Fire the bullet
		std::cout << "Bullet 2 fired!" << std::endl;
	}
	else {
		std::cout << "No available bullets!" << std::endl;
	}

	// Get another bullet from the pool
	auto bullet3 = bulletPool.GetBullet();
	if (bullet3) {
		bullet3->Fire(); // Fire the bullet
		std::cout << "Bullet 3 fired!" << std::endl;
	}
	else {
		std::cout << "No available bullets!" << std::endl;
	}

	// OBJECT POOLING_CALL END

	return 0;
}