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
void prioritynonpre(struct node *);
void prioritypre(struct node *);
void rrpre(struct node *);
void result(struct node *);
struct node *insertBack(struct node *, int, int, int);
struct node *createNode(int, int, int);
void display(struct node *);
void arrivalsort(node *&);
void burstsort(node *&);
void prioritysort(node *&);
struct node
{
    int burst, arrival, priority, waitingtime;
    int pid;
    struct node *next;
};
string inputFilename;
string outputFilename;
string smethod;
int id=1;
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
       

        process = insertBack(process, stoi(num1), stoi(num2), stoi(num3));
    }

    // this is just a test
    // clear this part
    cout << fileContents << endl;
    cout << "normal: " << endl;
    display(process);
    cout << endl
         << "sorted: " << endl;
    arrivalsort(process);
    display(process);
    //end of test


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
                sjfpre(process);
            }

            break;
        case '3': 
        if (!preemtive)
                 prioritynonpre(process);
            else
            {
               // prioritypre(process);
            }
           

            break;
        case '4':
            //  rrpre(process);

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
        result(process);
        menu(process);
        break;

    case '4': /*fcfs(process);
        result(process);
        sjfnonpre(process);
        result(process);
        sjfpre(process);
        result(process);
        priority(process);
        result(process);
        rrpre(process);
        result(process);
*/
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
    temp->pid=id;
    id++;
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
void arrivalsort(node *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return; // No need to sort
    }

    bool swapped;
    node *current;
    node *last = nullptr;
    do
    {
        swapped = false;
        current = head;

        while (current->next != last)
        {
            if (current->arrival > current->next->arrival)
            {
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
void burstsort(node *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return; // No need to sort
    }

    bool swapped;
    node *current;
    node *last = nullptr;

    do
    {
        swapped = false;
        current = head;

        while (current->next != last)
        {
            if (current->burst > current->next->burst)
            {
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
void prioritysort(node *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return; // No need to sort
    }

    bool swapped;
    node *current;
    node *last = nullptr;

    do
    {
        swapped = false;
        current = head;

        while (current->next != last)
        {
            if (current->priority > current->next->priority)
            {
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
void sjfnonpre(struct node *process)
{
    burstsort(process);
    smethod = "shortest job first _ non preemtive";

    if (!process)
    {
        cout << "No processes in the list." << endl;
        return;
    }

    node *current = process;
    int timer = 0;

    while (current)
    {
        if (current->arrival > timer)
        {
            timer = current->arrival;
        }

        current->waitingtime = timer - current->arrival;
        timer += current->burst;
        current = current->next;
    }
    menu(process);
}
void sjfpre(struct node *process)
{
    arrivalsort(process);
    if (!process)
    {
        cout << "there is no process!" << endl;
        return;
    }

    node *current = process;
    int timer = 0;

    while (current)
    {
        if (current->arrival > timer)
        {

            timer = current->arrival;
        }

        node *shortestJob = current;
        node *temp = current->next;

        while (temp && temp->arrival <= timer)
        {
            if (temp->burst < shortestJob->burst)
            {
                shortestJob = temp;
            }
            temp = temp->next;
        }

        if (shortestJob == current)
        {
            timer += current->burst;
            current->waitingtime = timer - current->arrival - current->burst;
            current = current->next;
        }
        else
        {
            node *temp = current;
            while (temp->next != shortestJob)
            {
                temp = temp->next;
            }
            temp->next = shortestJob->next;
            shortestJob->next = current;
            current = shortestJob;
        }
    }
    menu(process);
}
void prioritynonpre(node* process) {
    arrivalsort(process);
    node* current = process;
    int timer = 0;
    while (current != nullptr) {
        
        if (current->arrival <= timer) {
            current->waitingtime = timer - current->arrival;

            // Update current time
            timer += current->burst;

            // Move to the next process
            current = current->next;
        } else {
            // If the process hasn't arrived, wait for it
            timer++;
        }
    }
    menu(process);
}
void rrpre()
{
    smethod = "round robbin _ preemtive";
}
void fcfs(struct node *head)
{

    smethod = "first come first served";

    arrivalsort(head);
    if (!head)
    {
        cout << "Linked list is empty.\n";
        return;
    }
    node *current = head;
    int timer = 0;
    float totalWaitingTime = 0.0;
    while (current)
    {
        int i = 1;
        if (current->arrival > timer)
        {
            timer = current->arrival;
        }
        current->waitingtime = timer - current->arrival;
        totalWaitingTime += current->waitingtime;
        timer += current->burst;
        current = current->next;
    }
    menu(head);
}
void display(struct node *h)
{

    if (h == NULL)
        cout << "empty";

    struct node *t = h;
    while (t != NULL)
    {
        cout << t->burst << "," << t->arrival << "," << t->priority<<" , "<<"id : "<<t->pid << endl;
        t = t->next;
    }
    cout << endl;
}
void result(struct node *process)
{
    struct node *temp = process;
    float totalWaitingTime = 0.0;

    ofstream outputfile(outputFilename);

    if (!outputfile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return;
    }

    cout << "Scheduling method : " << smethod << endl;
    outputfile << "Scheduling method : " << smethod << endl;
    for (int i = 0; i < length(process); i++)
    {
        cout << "p" << temp->pid << " : "
             << "waiting time = " << temp->waitingtime << endl;

        outputfile << "p" << temp->pid << " : "
                   << "waiting time = " << temp->waitingtime << endl;

        totalWaitingTime += temp->waitingtime;
        temp = temp->next;
    }
    float averageWaitingTime = totalWaitingTime / length(process);
    cout << "Average Waiting Time: " << averageWaitingTime << "\n";
    outputfile << "Average Waiting Time: " << averageWaitingTime << "\n";
}
