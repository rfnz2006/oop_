#pragma once
#include <memory>
#include <deque>
#include "Field.h"
#include "Ability.h"
class AbilityManager
{
public:
	AbilityManager();
	~AbilityManager();
	std::shared_ptr<Ability> GetAbility();
	void AddAbility(std::shared_ptr<Ability>);
	size_t Size()const;
	void AddRandomAbility(Field&);
	bool Empty()const;
	void Save(std::ostream&);
	void Load(std::istream&);
private:
	std::deque<std::shared_ptr<Ability> > Queue;
};