#include <iostream>
#include <memory>
#include <vector>

class Weapon
{
private:
	int m_damage, m_Ammunition;

public:
	Weapon(int damage, int Ammunition) : m_damage(damage), m_Ammunition(Ammunition) {}
	virtual ~Weapon() = default;

	int GetDamage() const { return m_damage; }
	void Use() { if (m_Ammunition > 0) m_Ammunition--; }
	bool HasAmmunition() const { return m_Ammunition > 0; }
};

class Lasers : public Weapon
{
public:
	Lasers(int damage, int Ammunition) : Weapon(damage, Ammunition) {}
};

class Missiles : public Weapon
{
public:
	Missiles(int damage, int Ammunition) : Weapon(damage, Ammunition) {}
};

class PlasmaCannons : public Weapon
{
public:
	PlasmaCannons(int damage, int Ammunition) : Weapon(damage, Ammunition) {}
};

class SpaceShip
{
private:
	std::string m_name, m_pilot;
	int m_shield, m_health;
	std::unique_ptr<Weapon> m_weapon;

public:
	SpaceShip(std::string name, int shield, int health, std::string pilot) :
		m_name(name), m_shield(shield), m_health(health), m_pilot(pilot) {}

	std::string GetName() const { return m_name; }
	int GetHealth() const { return m_health; }

	void SetWeapon(std::unique_ptr<Weapon> weapon) { m_weapon = std::move(weapon); }

	void Attack(std::shared_ptr<SpaceShip> target)
	{
		if (m_weapon && m_weapon->HasAmmunition())
		{
			int damage = m_weapon->GetDamage();
			m_weapon->Use();

			std::cout << m_name << " attacks " << target->m_name << " damaging " << damage << " damage." << std::endl;

			if (target->m_shield > 0)
			{
				int shieldDamage = std::min(damage, target->m_shield);
				target->m_shield -= shieldDamage;
				damage -= shieldDamage;
			}

			std::cout << target->m_name << " - shield: " << target->m_shield << ", Health: " << target->m_health << std::endl;

			if (damage > 0) {
				target->m_health -= damage;
				if (target->m_health < 0) {
					target->m_health = 0;
					std::cout << target->m_name << " Destroyed!" << std::endl;
				}
			}
		}
		else
		{
			std::cout << m_name << " has no Ammunition left!" << std::endl;
		}
	}

	bool isDestroyed() const { return m_health <= 0; }
};


class Fleet
{
private:
	std::string m_commanderName;
	std::shared_ptr<SpaceShip> m_commander;
	std::vector<std::weak_ptr<SpaceShip>> m_squadMembers;

public:
	Fleet(std::shared_ptr<SpaceShip> commander) : m_commander(commander) {
		m_commanderName = commander->GetName();
	}

	void AddSquadMember(std::shared_ptr<SpaceShip> member) { m_squadMembers.push_back(member); }

	void ShowFleetStatus()
	{
		std::cout << "Fleet commander by " << m_commanderName << ":" << std::endl;
		for (const std::weak_ptr<SpaceShip>& weakMember : m_squadMembers)
		{
			if (std::shared_ptr<SpaceShip> member = weakMember.lock())
			{
				std::cout << member->GetName() << " - Health: " << member->GetHealth() << std::endl;
			}
		}
	}
};

int main()
{
	std::shared_ptr<SpaceShip> spaceship_s1 = std::make_shared<SpaceShip>("S1", 150, 100, "UTK");
	spaceship_s1->SetWeapon(std::make_unique<Lasers>(30, 15));

	std::shared_ptr<SpaceShip> spaceship_s2 = std::make_shared<SpaceShip>("S2", 150, 100, "AMAY");
	spaceship_s2->SetWeapon(std::make_unique<Missiles>(40, 4));

	std::shared_ptr<SpaceShip> spaceship_s3 = std::make_shared<SpaceShip>("S3", 150, 100, "RAMU");
	spaceship_s3->SetWeapon(std::make_unique<PlasmaCannons>(50, 2));

	spaceship_s1->Attack(spaceship_s2);
	spaceship_s2->Attack(spaceship_s3);
	spaceship_s3->Attack(spaceship_s1);
	spaceship_s1->Attack(spaceship_s3);
	spaceship_s1->Attack(spaceship_s2);
	spaceship_s2->Attack(spaceship_s3);
	spaceship_s3->Attack(spaceship_s1);
	spaceship_s1->Attack(spaceship_s3);
	spaceship_s1->Attack(spaceship_s2);
	spaceship_s2->Attack(spaceship_s3);
	spaceship_s3->Attack(spaceship_s1);
	spaceship_s1->Attack(spaceship_s3);
	spaceship_s1->Attack(spaceship_s3);
	spaceship_s2->Attack(spaceship_s3);
	spaceship_s2->Attack(spaceship_s3);

	Fleet fleet(spaceship_s1);
	fleet.AddSquadMember(spaceship_s2);
	fleet.AddSquadMember(spaceship_s3);

	fleet.ShowFleetStatus();

	return 0;
}