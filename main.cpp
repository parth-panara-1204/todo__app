#include<iostream>
#include<fstream>

using namespace std;

void add() {
    // adds a task to task.txt file
    string task;
    cout<<"enter task: ";
    getline(cin, task);

    ofstream out("task.txt", ios::app);
    out<<task<<endl;
    out.close();
}

void list(string path) {
    // lists all the tasks in the task.txt file
    int i=1;
    string res;

    ifstream in(path);
    getline(in, res);

    while (res != "") {
        cout << i <<". "<< res << endl;
        getline(in, res);
        i++;
    }

    in.close();
}

void delete_task(int d) {
    // delets a task in the task.txt file, given line number
    int i = 1;
    string s;

    ifstream in("task.txt");

    ofstream out("temp.txt");

    if (d == 1) {
        getline(in, s);
        i += 1;
    }

    while (getline(in, s)) {
        if (i == d) {
            i += 1;
            continue;
        }
        out<<s<<endl;
        i += 1;
    }

    in.close();
    out.close();

    remove("task.txt");
    rename("temp.txt", "task.txt");
}

int main() {
    add();

    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
    list("task.txt");
    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;

    cout<<endl<<"enter the number of line you wanna delete: ";
    int m;
    cin>>m;
    delete_task(m);

    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
    list("task.txt");
    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
    return 0;
}