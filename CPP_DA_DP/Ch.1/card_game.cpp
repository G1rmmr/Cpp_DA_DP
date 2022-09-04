#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <random>
#include <string>

#include <cstdlib>
#include <ctime>

class Player
{
public:
    std::string name;
    int num_of_cards;
    std::list<int> Cards;

    Player();
    ~Player();

    void ShuffleCard();
    int GetCard();
};

Player::Player()
{
    this->num_of_cards = 13;
    for(int i = 1; i <= 13; ++i)
        this->Cards.push_back(i);
}

void Player::ShuffleCard()
{
    std::random_device RandomDevice;
    std::default_random_engine RandomEngine(RandomDevice());
    std::shuffle(this->Cards.begin(), this->Cards.end(), RandomEngine);
}

int Player::GetCard()
{
    this->num_of_cards--;
    int card_num = this->Cards.front();
    this->Cards.pop_front();
    return card_num;
}

Player::~Player()
{
    std::cout << this->name << " Win!!" << '\n';
}

void IsMatched(std::vector<Player> Players);

bool CheckWinner(std::vector<Player> Players);

int main()
{
    Player Player1 = Player(), Player2 = Player(), Player3 = Player(), Player4 = Player();
    std::vector<Player> Players = {Player1, Player2, Player3, Player4};



    return 0;
}

void IsMatched(std::vector<Player> Players)
{
    std::vector<int> Cards;

    for(auto player : Players) Cards.push_back(player.GetCard());
    for(int i = 0; i < 4; ++i)
    {
        for(int j = i + 1; j < 4; ++j)
            if(Cards[i] == Cards[j])
            {
                Players[i].Cards.erase(Players[i].Cards.begin() + i);
                Players[j].Cards.remove(Cards[j]);
            }
    }
}

bool CheckWinner(std::vector<Player> Players)
{
    for(auto player : Players)
        if(!player.num_of_cards)
        {
            player.~Player();
            return true;
        }

    return false
}