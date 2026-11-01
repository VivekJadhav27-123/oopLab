#include <iostream>
#include <string>
using namespace std;

// 1. Base Class
class Character {
protected:
    string name;
    int damage;

private:
    int health; // Encapsulation

public:
    // 2. Constructor
    Character(string n, int h, int d) {
        name = n;
        health = h;
        damage = d;
    }

    int getHealth() {
        return health;
    }

    void takeDamage(int d) {
        health -= d;
        if (health < 0)
            health = 0;
    }

    void heal(int h) {
        health += h;
        if (health > 100)
            health = 100;
    }

    // 3. Function Overloading
    void attack(Character &enemy) {
        cout << name << " attacks!\n";
        enemy.takeDamage(damage);
    }

    void attack(Character &enemy, int bonus) {
        cout << name << " uses powerful attack!\n";
        enemy.takeDamage(damage + bonus);
    }

    // 4. Virtual Function
    virtual void special(Character &enemy) {
        attack(enemy);
    }

    void showHealth() {
        cout << name << " Health: " << health << endl;
    }
};

// 5. Inheritance
class Warrior : public Character {
public:
    Warrior(string n) : Character(n, 100, 20) {}

    // 6. Function Overriding
    void special(Character &enemy) override {
        cout << name << " uses Sword Attack!\n";
        attack(enemy, 15);
    }
};

class Mage : public Character {
public:
    Mage(string n) : Character(n, 100, 25) {}

    void special(Character &enemy) override {
        cout << name << " uses Magic Attack!\n";
        attack(enemy, 20);
    }
};

class Monster : public Character {
public:
    Monster(string n) : Character(n, 100, 15) {}

    void special(Character &enemy) override {
        cout << name << " uses Fire Attack!\n";
        attack(enemy, 10);
    }
};

int main() {
    string name;
    int choice, move, potion = 2, score = 0;

    cout << "===== WARRIOR BATTLE GAME =====\n";

    // User Input
    cout << "Enter Player Name: ";
    cin >> name;

    cout << "\n1. Warrior\n2. Mage\n";
    cout << "Select Character: ";
    cin >> choice;

    Warrior warrior(name);
    Mage mage(name);

    // 7. Runtime Polymorphism
    Character *player;

    if (choice == 1)
        player = &warrior;
    else if (choice == 2)
        player = &mage;
    else {
        cout << "Invalid choice! Warrior selected.\n";
        player = &warrior;
    }

    Monster enemy("Dragon");

    while (player->getHealth() > 0 &&
           enemy.getHealth() > 0) {

        cout << "\n===== BATTLE MENU =====\n";
        player->showHealth();
        enemy.showHealth();

        cout << "\n1. Normal Attack";
        cout << "\n2. Special Attack";
        cout << "\n3. Health Potion";
        cout << "\nChoose: ";
        cin >> move;

        if (move == 1)
            player->attack(enemy);

        else if (move == 2)
            player->special(enemy);

        else if (move == 3 && potion > 0) {
            player->heal(30);
            potion--;
            cout << "Health Restored! Potion Left: "
                 << potion << endl;
        }

        else {
            cout << "Invalid move or no potions!\n";
            continue;
        }

        // Enemy Counter Attack
        if (enemy.getHealth() > 0) {
            enemy.special(*player);
        }
    }

    cout << "\n===== GAME RESULT =====\n";

    if (player->getHealth() > 0) {
        cout << "Congratulations! You Won!\n";
        score = 100;
    }
    else {
        cout << "Game Over! Monster Won!\n";
    }

    cout << "Final Score: " << score << endl;

    return 0;
}