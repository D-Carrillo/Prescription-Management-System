#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct patient {
    string name;
    int prescriptionNumber = 0;
    string medication;
    int numConflicts;
    string conflictingIngredients[3] = {"", "", ""};
    string primaryDoctor;
};
void loadPatients(string fname, patient patients[], int &numOfPatients){
    string name, ingredients;
    numOfPatients = 0;
    ifstream inFS;
    inFS.open(fname);

    //if (!inFS.is_open()){return 1;}

    for (int i = 0; i < 3; i++) {
        getline(inFS, patients[i].name);
        inFS >> patients[i].prescriptionNumber;
        inFS.ignore();
        getline(inFS, patients[i].medication);
        getline(inFS, ingredients);
        istringstream inSS(ingredients);
        for(int j = 0; j < 3; j++){
            getline(inSS, patients[i].conflictingIngredients[j], ' ');
        }
        getline(inFS, patients[i].primaryDoctor);
        numOfPatients += 1;
    }

    patient hold;

    for( int t = 0; t < numOfPatients; t++){
        for(int m = t+1; m < numOfPatients; m++){
            if(patients[t].prescriptionNumber > patients[m].prescriptionNumber){
                hold        = patients[t];
                patients[t] = patients[m];
                patients[m] = hold;
                    
                
            }
        }
    }

    inFS.close();
    cout << " Successfully loaded the database with patients.\n";


}
void savePatients(string fname, patient patients[], int numOfPatients){
    ofstream outFS;
    outFS.open(fname);
    int j =0;

    for( int i = 0; i < numOfPatients; i++){
        outFS << patients[i].name << endl;
        outFS << patients[i].prescriptionNumber << endl;
        outFS << patients[i].medication << endl;
        if (patients[i].conflictingIngredients[j] != "")
            outFS << patients[i].conflictingIngredients[j];
        if (patients[i].conflictingIngredients[j+1] != "")
            outFS << " " << patients[i].conflictingIngredients[j+1];
        if (patients[i].conflictingIngredients[j+2] != "")
            outFS << " " <<patients[i].conflictingIngredients[j+2];
    
        outFS << endl;
        outFS << patients[i].primaryDoctor << endl;

    }
    outFS.close();

}

void addNewPatient(patient patients[], patient newPatient, int &numOfPatients){
    string ingredients;
    bool newp = true;

    if(numOfPatients == 20){
        cout << "Patient Database already full!\n"; 
    }

    for(int i = 0; i < numOfPatients; i++){
        if(newPatient.prescriptionNumber == patients[i].prescriptionNumber){
            newp = false;
            break;
        }
    }
    if(newp){
        patients[numOfPatients] = newPatient;
        numOfPatients += 1;
        cout << "Successfully added " << newPatient.name <<  " with ID: "<< newPatient.prescriptionNumber <<  " to the database.\n\n";
    }
    else{
        cout <<  "Prescription Number already exists in database.\n" ;
    }

}

void listAllPatients(patient patients[], int numOfPatients){

    for( int i =0; i < numOfPatients; i++){
        cout << "\nName: " << patients[i].name << endl;
        cout << "Prescription Number: " << patients[i].prescriptionNumber << endl;
        cout << "Medication: " << patients[i].medication << endl;
        cout << "Conflicting Ingredients: ";
        if (patients[i].conflictingIngredients[0] != "")
            cout << patients[i].conflictingIngredients[0] << " ";
        if (patients[i].conflictingIngredients[1] != "")
            cout << patients[i].conflictingIngredients[1] << " ";
        if (patients[i].conflictingIngredients[2] != "")
            cout <<patients[i].conflictingIngredients[2];
        cout << endl;
        cout << "Primary Doctor: " << patients[i].primaryDoctor << endl;
        cout << "---";
    }
    cout << endl << endl;

}
void updatePrescription(patient patients[], int numOfPatients, int prescriptionNumber, string newMedication, string conflicts){
    istringstream inSS(conflicts);
    int num;

    for ( int i = 0;  i < numOfPatients; i++){
        if (patients[i].prescriptionNumber == prescriptionNumber){
            num = i;
            break;
        }
    }
    if(num != 0 ){
        patients[num].medication = newMedication;
        for(int j = 0; j < 3; j++){
            getline(inSS, patients[num].conflictingIngredients[j], ' ');
        }
        cout << "Prescription updated successfully.\n\n";
    }else{
        cout << "Patient with Prescription Number <prescriptionNumber> not found.\n\n";
    }


}

