#pragma once
#include "Field.h"
#include "ShipManager.h"
#include "Ship.h"
#include "AbilityManager.h"
#include <ostream>
#include <istream>

struct GameState {
    int playerScore;
    int enemyScore;
    int currentRound;
    bool isEnemyTurn;
    void initialize();
    void save(std::ostream& outStream);
    void load(std::istream& inStream);
};

enum class RoundOutcome { Quit, GameOver, RoundComplete };

class Game {
private:
    size_t fieldWidth = 10;
    size_t fieldHeight = 10;
    Field playerField;
    Field enemyField;
    GameState gameState;
    AbilityManager abilityManager;

private:
    void initializeGame();
    void initializeRound();
    Field generateRandomField();
    void initializePlayerField();
    void initializeEnemyField();
    void initializeAbilities();
    RoundOutcome playRound();
    bool UserTurn(size_t x, size_t y, bool useAbility);
    bool EnemyTurn();
    unsigned applyAbility(Ability& ability, Field& field, int x, int y);
    char getCommandFromUser();
    void saveGame();
    void loadGame();

public:
    Game();
    ~Game();
    void startGame();
};
