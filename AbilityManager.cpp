#include "AbilityManager.h"
#include "Exceptions.h"

AbilityManager::AbilityManager() :Queue()
{
}

AbilityManager::~AbilityManager()
{
}

std::shared_ptr<Ability> AbilityManager::GetAbility()
{
	if (Queue.empty())
		throw AbilityAbsence();
	auto ab = Queue.front();
	Queue.pop_front();
	return ab;
}
void AbilityManager::AddAbility(std::shared_ptr<Ability> ab)
{
	Queue.push_back(ab);
}
void AbilityManager::AddRandomAbility(Field& Field)
{
    // Генерация случайного числа
    unsigned r = std::rand();
    
    // Получаем размеры поля один раз
    auto [w, h] = Field.GetFieldSize();
    
    // Умный указатель на способность
    std::shared_ptr<Ability> p;

    switch (r % 3) {
        case 0:
            p = std::make_shared<DoubleDamage>();
            break;
        case 1: {
            unsigned x = std::rand() % (w - 1);
            unsigned y = std::rand() % (h - 1);
            p = std::make_shared<Scanner>(x, y);
            break;
        }
        case 2:
            p = std::make_shared<Bombing>();
            break;
    }

    // Добавление способности в очередь, если она была успешно создана
    if (p) {
        Queue.push_back(std::move(p));
    }
}

bool AbilityManager::Empty() const
{
	return Queue.empty();
}
void AbilityManager::Save(std::ostream& s)
{
	s << Queue.size() << std::endl;
	for (auto& ab : Queue)
		ab->Save(s);
}

size_t AbilityManager::Size() const
{
	return Queue.size();
}

void AbilityManager::Load(std::istream& s)
{
	size_t sz;
	s >> sz;
	Queue.clear();
	for (size_t i = 0; i < sz; i++) {
		int type;
		s >> type;
		Ability* p = nullptr;
		switch (type) {
		case 1:
			p = new DoubleDamage();
			break;
		case 2: {
			p = new Scanner(0,0);
			break;
		}
		case 3:
			p = new Bombing();
			break;
		}
		if (p) {
			p->Load(s);
			Queue.push_back(std::shared_ptr<Ability>(p));
		}
	}
}

