#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Party;

class Weapon
{
private:
	int m_damage, m_durability;
	std::string m_special_ability;

public:
	Weapon(int damage, int durability, std::string special_ability) :
		m_damage(damage), m_durability(durability), m_special_ability(special_ability) {}

	void Use() const { std::cout << "Using " << m_special_ability << "(Damage: " << m_damage << ", " << "Durability: " << m_durability << ")\n"; }
	int GetDamage() const { return m_damage; }
};

class Character
{
private:
	std::string m_name;
	int m_level, m_health, m_mana;

	std::unique_ptr<Weapon> m_weapon;
	std::vector<std::shared_ptr<Character>> m_inventory;
	std::shared_ptr<Party> m_party;

public:

	Character(std::string name, int level, int health, int mana, std::shared_ptr<Party> party) :
		m_name(name), m_level(level), m_health(health), m_mana(mana), m_party(party) {}

	std::shared_ptr<Character> m_teammates;

	std::string GetName() { return m_name; }

	void SetWeapon(std::unique_ptr<Weapon> w) { m_weapon = std::move(w); }

	std::shared_ptr<Party> GetParty() const { return m_party; }

	void Attack(std::shared_ptr<Character> player);
};

class Party
{
private:
	int m_Id, m_max_players;
	std::string m_name;
	std::vector<std::shared_ptr<Character>> m_players;

public:
	Party(int id, std::string name, int max_players) :
		m_Id(id), m_name(name), m_max_players(max_players) {
	}

	void Show()
	{
		for (std::shared_ptr<Character> player : m_players)
		{
			std::cout << "Party ID -> " << m_Id << " Name -> "
				<< m_name << " Player Name -> " << player->GetName()
				<< " Players -> " << m_players.size()
				<< " / " << m_max_players << std::endl;
		}
	}

	int GetPlayersSize() { return m_players.size(); }

	void Join(std::shared_ptr<Character> player)
	{
		if (GetPlayersSize() < m_max_players)
			m_players.push_back(player);
		else std::cout << "Party is full" << std::endl;
	}

	void Remove(std::shared_ptr<Character> player) { 
		m_players.erase(std::remove(m_players.begin(), m_players.end(), player), m_players.end());
	}
};

void Character::Attack(std::shared_ptr<Character> player) {
	if (player != nullptr && m_party != nullptr && player->GetParty() != nullptr)
	{
		if (m_party != player->GetParty())
		{
			if (m_weapon) {
				std::cout << GetName() << " --> " << player->GetName() << "\n\t";
				m_weapon->Use();
				player->m_health -= m_weapon->GetDamage();
				if (player->m_health <= 0) player->GetParty()->Remove(player);
			}
			else std::cout << m_name << " has no weapon!" << std::endl;
		}
	}
}

int main()
{
	std::shared_ptr<Party> alpha_party = std::make_shared<Party>(114, "ALPHA", 5);
	std::shared_ptr<Party> bravo_party = std::make_shared<Party>(2432, "BRAVO", 3);
	std::shared_ptr<Party> champions_party = std::make_shared<Party>(32, "CHAMPIONS", 6);

	std::shared_ptr<Character> alex = std::make_shared<Character>("ALEX", 5, 100, 80, alpha_party);
	alex->SetWeapon(std::make_unique<Weapon>(30, 100, "Sword"));

	std::shared_ptr<Character> brody = std::make_shared<Character>("BRODY", 5, 100, 90, bravo_party);
	brody->SetWeapon(std::make_unique<Weapon>(23, 100, "Knife"));

	std::shared_ptr<Character> chimcandy = std::make_shared<Character>("CHIMCANDY", 7, 100, 30, champions_party);
	chimcandy->SetWeapon(std::make_unique<Weapon>(30, 141, "AK47"));
	
	std::shared_ptr<Character> bruno = std::make_shared<Character>("BRUNO", 3, 100, 100, alpha_party);
	bruno->SetWeapon(std::make_unique<Weapon>(32, 100, "M416"));

	std::shared_ptr<Character> hex = std::make_shared<Character>("HEX", 5, 100, 10, alpha_party);
	hex->SetWeapon(std::make_unique<Weapon>(23, 100, "Bazuka"));

	std::shared_ptr<Character> crokx = std::make_shared<Character>("CROKX", 5, 130, 30, alpha_party);
	crokx->SetWeapon(std::make_unique<Weapon>(64, 10, "Axe"));
	
	std::shared_ptr<Character> dg = std::make_shared<Character>("DG", 5, 20, 100, bravo_party);
	dg->SetWeapon(std::make_unique<Weapon>(5, 100, "Spear"));
	
	std::shared_ptr<Character> nibin = std::make_shared<Character>("NIBIN", 5, 30, 100, bravo_party);
	nibin->SetWeapon(std::make_unique<Weapon>(52, 100, "Bow&Arrow"));
	
	std::shared_ptr<Character> chimu = std::make_shared<Character>("CHIMU", 2, 100, 10, bravo_party);
	chimu->SetWeapon(std::make_unique<Weapon>(45, 100, "Wipe"));

	alpha_party->Join(alex);
	alpha_party->Join(bruno);
	alpha_party->Join(hex);
	alpha_party->Join(crokx);

	alex->m_teammates = bruno;
	bruno->m_teammates = hex;
	hex->m_teammates = crokx;
	crokx->m_teammates = alex;

	bravo_party->Join(brody);
	bravo_party->Join(dg);
	bravo_party->Join(nibin);
	bravo_party->Join(chimu);

	brody->m_teammates = dg;
	dg->m_teammates = nibin;
	nibin->m_teammates = chimu;
	chimu->m_teammates = brody;

	champions_party->Join(chimcandy);

	alpha_party->Show();
	bravo_party->Show();
	champions_party->Show();

	alex->Attack(brody);
	brody->Attack(alex);
	chimcandy->Attack(nullptr);
	bruno->Attack(dg);
	hex->Attack(chimu);
	crokx->Attack(nibin);
	dg->Attack(alex);
	nibin->Attack(hex);
	chimu->Attack(crokx);
}