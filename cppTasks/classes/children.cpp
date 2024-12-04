#include <iostream>
#include <string>

using namespace std;

class Children{
private:
    string firstName;
    string lastName;
    int age;

public:
    void inputData(){
        cout << "Enter name: " << endl;
        cin >> firstName;
        cout << "Enter second name: " << endl;
        cin >> lastName;
        cout << "Enter age: " << endl;
        cin >> age;
    }

    void displayData() const{
        cout << "Name: " << firstName << "Last name: " << lastName << "Age: " << age << endl;
    }
};

int main(){
    Children child1, child2;

    cout << "Enter data of first child: " << endl;
    child1.inputData();

    cout << "Enter data of second child: " << endl;
    child2.inputData();

    cout << "\nFirst child:" << endl;
    child1.displayData();

    cout << "\nSecond child:" << endl;
    child2.displayData();

    return 0;
}