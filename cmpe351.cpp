#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
using namespace std;
void menu();
void fcfs();
void sjf();
void priority();
void rr();
void result();
void sort(struct node **);
struct node *insertBack(struct node *, int, int, int);
struct node *createNode(int, int, int);
void printList(struct node *); 

struct node
{
    int burst, arrival, priority;
    struct node *next;
};
int main(int argc, char *argv[])
{

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

                inputFilename = argv[i + 1];
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

                outputFilename = argv[i + 1];
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

    string fileContents((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    inputFile.close();
    cout << "File contents: \n"
         << fileContents << endl;

    menu();
    return 0;
}
void menu()
{
    cout << "CPU Scheduler Simulator" << endl;
    cout << "1) choosing Scheduling Method " << endl
         << "2) choosing Preemptive Mode" << endl
         << "3) Show Result" << endl
         << "4) End Program" << endl;
    int menuchoose;
    cin >> menuchoose;

    bool preemtive;
    int preemtivechoose;
    int methodchoice;
    switch (menuchoose)
    {
    case 1:
        cout << "choose your Scheduling Method (None)" << endl
             << "1-first come first served " << endl
             << "2-shortest job first" << endl
             << "3-priority scheduling" << endl
             << "4-Round-Robin" << endl
             << "5-none"
             << "6-back to menu" << endl;
        cin >> methodchoice;
        menu();
        break;

    case 2:
        cout << "1-preemtive mode on " << endl
             << "2-preemtive mode off" << endl;
        cin >> preemtivechoose;
        if (preemtivechoose == 1)
            preemtive = true;
        else
            preemtive = false;
        break;

    case 3:
        result();

        break;

    case 4:
        exit(1);

        break;

    default:
        menu();
        break;
    }

    switch (methodchoice)
    {
    case 1:
        fcfs();

        break;

    case 2:
        sjf();

        break;

    case 3:
        priority();

        break;

    case 4:
        rr();

        break;

    default:
        menu();
        break;
    }
}
void fcfs()
{
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
    temp = (struct node *)malloc(sizeof(node));
    temp->burst = burst;
    temp->arrival = arrival;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}


void printList(node* head) 
{ 
    while (head != NULL) 
    { 
        cout << head->data; 
        if (head->next != NULL) 
            cout << " -> "; 
        head = head->next; 
    } 
    cout<<endl; 
} 
  

void sort(node** head) 
{ 
    node* last = (*head); 
    node* first = (*head)->next; 
     while (first != NULL) 
    { 
        if (first->arrival < last->arrival)
        {
            last->next = first->next;
            first->next = (*head); 
            (*head) = first;
            first = last;
        } 
        else
            last = first; 
            first = first->next;
}
} 