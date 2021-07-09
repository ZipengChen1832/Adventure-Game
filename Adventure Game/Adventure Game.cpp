#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//player stats at level 1
const int player_health_1 = 11, player_attack_1 = 5, player_defense_1 = 2;
const int player_health_2 = 15, player_attack_2 = 7, player_defense_2 = 3;
const int player_health_3 = 19, player_attack_3 = 9, player_defense_3 = 4;
const int player_health_4 = 22, player_attack_4 = 11, player_defense_4 = 4;
const int player_health_5 = 27, player_attack_5 = 13, player_defense_5 = 5;
const int player_health_6 = 30, player_attack_6 = 15, player_defense_6 = 10;

//this determines whether the player has alreayd leveled up
bool triggered_2 = true;
bool triggered_3 = true;
bool triggered_4 = true;
bool triggered_5 = true;
bool triggered_6 = true;

class Mob
{
    public:
        string name;
        int health;
        int attack;
        int defense;
        int exp;

        Mob(string aName, int aHealth, int aAttack, int aDefense, int aExp) {
            name = aName;
            health = aHealth;
            attack = aAttack;
            defense = aDefense;
            exp = aExp;
        }
};  

//This section describes the stats for different monsters
Mob slime("Slime", 5, 3, 1, 2);
Mob zombie("Zombie", 6, 4, 2, 4);
Mob orc("Orc", 9, 6, 4, 6);
Mob ravager("Ravager", 15, 7, 6, 9);
Mob abomination("Abomination", 18, 8, 7, 10);
Mob demon("Demon", 30, 14, 10, 0);

class Player
{
    public:
        string name;
        int health;
        int attack;
        int defense;
        int exp;

        Player(string aName, int aHealth, int aAttack, int aDefense) {
            name = aName;
            health = aHealth;
            attack = aAttack;
            defense = aDefense;
            exp = 0;
        }
};    

void view_player_stats(Player player);
void view_mob(Mob monster[],int n); // display mob stats
void fight(Player& player, Mob monster);
void delete_mob(Mob current_layer[], int& n, int index);
int choose_action(int n);
void clear_layer(Player& player, Mob current_layer[], int& n);
void level_up(Player& player);
void chest1(Player& player);
void chest2(Player& player);




int main()
{
    cout << "You are an adventurer trying to clear a dungeon.\nFight the monsters to level up, defeat the demon to win the game." << endl;
    cout << endl << "Enter your name: ";
    string player_name;
    getline(cin, player_name);
    Player player(player_name, player_health_1, player_attack_1, player_defense_1);
    view_player_stats(player);
    
    cout << endl << "Tips:\nYou can enter the next layer when there is no more than one monster remaining." << endl
        << "When you level up, your health will be reset and stats will increase. Take advantage of that." << endl;

    //layer 1
    cout << endl << "Layer 1" << endl;
    Mob layer1[] = { slime, slime, zombie };
    int length = sizeof(layer1) / sizeof(layer1[0]);
    view_mob(layer1, length);
    clear_layer(player, layer1, length);


    //layer 2
    cout << endl << "Layer 2" << endl;
    Mob layer2[] = { slime, zombie, zombie, orc, orc };
    length = sizeof(layer2) / sizeof(layer2[0]);
    view_mob(layer2, length);
    clear_layer(player, layer2, length);

    //layer 3
    cout << endl << "Layer 3" << endl;
    Mob layer3[] = { slime, orc, orc, zombie };
    length = sizeof(layer3) / sizeof(layer3[0]);
    view_mob(layer3, length);
    clear_layer(player, layer3, length);
    chest1(player);

    //layer 4
    cout << endl << "Layer 4" << endl;
    Mob layer4[] = { orc, orc, ravager, ravager };
    length = sizeof(layer4) / sizeof(layer4[0]);
    view_mob(layer4, length);
    clear_layer(player, layer4, length);
    chest2(player);

    //layer 5
    cout << endl << "Layer 5" << endl;
    Mob layer5[] = { ravager, abomination, abomination };
    length = sizeof(layer5) / sizeof(layer5[0]);
    view_mob(layer5, length);
    clear_layer(player, layer5, length);

    //layer 6
    cout << endl << "Layer 6" << endl;
    Mob layer6[] = { demon };
    length = sizeof(layer6) / sizeof(layer5[6]);
    view_mob(layer6, length);
    while (length){
        switch (choose_action(2)) {
        case 1:
            view_player_stats(player);
            break;
        case 2:
            fight(player, layer6[0]);
            length--;
            break; 
        }
    }
    cout << endl << "Congratulations! You win the game!" << endl;

    return 0;
}

