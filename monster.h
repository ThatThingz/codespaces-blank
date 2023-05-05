#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <memory>

class Player;

class Monster {
protected:
    int level;
    std::string name;
    int health;
    const int maxHealth;
    const double attack;
    const double defense;

public:
    Monster();
    virtual ~Monster() {}

    int getLevel() const;
    std::string getName() const;
    double getAttack() const;
    double getDefense() const;
    int getExp() const;
    int getHealth() const;
    void reduceHealth(int amount);
    bool isDefeated() const;
    bool isAlive() const;

    void setName(const std::string& name);
    void setLevel(int level);
    std::string getDescription() const;

    void print() const;
    void levelUp();

    virtual int attackPlayer(std::unique_ptr<Player>& player) const;
    virtual void takeDamage(int damage);
};

class LeveledMonster : public Monster {
private:
    static constexpr int NAME_CHANGE_LEVEL = 21;
    static constexpr int STATS_CHANGE_LEVEL = 10;
    static constexpr double STATS_INCREASE_PERCENT = 0.005;
    static constexpr double STATS_INCREASE_TENTH_LEVEL_PERCENT = 0.01;
    static constexpr int STATS_CHANGE_THRESHOLD = STATS_CHANGE_LEVEL * 10;

public:
    LeveledMonster();
    virtual ~LeveledMonster() {}

    virtual void levelUp();
    virtual void updateName();
};

#endif // MONSTER_H
