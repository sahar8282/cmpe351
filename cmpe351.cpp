#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
using namespace std;
void fcfs();
void sjf();
void priority();
void rr();
int main(int argc, char* argv[])
{

 if (argc < 5) {
        cout<<"wrong command"<<endl<<"command should be like this: ./program_name -f inputfile -o outputfile"<<endl;
        return 1; 
    }

             string inputFilename;
             string outputFilename;

     for (int i = 1; i < argc; ++i) {
      
        if (string(argv[i]) == "-f") {
           
            if (i + 1 < argc) {
                
                inputFilename = argv[i + 1];
            } else {
                
                cout<< "No input file after -f" <<endl;
                return 1;
            }
        }
         if (string(argv[i]) == "-o") {
            
            if (i + 1 < argc) {
               
                outputFilename = argv[i + 1];
            } else {
                
               cout<< "No output file after -o" <<endl;
                return 1; 
            }
        }
    }
            ifstream inputFile(inputFilename);

        if (!inputFile.is_open()) {
        cout<< "Unable to open input file" <<endl;
        return 1; 
                  }



    string fileContents((istreambuf_iterator<char>(inputFile)),istreambuf_iterator<char>());

    inputFile.close();
    cout<< "File contents: \n" << fileContents <<endl;

    cout <<"CPU Scheduler Simulator"<<endl;
    cout<<"choose your Scheduling Method (None)"<<endl<<"1-first come first served "<<
    endl<<"2-shortest job first"<<endl<<"3-priority scheduling"<<endl<<"4-Round-Robin"<<endl<<"5-none";
   int ch;
   cin>>ch;

   switch (ch)
   {
   case 1:

    break;

   case 2:

    break;

   case 3:

    break;

   case 4:

    break;
   
   default:
    break;
   }
    return 0;
}