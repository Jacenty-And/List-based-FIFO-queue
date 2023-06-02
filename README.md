# List-based-FIFO-queue
### Semester 2 - Algorithms and Data Structures
---
The task is to implement FIFO queue using doubly or singly linked list. It is an extension of [XOR linked list](https://github.com/Jacenty-And/XOR-linked-list) assignment and the list implemented for that assignment can be reused; but also an STL <list> list can be used.  
  
In addition to the functions of the XOR list (ADD_BEG, ADD_END, DEL_BEG, DEL_END, PRINT_FORWARD, PRINT_BACKWARD) from the assignment [XOR linked list](https://github.com/Jacenty-And/XOR-linked-list) the list implements:
- SIZE - number of elements in the list.  
  
The queue is a data structure that uses list and provides functions corresponding to the following commands:
- PUSH N - add element N to the end of the queue.
- POP - remove the first element from the queue.
- PRINT_QUEUE - print the queue from the first element to the lastly added.
- COUNT - the number of elements in queue ≤ SIZE.
- GARBAGE_SOFT - change the values of all elements of the list that do not belong to the queue to 0.
- GARBAGE_HARD - remove all elements from the list that does not belong to the queue.
The FIFO queue extends the list to the pointers to the beginning (FRONT) and the end (BACK) of the queue. After inserting an element to the queue the pointer to the end of the queue (BACK) has to be changed so it will point to the next element of the list. After removing an element from the queue (FRONT) pointer has to start pointing at the element after the previously pointer by (FRONT). Notice, that by both removing and adding the element the queue has to “follow the list”. To avoid memory loss and to be able to reuse one can use a cyclical list or after reaching the end of the queue start from the beginning. Also, one has to handle exceptions: inserting an element to an empty queue (no elements), adding elements to full list (the number of elements of the queue equal to the number of elements of the list), or trying to remove elements from an empty queue.  
  
When the list is empty (no elements in it) the pointers point to nullptr. When adding an element (PUSH N) to the queue and the list is empty, then before executing the operation one element has to be added to the list. Similarly, the list has to be extended when the list is not empty, but all the elements are occupied by the queue. Inserted element should be inserted before the element pointed by pointer to the end of the queue (BACK).  

---
  
#### Input  
Some number of commands for the list or for the queue.  
  
---
  
#### Output  
The results of the operations of commands on the queue or directly on the list characterized by some state. Initially the list and the queue are empty, later their state depends on the commands. Some commands do not generate any output, but influence the state of the list and indirectly the queue and for the consecutive commands which print some in formations.
  
---
  
#### Example
Input:
```
PUSH 1
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
PUSH 2
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
PUSH 3
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
POP
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
PUSH 4
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
POP
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
POP
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
POP
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
POP
PRINT_FORWARD
PRINT_QUEUE
SIZE
COUNT
```
| Input:        | Output: |
|---------------|---------|
| PUSH 1        |         |
| PRINT_FORWARD | 1       |
| PRINT_QUEUE   | 1       |
| SIZE          | 1       |
| COUNT         | 1       |
| PUSH 2        |         |
| PRINT_FORWARD | 2 1     |
| PRINT_QUEUE   | 1 2     |
| SIZE          | 2       |
| COUNT         | 2       |
| PUSH 3        |         |
| PRINT_FORWARD | 3 2 1   |
| PRINT_QUEUE   | 1 2 3   |
| SIZE          | 3       |
| COUNT         | 3       |
| POP           | 1       |
| PRINT_FORWARD | 3 2 1   |
| PRINT_QUEUE   | 2 3     |
| SIZE          | 3       |
| COUNT         | 2       |
| PUSH 4        |         |
| PRINT_FORWARD | 3 2 4   |
| PRINT_QUEUE   | 2 3 4   |
| SIZE          | 3       |
| COUNT         | 3       |
| POP           | 2       |
| PRINT_FORWARD | 3 2 4   |
| PRINT_QUEUE   | 3 4     |
| SIZE          | 3       |
| COUNT         | 2       |
| POP           | 3       |
| PRINT_FORWARD | 3 2 4   |
| PRINT_QUEUE   | 4       |
| SIZE          | 3       |
| COUNT         | 1       |
| POP           | 4       |
| PRINT_FORWARD | 3 2 4   |
| PRINT_QUEUE   | NULL    |
| SIZE          | 3       |
| COUNT         | 0       |
| POP           | NULL    |
| PRINT_FORWARD | 3 2 4   |
| PRINT_QUEUE   | NULL    |
| SIZE          | 3       |
| COUNT         | 0       |
