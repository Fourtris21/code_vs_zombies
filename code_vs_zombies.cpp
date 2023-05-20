#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

static constexpr const int units_for_Ash = 2000;
static constexpr const int units_for_zombie = 400;

struct Human
{
    int human_id;
    int human_x;
    int human_y; 
};

struct Zombie
{
    int zombie_id;
    int zombie_x;
    int zombie_y;        
    int zombie_xnext;
    int zombie_ynext;
};

void AddPeople(std::vector<Human>& people, const int human_count)
{
    for(int count = 0; count < human_count; count++)
    {
        Human human{};
        std::cin >> human.human_id >> human.human_x >> human.human_y; std::cin.ignore();
        people.push_back(human);
    }
} 
void AddZombies(std::vector<Zombie>& zombies, const int zombie_count)
{
    for(int count = 0; count < zombie_count; count++)
    {
        Zombie zombie{};
        std::cin >> zombie.zombie_id >> zombie.zombie_x >> zombie.zombie_y >> zombie.zombie_xnext >> zombie.zombie_ynext; std::cin.ignore();
        zombies.push_back(zombie);
    }
}

int MovesNecessaryAshToKillZombie(const Zombie& zombie, const int ash_x, const int ash_y, const int units_for_Ash)
{
    double distance = sqrt(pow(zombie.zombie_xnext - ash_x, 2) + pow(zombie.zombie_ynext - ash_y, 2));
    int moves = distance / units_for_Ash;
    return moves;
}

int MinMovesNecessaryZombieToKillHuman(const std::vector<Human>& humans, const int x_zombie, const int y_zombie, const int units_for_zombie)
{ 
    int min_moves = INT_MAX;
    int moves{};
    for(auto& human :humans)
    {
        double distance = sqrt(pow(human.human_x - x_zombie, 2) + pow(human.human_y - y_zombie, 2));
        moves = distance / units_for_zombie;
        if(moves < min_moves)
        {
            min_moves = moves;
        }
    }
    return min_moves;
}
 
Zombie FindAppropriateZombieToKill(const std::vector<Zombie>& zombies, const std::vector<Human>& people, const int x, const int y)
{
    std::vector<int> moves_Ash_to_each_zombie{};
    for(auto& zombie : zombies)
    {
        int moves = MovesNecessaryAshToKillZombie(zombie, x, y, units_for_Ash); 
        moves_Ash_to_each_zombie.push_back(moves);
    }
    int min_moves_to_zombie = INT_MAX;
    int moves_to_closest_zombie_to_person = INT_MAX;
    int count_index = 0;
    int moves_to_kill_human = 0;
    
    int index_of_zombie{};
    for(int ash_moves : moves_Ash_to_each_zombie)
    {
        moves_to_kill_human = MinMovesNecessaryZombieToKillHuman(people, zombies[count_index].zombie_x, zombies[count_index].zombie_y, units_for_zombie);
        if(ash_moves < min_moves_to_zombie && moves_to_kill_human > ash_moves && moves_to_kill_human < moves_to_closest_zombie_to_person)
        {
            min_moves_to_zombie = ash_moves;
            index_of_zombie = count_index;
            moves_to_closest_zombie_to_person = moves_to_kill_human;
        }
        count_index++;
    }
    Zombie target = zombies[index_of_zombie];
    return target;
}
 
int main()
{  
    // game loop
    while (1) {
        int ash_x;
        int ash_y;
        std::cin >> ash_x >> ash_y; std::cin.ignore();
 
        std::vector<Human> people;
        int human_count;
        std::cin >> human_count; std::cin.ignore();
        AddPeople(people, human_count);
 
        std::vector<Zombie> zombies;
        int zombie_count;
        std::cin >> zombie_count; std::cin.ignore();
        AddZombies(zombies, zombie_count);
 
        Zombie target = FindAppropriateZombieToKill(zombies, people, ash_x, ash_y);
        std::string xs = std::to_string(target.zombie_xnext);
        std::string ys = std::to_string(target.zombie_ynext);
 
        std::cout << xs + " " + ys << std::endl; // Your destination coordinates
    }
}