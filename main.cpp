#include "CircularList.h"
#include <limits>
using namespace std;

// Helper to handle safe node instantiation
BookNode* CreateBookNode(int id, string title)
{
    BookNode* newBook = new BookNode;
    newBook->bookID = id;
    newBook->title = title;
    newBook->next = NULL;
    return newBook;
}

// Helper for cleaning up standard stream failures
int ReadSafeInteger(string prompt)
{
    int val;
    while (true)
    {
        cout << prompt;
        if (cin >> val)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "Invalid input. Enter a proper integer setup.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    CircularLinkedList library;
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "   CIRCULAR LINKED LIST LIBRARY SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Display All Books\n";
        cout << "2. Insert Book at Front (Head)\n";
        cout << "3. Remove Book from Front\n";
        cout << "4. Insert Book at Custom Index\n";
        cout << "5. Remove Book at Custom Index\n";
        cout << "6. Swap Two Books\n";
        cout << "7. Sort Books by ID\n";
        cout << "8. Reverse Collection Flow\n";
        cout << "9. Cycle to Next Book Node\n";
        cout << "10. Exit System\n";
        cout << "========================================\n";

        choice = ReadSafeInteger("Enter choice option: ");

        switch (choice)
        {
            case 1:
                library.Print();
                break;

            case 2:
            {
                int id = ReadSafeInteger("Enter Book ID: ");
                string title;
                cout << "Enter Book Title: ";
                getline(cin, title);
                library.Insert(CreateBookNode(id, title));
                cout << "Book added to front successfully.\n";
                break;
            }

            case 3:
            {
                BookNode* removed = library.Remove();
                if (removed != NULL)
                {
                    cout << "Removed: ID " << removed->bookID << " - " << removed->title << "\n";
                    delete removed;
                }
                else cout << "Collection list is empty.\n";
                break;
            }

            case 4:
            {
                int index = ReadSafeInteger("Enter insertion index (supports wrap negative/overflow values): ");
                int id = ReadSafeInteger("Enter Book ID: ");
                string title;
                cout << "Enter Book Title: ";
                getline(cin, title);
                library.InsertAt(CreateBookNode(id, title), index);
                cout << "Book inserted at designated location.\n";
                break;
            }

            case 5:
            {
                int index = ReadSafeInteger("Enter removal index position: ");
                BookNode* removed = library.RemoveAt(index);
                if (removed != NULL)
                {
                    cout << "Removed: ID " << removed->bookID << " - " << removed->title << "\n";
                    delete removed;
                }
                else cout << "Invalid target index or configuration empty.\n";
                break;
            }

            case 6:
            {
                int idx1 = ReadSafeInteger("Enter index of first book: ");
                int idx2 = ReadSafeInteger("Enter index of second book: ");
                library.Swap(idx1, idx2);
                break;
            }

            case 7:
                library.Sort();
                break;

            case 8:
                library.Reverse();
                break;

            case 9:
                library.MoveToNextBook();
                break;

            case 10:
                cout << "Exiting Lab 6 evaluation terminal setup. Goodbye!\n";
                break;

            default:
                cout << "Choice entry invalid. Select values between 1 and 10.\n";
        }
    } while (choice != 10);

    return 0;
}