void clear_layer(Player& player, Mob current_layer[], int& n)
{
    /*this function simulates the process of the player clearing the monsters in the currenty layer. 
    "n" it the length of the array currenty_layer[], which represents the number of monsters.*/

    while (n > 0) {
        cout << endl;
        int choice = choose_action(n);
        switch (choice) {
        case 1:
            view_player_stats(player);
            break;
        case 2:
            cout << "Choose a monster: ";
            int monster_index;
            cin >> monster_index;
            while (monster_index>n) {
                cout << "Monster not found, enter again: ";
                cin >> monster_index;
            }
            monster_index--;
            fight(player, current_layer[monster_index]);
            delete_mob(current_layer, n, monster_index);
            view_mob(current_layer, n);
            break;
            
        case 3:
            n = 0;
            break;
        }
    }
}

void fight(Player &player, Mob monster)
{
    //this function determines the outcome of a fight with the monster

    while (player.health > 0 && monster.health > 0)
    {
        player.health -= monster.attack - player.defense;
        monster.health -= player.attack - monster.defense;
    }

    if (player.health <= 0) {
        cout << "You died while fighting the monster! Please try again." << endl;
        exit(0);
    }
    else {
        player.exp += monster.exp;
        cout << "You win!" << endl;
        view_player_stats(player);
        level_up(player);
    }
    return;
}

void view_player_stats(Player player)
{
    cout << endl;
    cout << "Name: " << player.name << endl;
    cout << "===============================================" << endl;
    cout << "  Health     Attack     Defense     Exp" << endl;
    cout << right << setw(6) << player.health << setw(11) << player.attack << setw(12) << player.defense<< setw(8) << player.exp << "/";

    //this section displays the next experience threshold to level up
    if (player.exp < 10)
        cout << "10";
    else if (player.exp < 25)
        cout << "25";
    else if (player.exp < 45)
        cout << "45";
    else if (player.exp < 75)
        cout << "75";
    else if (player.exp < 100)
        cout << "100";
    else if (player.exp >= 100)
        cout << "MAX";
    cout  <<  endl;
    cout << "===============================================" << endl;
}

int choose_action(int n)
{
    //this function allows the player to choose an action
    int choice;
    if (n > 1) {
        cout << "Menu" << endl;
        cout << "1. View player stats" << endl;
        cout << "2. Fight a monster" << endl;
        cout << "Choose an action: ";
        cin >> choice;
        while (choice != 1 && choice != 2) {
            cout << "Invalid choice, choose again: ";
            cin >> choice;
        }
    }

    if (n == 1) {
        cout << "Choose an action: " << endl;
        cout << "1. View player stats" << endl;
        cout << "2. Fight a monster" << endl;
        cout << "3. Go to the next layer" << endl;
        cout << "Choose: ";
        cin >> choice;
        while (choice != 1 && choice != 2 && choice != 3) {
            cout << "Invalid choice, choose again: ";
            getchar();
            cin >> choice;
        }
    }
    return choice;
}

