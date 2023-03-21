#include <iostream>
#include <string>

namespace Circular
{
    template <typename T>
    struct Node
    {
        T* Data;
        Node* Next;
        Node* Prev;

        ~Node()
        {
            delete Data;
        }
    };

    template <typename T>
    class List
    {
    public:
        using Node = Node<T>;
        using NodePtr = Node*;

    private:
        NodePtr mHead;
        size_t mSize;

    public:
        List() : mSize(0)
        {
            mHead = new Node {nullptr, nullptr, nullptr};
            mHead->Next = mHead;
            mHead->Prev = mHead;
        }

        size_t GetSize() const { return mSize; }

        void InsertNode(const T& Value)
        {
            NodePtr NewNode = new Node {
                new T(Value), nullptr, nullptr
            };

            mSize++;
            Node* Dummy = mHead->Prev;
        
            Dummy->Next = NewNode;
            NewNode->Prev = Dummy;

            if (mHead == Dummy)
            {
                Dummy->Prev = NewNode;
                NewNode->Next = Dummy;
                mHead = NewNode;
            }
            else
            {
                NewNode->Next = mHead;
                mHead->Prev = NewNode;
            }
            mHead = NewNode;
        }

        void RemoveNode(const T& Value)
        {
            NodePtr NowNode = mHead;
            NodePtr Dummy = mHead->Prev;

            while (NowNode != Dummy)
            {
                if(*(NowNode->Data) == Value)
                {
                    NowNode->Prev->Next = NowNode->Next;
                    NowNode->Next->Prev = NowNode->Prev;

                    if (NowNode == mHead)
                    {
                        mHead = mHead->Next;
                    }

                    delete NowNode;
                    mSize--;
                
                    return;
                }
                NowNode = NowNode->Next;
            }
        }

        struct Iterator
        {
        private:
            NodePtr mPtr;

        public:
            Iterator(const NodePtr& Ptr) : mPtr(Ptr){}

            T& operator*() {return *(mPtr->Data);}

            NodePtr GetPtr() {return mPtr;}

            Iterator& operator++()
            {
                mPtr = mPtr->Next;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator Iter = *this;
                ++(*this);

                return Iter;
            }

            Iterator& operator--()
            {
                mPtr = mPtr->Prev;
                return *this;
            }

            Iterator operator--(int)
            {
                Iterator Iter = *this;
                --(*this);

                return Iter;
            }

            friend bool operator==(const Iterator& Iter1,
                const Iterator& Iter2)
            {
                return Iter1.mPtr == Iter2.mPtr;
            }

            friend bool operator!=(const Iterator& Iter1,
                const Iterator& Iter2)
            {
                return Iter1.mPtr != Iter2.mPtr;
            }
        };

        Iterator begin()
        {
            return Iterator(mHead);
        }

        Iterator begin() const
        {
            return Iterator(mHead);
        }

        Iterator end()
        {
            return Iterator(mHead->Prev);
        }

        Iterator end() const
        {
            return Iterator(mHead->Prev);
        }

        List(const List<T>& Other) : List()
        {
            for (const auto& Node : Other)
            {
                InsertNode(Node);
            }
        }

        List(const std::initializer_list<T>& InitList) :
            mHead(nullptr),
            mSize(0)
        {
            for (const auto& Node : InitList)
            {
                InsertNode(Node);
            }
        }

        ~List()
        {
            while (GetSize())
            {
                RemoveNode(*(mHead->Data));
            }
            delete mHead;
        }
    };
};

struct MusicPlayer
{
    Circular::List<std::string> Player;
    Circular::List<std::string>::Iterator NowTrack = nullptr;

    void SetNowPlay(int TrackNo)
    {
        auto Iter = Player.begin();

        while (TrackNo--)
        {
            Iter++;
        }

        NowTrack = --Iter;

        std::cout << "\nNow Playing... <"
            << *NowTrack.GetPtr()->Data << ">\n";
    }

    void PrintAll()
    {
        unsigned int TrackNo = 1;
        std::cout << "\n[ Current Track List ]\n";

        for (const auto& Track : Player)
        {
            std::cout << TrackNo++ << ' ' << Track << '\n';
        }
        std::cout << '\n';
    }

    void InsertTrack(const std::string& TrackName)
    {
        Player.InsertNode(TrackName);
        std::cout << "The Track <" << TrackName << "> is inserted!\n";
    }

    void RemoveTrack(const std::string& TrackName)
    {
        Player.RemoveNode(TrackName);
        std::cout << "The Track <" << TrackName << "> is deleted!\n";
    }

    void PlayNext()
    {
        std::cout << "Now Play the Next Track <" 
            << *(++NowTrack) << "> \n";
    }

    void PlayPrev()
    {
        std::cout << "Now Play the Previous Track <" 
            << *(--NowTrack) << "> \n";
    }
};

int main()
{
    MusicPlayer iPod;
    iPod.NowTrack = iPod.Player.begin();
    
    iPod.InsertTrack("Everglow"); // No.1
    iPod.InsertTrack("Haven"); // No.2
    iPod.InsertTrack("No Fear No More"); // No.3
    iPod.InsertTrack("Mirror"); // No.4
    iPod.InsertTrack("Boy-X"); // No.5

    iPod.SetNowPlay(2);
    iPod.PrintAll();

    iPod.PlayNext();
    
    iPod.RemoveTrack("Mirror");
    iPod.PlayPrev();

    iPod.PrintAll();
    return 0;
}