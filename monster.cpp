#include "monster.h"
#include "player.h"
#include <iostream>
#include <random>
#include <chrono>
#include <memory>

int getRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

Monster::Monster()
    : level(1), name("Goblin"), health(20), maxHealth(20), attack(4), defense(2)
{
}

double Monster::getAttack() const
{
    return attack;
}

double Monster::getDefense() const
{
    return defense;
}

int Monster::getExp() const
{
    return level * 10;
}

int Monster::getHealth() const
{
    return health;
}

void Monster::reduceHealth(int amount)
{
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

bool Monster::isDefeated() const
{
    return health == 0;
}

void Monster::print() const
{
    std::string monsterName = (level <= 20) ? "Goblin" : "Troll";
    std::cout << monsterName << " [Level " << level << "]:\n";
    std::cout << "Health: " << health << "/" << maxHealth << "\n";
    std::cout << "Attack: " << attack << "\n";
    std::cout << "Defense: " << defense << "\n";
    std::cout << "Experience: " << getExp() << "\n\n";
}

void Monster::levelUp() {
    level += 1;
    maxHealth += maxHealth * STATS_INCREASE_PERCENT;
    attack += attack * STATS_INCREASE_PERCENT;
    defense += defense * STATS_INCREASE_PERCENT;
    if (level % 10 == 0) {
        maxHealth += maxHealth * STATS_INCREASE_TENTH_LEVEL_PERCENT / 100;
        attack += attack * STATS_INCREASE_TENTH_LEVEL_PERCENT / 100;
        defense += defense * STATS_INCREASE_TENTH_LEVEL_PERCENT / 100;
    }
}

void Monster::attack(Player& player) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> attackDist(0, attack);
    int damage = attackDist(generator) - player.getDefense();
    damage = damage > 0 ? damage : 0;
    player.takeDamage(damage);
}

int Monster::attackPlayer(std::unique_ptr<Player, std::default_delete<Player>>& player) const {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> attackDist(0, attack);
    int damage = attackDist(generator) - player->getDefense();
    damage = damage > 0 ? damage : 0;
    player->takeDamage(damage);
    return damage;
}

const int STATS_INCREASE_TENTH_LEVEL_PERCENT = 10;
const double STATS_INCREASE_PERCENT = 0.05;

void Monster::takeDamage(int damage) {
    int healthAfterDamage = health - damage;
    health = healthAfterDamage > 0 ? healthAfterDamage : 0;
}

void Monster::setName(std::string name)
{
    this->name = name;
}

void Monster::setLevel(int level)
{
    this->level = level;
}

std::string Monster::getDescription() const
{
    return "a level " + std::to_string(level) + " " + name;
}