#include "CircularPatientList.h"
using namespace std;

PatientNode* CircularPatientList::GetNodeAt(int index)
{
    if (head == NULL || index < 0 || index >= count)
        return NULL;

    PatientNode* current = head->next;
    for (int i = 0; i < index; i++)
        current = current->next;

    return current;
}

int CircularPatientList::NormalizeIndex(int index)
{
    return ((index % count) + count) % count;
}

void CircularPatientList::SwapData(PatientNode* first, PatientNode* second)
{
    if (first == NULL || second == NULL) return;

    int tempID = first->patientID;
    first->patientID = second->patientID;
    second->patientID = tempID;

    string tempName = first->name;
    first->name = second->name;
    second->name = tempName;

    int tempAge = first->age;
    first->age = second->age;
    second->age = tempAge;

    string tempCondition = first->condition;
    first->condition = second->condition;
    second->condition = tempCondition;
}

void CircularPatientList::ResetCurrentPatient()
{
    if (head == NULL)
        currentPatient = NULL;
    else
        currentPatient = head->next;
}

CircularPatientList::CircularPatientList()
{
    head = NULL;
    currentPatient = NULL;
    count = 0;
}

bool CircularPatientList::IsEmpty() { return count == 0; }
bool CircularPatientList::IsNotEmpty() { return count > 0; }
int CircularPatientList::GetCount() { return count; }

void CircularPatientList::Insert(PatientNode* patient)
{
    if (patient == NULL) return;

    if (head == NULL)
    {
        head = patient;
        patient->next = patient;
    }
    else
    {
        patient->next = head->next;
        head->next = patient;
    }

    count++;
    ResetCurrentPatient();
}

PatientNode* CircularPatientList::Remove()
{
    if (IsEmpty()) return NULL;

    PatientNode* first = head->next;

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
    ResetCurrentPatient();

    return first;
}

void CircularPatientList::InsertAt(PatientNode* patient, int index)
{
    if (patient == NULL) return;

    if (count == 0)
    {
        head = patient;
        patient->next = patient;
        count++;
        ResetCurrentPatient();
        return;
    }

    if (index < 0)
        index = NormalizeIndex(index);

    if (index > count)
        index %= count;

    if (index == 0)
    {
        Insert(patient);
        return;
    }

    if (index == count)
    {
        patient->next = head->next;
        head->next = patient;
        head = patient;
        count++;
        ResetCurrentPatient();
        return;
    }

    PatientNode* previous = GetNodeAt(index - 1);
    patient->next = previous->next;
    previous->next = patient;

    count++;
    ResetCurrentPatient();
}

PatientNode* CircularPatientList::RemoveAt(int index)
{
    if (IsEmpty()) return NULL;

    index = NormalizeIndex(index);

    if (index == 0)
        return Remove();

    PatientNode* previous = GetNodeAt(index - 1);
    PatientNode* target = previous->next;

    previous->next = target->next;

    if (target == head)
        head = previous;

    target->next = NULL;
    count--;
    ResetCurrentPatient();

    return target;
}

void CircularPatientList::Swap(int index1, int index2)
{
    if (IsEmpty())
    {
        cout << "No patients available to swap.\n";
        return;
    }

    index1 = NormalizeIndex(index1);
    index2 = NormalizeIndex(index2);

    if (index1 == index2)
    {
        cout << "Both indexes refer to the same patient.\n";
        return;
    }

    PatientNode* first = GetNodeAt(index1);
    PatientNode* second = GetNodeAt(index2);

    SwapData(first, second);
    ResetCurrentPatient();

    cout << "Patients swapped successfully.\n";
}

void CircularPatientList::Sort()
{
    if (count < 2)
    {
        cout << "At least two patients are needed to sort.\n";
        return;
    }

    PatientNode* first = head->next;

    for (int i = 0; i < count - 1; i++)
    {
        PatientNode* second = first->next;

        for (int j = i + 1; j < count; j++)
        {
            if (first->patientID > second->patientID)
                SwapData(first, second);

            second = second->next;
        }

        first = first->next;
    }

    ResetCurrentPatient();
    cout << "Patients sorted by ID successfully.\n";
}

void CircularPatientList::Reverse()
{
    if (count < 2)
    {
        cout << "At least two patients are needed to reverse.\n";
        return;
    }

    PatientNode* oldLast = head;
    PatientNode* oldFirst = head->next;
    PatientNode* previous = oldLast;
    PatientNode* current = oldFirst;

    while (current != oldLast)
    {
        PatientNode* nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    oldLast->next = previous;
    head = oldFirst;

    ResetCurrentPatient();
    cout << "Patient list reversed successfully.\n";
}

void CircularPatientList::Print()
{
    if (IsEmpty())
    {
        cout << "\nNo patients in the list.\n";
        return;
    }

    PatientNode* current = head->next;

    cout << "\nIndex\tID\tName\tAge\tCondition\n";
    cout << "--------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        cout << i << "\t" << current->patientID << "\t" << current->name << "\t" << current->age << "\t" << current->condition << "\n";
        current = current->next;
    }
    cout << "--------------------------------------------------------\n";
    cout << "Total patients: " << count << "\n";
}

void CircularPatientList::MoveToNextPatient()
{
    if (IsEmpty())
    {
        cout << "No patients available to display.\n";
        return;
    }

    if (currentPatient == NULL)
        currentPatient = head->next;

    cout << "\nCurrent patient: " << currentPatient->name 
         << " (ID: " << currentPatient->patientID 
         << ", Condition: " << currentPatient->condition << ")\n";

    currentPatient = currentPatient->next;
}

CircularPatientList::~CircularPatientList()
{
    while (IsNotEmpty())
    {
        PatientNode* removed = Remove();
        delete removed;
    }
}

PatientNode* CreatePatientNode(int id, string name, int age, string condition)
{
    PatientNode* patient = new PatientNode;
    patient->patientID = id;
    patient->name = name;
    patient->age = age;
    patient->condition = condition;
    patient->next = NULL;
    return patient;
}
