#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>


#if defined(__GNUC__) || defined(__clang__)
	#include <cmath>
#else 
	#ifndef M_PI
	#define M_PI 3.14159265358979323846
	#endif
#endif

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

// DATA STRUCTURES: START
// LINKED LIST: START

class Node
{
public:
	int data;
	Node* next;

	Node(int value) : data(value), next(NULL) {}
};

void printList(Node* head)
{
	while (head != NULL)
	{
		std::cout << head->data << "->";
		head = head->next;
	}

	std::cout << "NULL" << std::endl;
}

// LINKED LIST: END

// TREES: START
class TNode
{
public:
	int data;
	TNode* left;
	TNode* right;

	TNode(int value) : data(value) {
		left = right = NULL;
	}
};

void inorder(TNode* root)
{
	if (root == NULL) return;
	inorder(root->left);
	std::cout << root->data << std::endl;
	inorder(root->right);
}
// TREES: END 
// DATA STRUCTURES: END

// MATHS: START
// VECTORS: START
struct Vector3
{
	float m_x, m_y, m_z;
	
	Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}

	Vector3 operator+(const Vector3& vec)
	{
		return Vector3(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	void print() const { std::cout << "[" << m_x << ", " << m_y << ", " << m_z << "]" << std::endl; }
};

static float dot(Vector3 A, Vector3 B) { return A.m_x * B.m_x + A.m_y * B.m_y + A.m_z * B.m_z; }

static Vector3 cross(Vector3 A, Vector3 B) {
	return Vector3(
		A.m_y * B.m_z - A.m_z - B.m_y,
		A.m_z * B.m_z - A.m_x * B.m_z,
		A.m_x * B.m_y - A.m_y * B.m_x
	);
}

// VECTORS: END
// ROTATION: START
static Vector3 rotateZ(Vector3 vec, float angle)
{
	float rad = angle * (3.14159265 / 100);
	return Vector3(
		vec.m_x * cos(rad) - vec.m_y * sin(rad),
		vec.m_x * cos(rad) + vec.m_y * sin(rad),
		vec.m_z
	);
}

static Vector3 scale(Vector3 vec, float scale_x, float scale_y, float scale_z)
{
	return Vector3(vec.m_x * scale_x, vec.m_y * scale_y, vec.m_z * scale_z);
}
// ROTATION: END
// ROTATION USING TRIGONOMETRY: START
struct Vector2 {
	float m_x, m_y;

	Vector2(float x, float y) : m_x(x), m_y(y) {}

	Vector2 rotate(float angle)
	{
		float rad = angle * (M_PI / 180);
		return Vector2(
			m_x * cos(rad) - m_y * sin(rad),
			m_x * sin(rad) + m_y * cos(rad)
		);
	}

	void print() const { std::cout << "[" << m_x << ", " << m_y << "]" << std::endl; }
};
// ROTATOIN USING TRIGONOMETRY: END
// MATHS: END

// DIJKSTRA ALGORITHM: START
struct Edge
{
	int to, weight;
};

void dijkstra(int source, int n, std::vector<std::vector<Edge>>& graph)
{
	std::vector<int> dist(n, INT_MAX);
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

	dist[source] = 0;
	pq.push({ 0, source });
	while (!pq.empty())
	{
		int currentDist = pq.top().first;
		int node = pq.top().second;
		pq.pop();

		if (currentDist > dist[node]) continue;

		for (const Edge& edge : graph[node])
		{
			int next = edge.to;
			int newDist = currentDist + edge.weight;

			if (newDist < dist[next])
			{
				dist[next] = newDist;
				pq.push({ newDist, next });
			}
		}
	}

	std::cout << "Shortest distance from source " << source << ":\n";
	for (int i = 0; i < n; i++)
	{
		std::cout << "To Node " << i << " -> " << (dist[i] == INT_MAX ? -1 : dist[i]) << std::endl;
	}
}
// DIJKSTRA ALGORITHM: END

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

	// DATA STRUCTURES_CALL: START
	// LINKED LIST_CALL: START
	Node* head = new Node(10);
	head->next = new Node(20);
	head->next->next = new Node(30);

	printList(head);
	// LINKED LIST_CALL: END
	// STACK_CALL: START
	std::stack<int> s;
	s.push(10);
	s.push(20);
	s.push(30);
	
	std::cout << "Top Element: " << s.top() << std::endl;
	s.pop();
	std::cout << "Top After Pop: " << s.top() << std::endl;
	// STACK_CALL: END
	// QUEUE_CALL: START
	std::queue<int> q;
	q.push(10);
	q.push(20);
	q.push(30);

	std::cout << "Front: " << q.front() << std::endl;
	q.pop();
	std::cout << "Front after pop " << q.front() << std::endl;
	// QUEUE_CALL: END
	
	// TREES_CALL: START
	TNode* root = new TNode(30);
	root->left = new TNode(20);
	root->right = new TNode(10);

	inorder(root);
	// TREES_CALL: END
	// DATA STRUCTURES_CALL: END

	// MATHS: START
	// VECTOR_CALL: START
	// VECTOR_CALL: END
	Vector3 A(3, 4, 0), B(1, 3, 5);
	Vector3 C = A + B;
	float D = dot(A, B);
	Vector3 E = cross(A, B);
	C.print();
	std::cout << D << std::endl;
	E.print();
	Vector3 F = scale(A, 100, 100, 100);
	Vector3 G = rotateZ(A, 20);
	F.print();
	G.print();
	Vector2 point(1, 0);
	Vector2 rotated = point.rotate(90);
	rotated.print();
	// MATHS: END

	// DIJKSTRA ALGORITHM_CALL: START
	int n = 5;
	std::vector<std::vector<Edge>> graph(n);
	
	graph[0] = { {1, 4}, {2, 1} };
	graph[1] = { {0, 4}, {2, 2}, {3, 5} };
	graph[2] = { {0, 1}, {1, 2}, {4, 3} };
	graph[3] = { {1, 5}, {4, 6} };
	graph[4] = { {2, 3}, {3, 6} };

	dijkstra(0, n, graph);
	// DIJKSTRA ALGORITHM_CALL: END // TIME COMPLEXITY O((V + E) LOG V) where V is number of Vertices and E is number of Edges

	return 0;
}