void view_mob(Mob monster[],int n)
{
    //this function displays the monsters in the current layer and their stats

    cout << endl << "Remaining monsters" << endl;
    cout << "==============================================================" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << left << setw(12) << monster[i].name << "Health: " << left << setw(5) << monster[i].health
            << "Attack: " << left << setw(5) << monster[i].attack << "Defense: " << left << setw(5) << monster[i].defense
            << "EXP: " << monster[i].exp << endl;
    }
    cout << "==============================================================" << endl;
}

void delete_mob(Mob current_layer[], int& n, int index)
{
    for (int i = index; i < n-1; i++) {
        current_layer[i] = current_layer[i + 1];
    }
    n--;
}

void level_up(Player& player)
{
    //this program determines whether the player has met the requirements to level up
    //the boolean types in this function are used to check if the player has already leveled up, thus avoiding restoring health after each fight

    if (player.exp >= 100 && triggered_6) {
        player.health = player_health_6;
        player.attack = player_attack_6;
        player.defense = player_defense_6;
        cout << endl << "Your have leveled up! Here is your new stats: ";
        view_player_stats(player);
        triggered_6 = false;
    }
    else if (player.exp >= 70 && triggered_5) {
        player.health = player_health_5;
        player.attack = player_attack_5;
        player.defense = player_defense_5;
        cout << endl << "Your have leveled up! Here is your new stats: ";
        view_player_stats(player);
        triggered_5 = false;
    }
    else if (player.exp >= 45 && triggered_4) {
        player.health = player_health_4;
        player.attack = player_attack_4;
        player.defense = player_defense_4;
        cout << endl << "Your have leveled up! Here is your new stats: ";
        view_player_stats(player);
        triggered_4 = false;
    }
    else if (player.exp >= 25 && triggered_3) {
        player.health = player_health_3;
        player.attack = player_attack_3;
        player.defense = player_defense_3;
        cout << endl << "Your have leveled up! Here is your new stats: ";
        view_player_stats(player);
        triggered_3 = false;
    }
    else if (player.exp >= 10 && triggered_2) {
        player.health = player_health_2;
        player.attack = player_attack_2;
        player.defense = player_defense_2;
        cout << endl << "Your have leveled up! Here is your new stats: ";
        view_player_stats(player);
        triggered_2 = false;
    }
    

}

void chest1(Player& player)
{
    char open_chest;
    cout << endl << "You discovered a chest. Do you want to answer the question to unlock it?(Y/N): ";
    cin >> open_chest;
    while (open_chest != 'Y' && open_chest != 'N') {
        cout << "Invalid entry, try again: ";
        cin >> open_chest;
    }

    if (open_chest == 'Y') {
        cout << "What is 1+1?\nA.1  B.2  C.3\n";
        char ans;
        cin >> ans;
        if (ans == 'B' || ans == 'b') {
            cout << "Correct! You opened the chest and EXP +4" << endl;
            player.exp += 4;
            view_player_stats(player);
            level_up(player);
        }
        else {
            cout << "Wrong answer. The chest is destroyed." << endl;
        }
    }
    else cout << "You choose not to open the chest and proceed to the next layer." << endl;

}
void chest2(Player& player)
{
    char open_chest;
    cout << endl << "You discovered a chest. Do you want to answer the question to unlock it?(Y/N): ";
    cin >> open_chest;
    while (open_chest != 'Y' && open_chest != 'N') {
        cout << "Invalid entry, try again: ";
        cin >> open_chest;
    }

    if (open_chest == 'Y') {
        cout << "What is 1+1?\nA.1  B.2  C.3\n";
        char ans;
        cin >> ans;
        if (ans == 'B' || ans == 'b') {
            cout << "Correct! You opened the chest and EXP +4" << endl;
            player.exp += 4;
            view_player_stats(player);
            level_up(player);
        }
        else {
            cout << "Wrong answer. The chest is destroyed." << endl;
        }
    }
    else cout << "You choose not to open the chest and proceed to the next layer." << endl;

}
