#include <iostream>
#include <stack>
#include <string>
using namespace std;

//dmethod for decoding string sequence
void decoder(string sequence) {
    string result;
    stack<int> stk;

    for (int i = 1; i <= sequence.length(); i++)
    {
        stk.push(i);
        if ( sequence[i-1]=='S' || i==sequence.length() ) //if a character is 'S' or the entire string has been processed,
        {                                                 //we loop until the stack is empty and add the stack elements to an output string
            while (!stk.empty()) 
            {
                result+=to_string(stk.top());
                stk.pop(); //then we pop the stack
            }
        }
    }
    cout<<result<<endl;
}

//driver/testing code
int main() {
    int noOfSeqs;
    cout<<"Enter number of sequences to be decoded: "<<endl;
    cin>>noOfSeqs;
    for (int i = 0; i < noOfSeqs; i++)
    {
        string seq;
        cout<<"Enter string sequence: "<<endl;
        cin>>seq;
        cout<<"Decoded integer sequence is: "<<endl;
        decoder(seq);
    }
    
    return 0;
}