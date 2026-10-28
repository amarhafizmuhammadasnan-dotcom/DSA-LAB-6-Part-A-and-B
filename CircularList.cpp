#include "CircularList.h"
using namespace std;

BookNode* CircularLinkedList::GetNodeAt(int index)
{
    if (head == NULL || index < 0 || index >= count)
        return NULL;

    BookNode* current = head->next;
    for (int i = 0; i < index; i++)
        current = current->next;

    return current;
}

int CircularLinkedList::NormalizeIndex(int index)
{
    return ((index % count) + count) % count;
}

void CircularLinkedList::SwapData(BookNode* first, BookNode* second)
{
    if (first == NULL || second == NULL) return;

    int tempID = first->bookID;
    first->bookID = second->bookID;
    second->bookID = tempID;

    string tempTitle = first->title;
    first->title = second->title;
    second->title = tempTitle;
}

void CircularLinkedList::ResetCurrentBook()
{
    if (head == NULL)
        currentBook = NULL;
    else
        currentBook = head->next;
}

CircularLinkedList::CircularLinkedList()
{
    head = NULL;
    currentBook = NULL;
    count = 0;
}

bool CircularLinkedList::IsEmpty() { return count == 0; }
bool CircularLinkedList::IsNotEmpty() { return count > 0; }
int CircularLinkedList::GetCount() { return count; }

void CircularLinkedList::Insert(BookNode* book)
{
    if (book == NULL) return;

    if (head == NULL)
    {
        head = book;
        book->next = book;
    }
    else
    {
        book->next = head->next;
        head->next = book;
    }

    count++;
    ResetCurrentBook();
}

BookNode* CircularLinkedList::Remove()
{
    if (IsEmpty()) return NULL;

    BookNode* first = head->next;

    if (first == head)
    {
        head = NULL;
    }
    else
    {
        head->next = first->next;
    }

    first->next = NULL;
    count--;
    ResetCurrentBook();

    return first;
}

void CircularLinkedList::InsertAt(BookNode* book, int index)
{
    if (book == NULL) return;

    if (count == 0)
    {
        head = book;
        book->next = book;
        count++;
        ResetCurrentBook();
        return;
    }

    if (index < 0)
        index = NormalizeIndex(index);

    if (index > count)
        index %= count;

    if (index == 0)
    {
        Insert(book);
        return;
    }

    if (index == count)
    {
        book->next = head->next;
        head->next = book;
        head = book;
        count++;
        ResetCurrentBook();
        return;
    }

    BookNode* previous = GetNodeAt(index - 1);
    book->next = previous->next;
    previous->next = book;

    count++;
    ResetCurrentBook();
}

BookNode* CircularLinkedList::RemoveAt(int index)
{
    if (IsEmpty()) return NULL;

    index = NormalizeIndex(index);

    if (index == 0)
        return Remove();

    BookNode* previous = GetNodeAt(index - 1);
    BookNode* target = previous->next;

    previous->next = target->next;

    if (target == head)
        head = previous;

    target->next = NULL;
    count--;
    ResetCurrentBook();

    return target;
}

void CircularLinkedList::Swap(int index1, int index2)
{
    if (IsEmpty())
    {
        cout << "The collection is empty.\n";
        return;
    }

    index1 = NormalizeIndex(index1);
    index2 = NormalizeIndex(index2);

    if (index1 == index2)
    {
        cout << "Both indexes refer to the same book.\n";
        return;
    }

    BookNode* first = GetNodeAt(index1);
    BookNode* second = GetNodeAt(index2);

    SwapData(first, second);
    ResetCurrentBook();

    cout << "Books swapped successfully.\n";
}

void CircularLinkedList::Sort()
{
    if (count < 2)
    {
        cout << "At least two books are needed to sort.\n";
        return;
    }

    BookNode* first = head->next;

    for (int i = 0; i < count - 1; i++)
    {
        BookNode* second = first->next;

        for (int j = i + 1; j < count; j++)
        {
            if (first->bookID > second->bookID)
                SwapData(first, second);

            second = second->next;
        }

        first = first->next;
    }

    ResetCurrentBook();
    cout << "Books sorted by ID successfully.\n";
}

void CircularLinkedList::Reverse()
{
    if (count < 2)
    {
        cout << "At least two books are needed to reverse.\n";
        return;
    }

    BookNode* oldLast = head;
    BookNode* oldFirst = head->next;
    BookNode* previous = oldLast;
    BookNode* current = oldFirst;

    while (current != oldLast)
    {
        BookNode* nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    oldLast->next = previous;
    head = oldFirst;

    ResetCurrentBook();
    cout << "Collection reversed successfully.\n";
}

void CircularLinkedList::Print()
{
    if (IsEmpty())
    {
        cout << "\nNo books in the collection.\n";
        return;
    }

    BookNode* current = head->next;

    cout << "\nIndex\tBook ID\tTitle\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        cout << i << "\t" << current->bookID << "\t" << current->title << "\n";
        current = current->next;
    }

    cout << "Total books: " << count << "\n";
    cout << "The last book links back to the first book.\n";
}

void CircularLinkedList::MoveToNextBook()
{
    if (IsEmpty())
    {
        cout << "No books available to display.\n";
        return;
    }

    if (currentBook == NULL)
        currentBook = head->next;

    cout << "\nCurrent book: " << currentBook->title << " (ID: " << currentBook->bookID << ")\n";
    currentBook = currentBook->next;
}

CircularLinkedList::~CircularLinkedList()
{
    while (IsNotEmpty())
    {
        BookNode* removed = Remove();
        delete removed;
    }
}
