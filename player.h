#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "monster.h"

class Player {
public:
    // Constructor
    Player(const std::string& name, int health, int attack, int defense, int experience);

    // Destructor
    ~Player() {}

    // Level up 
    void levelUp();
    int getExperienceToNextLevel() const;
    void addExp(int exp);
    void gainExp(unsigned int amount);
    int getNextLevelExperience() const;
    unsigned int getLevel() const { return level_; }
    unsigned int getExperience() const { return exp_; }
    void setLevel(unsigned int level) { level_ = level; }
    void setExperience(unsigned int exp) { exp_ = exp; }
    void setExperienceToNextLevel(unsigned int expThreshold) { expThreshold_ = expThreshold; }
    bool isAlive() const;
    void addExperience(int experiencePoints);

    // Getters and setters
    int getAttack() const;
    std::string getName() const {
        return name_;
    } 
    void printStats() const;
    
    // Combat-related methods
    int attackMonster(Monster* monster);
    void reduceHealth(int damage);
    bool isDefeated() const;
    int getDefense() const;
    void setHealth(unsigned int health) { health_ = health; }
    void setAttack(unsigned int attack) { attack_ = attack; }
    void setDefense(int defense) { defense_ = defense; }
    int getHealth() const { return health_; }

    // Methods to modify player attributes
    void increaseHealth(unsigned int amount);
    void decreaseHealth(unsigned int amount);
    void increaseAttack(unsigned int amount);
    void decreaseAttack(unsigned int amount);
    

private:
    // Player attributes
    std::string name_;
    unsigned int maxHealth_;
    unsigned int level_;
    unsigned int exp_;
    unsigned int expThreshold_;
    unsigned int health_;
    unsigned int attack_;
    int defense_; 
};

#endif
