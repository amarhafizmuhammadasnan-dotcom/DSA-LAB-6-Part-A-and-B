#ifndef CIRCULAR_PATIENT_LIST_H
#define CIRCULAR_PATIENT_LIST_H

#include <iostream>
#include <string>

struct PatientNode
{
    int patientID;
    std::string name;
    int age;
    std::string condition;
    PatientNode* next;
};

class CircularPatientList
{
private:
    PatientNode* head;
    PatientNode* currentPatient;
    int count;

    PatientNode* GetNodeAt(int index);
    int NormalizeIndex(int index);
    void SwapData(PatientNode* first, PatientNode* second);
    void ResetCurrentPatient();

    // Prevent unsafe shallow copies of the circular list
    CircularPatientList(const CircularPatientList&);
    CircularPatientList& operator=(const CircularPatientList&);

public:
    CircularPatientList();
    bool IsEmpty();
    bool IsNotEmpty();
    int GetCount();
    void Insert(PatientNode* patient);
    PatientNode* Remove();
    void InsertAt(PatientNode* patient, int index);
    PatientNode* RemoveAt(int index);
    void Swap(int index1, int index2);
    void Sort();
    void Reverse();
    void Print();
    void MoveToNextPatient();
    ~CircularPatientList();
};

PatientNode* CreatePatientNode(int id, std::string name, int age, std::string condition);

#endif
