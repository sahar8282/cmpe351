#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
void menu(struct node *);
void fcfs(struct node *);
void sjf();
void priority();
void rr();
void result();
struct node *sort(struct node *);
struct node *insertBack(struct node *, int, int, int);
struct node *createNode(int, int, int);

struct node
{
    int burst, arrival, priority;
    struct node *next;
};

int main(int argc, char *argv[])
{
    struct node *process = NULL;

    if (argc < 5)
    {
        cout << "wrong command" << endl
             << "command should be like this: ./program_name -f inputfile -o outputfile" << endl;
        return 1;
    }

    string inputFilename;
    string outputFilename;

    for (int i = 1; i < argc; ++i)
    {

        if (string(argv[i]) == "-f")
        {

            if (i + 1 < argc)
            {

                inputFilename = string(argv[i + 1]);
            }
            else
            {

                cout << "No input file after -f" << endl;
                return 1;
            }
        }
        if (string(argv[i]) == "-o")
        {

            if (i + 1 < argc)
            {
                outputFilename = string(argv[i + 1]);
            }
            else
            {
                cout << "No output file after -o" << endl;
                return 1;
            }
        }
    }
    ifstream inputFile(inputFilename);

    if (!inputFile.is_open())
    {
        cout << "Unable to open input file" << endl;
        return 1;
    }

    stringstream b;
    b << inputFile.rdbuf();
    inputFile.close();
    string fileContents = b.str();
    cout << fileContents << endl;

    istringstream iss(fileContents);
    string line;
    while (getline(iss, line, '\n'))
    {
        istringstream iss2(line);
        string num1, num2, num3;
        char delimiter = ':';
        getline(iss2, num1, delimiter);
        getline(iss2, num2, delimiter);
        getline(iss2, num3, delimiter);
        cout << "Number 1: " << stoi(num1) << endl;
        cout << "Number 2: " << stoi(num2) << endl;
        cout << "Number 3: " << stoi(num3) << endl;
        cout << endl;

        process = insertBack(process, stoi(num1), stoi(num2), stoi(num3));
    }

    menu(process);
    return 0;
}
bool preemtive;
void menu(struct node *process)
{
    char preemtivechoose;
    char methodchoice;
    char menuchoose;
    cout <<endl<< "*************************************" << endl;
    cout << "CPU Scheduler Simulator" << endl;
    cout << "1) choosing Scheduling Method " << endl
         << "2) choosing Preemptive Mode" << endl
         << "3) Show Result" << endl
         << "4) End Program" << endl;
    cout << "*************************************" << endl;
    cin >> menuchoose;

    switch (menuchoose)
    {
    case '1':
        cout << "*************************************" << endl;
        cout << "choose your Scheduling Method (None)" << endl
             << "1-first come first served " << endl
             << "2-shortest job first" << endl
             << "3-priority scheduling" << endl
             << "4-Round-Robin" << endl
             << "5-none"
             << "6-back to menu" << endl;
        cout << "*************************************" << endl;
        cin >> methodchoice;

        switch (methodchoice)
        {
        case '1':
            if (!preemtive)
                fcfs(process);
            else
            {
                cout << "please turn off preemtive mod off" << endl;
                menu(process);
            }

            break;
        case '2':
            sjf();

            break;
        case '3':
            priority();

            break;
        case '4':
            rr();

            break;
        default:
            cout << "wrong";
            menu(process);
            break;
        }

        break;

    case '2':
        cout << "*************************************" << endl;
        cout << "1-preemtive mode on " << endl
             << "2-preemtive mode off" << endl;
        cout << "*************************************" << endl;
        cin >> preemtivechoose;
        if (preemtivechoose == '1')
            preemtive = true;
        else
            preemtive = false;
        menu(process);
        break;

    case '3':
        result();

        break;

    case '4':
        result();
        exit(1);

        break;

    default:
        cout << "*************************************" << endl;
        cout << "wrong choice";
        menu(process);
        break;
    }
}
void sjf()
{
}
void priority()
{
}
void rr()
{
}
void result()
{
}

struct node *insertBack(struct node *header, int burst, int arrival, int priority)
{
    struct node *temp = createNode(burst, arrival, priority);
    struct node *headertemp;
    if (header == NULL)
    {
        header = temp;
        return header;
    }
    headertemp = header;
    while (headertemp->next != NULL)
        headertemp = headertemp->next;
    headertemp->next = temp;
    return header;
}

struct node *createNode(int burst, int arrival, int priority)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->burst = burst;
    temp->arrival = arrival;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}

int length(struct node *head)
{
    struct node *temp = head;
    int len = 0;
    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }
    return len;
}

struct node *sort(struct node *head)
{
    struct node *i = head;
    int len = length(head);
    int itr = 0;
    while (itr < len)
    {
        struct node *j = head;
        struct node *prev = head;
        while (j->next)
        {
            struct node *temp = j->next;
            if (j->arrival > temp->arrival)
            {
                if (j == head)
                {
                    j->next = temp->next;
                    temp->next = j;
                    prev = temp;
                    head = prev;
                }
                else
                {
                    j->next = temp->next;
                    temp->next = j;
                    prev->next = temp;
                    prev = temp;
                }
                continue;
            }
            prev = j;
            j = j->next;
        }
        ++itr;
    }
    return head;
}

void fcfs(struct node *head)
{
    if (!head)
    {
        cout << "Linked list is empty.\n";
        return;
    }
    node *current = head;
    int currentTime = 0;
    float totalWaitingTime = 0.0;

    cout << "FCFS Schedule:\n";
    while (current)
    {
        if (current->arrival > currentTime)
        {
            currentTime = current->arrival;
        }
        int waitingTime = currentTime - current->arrival;
        totalWaitingTime += waitingTime;

        cout << "Process with Burst Time " << current->burst << " starts at time " << currentTime
             << " (Waiting Time: " << waitingTime << ")\n";
        currentTime += current->burst;
        current = current->next;
    }
    float averageWaitingTime = totalWaitingTime / length(head);
    cout << "Average Waiting Time: " << averageWaitingTime << "\n";
    menu(head);
}