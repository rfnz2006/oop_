#pragma once

#include <memory>
#include <deque>
#include <ostream>
#include <istream>
#include "Field.h"

class Game;

class Ability 
{
public:
	virtual unsigned Apply(Field& field, int x, int y) = 0;
	virtual unsigned Type()const = 0;
	virtual ~Ability() {}
	virtual void Save(std::ostream&) = 0;
	virtual void Load(std::istream&) = 0;
};

class DoubleDamage : public Ability 
{
public:
	virtual unsigned Apply(Field& field, int x, int y)override;
	virtual unsigned Type()const override{ return 0; }
	virtual void Save(std::ostream&)override;
	virtual void Load(std::istream&)override;
};

class Scanner : public Ability
{
public:
	Scanner(size_t x, size_t y);
	virtual unsigned Apply(Field& field, int x, int y)override;	
	virtual unsigned Type()const override{ return 1; }
	virtual void Save(std::ostream&)override;
	virtual void Load(std::istream&)override;
private:
	size_t X, Y;
};

class  Bombing: public Ability
{
public:
	Bombing();
	virtual unsigned Apply(Field& field, int x, int y)override;
	virtual unsigned Type()const override{ return 2; }
	virtual void Save(std::ostream&)override;
	virtual void Load(std::istream&)override;

};