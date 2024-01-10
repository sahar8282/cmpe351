#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
void menu(struct node *);
void fcfs(struct node *);
void sjfnonpre(node **);
void sjfpre(node **);
void prioritynonpre(struct node *);
void prioritypre(node **);
void rrpre(struct node **);
void result(struct node *);
struct node *insertBack(struct node *, int, int, int);
struct node *createNode(int, int, int);
struct node *match(struct process *, int );
void display(struct node *);
void swapNode(struct node *&, struct node *&);
void arrivalsort(struct node *&);
void apsort(struct node *&);
void burstsort(struct node *&);
void prioritysort(struct node *&);
void pidsort(struct node *&);
struct node *pop(struct process **);
struct node *push(struct node *, struct node *);
bool isdone(struct node *);
struct node
{
    int burst, arrival, priority, waitingtime;
    int pid;
    struct node *next;
    bool executed;
    int timepassed;
};
// global variables
string inputFilename;
string outputFilename;
string smethod;
int id = 1;
bool preemtive;
int quantum;
// main and menu functions
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
        if (getline(iss2, num1, delimiter) && getline(iss2, num2, delimiter) && getline(iss2, num3, delimiter))
        {
            process = insertBack(process, stoi(num1), stoi(num2), stoi(num3));
        }
        else
            return 1;
    }

    menu(process);
    return 0;
}
void menu(struct node *process)
{
    char preemtivechoose;
    char methodchoice;
    char menuchoose;
    cout << endl
         << "*************" << endl;
    cout << "CPU Scheduler Simulator" << endl;
    cout << "1) choosing Scheduling Method " << endl
         << "2) choosing Preemptive Mode" << endl
         << "3) Show Result" << endl
         << "4) End Program" << endl;
    cout << "*************" << endl;
    cin >> menuchoose;

    switch (menuchoose)
    {
    case '1':
        cout << "*************" << endl;
        cout << "choose your Scheduling Method (None)" << endl
             << "1-first come first served " << endl
             << "2-shortest job first" << endl
             << "3-priority scheduling" << endl
             << "4-Round-Robin" << endl
             << "5-none" << endl
             << "6-back to menu" << endl;
        cout << "*************" << endl;
        cin >> methodchoice;

        switch (methodchoice)
        {
        case '1':
            if (!preemtive)
            {
                fcfs(process);
                menu(process);
            }
            else
            {
                cout << "warning : fcfs doesn't support preemtive mode but you can see nonpreemtive in result" << endl
                     << endl;
                fcfs(process);
                menu(process);
            }

            break;

        case '2':
            if (!preemtive)
            {
                sjfnonpre(&process);
                menu(process);
            }
            else
            {
                sjfpre(&process);
                menu(process);
            }

            break;
        case '3':

            if (!preemtive)
            {
                prioritynonpre(process);
                menu(process);
            }
            else
            {
                prioritypre(&process);
                menu(process);
            }

            break;
        case '4':

            /*cout << "please enter time quantum for Round Robin : ";
            cin >> quantum;

            if (!preemtive)
            {
                cout << "warning : round robin doesn't support non preemtive mode but you can see preemtive in result" << endl
                     << endl;
                rrpre(&process);
                menu(process);
            }
            else
            {
                rrpre(&process);
                menu(process);
            }

            break;*/
        case '5':
            cout << "you choose non of the methodes" << endl
                 << endl;
            menu(process);

            break;
        case '6':
            menu(process);
            break;

        default:
            cout << "wrong choice" << endl
                 << endl;
            menu(process);
            break;
        }

        break;

    case '2':
        cout << "*************" << endl;
        cout << "1-preemtive mode on " << endl
             << "2-preemtive mode off" << endl;
        cout << "*************" << endl;
        cin >> preemtivechoose;

        if (preemtivechoose == '1')
            preemtive = true;
        else
            preemtive = false;

        menu(process);
        break;

    case '3':
        if (smethod == "")
        {
            cout << "you didn't choose any method please select a method : " << endl
                 << endl;
            menu(process);
        }
        else
        {
            result(process);
            menu(process);
        }
        break;

    case '4':

        fcfs(process);
        result(process);

        preemtive = false;
        prioritynonpre(process);
        result(process);

        preemtive = true;
        prioritypre(&process);
        result(process);

        preemtive = true;
        sjfpre(&process);
        result(process);

        preemtive = false;
        sjfnonpre(&process);
        result(process);

       /* quantum = 2;
        preemtive = true;
        rrpre(&process);
        result(process);*/
        exit(1);
        break;

    default:
        cout << "*************" << endl;
        cout << "wrong choice";
        menu(process);
        break;
    }
}
// functions used for linked list
struct node *createNode(int burst, int arrival, int priority)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->burst = burst;
    temp->arrival = arrival;
    temp->priority = priority;
    temp->waitingtime = 0;
    temp->next = NULL;
    temp->pid = id;
    temp->executed = false;
    temp->timepassed = 0;
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
// swapping func used in sort
void swapNode(struct node *&a, struct node *&b)
{
    int temp = a->burst;
    a->burst = b->burst;
    b->burst = temp;

    temp = a->arrival;
    a->arrival = b->arrival;
    b->arrival = temp;

    temp = a->priority;
    a->priority = b->priority;
    b->priority = temp;

    temp = a->waitingtime;
    a->waitingtime = b->waitingtime;
    b->waitingtime = temp;

    temp = a->pid;
    a->pid = b->pid;
    b->pid = temp;

    bool temp2 = a->executed;
    a->executed = b->executed;
    b->executed = temp2;

    temp = a->timepassed;
    a->timepassed = b->timepassed;
    b->timepassed = temp;
}
// sort functions
void arrivalsort(struct node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }

    int swapped;
    struct node *ptr1;
    struct node *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->arrival > ptr1->next->arrival)
            {
                swapNode(ptr1, (ptr1->next));
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void burstsort(struct node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }

    int swapped;
    struct node *ptr1;
    struct node *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->burst > ptr1->next->burst)
            {
                swapNode(ptr1, (ptr1->next));
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void prioritysort(struct node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }

    int swapped;
    struct node *ptr1;
    struct node *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->priority > ptr1->next->priority)
            {
                swapNode(ptr1, (ptr1->next));
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void pidsort(struct node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }

    int swapped;
    struct node *ptr1;
    struct node *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->pid > ptr1->next->pid)
            {
                swapNode(ptr1, (ptr1->next));
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void apsort(struct node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }
    int swapped;
    struct node *ptr1;
    struct node *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {

            if (ptr1->arrival > ptr1->next->arrival)
            {
                swapNode(ptr1, (ptr1->next));
                swapped = 1;
            }

            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->arrival == ptr1->next->arrival)
            {
                if (ptr1->priority > ptr1->next->priority)
                {
                    swapNode(ptr1, (ptr1->next));
                    swapped = 1;
                }
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// scheduling methodes
void sjfnonpre(node **process)
{
    pidsort(*process);
    burstsort(*process);

    smethod = "shortest job first _non preemtive";
    struct node *temp = *process;
    int timer = 0;
    int count = length(*process);
    struct node *min;

    for (int i = 0; i < length(*process); i++)
    {
        temp->executed = false;
        temp = temp->next;
    }

    while (count > 0)
    {
        
        min = NULL;
        while (min == NULL)
        {
            temp = *process;
            while (temp != NULL)
            {
                if (temp->arrival <= timer && !temp->executed)
                {

                    if (min == NULL || (temp->burst < min->burst && min->arrival > temp->arrival))
                    {
                        min = temp;
                    }
                }
                temp = temp->next;
            }
             if (min == NULL)
        {
            timer++;
        }
        }

        if (min == NULL)
        {
            timer++;
        }
        else
        {

            min->executed = true;
            min->waitingtime = timer - min->arrival;
            timer += min->burst;
            count--;
        }
    }
}
void sjfpre(node **process)
{
    pidsort(*process);
    burstsort(*process);

    smethod = "shortest job first _ preemtive";
    struct node *temp = *process;

    int timer = 0;
    int count = length(*process);
    struct node *min;

    for (int i = 0; i < length(*process); i++)
    {
        temp->timepassed = 0;
        temp->waitingtime = 0;
        temp = temp->next;
    }

    while (count > 0)
    {
        
        min = NULL;
        while (min == NULL)
        {
            temp = *process;
            while (temp != NULL)
            {
                if (timer >= temp->arrival)
                {
                    if (temp->timepassed < temp->burst)
                    {
                        if (min == NULL)
                        {
                            min = temp;
                        }
                        else
                        {
                            if ((min->burst - min->timepassed) == (temp->burst - temp->timepassed) && min->arrival > temp->arrival)
                            {
                                min = temp;
                            }
                            else if ((min->burst - min->timepassed) > (temp->burst - temp->timepassed))
                            {
                                min = temp;
                            }
                        }
                    }
                }
                temp = temp->next;
            }
            timer++;
        }
        min->timepassed++;
        if (min->timepassed == min->burst)
        {
            min->waitingtime = timer - min->arrival - min->burst;
            count--;
        }
    }
}
void prioritynonpre(struct node *head)
{
    smethod = "priority scheduling _ non preemtive";
    pidsort(head);
    apsort(head);
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }
    struct node *temp = head;
    for (int i = 0; i < length(head); i++)
    {
        temp->executed = false;
        temp = temp->next;
    }

    int timer = 0;
    temp = head;
    struct node *select;
    int remain = length(head);

    while (remain > 0)
    {
        temp = head;
        select = NULL;
        while (temp != NULL)
        {
            if (temp->arrival > timer)
            {
                break;
            }
            else if (temp->executed == true)
            {
                temp = temp->next;
                continue;
            }
            else if (select != NULL)
            {
                if (select->arrival > temp->arrival)
                    select = temp;
                else if (select->priority > temp->priority)
                    select = temp;
            }
            else
                select = temp;
            temp = temp->next;
        }
        if (select == NULL)
        {
            timer++;
        }
        else
        {
            remain--;
            select->waitingtime = timer - select->arrival;
            timer += select->burst;
            select->executed = true;
        }
    }
}
void prioritypre(node **process)
{
    pidsort(*process);
    prioritysort(*process);

    smethod = "priority scheduling _ preemtive";
    struct node *temp = *process;

    int timer = 0;
    int count = length(*process);
    struct node *min;

    for (int i = 0; i < length(*process); i++)
    {
        temp->timepassed = 0;
        temp = temp->next;
    }

    while (count > 0)
    {
        
        min = NULL;
        while (min == NULL)
        {
            temp = *process;
            while (temp != NULL)
            {
                if (timer >= temp->arrival)
                {
                    if (temp->timepassed < temp->burst)
                    {
                        if (min == NULL)
                        {
                            min = temp;
                        }
                        else
                        {
                            if (min->priority == temp->priority && min->arrival > temp->arrival)
                            {
                                min = temp;
                            }
                            else if (min->priority > temp->priority)
                            {
                                min = temp;
                            }
                        }
                    }
                }
                temp = temp->next;
            }
            timer++;
        }
        min->timepassed++;
        if (min->timepassed == min->burst)
        {
            min->waitingtime = timer - min->arrival - min->burst;
            count--;
        }
    }
}
void fcfs(struct node *head)
{

    smethod = "first come first served _ non preemtive";
    pidsort(head);
    arrivalsort(head);

    if (!head)
    {
        cout << "Linked list is empty.\n";
        return;
    }

    struct node *temp = head;
    for (int i = 0; i < length(head); i++)
    {
        temp->waitingtime = 0;
        temp = temp->next;
    }

    struct node *current = head;
    int timer = 0;

    while (current != NULL)
    {
        int i = 1;
        if (current->arrival > timer)
        {
            timer = current->arrival;
        }
        current->waitingtime = timer - current->arrival;
        timer += current->burst;
        current = current->next;
    }
}

// result and displaying functions
void display(struct node *h)
{

    if (h == NULL)
        cout << "empty";

    struct node *t = h;
    while (t != NULL)
    {
        cout << t->burst << "," << t->arrival << "," << t->priority << " , "
             << "id : " << t->pid << endl;
        t = t->next;
    }
    cout << endl;
}
void result(struct node *process)
{
    pidsort(process);
    struct node *temp = process;
    float totalWaitingTime = 0.0;

    ofstream outputfile(outputFilename, std::ios::app);

    if (!outputfile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return;
    }
    if (smethod == "round robbin _ preemtive")
    {

        cout << "Scheduling method : " << smethod << " _time quantum : " << quantum << endl;
        outputfile << "Scheduling method : " << smethod << " _time quantum : " << quantum << endl;
        for (int i = 0; i < length(process); i++)
        {
            cout << "p" << temp->pid << " : "
                 << "waiting time = " << temp->waitingtime << endl;

            outputfile << "p" << temp->pid << " : "
                       << "waiting time = " << temp->waitingtime << endl;

            totalWaitingTime += temp->waitingtime;
            temp = temp->next;
        }
    }
    else
    {
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
    }

    float averageWaitingTime = totalWaitingTime / length(process);
    cout << "Average Waiting Time: " << averageWaitingTime << endl
         << endl;
    outputfile << "Average Waiting Time: " << averageWaitingTime << endl
               << endl;
}