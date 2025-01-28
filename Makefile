# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall

# Цель по умолчанию
all: test_class

# Сборка программы py из объектных файлов
test_class: Ship.o main.o ShipManager.o Field.o Exceptions.o Ability.o AbilityManager.o Game.o
	$(CXX) $(CXXFLAGS) Ship.o main.o ShipManager.o Field.o Exceptions.o Ability.o AbilityManager.o Game.o -o test_class


# Компиляция Ship.cpp в Ship.o
Ship.o: Ship.cpp Ship.h
	$(CXX) $(CXXFLAGS) -c Ship.cpp -o Ship.o

main.o: main.cpp ShipManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Компиляция ShipManager.cpp в ShipManager.o
ShipManager.o: ShipManager.cpp ShipManager.h
	$(CXX) $(CXXFLAGS) -c ShipManager.cpp -o ShipManager.o

# Компиляция Field.cpp в Field.o
Field.o: Field.cpp Field.h
	$(CXX) $(CXXFLAGS) -c Field.cpp -o Field.o


# Компиляция Exceptions.cpp в Exceptions.o
Exceptions.o: Exceptions.cpp Exceptions.h
	$(CXX) $(CXXFLAGS) -c Exceptions.cpp -o Exceptions.o

Ability.o: Ability.cpp Ability.h
	$(CXX) $(CXXFLAGS) -c Ability.cpp -o Ability.o

AbilityManager.o: AbilityManager.cpp AbilityManager.h
	$(CXX) $(CXXFLAGS) -c AbilityManager.cpp -o AbilityManager.o

Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp -o Game.o

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f *.o test_class.exe

# Указание, что цели 'all' и 'clean' являются псевдоцелями
.PHONY: all clean