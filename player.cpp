#include "Player.h"
#include "Monster.h"

#include <iostream>
#include <string>

using namespace std;

// Constructor
Player::Player(const string& name, int health, int attack, int defense, int experience) :
    name_(name),
    maxHealth_(health),
    level_(1),
    exp_(experience),
    expThreshold_(100),
    health_(health),
    attack_(attack),
    defense_(defense)
{}

// Level up 
void Player::levelUp() {
    ++level_;
    expThreshold_ = static_cast<int>(expThreshold_ * 1.5);
    maxHealth_ += 10;
    health_ = maxHealth_;
    attack_ += 5;
    defense_ += 5;
    cout << "Congratulations, you have leveled up to level " << level_ << "!" << endl;
}

int Player::getExperienceToNextLevel() const {
    return expThreshold_ - exp_;
}

void Player::addExp(int exp) {
    exp_ += exp;
}

void Player::gainExp(unsigned int amount) {
    addExp(amount);
    while (exp_ >= expThreshold_) {
        levelUp();
    }
}

int Player::getNextLevelExperience() const {
    return expThreshold_ - exp_;
}

bool Player::isAlive() const {
    return health_ > 0;
}

void Player::addExperience(int experiencePoints) {
    exp_ += experiencePoints;
}

int Player::getAttack() const {
    return attack_;
}

void Player::printStats() const {
    cout << "Name: " << name_ << endl;
    cout << "Level: " << level_ << endl;
    cout << "Experience: " << exp_ << endl;
    cout << "Experience to next level: " << getExperienceToNextLevel() << endl;
    cout << "Health: " << health_ << "/" << maxHealth_ << endl;
    cout << "Attack: " << attack_ << endl;
    cout << "Defense: " << defense_ << endl;
}

int Player::attackMonster(Monster* monster) {
    int damageDealt = attack_ - monster->getDefense();
    if (damageDealt <= 0) {
        damageDealt = 1;
    }
    monster->reduceHealth(damageDealt);
    cout << "You attacked the " << monster->getName() << " and dealt " << damageDealt << " damage!" << endl;
    return damageDealt;
}

void Player::reduceHealth(int damage) {
    health_ -= damage;
}

bool Player::isDefeated() const {
    return health_ <= 0;
}

int Player::getDefense() const {
    return defense_;
}

void Player::increaseHealth(unsigned int amount) {
    maxHealth_ += amount;
    health_ = maxHealth_;
}

void Player::decreaseHealth(unsigned int amount) {
    if (health_ > amount) {
        health_ -= amount;
    }
    else {
        health_ = 0;
    }
}

void Player::increaseAttack(unsigned int amount) {
    attack_ += amount;
}

void Player::decreaseAttack(unsigned int amount) {
    if (attack_ > amount) {
        attack_ -= amount;
    }
    else {
        attack_ = 0;
    }
}

