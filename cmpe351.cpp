#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
void menu(struct node *);
void fcfs(struct node *);
void sjfnonpre(struct node *);
void sjfpre(struct node *);
void priority();
void rr();
void result();
//void arrivalsort(struct node *);
struct node *burstsort(struct node *);
struct node *insertBack(struct node *, int, int, int);
struct node *createNode(int, int, int);
void display(struct node *);
void arrivalsort(node*&);
struct node
{
    int burst, arrival, priority, waitingtime;
    struct node *next;
};
string inputFilename;
string outputFilename;



int main(int argc, char *argv[])
{
    struct node *process = NULL;

    if (argc < 5)
    {
        cout << "wrong command" << endl
             << "command should be like this: ./program_name -f inputfile -o outputfile" << endl;
        return 1;
    }

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
        cout << "burst:    " << stoi(num1) << endl;
        cout << "arrival:  " << stoi(num2) << endl;
        cout << "priority: " << stoi(num3) << endl;
        cout << endl;

        process = insertBack(process, stoi(num1), stoi(num2), stoi(num3));
    }

    // this is just a test
    // clear this part
    cout << "normal: " << endl;
    display(process);
    cout << endl
         << "sorted: " << endl;
    arrivalsort(process);
    display(process);

    menu(process);
    return 0;
}
bool preemtive;
void menu(struct node *process)
{
    char preemtivechoose;
    char methodchoice;
    char menuchoose;
    cout << endl
         << "*************************************" << endl;
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
            if (!preemtive)
                sjfnonpre(process);
            else
            {
                // sjfpre(process);
            }

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
struct node *createNode(int burst, int arrival, int priority)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->burst = burst;
    temp->arrival = arrival;
    temp->priority = priority;
    temp->waitingtime = 0;
    temp->next = NULL;
    return temp;
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
/*void arrivalsort(struct node *head)
{
    
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
    return;
}*/

void arrivalsort(node*& head) {
    if (head == nullptr || head->next == nullptr) {
        return;  // No need to sort
    }

    bool swapped;
    node* current;
    node* last = nullptr;

    do {
        swapped = false;
        current = head;

        while (current->next != last) {
            if (current->arrival > current->next->arrival) {
                // Swap the nodes
               swap(current->arrival, current->next->arrival);
               swap(current->burst, current->next->burst);
               swap(current->priority, current->next->priority);
               swap(current->waitingtime, current->next->waitingtime);
                swapped = true;
            }
            current = current->next;
        }

        last = current;

    } while (swapped);
}
struct node *burstsort(struct node *head)
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
            if (j->burst > temp->burst)
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
void sjfnonpre(struct node *head)
{
    int totalWaitingTime = 0;
    float averageWaitingTime;

    if (!head)
    {
        cout << "No processes in the list." << endl;
        return;
    }

    node *current = head;
    int currentTime = 0;

    while (current)
    {
        current->waitingtime = max(0, currentTime - current->arrival);
        currentTime += current->burst;
        current = current->next;
        cout << "Process with Burst Time " << current->burst << " starts at time " << currentTime
             << " (Waiting Time: " << current->waitingtime << ")\n";
        totalWaitingTime += current->waitingtime;
    }
    averageWaitingTime = totalWaitingTime / length(head);
    cout << "Average Waiting Time: " << averageWaitingTime << "\n";
}
void priority()
{
}
void rr()
{
}
void result()
{
    ofstream outputfile(outputFilename);
}
void fcfs(struct node *head)
{
    // need edit

    arrivalsort(head);
    if (!head)
    {
        cout << "Linked list is empty.\n";
        return;
    }
    node *current = head;
    int timer = 0;
    float totalWaitingTime = 0.0;

    cout << "FCFS Schedule:\n";
    while (current)
    {
        int i = 1;
        if (current->arrival > timer)
        {
            timer = current->arrival;
        }
        current->waitingtime = timer - current->arrival;
        totalWaitingTime += current->waitingtime;

        cout << "Process with Burst Time " << current->burst << " starts at time " << timer
             << " (Waiting Time: " << current->waitingtime << ")\n";
        timer += current->burst;
        current = current->next;
    }
    float averageWaitingTime = totalWaitingTime / length(head);
    cout << "Average Waiting Time: " << averageWaitingTime << "\n";
    menu(head);
}
void display(struct node *h)
{

    if (h == NULL)
        cout << "empty";

    struct node *t = h;
    while (t != NULL)
        {
            cout << t->burst << "," << t->arrival << "," << t->priority << endl;
            t = t->next;

        }
                cout<< endl;
}