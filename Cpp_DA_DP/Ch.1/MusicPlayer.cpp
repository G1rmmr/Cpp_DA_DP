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
    void add_track(string track_name)
    {
        auto new_track = new track {track_name, NULL};

        if(front == NULL)
        {
            front = new_track;
            front->next = front;
            rear = front;
        }
        else
        {
            new_track->next = front;
            if(rear != front)
                rear->next = new_track;
            
            rear = new_track;
        }
        cout << track_name << "is added in player." << endl;
    }

    void delete_track()
    {
        auto last = rear;
        if(rear)
        {
            rear = rear->next;

            cout << rear->data << "is deleting..." << endl;
            delete last;
        }
        cout << "Player has no track to delete!!" << endl;
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
            ptr = ptr->next;
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

    music_player_iterator begin(){return music_player_iterator(front);}
    music_player_iterator end(){return music_player_iterator(rear);}
    music_player_iterator begin() const {return music_player_iterator(front);}
    music_player_iterator end() const {return music_player_iterator(rear);}

    music_player() = default;
    music_player(const music_player& other) : front(NULL)
    {
        if(other.front)
        {
            front = new track{"0", NULL};
            auto cur = front;
            auto it = other.begin();
            while(true)
            {
                cur->data = *it;

                auto tmp = it;
                ++tmp;

                if(tmp == other.end())
                    break;
                
                cur->next = new track{"0", NULL};
                cur = cur->next;
                it = tmp;
            }
        }
    }
    music_player(const initializer_list<string>& ilist) : front(NULL)
    {
        for(auto it = rbegin(ilist); it != rend(ilist); it++)
            add_track(*it);
    }
};

int main()
{
    music_player mp3 = {"Stay", "Eden", "Unsaid"};
    mp3.add_track("Fantasy");

    for(auto i : mp3) cout << "Now playing..." << i << endl;
    return 0;
}