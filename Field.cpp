#include "Field.h"
#include "Exceptions.h"
#include "Ability.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>

Field::Field()
	:ShipMan(), Cells(), NextAttackDouble(false)
{
}

Field::Field(const ShipManager& shpmn, size_t width, size_t height)
	:ShipMan(shpmn), Cells(), NextAttackDouble(false)
{
	SetFieldSize(width, height);
}

void Field::SetFieldSize(size_t w, size_t h)
{
	Cells.resize(h); 
	for (auto& row : Cells)
		row.resize(w, { EmptyCell,CellState::Unknown,ShipState::Good }); //X
}

Field::Field(const Field& r)
	:ShipMan(r.ShipMan), Cells(r.Cells), NextAttackDouble(r.NextAttackDouble)
{
}

Field::Field(Field&& r)
	:ShipMan(std::move (r.ShipMan)), Cells(std::move(r.Cells)), NextAttackDouble(r.NextAttackDouble)
{
}

Field& Field::operator=(const Field& r)
{
	ShipMan = r.ShipMan;
	Cells = r.Cells;
	NextAttackDouble = r.NextAttackDouble;
	return  *this;
}
Field& Field::operator=(Field&& r)
{
	ShipMan = std::move(r.ShipMan);
	Cells = std::move(r.Cells);
	NextAttackDouble = r.NextAttackDouble;
	return  *this;
}

Field::~Field()
{
}

// Функция для корректировки координат с учетом границ
inline void ClipCoordinates(int& x0, int& y0, int& x1, int& y1, int w, int h)
{
    x0 = std::max(0, std::min(w - 1, x0));
    y0 = std::max(0, std::min(h - 1, y0));
    x1 = std::max(0, std::min(w - 1, x1));
    y1 = std::max(0, std::min(h - 1, y1));
}

bool Field::PlaceShip(size_t ship_index, size_t x0, size_t y0, ShipOrientation ori)
{
    Ship& ship = ShipMan[ship_index];
    size_t len = ship.getSize();
    auto [w, h] = GetFieldSize();
    
    // Проверка на выход за пределы
    if (y0 >= h || x0 >= w)
        throw OutOfBoundaries();

    // Проверка для горизонтального размещения
    if (ori == ShipOrientation::Horizontal) {
        if (x0 + len > w)
            throw IllegalShipPlacement();
        
        // Упрощенная проверка: проверяем возможное размещение с учетом границ
        if (!CanPlaceShip(x0 - 1, y0 - 1, x0 + len, y0 + 1))
            throw IllegalShipPlacement();
        
        DrawShipHor(ship_index, x0, y0, len);
    }
    else { // Для вертикального размещения
        if (y0 + len > h)
            throw IllegalShipPlacement();
        
        if (!CanPlaceShip(x0 - 1, y0 - 1, x0 + 1, y0 + len))
            throw IllegalShipPlacement();
        
        DrawShipVer(ship_index, x0, y0, len);
    }
    
    ship.setOrientation(ori);
    return true;
}

Ship& Field::GetShip(size_t shpindx)
{
	return ShipMan[shpindx];
}

const ShipManager& Field::GetShipMan() const
{
	return ShipMan;
}

// Проверка на возможность размещения корабля
bool Field::CanPlaceShip(int x0, int y0, int x1, int y1)
{
    auto [w, h] = GetFieldSize();
    
    // Корректировка координат с учетом границ
    ClipCoordinates(x0, y0, x1, y1, w, h);
    
    for (int x = x0; x <= x1; ++x) {
        for (int y = y0; y <= y1; ++y) {
            if (Cells[y][x].Own != EmptyCell && Cells[y][x].Own != SurrCell)
                return false;
        }
    }
    return true;
}

// Оптимизация методов MarkHor и MarkVer
void Field::MarkHor(int value, int x0, int y0, int x1)
{
    auto [w, h] = GetFieldSize();
    
    // Корректировка координат с учетом границ
    ClipCoordinates(x0, y0, x1, y0, w, h);
    
    for (int x = x0; x <= x1; ++x)
        Cells[y0][x].Own = value;
}

void Field::MarkVer(int value, int x0, int y0, int y1)
{
    auto [w, h] = GetFieldSize();
    
    // Корректировка координат с учетом границ
    ClipCoordinates(x0, y0, x0, y1, w, h);
    
    for (int y = y0; y <= y1; ++y)
        Cells[y][x0].Own = value;
}

// Рисуем корабль горизонтально
void Field::DrawShipHor(size_t ship_index, size_t x0, size_t y0, size_t len)
{
    MarkHor((int)ship_index, (int)x0, (int)y0, (int)(x0 + len - 1));
    MarkHor(SurrCell, (int)x0, (int)y0 - 1, (int)(x0 + len - 1));
    MarkHor(SurrCell, (int)x0, (int)y0 + 1, (int)(x0 + len - 1));
    MarkVer(SurrCell, (int)x0 - 1, (int)y0 - 1, (int)y0 + 1);
    MarkVer(SurrCell, (int)(x0 + len), (int)y0 - 1, (int)y0 + 1);
}

// Рисуем корабль вертикально
void Field::DrawShipVer(size_t ship_index, size_t x0, size_t y0, size_t len)
{
    MarkVer((int)ship_index, (int)x0, (int)y0, (int)(y0 + len - 1));
    MarkVer(SurrCell, (int)x0 - 1, (int)y0, (int)(y0 + len - 1));
    MarkVer(SurrCell, (int)x0 + 1, (int)y0, (int)(y0 + len - 1));
    MarkHor(SurrCell, (int)x0 - 1, (int)y0 - 1, (int)x0 + 1);
    MarkHor(SurrCell, (int)x0 - 1, (int)(y0 + len), (int)x0 + 1);
}

