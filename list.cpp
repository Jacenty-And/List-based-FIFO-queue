#include "List.hpp"
#include <iostream>
Node::Node(int val)
: val(val), Xor(nullptr)
{}
List::List()
: beg(nullptr), prev(nullptr), act(nullptr), next(nullptr), end(nullptr)
{}
void List::INPUT()
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
    }
}
int List::ACTUAL()
{
    if (act)
        return act->val;
    else
        return -1;
}
int List::NEXT()
{
    if (next == nullptr)
    {
        act = beg;
        prev = nullptr;
    }
    else
    {
        Node* temp = act;
        act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
        prev = temp;
    }
    if (act == end) 
        next = nullptr;
    else
        next = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
    return ACTUAL();
}
int List::PREV()
{
    if (prev == nullptr)
    {
        act = end;
        next = nullptr;
    }
    else
    {
        Node* temp = act;
        act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
        next = temp;
    }
    if (act == beg)
        prev = nullptr;
    else
        prev = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
    return ACTUAL();
}
void List::ADD_BEG(int val)
{
    Node* New = new Node(val);
    if (beg == nullptr)
        beg = act = end = New;
    else
    {
        if (prev == nullptr)
            prev = New;
        beg->Xor = (Node*)((uintptr_t)beg->Xor ^ (uintptr_t)New);
        New->Xor = beg;
        beg = New;
    }
}
void List::ADD_END(int val)
{
    Node* New = new Node(val);
    if (end == nullptr)
        beg = act = end = New;
    else
    {
        if (next == nullptr)
            next = New;
        end->Xor = (Node*)((uintptr_t)end->Xor ^ (uintptr_t)New);
        New->Xor = end;
        end = New;
    }
}
void List::ADD_ACT(int val)
{
    if (prev == nullptr)
        ADD_BEG(val);
    else
    {
        Node* New = new Node(val);
        prev->Xor = (Node*)((uintptr_t)prev->Xor ^ (uintptr_t)act ^ (uintptr_t)New);
        New->Xor = (Node*)((uintptr_t)prev ^ (uintptr_t)act);
        act->Xor = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev ^ (uintptr_t)New);
        prev = New;
    }
}
void List::DEL_BEG()
{
    if (beg)
    {
        if (act == beg)
            PREV();
        else if (prev == beg)
            prev = nullptr;
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
void List::DEL_END()
{
    if (end)
    {
        if (act == end)
            NEXT();
        else if (next == end)
            next = nullptr;
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
void List::DEL_VAL(int val)
{
    Node* act = beg;
    while (act)
    {
        act = beg;
        Node* prev = nullptr;
        while(act)
        {
            if (act->val == val)
            {
                if (act == beg)
                    DEL_BEG();
                else if (act == this->act)
                    DEL_ACT();
                else if (act == end)
                    DEL_END();
                else
                {
                    Node* temp = act;
                    Node* next = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
                    prev->Xor = (Node*)((uintptr_t)prev->Xor ^ (uintptr_t)act ^ (uintptr_t)next);
                    next->Xor = (Node*)((uintptr_t)next->Xor ^ (uintptr_t)act ^ (uintptr_t)prev);
                    act = prev;
                    prev = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
                    delete temp;
                }
                break;
            }
            else
            {
                Node* temp = act;
                act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
                prev = temp;
            }
        }
    }
}
void List::DEL_ACT()
{
    if (act)
    {
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
void List::PRINT_FORWARD()
{
    Node* act = beg;
    Node* prev = nullptr;
    while(act)
    {
        std::cout << act->val << " ";
        Node* temp = act;
        act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)prev);
        prev = temp;
    }
    std::cout << std::endl;
}
void List::PRINT_BACKWARD()
{
    Node* act = end;
    Node* next = nullptr;
    while(act)
    {
        std::cout << act->val << " ";
        Node* temp = act;
        act = (Node*)((uintptr_t)act->Xor ^ (uintptr_t)next);
        next = temp;
    }
    std::cout << std::endl;
}