#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <iomanip>
#include <sstream>

using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    int priority;

    string toCSV() const {
        return to_string(id) + "," + name + "," + to_string(age) + "," + to_string(priority);
    }
};

class Hospital {
private:
    unordered_map<int, Patient> registry;
    queue<int> pQueues[4];
    int idCounter = 1001;
    const string database = "hospital_records.csv";

    void loadData() {
        ifstream file(database);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string sId, name, sAge, sPriority;
            getline(ss, sId, ','); getline(ss, name, ','); 
            getline(ss, sAge, ','); getline(ss, sPriority, ',');
            if(sId.empty()) continue;

            Patient p = {stoi(sId), name, stoi(sAge), stoi(sPriority)};
            registry[p.id] = p;
            pQueues[p.priority].push(p.id);
            if (p.id >= idCounter) idCounter = p.id + 1;
        }
        file.close();
    }

    void saveData() {
        ofstream file(database);
        for (auto const& [id, p] : registry) {
            file << p.toCSV() << "\n";
        }
        file.close();
    }

public:
    Hospital() { loadData(); }
    ~Hospital() { saveData(); }

    void addPatient() {
        Patient p;
        p.id = idCounter++;
        cout << "\n--- REGISTER NEW PATIENT ---" << endl;
        cout << "Enter Name: "; cin.ignore(); getline(cin, p.name);
        cout << "Enter Age: "; cin >> p.age;
        cout << "Priority (1-Critical, 2-Serious, 3-Normal): "; cin >> p.priority;
        if(p.priority < 1 || p.priority > 3) p.priority = 3;

        registry[p.id] = p;
        pQueues[p.priority].push(p.id);
        saveData();
        cout << "\n[SUCCESS] Patient ID: " << p.id << " added." << endl;
        cout << "Press Enter to continue..."; cin.ignore(); cin.get();
    }

    void treatPatient() {
        bool found = false;
        for (int i = 1; i <= 3; ++i) {
            while (!pQueues[i].empty()) {
                int id = pQueues[i].front();
                pQueues[i].pop();

                if (registry.count(id)) {
                    cout << "\n>>> TREATING: " << registry[id].name << " (ID: " << id << ")" << endl;
                    registry.erase(id);
                    saveData();
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
        if(!found) cout << "\n[INFO] No patients waiting." << endl;
        cout << "Press Enter to continue..."; cin.ignore(); cin.get();
    }

    void displayStatus() {
        cout << "\n==========================================================" << endl;
        cout << "             CURRENT WAITING ROOM STATUS                 " << endl;
        cout << "==========================================================" << endl;
        cout << left << setw(8) << "ID" << setw(20) << "NAME" << setw(8) << "AGE" << "STATUS" << endl;
        cout << "----------------------------------------------------------" << endl;

        bool empty = true;
        for (int i = 1; i <= 3; ++i) {
            queue<int> temp = pQueues[i];
            while(!temp.empty()) {
                int id = temp.front(); temp.pop();
                if(registry.count(id)) {
                    empty = false;
                    Patient p = registry[id];
                    cout << left << setw(8) << p.id << setw(20) << p.name << setw(8) << p.age 
                         << (i==1?"CRITICAL":(i==2?"SERIOUS":"NORMAL")) << endl;
                }
            }
        }
        if(empty) cout << "             (No patients in queue)              " << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "Press Enter to continue..."; cin.ignore(); cin.get();
    }
};

int main() {
    Hospital h;
    int choice;
    while (true) {
        cout << "\n--- CITY HOSPITAL MANAGEMENT SYSTEM ---" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Treat Next Patient" << endl;
        cout << "3. View All Patients" << endl;
        cout << "4. Exit" << endl;
        cout << "Choice: ";
        
        if(!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        if (choice == 1) h.addPatient();
        else if (choice == 2) h.treatPatient();
        else if (choice == 3) h.displayStatus();
        else if (choice == 4) break;
        else cout << "Invalid Choice!" << endl;
    }
    return 0;
}#MSYS=winsymlinks:nativestrict
#MSYS=error_start:mingw64/bin/qtcreator.exe|-debug|<process-id>
#CHERE_INVOKING=1
#MSYS2_PATH_TYPE=inherit
MSYSTEM=UCRT64