void searchByName(patient patients[], int numOfPatients, string name){
    
    bool none = true;

    for (int i = 0; i < numOfPatients; i++){
        if(patients[i].name == name){
            cout << "\nName: " << patients[i].name << endl;
            cout << "Prescription Number: " << patients[i].prescriptionNumber << endl;
            cout << "Medication: " << patients[i].medication << endl;
            cout << "Conflicting Ingredients: ";
            if (patients[i].conflictingIngredients[0] != "")
                cout << patients[i].conflictingIngredients[0] << " ";
            if (patients[i].conflictingIngredients[1] != "")
                cout << patients[i].conflictingIngredients[1] <<  " ";
            if (patients[i].conflictingIngredients[2] != "")
                cout << patients[i].conflictingIngredients[2];
            cout << endl;
            cout << "Primary Doctor: " << patients[i].primaryDoctor << endl;
            cout << "---";
            none = false;
        }
    }

    if(none){
        cout <<"Patient with Name " << name << " not found.\n";
    }

}
void searchByPrescriptionNumber(patient patients[], int numOfPatients, int prescriptionNumber){
    int num;
    bool none = true;

    for (int i = 0; i < numOfPatients; i++){
        if(patients[i].prescriptionNumber == prescriptionNumber){
            cout << "\nName: " << patients[i].name << endl;
            cout << "Prescription Number: " << patients[i].prescriptionNumber << endl;
            cout << "Medication: " << patients[i].medication << endl;
            cout << "Conflicting Ingredients: ";
            if (patients[i].conflictingIngredients[0] != "")
                cout << patients[i].conflictingIngredients[0] << " ";
            if (patients[i].conflictingIngredients[1] != "")
                cout << patients[i].conflictingIngredients[1] << " ";
            if (patients[i].conflictingIngredients[2] != "")
                cout << patients[i].conflictingIngredients[2];
            cout << endl;
            cout << "Primary Doctor: " << patients[i].primaryDoctor << endl;
            cout << "---";
            none = false;
        }
    }

    if(none){
        cout << "Patient with prescription number " << prescriptionNumber << " not found.\n";
    }
}
void searchByMedication(patient patients[], int numOfPatients, string medication){
    int num;
    bool none = true;

    for (int i = 0; i < numOfPatients; i++){
        if(patients[i].medication == medication){
            cout << "\nName: " << patients[i].name << endl;
            cout << "Prescription Number: " << patients[i].prescriptionNumber << endl;
            cout << "Medication: " << patients[i].medication << endl;
            cout << "Conflicting Ingredients: ";
            if (patients[i].conflictingIngredients[0] != "")
                cout << patients[i].conflictingIngredients[0] << " ";
            if (patients[i].conflictingIngredients[1] != "")
                cout << patients[i].conflictingIngredients[1] <<  " ";
            if (patients[i].conflictingIngredients[2] != "")
                cout <<patients[i].conflictingIngredients[2];
            cout << endl;
            cout << "Primary Doctor: " << patients[i].primaryDoctor << endl;
            cout << "---";
            none = false;
        }
    }

    if(none){
        cout <<"No patients found with that use medication " << medication << "." << endl;
    }
}

