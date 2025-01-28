#include "ShipManager.h"
#include "Exceptions.h"
#include <algorithm>

ShipManager::ShipManager() 
{
}

ShipManager::ShipManager(const std::vector<size_t>& sizes)
{
	for (auto i = sizes.begin(); i != sizes.end(); ++i)
		Ships.emplace_back(*i);
}

Ship& ShipManager::operator[](size_t index)
{
	if (index >= Ships.size())
		throw OutOfShipSize();
	return Ships[index];
}

const Ship& ShipManager::operator[](size_t index)const
{
	if (index >= Ships.size())
		throw OutOfShipSize();
	return Ships[index];
}


size_t ShipManager::getSize()const
{
	return Ships.size();
}

bool ShipManager::areAllShipsDestroyed() const
{
    return std::all_of(Ships.begin(), Ships.end(), [](const Ship& sh) {
        return sh.getState() == ShipState::Destroyed;
    });
}

void ShipManager::save(std::ostream& str)
{
	str << Ships.size()<<std::endl;
	for (auto& shp : Ships)
		shp.save(str);
}

void ShipManager::load(std::istream& str)
{
	size_t sz;
	str >> sz;
	Ships.resize(sz,{1});
	for (auto& shp : Ships)
		shp.load(str);
}
