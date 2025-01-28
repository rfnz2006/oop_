#pragma once

#include <vector>
#include <ostream>
#include <istream>

enum class ShipState { Good, Damaged, Destroyed };
enum class ShipOrientation { Horizontal, Vertical };

class Ship
{
private:
    std::vector<ShipState> body;
    ShipOrientation orientation; 

public:
    Ship(size_t size); 
    bool hit(size_t index); 
    ShipState getState() const; 
    ShipState getState(size_t index) const; 
    size_t getSize() const; 
    ShipOrientation getOrientation() const; 
    void setOrientation(ShipOrientation newOrientation); 
    void save(std::ostream& out); 
    void load(std::istream& in); 
};
