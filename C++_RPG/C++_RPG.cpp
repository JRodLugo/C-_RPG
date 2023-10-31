#include <iostream> // the one everything runs off of
#include <string> // its in the name
#include <stdlib.h> // rand()
#include <cstdlib> // srand() functionality
#include <ctime> // time and other things relating to time
#include <cmath>//imports math functions and operations into c++

using namespace std;

// class for player
class player {
    private:
        string name;
    public:
        //setters and getters for players name

        void setName(string Name) {
            name = Name;
        }
        string getName() {
            return name;
        }
        // defualt varibles for heatlh, armor, damage, and gold the player has
        int Health = 10;
        int Armor = 10;
        int Damage = 2;
        int Gold = 8;
        bool combatCode = false;
};

// class for smelly little goblins
class enemy{
    public:
        int Health = 0;
        int Armor = 5;
        int Damage = 2;
        int Gold = 4;
        
};

// class to represent a town where player can purchase better armor weapons and heal

player Player1;

class town {
    public:
        // price for the towns services
        int price = 1;
        // stat to increase weapon damage and armor points if player has enough gold
        int Gear(int equpiment) {
            if (Player1.Gold >= 7) {
                cout << "The wanders gear has become stronger! \n";
                Player1.Gold = Player1.Gold - price;
                equpiment++;
                return equpiment;
            }
            else {
                cout << "The wanderer dosn't have enough gold for this service \n";
            }
        }
        // so the player dosn't exceed the indended amount of health it will always equal 10
        int heal(){
            if (Player1.Health <= 10 && Player1.Gold >= 8) {
                cout << "You feel well rested now \n";
                Player1.Health = 10;
                Player1.Gold = Player1.Gold - price;
                return Player1.Health;
            }
            else if (Player1.Gold < 8){
                cout << "The wanderer dosn't have enough gold for this service \n";
                return Player1.Health;
            }
            else {
                cout << " your wanderer is already well rested \n";
                return Player1.Health;
            }
        }
};

// Global varibles
string Answer;
bool GameRunning = true;
enemy Goblin1;
town Town1;

// combat ancounters
bool EnteredCombat();
// randmoised text promts about the world and location
string WorldEnviorment();
// the town for healthing and upgrading gear
void settlement();

void PlayerStats();

// main function
int main(){
    //engine for main function
    srand(time(0));
    // varibles
    string PlName;
    int EnemyHPIncrease = 5;
  
    // Asks the player for the characters name and asks if they want to change it befor game begins
    do {
        cout << "What is the name of your Wanderer? \n";
        // using the getline function just incase player wants wanderer to have a last name
        getline(cin, PlName);
        Player1.setName(PlName);
        cout << "Conferm that your Wanderers name is " << Player1.getName() << " yes or no?" << endl;
        cin >> Answer;
        //clears getline() and allows player to pick a different name if they choose
        cin.ignore();
    } while (Answer == "no" || Answer == "No");
    
    while (GameRunning == true) {
        //distributor for main function
        int mainGen = (rand() % 3) + 1;
        //A little break so the player can read whats going on or check their wanderers stats
        cout << Player1.getName() << " wanders through a large streach of wastes of the dead world" << endl;
        cout << "continue : Stats \n";
        cin >> Answer;
        // player stats
        if (Answer == "stats" || Answer == "Stats") {
            PlayerStats();
        }
        //switch and case for randomizing events like world discription, encounters, and when the town will apear
        //issue where combat will start out of nowhere interupting current code including combat <- fix this issue
        switch (mainGen) {
            case 1:
                // if the player has won combat the loop will continue
                cout << mainGen << endl;
                cout << "out of nowhere a Beast apears and challenged " << Player1.getName() << " to a battle" << endl;
                Goblin1.Health = EnemyHPIncrease;
                if (EnteredCombat() == true) {
                    EnemyHPIncrease = Goblin1.Health + Player1.Gold;
                }
                EnteredCombat();
                // enemy heath increases the more gold a player has 
                break;
            case 2:
                // randomized enviorment details
                cout << mainGen << endl;
                cout << WorldEnviorment() << endl;
                break;
            case 3:
                // rest stop
                cout << mainGen << endl;
                cout << Player1.getName() << " finds a town to rest and upgrade equpment! \n";
                settlement();
                break;
            default:
                // if somthing breaks
                cout << "Error somthing went wrong. What you might say? IDK you think I know wise guy?! \n";
                break;
        }
          // checks if player has either falled in combat or died some other way
        if (EnteredCombat() == false || Player1.Health <= 0) {
            cout << "Your wander has fallen \n";
            cout << "Game over \n";
        }
        // incase player ran away
        else if (Player1.combatCode == true) {
            cout << Player1.getName() << " Fleed from the battle \n";
            Player1.combatCode = false;
            continue;
        }
        else {
            continue;
        }
    }

    // to see if player wants to play again
    cout << "Play again? \n";
    cin >> Answer;

    if (Answer == "yes" || Answer == "Yes") {
        cin.ignore();
        GameRunning = true;
        main();
    }
    else {
        cout << " Good bye \n";
        return 0;
    }
}

