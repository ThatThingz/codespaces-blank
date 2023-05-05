#include <iostream>
#include <string>
#include <memory>
#include "player.h"
#include "monster.h"

// Function prototypes
void printHelp();
void printStats(const Player& player);
void levelUp(Player& player);
void attack(std::unique_ptr<Player>& player);

int main() {
    std::unique_ptr<Player> player = std::make_unique<Player>("Hero", 20, 10, 5, 0);
    printStats(*player);

    std::string command;
    while (true) {
        std::cout << "Enter your command: ";
        std::getline(std::cin, command);

        if (command == "help") {
            printHelp();
        } else if (command == "stats") {
            printStats(*player);
        } else if (command == "level up") {
            levelUp(*player);
        } else if (command == "attack") {
            attack(player);
        } else if (command == "quit") {
            std::cout << "Exiting game..." << std::endl;
            break;
        } else {
            std::cout << "Unknown command. Try using 'help'!" << std::endl;
        }
    }

    return 0;
}


void printHelp() {
    std::cout << "List of commands:" << std::endl
              << "- help: Display a list of all commands" << std::endl
              << "- stats: Display the player's stats" << std::endl
              << "- level up: Increase the player's level if they have enough exp" << std::endl
              << "- attack: Attack the monster" << std::endl;
}
void printStats(const Player& player) {
    std::cout << "Player Stats:" << std::endl;
    std::cout << "Name: " << player.getName() << std::endl;
    std::cout << "Level: " << player.getLevel() << std::endl;
    std::cout << "Health: " << player.getHealth() << std::endl;
    std::cout << "Attack: " << player.getAttack() << std::endl;
    std::cout << "Defense: " << player.getDefense() << std::endl;
    std::cout << "Experience: " << player.getExperience() << std::endl;
    std::cout << "Experience to Next Level: " << player.getExperienceToNextLevel() << std::endl;
}
void levelUp(Player& player) {
    int level = player.getLevel();
    int experienceToNextLevel = player.getExperienceToNextLevel();
    int experience = player.getExperience();

    if (experience >= experienceToNextLevel) {
        player.setLevel(level + 1);
        player.setHealth(player.getHealth() + 5);
        player.setAttack(player.getAttack() + 2);
        player.setDefense(player.getDefense() + 2);
        player.setExperience(experience - experienceToNextLevel);
        player.setExperienceToNextLevel(experienceToNextLevel * 2);

        std::cout << "Congratulations! You've leveled up to level " << (level + 1) << "!" << std::endl;
    } else {
        std::cout << "You don't have enough experience to level up yet." << std::endl;
    }
}
void attack(std::unique_ptr<Player>& player) {
    std::unique_ptr<Monster> monster = std::make_unique<Monster>();
    monster->setName("Goblin");
    monster->setLevel(1);
    std::cout << "You are fighting a " << monster->getName() << " (" << monster->getDescription() << ")." << std::endl;

    while (player->isAlive() && monster->isAlive()) {
        // Player attacks first
        int playerDamage = player->attackMonster(monster.get());
        std::cout << "You attack the " << monster->getName() << " for " << playerDamage << " damage." << std::endl;

        // Check if monster is still alive
        if (!monster->isAlive()) {
            std::cout << "You defeated the " << monster->getName() << "!" << std::endl;
            int experience = monster->getExp();
            player->addExperience(experience);
            std::cout << "You gained " << experience << " experience points!" << std::endl;
            break;
        }

        // Monster attacks back
        int monsterDamage = monster->attackPlayer(player);
        std::cout << "The " << monster->getName() << " attacks you for " << monsterDamage << " damage." << std::endl;

        // Check if player is still alive
        if (!player->isAlive()) {
            std::cout << "You have been defeated by the " << monster->getName() << ". Game over!" << std::endl;
            break;
        }
    }
}





