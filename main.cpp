#include<iostream>
#include<fstream>
#include<ctime>
#include<chrono>
#include<deque>

using namespace std;

class task {
    string t;

    public:
        void get_task() {
            cout << endl <<"     Enter the task: ";
            cin.ignore();
            getline(cin, t);
        }

        void add() {
            // adds a task to task.txt file
            get_task();

            ofstream out("task.txt", ios::app);
            out << t << endl;
            out.close();

            out.open("logs.txt",ios::app);
            out << log() << "   task added: " << t << endl;
            out.close();
        }

        void list(string path) {
            // lists all the tasks in the task.txt file
            int i=1;
            string res;

            ifstream in(path);
            getline(in, res);

            while (res != "") {
                cout << "     "<< i <<". "<< res << endl;
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
            cin.ignore();
            while (getline(in, s)) {
                if (i == d) {
                    i += 1;
                    
                    ofstream o("logs.txt", ios::app);
                    o << log() << "   task deleted: " << s << endl;
                    o.close();
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

        void done(int dn) {
            // marks a task done in done.txt file
            int i=1;
            string res;

            ifstream in1("task.txt");
            getline(in1, res);

            ofstream out1("done.txt", ios::app);

            while (res != "") {
                if (i == dn) {
                    out1<<res<<endl;
                    out1.close();
                    
                    out1.open("logs.txt", ios::app);
                    out1 << log() << "  task complete!: " << res << endl;
                    
                    out1.close();
                    in1.close();
                    delete_task(i);
                }
                getline(in1, res);
                i++;
            }
        }

        string log() {
            auto now = std::chrono::system_clock::now();
            time_t now_t = std::chrono::system_clock::to_time_t(now);
            return ctime(&now_t);
        }

        void show_logs() {
            ifstream file("logs.txt");
            deque<string> last10Lines;

            std::string line;
            while (std::getline(file, line)) {
                if (last10Lines.size() == 10) {
                    last10Lines.pop_front();
                }
                last10Lines.push_back(line);
            }

            file.close();
            
            cout<<endl;
            for(int i=0 ; i<10 ; i++){
                cout<< "     " << last10Lines[i] <<endl;
            }
        }
};

int main() {
    task T;

    int n;
    int p;
    
    cout<<"-----------------------------------------------------------To-do-----------------------------------------------------------"<<endl;
    
    do{
        cout<<endl<<"          1. Add a task"<<endl<<"          2. Delete a task"<<endl<<"          3. Mark a task complete!"<<endl<<"          4. List all pending tasks"<<endl<<"          5. List all completed tasks"<<endl<<"          6. Show logs"<<endl<<"          7. Exit"<<endl;
        cout<<endl<<"     Enter your choice: ";
        cin>>n;

        switch(n) {
            case 1:
                T.add();
                cout<<endl<<"     Task added!"<<endl;
                break;
                
            case 2:
                cout<<endl<<"-------------------------------------List of tasks-------------------------------------"<<endl;
                T.list("task.txt");
                cout<<endl<<"     Enter the number of task you wanna delete: ";
                cin>>p;
                
                T.delete_task(p);
                cout<<endl<<"     Task deleted"<<endl;
                break;

            case 3:
                cout<<endl<<"-------------------------------------List of tasks-------------------------------------"<<endl;
                T.list("task.txt");
                cout<<endl<<"     Enter the number of task you wanna mark done: ";
                cin>>p;
                
                T.done(p);
                cout<< endl <<"     Marked done!"<<endl;
                break;

            case 4:
                cout<<endl<<"-------------------------------------List of tasks-------------------------------------"<<endl;
                T.list("task.txt");
                cout<<endl;
                break;

            case 5:
                cout<<endl<<"-------------------------------------List of completed tasks-------------------------------------"<<endl;
                T.list("done.txt");
                cout<<endl;
                break;

            case 6:
                cout<<endl<<"--------------------------------------Logs--------------------------------------";
                T.show_logs();
                cout<<endl;
                break;        
        }
        
    }while(n != 7);
    return 0;
}
