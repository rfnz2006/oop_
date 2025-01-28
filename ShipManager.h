#pragma once

#include "Ship.h"
#include <vector>
#include <ostream>
#include <istream>


class ShipManager
{
private:
	std::vector<Ship> Ships;
public:
	ShipManager();
	ShipManager(const std::vector<size_t>& sizes);
	Ship& operator[](size_t index);
	const Ship& operator[](size_t index)const;
	size_t getSize()const;
	bool areAllShipsDestroyed() const;
	void save(std::ostream&);
	void load(std::istream&);
};