// combat function
bool EnteredCombat() {
    Player1.combatCode == true;
    // remove when done testing
    cout << "player has entered combat \n";
    // enemy encounter
    srand(time(0));
    // combat loop
    while (Goblin1.Health > 0 && Player1.Health > 0) {
  
        cout << "Attack Heal Run \n";
        cin >> Answer;
        // picks a number between 1 and 20 for attack ACs and other stuff
        // also acts as a distributor
        int PlayerOnHit = rand() % 20;
        int EnemyOnHit = rand() % 20;

        //player actions
        //checks if the player wants to attack and onHit is greater than the enemys AC
        if (Answer == "attack" && PlayerOnHit >= Goblin1.Armor && Goblin1.Health > 0 || Answer == "Attack" && PlayerOnHit >= Goblin1.Armor && Goblin1.Health > 0) {
            cout << Player1.getName() << " Attacks! \n";
            //nested if for critical hits
            if (PlayerOnHit == 20) {
                cout << "ITS A CRITICAL STRIKE!! \n";
                cout << "enemy takes " << Player1.Damage * 2 << " damage!" << endl;
                Goblin1.Health = Goblin1.Health - (Player1.Damage * 2);
            }
            else {
                cout << "enemy takes " << Player1.Damage << " damage!" << endl;
                Goblin1.Health = Goblin1.Health - Player1.Damage;
            }
            // end of if statment
        }
        // when onhit isn't greater than the enemies armor
        else if (PlayerOnHit < Goblin1.Armor) {
            cout << Player1.getName() << " Attacks! \n";
            cout << "bit completly misses \n";
        }
        // healing during combat
        else if (Answer == "heal" && Player1.Health < 10 || Answer == "Heal" && Player1.Health < 10) {
            int Medic = (rand() % 2) + 1;
            int heal = (rand() % 4) + 1;
            cout << Player1.getName() << " Atempts to use a med unit! \n";
            //switch and case for healing
            switch (Medic) {
                case 1:
                    cout << Player1.getName() << " quickly healths their wounds \n";
                    cout << Player1.getName() << " recovers " << heal << " health" << endl;
                    Player1.Health = Player1.Health + heal;
                    // check so player dosn't extend there health
                    if (Player1.Health > 10) {
                        Player1.Health = 10;
                    }
                    break;
                default:
                    cout << "But to no use \n";
                    break;
             }
          // running away
        } else if (Answer == "run" || Answer == "Run") {
            int flee = (rand() % 4) + 1;
            cout << Player1.getName() << " atempts to flee the battle \n";
            // switch for running
            switch (flee) {
                case 4:
                    Goblin1.Health = 0;
                    return false;
                default:
                    cout << "but the enemy was able to catch up with you! \n";
                    break;
            }
        }
        else {
            cout << Player1.getName() << " Just stares into the distance \n";
        }

        // enemy attacking code
        if (EnemyOnHit >= Player1.Armor && Goblin1.Health > 0) {
            cout << "The enemy attacks! \n";
            cout << Player1.getName() << " takes " << Goblin1.Damage << " damage!" << endl;
            Player1.Health = Player1.Health - Goblin1.Damage;
        }
        else if (EnemyOnHit < Player1.Armor) {
            cout << "The enemy attacks! \n";
            cout << "But it misses \n";
        }
        else {
            cout << " your opponent has fallen! \n";
            break;
        }

        //checks to see if the enemy health is 0 and if the player is still alive
       // if player is still alive at end of encounter than they will get gold and a victory message
        if (Goblin1.Health <= 0 && Player1.Health > 0) {
            cout << "Victory you gain " << Goblin1.Gold << " Gold coins!" << endl;
            Player1.Gold = Player1.Gold + Goblin1.Gold;
            return true;
        }
        // if the player has died
        else if (Player1.Health <= 0) {
            GameRunning = false;
            return false;
        }
        
    }
}

