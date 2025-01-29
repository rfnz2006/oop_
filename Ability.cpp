#include <cstdlib>
#include "Ability.h"
#include "Exceptions.h"
#include "ShipManager.h"
#include <iomanip>


unsigned DoubleDamage::Apply(Field& field, int x, int y)
{
    std::cout << "Used double damage!" << std::endl;
    field.SetNextAttackDouble();
	return 2;
}

void DoubleDamage::Save(std::ostream& s )
{
	s << 1<<std::endl;
}

void DoubleDamage::Load(std::istream& s )
{
}

Scanner::Scanner(size_t x, size_t y)
	: X(x),Y(y)
{
}

unsigned Scanner::Apply(Field& field, int x, int y)
{
	
    std::cout << "Used scanner: x = " << x << ", y = " << y << std::endl;
    return field.Scan2x2(X, Y);
}



void Scanner::Save(std::ostream& s)
{
	s << 2 << std::endl;
	s << X << " " << Y << std::endl;
}

void Scanner::Load(std::istream& s)
{
	s >> X >> Y;
}


Bombing::Bombing()
{
}

unsigned Bombing::Apply(Field& field, int x, int y)
{	std::cout << "Used Bombing" << std::endl;
	return 3;
}

void Bombing::Save(std::ostream& s)
{
	s << 3 << std::endl;
}

void Bombing::Load(std::istream& s)
{
}


