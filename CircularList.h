#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <iostream>
#include <string>
#include <sstream>

struct BookNode
{
    int bookID;
    std::string title;
    BookNode* next;
};

class CircularLinkedList
{
private:
    BookNode* head;
    BookNode* currentBook;
    int count;

    BookNode* GetNodeAt(int index);
    int NormalizeIndex(int index);
    void SwapData(BookNode* first, BookNode* second);
    void ResetCurrentBook();

    // Prevent unsafe shallow copies of the circular list
    CircularLinkedList(const CircularLinkedList&);
    CircularLinkedList& operator=(const CircularLinkedList&);

public:
    CircularLinkedList();
    bool IsEmpty();
    bool IsNotEmpty();
    int GetCount();
    void Insert(BookNode* book);
    BookNode* Remove();
    void InsertAt(BookNode* book, int index);
    BookNode* RemoveAt(int index);
    void Swap(int index1, int index2);
    void Sort();
    void Reverse();
    void Print();
    void MoveToNextBook();
    ~CircularLinkedList();
};

#endif
