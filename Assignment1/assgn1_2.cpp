#include <iostream>
#include <string>
using namespace std;

class RoundRobin {
    public:
        //specified quantum i.e time the cpu will allocate to each process
        int quantum = 5;

        //basic structure of node in linked list
        struct node {
            int processLenght;
            struct node* next;
        };
        //declaring the first(head) and last nodes and setting them to null
        struct node* head = NULL;
        struct node* last = NULL;
        
        //method to insert new node/process to the end of the circular linked list
        void insert() {
            struct node* newNode = new node;
            struct node* ptr = head;

            int ProcessLength;
            cout<<"Enter process length: "<<endl;
            cin>>ProcessLength;

            newNode->processLenght = ProcessLength;

            if (head==NULL) {
                newNode->next=newNode;
                head=newNode;
            } else {
                while (ptr->next!=head)
                {
                    ptr = ptr->next;
                }
                ptr->next = newNode;
                newNode->next = head;
                last = newNode;
            }
        }

        //method to process the nodes
        void process() {
            struct node* temp = head;

            //if process length of node is less than the specified quantum, we process it and then delete it
            if (temp->processLenght<=quantum) {
                if (head==last)
                {
                    delete temp;
                    head = NULL;
                    last = NULL;
                    cout<<"Process completed. List is now empty"<<endl;
                }
                else
                {
                    head = head->next;
                    last->next = head;
                    delete temp;
                    cout<<"Process completed"<<endl;
                }
            } else
            { //else we push that node to the end of the list
                nodeEnd();
                temp->processLenght-=quantum;
                cout<<"Process not completed as process length was greater than the specified quantum"<<endl;
            }
        }

        //method to push node to end of circular linked list
        void nodeEnd() {
            last->next = head;
            last = head;
            head = head->next;
        }
};

//driver/testing code
int main() {
    RoundRobin rr;
    int noOfProcesses;
    cout<<"Enter number of processes: "<<endl;
    cin>>noOfProcesses;

    for (int i = 0; i < noOfProcesses; i++)
    {
        rr.insert();
    }

    while (rr.head!=NULL)
    {
        rr.process();
    }
    return 0;    
}
