#include "Queue.hpp"
#include <iostream>
Queue::Queue()
: front(nullptr), back(nullptr), List()
{}
void Queue::INPUT()
{
    while (!std::cin.eof())
    {
        std::string s;
        std::cin >> s;
        if (s == "ACTUAL")
        {
            if (act)
                std::cout << ACTUAL() << std::endl;
            else
                std::cout << "NULL" << std::endl;
        }
        else if (s == "NEXT")
        {
            if (act)
                std::cout << NEXT() << std::endl;
            else
                std::cout << "NULL" << std::endl;
        }
        else if (s == "PREV")
        {
            if (act)
                std::cout << PREV() << std::endl;
            else
                std::cout << "NULL" << std::endl;
        }
        else if (s == "ADD_BEG")
        {
            int val;
            std::cin >> val;
            ADD_BEG(val);
        }
        else if (s == "ADD_END")
        {
            int val;
            std::cin >> val;
            ADD_END(val);
        }
        else if (s == "ADD_ACT")
        {
            int val;
            std::cin >> val;
            ADD_ACT(val);
        }
        else if (s == "DEL_BEG")
            DEL_BEG();
        else if (s == "DEL_END")
            DEL_END();
        else if (s == "DEL_VAL")
        {
            int val;
            std::cin >> val;
            DEL_VAL(val);
        }
        else if (s == "DEL_ACT")
            DEL_ACT();
        else if (s == "PRINT_FORWARD")
        {
            if (act)
                PRINT_FORWARD();
            else
                std::cout << "NULL" << std::endl;
        }
        else if (s == "PRINT_BACKWARD")
        {
            if (act)
                PRINT_BACKWARD();
            else
                std::cout << "NULL" << std::endl;
        }
        else if (s == "SIZE")
            std::cout << SIZE() << std::endl;
        else if (s == "PUSH")
        {
            int val;
            std:: cin >> val;
            PUSH(val); 
        }
        else if (s == "POP")
        {
            if (front)
                std::cout << POP() << std::endl;
            else
                std::cout << "NULL" << std::endl;
        }
        else if (s == "PRINT_QUEUE")
        {
            if (front)
                PRINT_QUEUE();
            else
                std::cout << "NULL" << std::endl;
        }
        else if (s == "COUNT")
            std::cout << COUNT() << std::endl;
        else if (s == "GARBAGE_SOFT")
            GARBAGE_SOFT();
        else if (s == "GARBAGE_HARD")
            GARBAGE_HARD();
        else
            std::cout << "Invalid command!" << std::endl;
    }
}
void Queue::DEL_BEG()
{
    if (beg)
    {
        if (act == beg)
            PREV();
        else if (prev == beg)
            prev = nullptr;

        if (front == beg && front == back)
            front = back = nullptr;
        else if (front == beg)
            front = end;
        else if (back == beg)
            back = back->Xor;
        Node* temp = beg;
        if (beg->Xor)
        {
            beg = beg->Xor;
            beg->Xor = (Node*)((uintptr_t)beg->Xor ^ (uintptr_t)temp);
        }
        else
            beg = act = end = nullptr;
        delete temp;
    }
}
void Queue::DEL_END()
{
    if (end)
    {
        if (act == end)
            NEXT();
        else if (next == end)
            next = nullptr;

        if (front == end && front == back)
            front = back = nullptr;
        else if (back == end)
            back = back->Xor;
        else if (front == end)
            back = beg;
        Node* temp = end;
        if (end->Xor)
        {
            end = end->Xor;
            end->Xor = (Node*)((uintptr_t)end->Xor ^ (uintptr_t)temp);
        }
        else
            beg = act = end = nullptr;
        delete temp;
    }
}
int Queue::SIZE()
{
    int size = 0;
    Node* act = beg;
    Node* prev = nullptr;
    while (act)
    {
        Node* temp = act;
        act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
        prev = temp;
        size++;
    }
    return size;
}
void Queue::PUSH(int val)
{
    if (act) // List is not empty
    {
        if (front) // Queue is not empty
        {
            if (SIZE() > COUNT()) // List size > queue size
            {
                Node* act = end;
                Node* next = nullptr;
                while(back)
                {
                    if (act == back)
                    {
                        if (act == beg)
                            back = end;
                        else
                            back = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
                        back->val = val;
                        break;
                    }
                    else
                    {
                        Node* temp = act;
                        act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
                        next = temp;
                    }
                }
            }
            else // Queue size == list size
            {
                Node* prev = nullptr;
                Node* act = end;
                Node* next = nullptr;
                /* Find back */
                while(back)
                {
                    if (act == back)
                    {
                        prev = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
                        break;
                    }
                    else
                    {
                        Node* temp = act;
                        act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
                        next = temp;
                    }
                }
                /* Add new node before back node */
                if (act == beg)
                {
                    ADD_BEG(val);
                    back = beg;
                }
                else
                {
                    Node* New = new Node(val);
                    New->Xor = (Node*)((uintptr_t)prev ^ (uintptr_t)act);
                    act->Xor = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev ^ (uintptr_t)New);
                    prev->Xor = (Node*)((uintptr_t)prev->Xor ^ (uintptr_t)act ^ (uintptr_t)New);
                    prev = New;
                    back = New;
                }
            }
        }
        else // Empty queue
        {
            front = back = end;
            front->val = val;
        }
    }
    else // Empty List
    {
        ADD_BEG(val);
        front = back = end;
    }
}
int Queue::POP()
{
    Node* prev = nullptr;
    Node* act = beg;
    Node* next = nullptr;
    /* Find front */
    while(front)
    {
        if (act == front)
        {
            next = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
            break;
        }
        else
        {
            Node* temp = act;
            act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
            prev = temp;
        }
    }
    Node* temp = front;
    /* Move front */
    if (front == back)
    {
        std::cout << "Pusta kolejka" << std::endl;
        front = back = nullptr;
    }
    else if (front == beg)
        front = end;
    else
        front = prev;
    return temp->val;
}
void Queue::PRINT_QUEUE()
{
    Node* prev = nullptr;
    Node* act = beg;
    Node* next = nullptr;
    /* Find front */
    while(front)
    {
        if (act == front)
        {
            next = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
            break;
        }
        else
        {
            Node* temp = act;
            act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
            prev = temp;
        }
    }
    while(front)
    {
        if (act)
        {
            std::cout << act->val << " ";
            if (act == back)
                break;
            Node* temp = act;
            act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
            next = temp;
        }
        else
        {
            act = end;
            next = nullptr;
        }
    }
    std::cout << std::endl;
}
int Queue::COUNT()
{
    Node* prev = nullptr;
    Node* act = beg;
    Node* next = nullptr;
    /* Find front */
    while(front)
    {
        if (act == front)
        {
            next = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
            break;
        }
        else
        {
            Node* temp = act;
            act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
            prev = temp;
        }
    }
    /* Counting starts from front */
    int size = 0;
    while(front)
    {
        size++;
        if (act == back)
            return size;
        else if (act)
        {
            Node* temp = act;
            act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
            next = temp;
        }
        else
        {
            act = end;
            next = nullptr;
            size--;
        }
    }
    return 0;
}
void Queue::GARBAGE_SOFT()
{
    Node* prev = nullptr;
    Node* act = beg;
    if (front && SIZE() > COUNT()) // Not empty queue size < list size
    {
        /* Find front */
        while(front)
        {
            if (act == front)
            {
                Node* temp = act;
                act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
                prev = temp;
                break;
            }
            else
            {
                Node* temp = act;
                act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
                prev = temp;
            }
        }
        /* Zeroing elements */
        while(front)
        {
            if (act)
            {
                if (act == back)
                    break;
                act->val = 0;
                Node* temp = act;
                act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
                prev = temp;
            }
            else
            {
                act = beg;
                prev = nullptr;
            }
        }
    }
    else if (COUNT() == 0) // Empty queue
    {
        while(act)
        {
            act->val = 0;
            Node* temp = act;
            act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
            prev = temp;
        }
    }
}
void Queue::GARBAGE_HARD()
{
    if (front && SIZE() > COUNT()) // Not empty queue size < list size
    {
        while (SIZE() > COUNT())
        {
            Node* prev = nullptr;
            Node* act = beg;
            Node* next = nullptr;
            /* Find front */
            while(front)
            {
                if (act == front)
                {
                    Node* temp = act;
                    act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
                    prev = temp;
                    next = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
                    break;
                }
                else
                {
                    Node* temp = act;
                    act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
                    prev = temp;
                }
            }
            /* Delete elements */
            if (act == beg)
                DEL_BEG();
            else if (act == end)
                DEL_END();
            else
            {
                Node* temp = act;
                prev->Xor = (Node*)((uintptr_t)prev->Xor ^ (uintptr_t)act ^ (uintptr_t)next);
                next->Xor = (Node*)((uintptr_t)next->Xor ^ (uintptr_t)act ^ (uintptr_t)prev);
                act = prev;
                prev = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
                delete temp;
            }
        }
    }
    else if (COUNT() == 0) // Empty queue
    {
        while(SIZE())
            DEL_BEG();
    }
}