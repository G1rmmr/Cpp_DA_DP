#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct circular_ll_node
{
    string data;
    circular_ll_node* next;
};

class music_player
{
public:
    using track = circular_ll_node;
    using track_ptr = track*;

private:
    track_ptr front;
    track_ptr rear;

public:
    void printall();

    circular_ll_node* next(const string& track_name);
    circular_ll_node* previous(const string& track_name);

    void insert(const string& track_name);
    void remove(const string& track_name);

    void add_track(const string& track_name)
    {
        auto new_track = new track {track_name, nullptr};

        if(front == nullptr)
        {
            front = new_track;
            front->next = front;
            rear = front;
        }
        else
        {
            new_track->next = front;
            if(rear != front) rear->next = new_track;
            
            rear = new_track;
        }
        cout << track_name << " is added in player." << endl;
    }

    void delete_track()
    {
        auto start = front;
        
        if(start)
        {
            front = front->next;
            rear->next = front;

            cout << rear->data << "is deleting..." << endl;
            delete start;
        }
        else
        {
            cout << "Player has no track to delete!!" << endl;
        }
    }

    struct music_player_iterator
    {
    private:
        track_ptr ptr;

    public:
        music_player_iterator(track_ptr p) : ptr(p){}

        string& operator*(){return ptr->data;}

        track_ptr get(){return ptr;}

        music_player_iterator& operator++()
        {
            if (ptr->next == *this)
            {
                return nullptr;
            }
            return *this;
        }

        music_player_iterator operator++(int)
        {
            music_player_iterator result = *this;
            ++(*this);
            return result;
        }

        friend bool operator==(const music_player_iterator& left,
            const music_player_iterator& right)
        {
            return left.ptr == right.ptr;
        }

        friend bool operator!=(const music_player_iterator& left,
            const music_player_iterator& right)
        {
            return left.ptr != right.ptr;
        }
    };

    music_player_iterator begin() {return music_player_iterator(front);}
    music_player_iterator end() {return nullptr;}
    music_player_iterator begin() const {return music_player_iterator(front);}
    music_player_iterator end() const {return nullptr;}

    music_player() = default;

    music_player(const music_player& other) : front(), rear(nullptr)
    {
        if(other.front)
        {
            front = new track{"0", nullptr};
            rear = front;

            auto cur = front;
            auto it = other.begin();

            while(true)
            {
                cur->data = *it;

                auto tmp = it;
                ++tmp;

                if(tmp == other.end())
                    break;
                
                cur->next = new track{"0", nullptr};
                cur = cur->next;
                it = tmp;
            }
        }
    }
    music_player(const initializer_list<string>& ilist) :
        front(), rear(nullptr) {
        for(auto it = rbegin(ilist);it != rend(ilist); it++)
            add_track(*it);
    }
};

void music_player::printall()
{
    cout << "\nNow Playing...\n";

    int track_no = 1;

    for (auto iter = front; iter <= rear; iter = iter->next)
    {
        cout << track_no++ << ' ' << iter->data << ' ';
    }
    cout << '\n';
}

circular_ll_node* music_player::next(const string& track_name)
{
    cout << "\nPlay the next track.\nNow Playing...";

    for (auto iter = front; iter <= rear; iter = iter->next)
    {
        if (iter->data == track_name)
        {
            cout << iter->next->data << '\n';
            return iter->next;
        }
    }
}

circular_ll_node* music_player::previous(const string& track_name)
{
    cout << "\nPlay the previous track.\nNow Playing...";

    for (auto iter = front; iter <= rear; iter = iter->next)
    {
        if (iter->next->data == track_name)
        {
            cout << iter->data << '\n';
            return iter;
        }
    }
}

void music_player::insert(const string& track_name)
{
    add_track(track_name);
}

void music_player::remove(const string& track_name)
{
    auto iter = front;
    bool is_exist = false;

    for (; iter <= rear; iter = iter->next)
    {
        if (iter->data == track_name)
        {
            is_exist = true;
            break;
        }
    }

    if (is_exist)
    {
        previous(track_name)->next = next(track_name);
        cout << "\nNow The track (" << track_name << ") Deleted.\n";
    }
    else
    {
        cout << "Player has no track to delete!!" << endl;
    }
}

int main()
{
    music_player mp3;

    mp3.insert("Everglow");
    mp3.insert("Haven");
    mp3.insert("No Fear No More");
    mp3.insert("Mirror");
    mp3.insert("Boy-X");

    std::cout << *mp3.begin() << '\n';

    mp3.printall();

    mp3.next("Haven");
    mp3.previous("mirror");

    mp3.remove("Boy-X");

    mp3.printall();
    return 0;
}