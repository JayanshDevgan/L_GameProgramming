#include <iostream>
#include <vector>
#include <memory>

class Weapon
{
private:
	int m_damage, m_durability;
	std::string m_special_ability;

public:
	Weapon(int damage, int durability, std::string special_ability) :
		m_damage(damage), m_durability(durability), m_special_ability(special_ability) {}
};

class Inventory
{
	// TODO
};

class Character
{
private:
	std::string m_name;
	int m_level, m_health, m_mana;

	std::shared_ptr<Inventory> m_inventory = std::make_shared<Inventory>();
	//std::unique_ptr<Weapon> m_weapon = std::make_unique<Weapon>();

public:
	Character(std::string name, int level, int health, int mana) :
		m_name(name), m_level(level), m_health(health), m_mana(mana) {}

	std::string GetName() { return m_name; }
};

class Party
{
private:
	int m_Id, m_max_players;
	std::string m_name;
	std::weak_ptr<Character*> m_player;
	std::vector<Character*> m_players;

public:
	Party(int id, std::string name, int max_players) :
		m_Id(id), m_name(name), m_max_players(max_players) {}

	void Show()
	{
		for (Character* player : m_players)
		{
			std::cout << "Party ID -> " << m_Id << " Name -> "
				<< m_name << " Player Name -> " << player->GetName()
				<< " Players -> " << m_players.size()
				<< " / " << m_max_players << std::endl;
		}
	}

	void Join(Character* player)
	{
		m_players.push_back(player);
	}
};

int main()
{
	Character* alex = new Character("ALEX", 5, 100, 80);
	Character* brody = new Character("BRODY", 5, 100, 90);
	Character* chimcandy = new Character("CHIMCANDY", 7, 100, 30);
	Character* bruno = new Character("BRUNO", 3, 100, 100);
	Character* hex = new Character("HEX", 5, 100, 10);
	Character* crokx = new Character("CROKX", 5, 130, 30);
	Character* dg = new Character("DG", 5, 20, 100);
	Character* nibin = new Character("NIBIN", 5, 30, 100);
	Character* chimu = new Character("CHIMU", 2, 100, 10);

	Party* alpha_party = new Party(114, "ALPHA", 5);
	Party* bravo_party = new Party(2432, "BRAVO", 6);
	Party* champions_party = new Party(32, "CHAMPIONS", 6);

	alpha_party->Join(alex);
	alpha_party->Join(bruno);
	alpha_party->Join(hex);
	alpha_party->Join(crokx);

	bravo_party->Join(brody);
	bravo_party->Join(dg);
	bravo_party->Join(nibin);
	bravo_party->Join(chimu);

	champions_party->Join(chimcandy);

	alpha_party->Show();
	bravo_party->Show();
	champions_party->Show();
}