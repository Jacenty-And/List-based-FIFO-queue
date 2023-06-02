#include "List.hpp"
class Queue: public List
{
    Node *front, *back;

public:
    Queue();

    void INPUT();

    void DEL_BEG();
    void DEL_END();

    int SIZE();

    void PUSH(int val);
    int POP();

    void PRINT_QUEUE();

    int COUNT();

    void GARBAGE_SOFT();
    void GARBAGE_HARD();
};