// world discription function
string WorldEnviorment(){
    //varible
    string world;
    //enigine for randomization
    srand(time(0));
    // distributor for randomization
    int Gen = (rand() % 10) + 1;
    int gold = (rand() % 25) + 1;
    // switch and case for randomised world discriptions
    switch (Gen) {
        case 1:
            world = Player1.getName() + " wanders the wastes for hours maybe even days until \n";
            return world;
        case 2:
            world = Player1.getName() + " desends into a deep cavern \n";
            return world;
        case 3:
            world = "heavy clouds begin to form in the distance " + Player1.getName() + " begins to seek shelter \n";
            return world;
        case 4:
            cout << Player1.getName() << " discovers, in an abandoned daycare some loose change! \n";
            cout << Player1.getName() << " finds " << gold << " gold coins!" << endl;
            world = "lUCKY YOU! \n";
            Player1.Gold = Player1.Gold + gold;
            return world;
        case 5:
            world = Player1.getName() + " finds a stronger weapon after wandering for so long \n";
            Player1.Damage = Player1.Damage + 1;
            Goblin1.Damage = Goblin1.Damage + 1;
            return world;
        case 6:
            world = "after passing through a localized biological dead zone " + Player1.getName() + " begins to feel not so great \n";
            Player1.Health = Player1.Health - 1;
            return world;
        case 7:
            world = Player1.getName() + " looted better armor off of a fallen ruin haunter, increasing their armor score! \n";
            Player1.Armor = Player1.Armor + 1;
            Goblin1.Armor = Goblin1.Armor + 1;
            return world;
        case 8:
            cout << Player1.getName() << " was robbed in the middle of the night by a gang of ruin haunters \n";
            if (Player1.Gold <= 0) {
                world = "but they didn't find any gold so they beat " + Player1.getName() + " instead for fun \n";
                Player1.Health = Player1.Health - 2;
                return world;
            }
            else {
                cout << Player1.getName() << " lost " << Player1.Gold * .25 << " gold by morning \n";
                world = "And was left to rot by morning \n";
                Player1.Gold = Player1.Gold * .25;
                return world;
            }
        case 9:
            world = Player1.getName() + "'s armor was damaged due to the high winds of a passing storm \n";
            Player1.Armor = Player1.Armor - 1;
            return world;
        case 10:
            world = Player1.getName() + " looks off into the distance......";
            return world;
        default:
            world = Player1.getName() + "has wandered to the very end of time itself as " + Player1.getName() + " spots somthing \n";
            return world;
    }
}

// function for towns to by weapons armor and to heal
void settlement() {
    // varibles for town
    string tAnswer;
    string gAnswer;
    cout << "Enter the town? yes or no \n";
    cin >> Answer;
    
    // loop for resting
    while(Answer == "yes" || Answer == "Yes") {
        cout << "exit town by typing Leave or leave \n";
        cout << "Rest: 10 gold or Gear: 7 gold \n";
        cin >> tAnswer;
        // so players can reset their health back to full
        if (tAnswer == "Rest" || tAnswer == "rest") {
            // setting the price to 10 gold
            cout << "test \n";
            Town1.price = 10;
            Player1.Health = Town1.heal();
        }
        // so the player can leave
        else if (tAnswer == "Leave" || tAnswer == "leave") {
            break;
        }
        // allows player to check their stats mainly to see how much gold they have
        else if (tAnswer == "stats" || tAnswer == "Stats") {
            PlayerStats();
        }
        else {
            cout << Player1.getName() << " wanders around the town looking for somthing to do \n";
        }

        // nested loop for players who want to upgrade armor
        while (tAnswer == "Gear" || tAnswer == "gear") {
            cout << Player1.getName() << " Stumbled upon a shop to upgrade their equipment! \n";
            cout << "Welcome to brother blacksmiths armor and more \n";
            cout << "Upgrade Armor or upgrade weapon comrade both cost 7 gold \n";
            cin >> gAnswer;
            // so the player can leave
            if (gAnswer == "Leave" || gAnswer == "leave") {
                break;
            }
            // upgrading armor class
            if (gAnswer == "armor" || gAnswer == "Armor") {
                //setting the price
                Town1.price = 7;
                Player1.Armor = Town1.Gear(Player1.Armor);
            }
            //upgrading weapon damage
            else if (gAnswer == "weapon" || gAnswer == "Weapon") {
                //setting the price
                Town1.price = 7;
                Player1.Damage = Town1.Gear(Player1.Damage);
            }
            // allows player to check their stats mainly to see how much gold they have
            else if (gAnswer == "stats" || gAnswer == "Stats") {
                PlayerStats();
            }
            else {
                cout << Player1.getName() << " looks around in brother blacksmiths shop \n";
                cout << "Brother blacksmith is growing impatient \n";
            }
        }
    }
}

// function to check the players currect stats
void PlayerStats() {
    cout << "Name " << Player1.getName() << endl;
    cout << "Health " << Player1.Health << endl;
    cout << "Armor " << Player1.Armor << endl;
    cout << "Weapon damage " << Player1.Damage << endl;
    cout << "Gold on hand " << Player1.Gold << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
