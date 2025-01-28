#include "Ship.h"
#include "Exceptions.h"
#include <algorithm>

Ship::Ship(size_t ship_size)
{
	orientation = ShipOrientation::Horizontal;
	if (ship_size > 4)
		ship_size = 4;
	if (ship_size < 1)
		ship_size = 1;
	body.resize(ship_size, ShipState::Good);
}

bool Ship::hit(size_t n) {
    if (n >= body.size()) {
        return false;
    }

    switch (body[n]) {
        case ShipState::Good:
            body[n] = ShipState::Damaged;
            break;
        case ShipState::Damaged:
            body[n] = ShipState::Destroyed;
            break;
        default:
            return false; // Если состояние не Good и не Damaged, возвращаем false.
    }

    return true;
}

ShipState Ship::getState() const {
    // Подсчитываем количество каждого состояния в теле корабля
    int destr_count = std::count(body.begin(), body.end(), ShipState::Destroyed);
    int good_count = std::count(body.begin(), body.end(), ShipState::Good);

    // Ранний выход, если все элементы в теле корабля имеют одно из состояний
    if (destr_count == int(body.size())) {
        return ShipState::Destroyed;
    } else if (good_count == int(body.size())) {
        return ShipState::Good;
    }

    // Если есть хотя бы один хороший и один разрушенный сегмент
    return ShipState::Damaged;
}

ShipState Ship::getState(size_t indx)const
{
	if (indx >= body.size())
		throw OutOfShipSize();
	return body[indx];
}

size_t Ship::getSize()const
{
	return body.size();
}

ShipOrientation Ship::getOrientation()const
{
	return orientation;
}

void Ship::setOrientation(ShipOrientation orient)
{
	orientation = orient;
}

void Ship::save(std::ostream& str)
{
	str << body.size()<<std::endl;
	for (const auto& seg : body)
		str << int(seg) << " ";
	str << int(orientation) << std::endl;
}

void Ship::load(std::istream& str) 
{
	size_t size;
	str >> size;
	body.resize(size);
	int tmp;
	for (auto& seg : body) {
		str >> tmp;
		seg = ShipState(tmp);
	}
	str >> tmp;
	orientation = ShipOrientation(tmp);
}