int main() {
    string name, savename, newMed, newconflicts = "", searchname, holdconflict, first, last, holddr, holddcname;
    int numOfPatients = 0, prescriptionnum;
    patient patients[20];
    string holdnewconflicts;
    patient newPatient;
    int choice, secondchoice;

    cout << "Enter file name to load from:";
    cin >> name;
    loadPatients(name, patients, numOfPatients);
    cout << endl;
    // listAllPatients(patients, numOfPatients);

    cout << "Prescription Management System\n" << "1. Patient Operations\n" << "2. Search Patients\n" << "3. Save/Load\n" << "4. Exit\n" << "Enter your choice: \n";
    cin >> choice;

    while (choice != 4){
        // cout << "Prescription Management System\n" << "1. Patient Operations\n" << "2. Search Patients\n" << "3. Save/Load\n" << "4. Exit\n" << "Enter your choice: \n";
        // cin >> choice;
        switch(choice){
            case 1:
                cout << "1. See all patients\n" << "2. Add patient\n" << "3. Update Prescription\n" << "4. Organize Patients\n"; 
                cin >> secondchoice;
                switch(secondchoice){
                    case 1:
                        cout << "Enter your patient operation choice: List Of Patients";
                        listAllPatients(patients, numOfPatients);
                        break;
                    case 2:
                        cout << "Enter your patient operation choice: ";
                        cout << "Enter Patient Name: \n"; 
                        cin >> first >> last;
                        newPatient.name = first + " " + last;
                        cout << "Enter Patient Prescription Number: \n";
                        cin >> newPatient.prescriptionNumber;
                        cout << "Enter Patient Medication: \n";
                        cin >> newPatient.medication;
                        cout << "Enter Conflicting ingredients: \n";
                        for(int h = 0; h < 3; h++){
                            cin >> holddr;
                            if (holddr != "Dr.")
                                newPatient.conflictingIngredients[h] = holddr;
                            else   
                                break; 
                        }
                        cout << "Enter Primary Doctor: \n";
                        // cin >> holddr;
                        cin >> holddcname;
                        newPatient.primaryDoctor = holddr + " " + holddcname;
                        addNewPatient(patients, newPatient, numOfPatients);
                        break;
                    case 3:
                        cout << "Enter your patient operation choice: Enter Prescription Number of the patient to update: \n";
                        cin >> prescriptionnum;
                        cout << "Enter Medication: \n"; 
                        cin >> newMed;
                        cout << "Enter the conflicting ingredients: \n";
                        cin >> newconflicts;
                        // for (int q = 0; q < 2; q++){
                        //     cin >> holdnewconflicts;
                        //     newconflicts += holdnewconflicts;
                        // }
                        updatePrescription(patients, numOfPatients, prescriptionnum, newMed, newconflicts);
                        break;
                    case 4:
                        break; 
                    default:
                        break;
                break;
                }
                break;
                
                
            case 2:
                cout << "1. By Name\n" << "2. By Prescription Number\n" << "3. By Medication\n";
                cout <<"Enter your search choice: ";
                cin >> secondchoice;
                switch(secondchoice){
                    case 1: 
                        cout << "Enter Patient Name:\n";
                        cin >> first >> last;
                        searchname = first + " " + last;
                        searchByName(patients, numOfPatients, searchname);
                        break;
                    case 2:
                        cout << "Enter Prescription Number:\n";
                        cin >> prescriptionnum;
                        searchByPrescriptionNumber(patients, numOfPatients, prescriptionnum);
                        break;
                    case 3:
                        cout << "Enter Medication:\n";
                        cin >> newMed;
                        searchByMedication(patients, numOfPatients, newMed);
                        break;
                    default:
                        cout << "Invalid search choice. Please try again.\n";
                        break;
                break;
                }
                break;
            case 3:
                cout << "1. Save\n" << "2. Load\n";
                cin >> secondchoice;
                switch(secondchoice){
                    case 1:
                        cout << "Enter file name to save to:\n";
                        cin >> savename;
                        savePatients(savename, patients, numOfPatients);
                        break;
                    case 2:
                        cout << "Enter file name to load from:\n";
                        cin >> savename;
                        loadPatients(savename, patients, numOfPatients);
                        break;
                break;
                }
                break;
            case 4:
                choice = 4;
                break;
            default:
                cout << "Invalid choice. Please try again.";
                break;
        break;
        }
        
        cout << "Prescription Management System\n" << "1. Patient Operations\n" << "2. Search Patients\n" << "3. Save/Load\n" << "4. Exit\n" << "Enter your choice: \n";
        cin >> choice;

        
    }

    return 0;
}

