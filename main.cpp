#include<iostream>
#include<fstream>
#include<chrono>
#include<ctime>

using namespace std;

class task {
    string t;

    public:
        void get_task() {
            cout << "Enter the task: ";
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

            // if (d == 1) {
            //     getline(in, s);
            //     i += 1;
            //     ofstream o("logs.txt", ios::app);
            //     o << log() << "   task deleted: " << s << endl;
            //     o.close();
            // }

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
};

int main() {
    task T;

    T.add();

    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
    T.list("task.txt");
    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;

    cout<<endl<<"enter the number of line you wanna delete: ";
    int m;
    cin>>m;
    T.delete_task(m);

    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
    T.list("task.txt");
    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;

    cout<<endl<<"enter the no of task you want to mark done: ";
    cin>>m;
    T.done(m);

    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
    T.list("task.txt");
    cout<<endl<<"-------------------------------------------------------------------------------"<<endl;

    return 0;
}