std::pair<size_t, size_t> Field::GetFieldSize() const
{
	size_t h = Cells.size();
	if (h == 0)
		throw EmptyField();
	size_t w = Cells[0].size();
	if (w == 0)
		throw EmptyField();
	return {w,h};
}

std::pair<CellState, ShipState > Field::Attack( size_t x, size_t y)
{
	bool doubledamage = NextAttackDouble;
	NextAttackDouble = false;
	auto [w, h] = GetFieldSize();
	if (x >= w || y >= h)
		throw OutOfBoundaries();
	int ship_index = Cells[y][x].Own;
	if (ship_index < 0)
		return { CellState::Empty,ShipState::Good };
	Ship& ship = ShipMan[ship_index];
	size_t n = 0;
	if (ship.getOrientation() == ShipOrientation::Horizontal) {
		while (x>n && Cells[y][x - n - 1].Own == ship_index)
			n++;
	}
	else {
		while (y > n && Cells[y-n-1][x].Own == ship_index)
			n++;
	}
	ship.hit(n);
	if(doubledamage){
		ship.hit(n);
        NextAttackDouble = false;}
    if(FlagBoombing){
        ship.hit(ship_index);
        FlagBoombing = false;
    }
    
	return { CellState::Occupied,ship.getState(n) };
}


void Field::SetEnemyState(size_t x, size_t y, CellState cell_state,ShipState ship_state)
{
	auto [w, h] = GetFieldSize();
	if (x >= w || y >= h)
		throw std::exception();
	Cells[y][x].State = cell_state;
	Cells[y][x].EnemyShip = ship_state;
}


void Field::SetNextAttackDouble()
{
	NextAttackDouble = true;
}

int Field::Scan2x2(size_t x, size_t y)
{
	auto [w, h] = GetFieldSize();
	if (x >= w-1 || y >= h-1)
		throw OutOfBoundaries();
	return unsigned(Cells[y][x].Own>=0 || Cells[y+1][x].Own >= 0 || Cells[y][x+1].Own >= 0 || Cells[y+1][x+1].Own >= 0);
}

void Field::Bombing()
{
	auto [w, h] = GetFieldSize();
        for(int x = 0; x < (int)w; x++)
        { 
            for(int y; y < (int)h; y++)
            {   
                int ship_index = Cells[x][y].Own;
		        if (ship_index >= 0) {
                    FlagBoombing = true;
                    break;
		        }
	        }
        }
}

Field::Cell Field::GetCell(size_t x, size_t y) const
{
	auto [w, h] = GetFieldSize();
	if (x >= w || y >= h)
		throw OutOfBoundaries();
	return Cells[y][x];
}


void Field::Save(std::ostream& str)
{
	auto [w, h] = GetFieldSize();
	str << w <<" "<< h<<std::endl;
	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			str << Cells[y][x].Own << " " << int(Cells[y][x].State) << " " << int(Cells[y][x].EnemyShip) << std::endl;
		}
	}
	ShipMan.save(str);
}

void Field::Load(std::istream& str)
{
	NextAttackDouble = false;
	size_t w, h;
	str >> w >> h;
	SetFieldSize(w, h);
	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			int state, enemishp;
			str >> Cells[y][x].Own >> state >> enemishp;
			Cells[y][x].State = CellState(state);
			Cells[y][x].EnemyShip = ShipState(enemishp);
		}
	}
	ShipMan.load(str);
}

std::ostream& operator<<(std::ostream& os, const Field& gb)
{
    auto [w, h] = gb.GetFieldSize();
    static const char ship_names[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char ship_state[] = {'+', '-', 'X'};  // Массив для состояний корабля

    // Отображаем строки поля
    for (size_t y = 0; y < h; ++y) {
        os << std::setw(3) << y << ":  ";
        
        // Пройдем по всем клеткам в строке для отображения кораблей и состояния атак
        for (size_t x = 0; x < w; ++x) {
            Field::Cell cell = gb.GetCell(x, y);
            int j = cell.Own;

            // Отображаем собственный корабль
            if (j < 0) {
                os << ". ";
                continue;
            }

            const ShipManager& shpmn = gb.GetShipMan();
            const Ship& ship = shpmn[j];
            char c = (unsigned)j >= sizeof(ship_names) ? '%' : ship_names[j];

            // Определяем, на какой части корабля находимся
            unsigned count = 0;
            if (ship.getOrientation() == ShipOrientation::Horizontal) {
                while (count + 1 <= x && gb.GetCell(x - count - 1, y).Own == j) {
                    ++count;
                }
            }
            else {
                while (count + 1 <= y && gb.GetCell(x, y - count - 1).Own == j) {
                    ++count;
                }
            }

            // Отображаем состояние корабля
            ShipState state = ship.getState(count);
            os << c << ship_state[static_cast<int>(state)];
        }

        os << "   ";  // Разделитель между двумя областями
        os << std::setw(3) << y << ":  ";

        // Отображаем атакованные клетки
        for (size_t x = 0; x < w; ++x) {
            os << ' ';
            Field::Cell cell = gb.GetCell(x, y);
            auto cs = cell.State;
            auto ss = cell.EnemyShip;

            // Отображаем состояние атак
            if (cs == CellState::Occupied) {
                os << ship_state[static_cast<int>(ss)];
            }
            else if (cs == CellState::Unknown) {
                os << '?';
            }
            else {
                os << '.';
            }
        }

        os << std::endl;
    }

    // Отображаем номера столбцов (X) снизу
    os << std::setw(5) << " ";
    for (int i = 0; i < int(w); ++i)
        os << std::setw(2) << i % 10;
    os << std::setw(10) << " ";
    for (int i = 0; i < int(w); ++i)
        os << std::setw(2) << i % 10;
    os << std::endl;

    return os;
}
