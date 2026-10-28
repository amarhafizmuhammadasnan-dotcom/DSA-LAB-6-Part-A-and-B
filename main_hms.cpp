#include "CircularPatientList.h"
using namespace std;

int main()
{
    CircularPatientList hospital;

    cout << "========================================\n";
    cout << " HOSPITAL CIRCULAR PATIENT SYSTEM\n";
    cout << "========================================\n";

    // Add initial mock test records
    hospital.InsertAt(CreatePatientNode(204, "Zain", 45, "Fever"), 0);
    hospital.InsertAt(CreatePatientNode(201, "Bilal", 19, "Flu"), 1);
    hospital.InsertAt(CreatePatientNode(205, "Amina", 32, "Asthma"), 2);

    cout << "\n1. INITIAL PATIENT CIRCULAR LIST:";
    hospital.Print();

    // Insert at front
    hospital.Insert(CreatePatientNode(200, "Dawood", 28, "Migraine"));
    cout << "\n2. AFTER INSERTING AT FRONT:";
    hospital.Print();

    // Remove from front
    PatientNode* rem = hospital.Remove();
    if (rem != NULL)
    {
        cout << "\nRemoved from front: " << rem->name << "\n";
        delete rem;
    }
    cout << "\n3. AFTER REMOVING FRONT ELEMENT:";
    hospital.Print();

    // Swap indexes
    hospital.Swap(0, 2);
    cout << "\n4. AFTER SWAPPING INDEX 0 AND 2:";
    hospital.Print();

    // Sorting 
    hospital.Sort();
    cout << "\n5. AFTER SORTING PATIENTS BY ID:";
    hospital.Print();

    // Reversing
    hospital.Reverse();
    cout << "\n6. AFTER REVERSING CIRCULAR FLOW:";
    hospital.Print();

    // Cycling Node Traversal Demonstration
    cout << "\n7. CYCLING TRAVERSAL DEMO (3 moves):";
    hospital.MoveToNextPatient();
    hospital.MoveToNextPatient();
    hospital.MoveToNextPatient();

    // Final Status Check
    cout << "\n8. DISCHARGE STATUS CHECK:\n";
    if (hospital.IsEmpty())
    {
        cout << "The patient list is empty.\n";
    }
    else
    {
        cout << "Active system running smoothly. Total records: " << hospital.GetCount() << "\n";
    }

    return 0;
}