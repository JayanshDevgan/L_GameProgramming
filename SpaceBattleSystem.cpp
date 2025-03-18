#include <iostream>
#include <memory>
#include <vector>

class Weapon
{
private:

};

class Lasers : public Weapon
{

};

class Missiles : public Weapon
{

};

class PlasmaCannons : public Weapon
{

};

class SpaceShip
{
private:
	std::string m_name, m_pilot;
	int m_shield, m_health;
	std::unique_ptr<Weapon> m_weapon;

public:
	SpaceShip(std::string name, int shild, int health, std::string pilot) :
		m_name(name), m_shield(shild), m_health(health), m_pilot(pilot) {}

	void SetWeapon(std::unique_ptr<Weapon> weapon) { m_weapon = std::move(weapon); }
};


int main()
{
	std::shared_ptr<SpaceShip> spaceship_s1 = std::make_shared<SpaceShip>("S1", 150, 100, "UTK");
	std::unique_ptr<Weapon> s1_laser = std::make_unique<Lasers>();
	spaceship_s1->SetWeapon(std::move(s1_laser));

	std::shared_ptr<SpaceShip> spaceship_s2 = std::make_shared<SpaceShip>("S2", 150, 100, "AMAY");
	std::unique_ptr<Weapon> s2_missiles = std::make_unique<Missiles>();
	spaceship_s2->SetWeapon(std::move(s2_missiles));

	std::shared_ptr<SpaceShip> spaceship_s3 = std::make_shared<SpaceShip>("S3", 150, 100, "RAMU");
	std::unique_ptr<Weapon> s3_plasma_cannons = std::make_unique<PlasmaCannons>();
	spaceship_s3->SetWeapon(std::move(s3_plasma_cannons));
}