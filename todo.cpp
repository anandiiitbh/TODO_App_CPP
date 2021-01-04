#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

void initialize()
{
    ofstream outfile;
    outfile.open("done.txt", ios::app);
    outfile.close();
    outfile.open("todo.txt", ios::app);
    outfile.close();
}

int main(int argc, char *argv[])
{
    initialize();
    if (argc > 1)
    {
        string operation = argv[1];
        if (operation == "ls")
        {
            ifstream infile;
            infile.open("todo.txt");
            string items[100];
            int noOfItems = -1;
            while (!infile.eof())
            {
                noOfItems++;
                getline(infile, items[noOfItems]);
            }
            infile.close();
            if (noOfItems < 1)
                cout << "There are no pending todos!" << endl;
            else
            {
                for (int temp_noOfItems = noOfItems - 1; temp_noOfItems > -1; temp_noOfItems--)
                {
                    cout << "[" << temp_noOfItems + 1 << "] " << items[temp_noOfItems] << endl;
                }
            }
        }
        else if (operation == "add")
        {
            if (argc < 3)
                cout << "Error: Missing todo string. Nothing added!" << endl;
            else
            {
                ofstream outfile;
                outfile.open("todo.txt", ios::app);
                outfile << argv[2] << endl;
                outfile.close();
                cout << "Added todo: \"" << argv[2] << "\"" << endl;
            }
        }
        else if (operation == "del")
        {
            if (argc < 3)
                cout << "Error: Missing NUMBER for deleting todo." << endl;
            else
            {
                ifstream infile;
                infile.open("todo.txt");
                string items[100];
                int noOfItems = 0;
                while (!infile.eof())
                {
                    getline(infile, items[noOfItems]);
                    noOfItems++;
                }
                infile.close();
                int toDelItem = stoi(argv[2]);
                if (toDelItem > 0 && toDelItem <= noOfItems - 1)
                {
                    ofstream outfile;
                    outfile.open("todo.txt", ios::out | ios::trunc);
                    for (int i = 0; i < noOfItems - 1; i++)
                    {
                        if (i != toDelItem - 1)
                            outfile << items[i] << endl;
                    }
                    cout << "Deleted todo #" << toDelItem << endl;
                }
                else
                {
                    cout << "Error: todo #" << toDelItem << " does not exist. Nothing deleted." << endl;
                }
            }
        }
        else if (operation == "done")
        {
            if (argc < 3)
                cout << "Error: Missing NUMBER for marking todo as done." << endl;
            else
            {
                ifstream infile;
                infile.open("todo.txt");
                string items[100];
                int noOfItems = 0;
                while (!infile.eof())
                {
                    getline(infile, items[noOfItems]);
                    noOfItems++;
                }
                infile.close();
                int toDoneItem = stoi(argv[2]);
                if (toDoneItem > 0 && toDoneItem <= noOfItems - 1)
                {
                    ofstream outfile;
                    outfile.open("todo.txt", ios::out | ios::trunc);
                    for (int i = 0; i < noOfItems - 1; i++)
                    {
                        if (i != toDoneItem - 1)
                            outfile << items[i] << endl;
                        else
                        {
                            ofstream outfile;
                            outfile.open("done.txt", ios::app);
                            outfile << items[i] << endl;
                            outfile.close();
                        }
                    }
                    cout << "Marked todo #" << toDoneItem << " as done." << endl;
                }
                else
                {
                    cout << "Error: todo #" << toDoneItem << " does not exist." << endl;
                }
            }
        }
        else if (operation == "report")
        {
            ifstream infile;
            infile.open("todo.txt");
            string items[100];
            int pendings = 0;
            while (!infile.eof())
            {
                getline(infile, items[pendings]);
                pendings++;
            }
            infile.close();

            infile.open("done.txt");
            int completed = 0;
            while (!infile.eof())
            {
                getline(infile, items[completed]);
                completed++;
            }
            infile.close();
            time_t now = time(0);
            tm *ltm = localtime(&now);
            cout << 1900 + ltm->tm_year << "-" << ((1 + ltm->tm_mon) < 10 ? "0" : "") << 1 + ltm->tm_mon << "-" << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday << " Pending : " << pendings - 1 << " Completed : " << completed - 1 << endl;
        }
        else
        {
            cout << "Usage :-\n$ ./todo add \"todo item\"  # Add a new todo\n$ ./todo ls               # Show remaining todos\n$ ./todo del NUMBER       # Delete a todo\n$ ./todo done NUMBER      # Complete a todo\n$ ./todo help             # Show usage\n$ ./todo report           # Statistics\n";
        }
    }
    else
    {
        cout << "Usage :-\n$ ./todo add \"todo item\"  # Add a new todo\n$ ./todo ls               # Show remaining todos\n$ ./todo del NUMBER       # Delete a todo\n$ ./todo done NUMBER      # Complete a todo\n$ ./todo help             # Show usage\n$ ./todo report           # Statistics\n";
    }
    return 0;
}
