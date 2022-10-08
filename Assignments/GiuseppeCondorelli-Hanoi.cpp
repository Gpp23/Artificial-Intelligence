//Hanoi code assignment 
//Student: Giuseppe Condorelli
#include<iostream>
#include<stack>
#include<math.h>
#include<Windows.h>
#include<sstream>
#include<iomanip>
#define A 0
#define B 1
#define C 2
using namespace std;

char peg(int i){
    if(i == A) return 'A';
    if(i == B) return 'B';
    return 'C';
}

void PrintStack(stack<int> s)
{
    stack<int> temp;
    while (s.empty() == false)
    {
        temp.push(s.top());
        s.pop();
    }  
 
    while (temp.empty() == false)
    {
        int t = temp.top();
        temp.pop();
        cout << t;
        if(!temp.empty()) cout << ",";
        s.push(t); 
    }
}

void print(int peg1, int peg2, int disk, stack<int> pegs[]){
    cout<<"Move disk "<<disk<<" from "<<peg(peg1)<<" to "<<peg(peg2)<<". ";
    for(int i = 0; i < 3; i++){
        cout<<peg(i)<<"=(";
        PrintStack(pegs[i]);
        cout<<"). ";
    }
    cout<<endl;
}

void moveDisk(int peg1, int peg2,stack<int> pegs[]){
    int extractedDisk;
    if(pegs[peg1].empty()){
                    extractedDisk = pegs[peg2].top();
                    pegs[peg2].pop();
                    pegs[peg1].push(extractedDisk);
                    print(peg2,peg1,extractedDisk,pegs);
                }else if(pegs[peg2].empty()){
                    extractedDisk = pegs[peg1].top();
                    pegs[peg1].pop();
                    pegs[peg2].push(extractedDisk);
                    print(peg1,peg2,extractedDisk,pegs);
                }else{
                    if(pegs[peg1].top() > pegs[peg2].top()){
                        extractedDisk = pegs[peg2].top();
                        pegs[peg2].pop();
                        pegs[peg1].push(extractedDisk);
                        print(peg2,peg1,extractedDisk,pegs);
                    }else{
                        extractedDisk = pegs[peg1].top();
                        pegs[peg1].pop();
                        pegs[peg2].push(extractedDisk);
                        print(peg1,peg2,extractedDisk,pegs);
                    }
                }
}

void iterative_hanoi(int n){
    stack<int> pegs[3];
    int aux,des,source;
    source = A;
    aux = B;
    des = C;
    if(n%2 == 0){
        aux = C;
        des = B;
    }
    int moves = pow(2,n) - 1;
    //initializer
    for(int i = n; i > 0; i--) pegs[A].push(i);
    for(int i = 1; i <= moves; i++){
        cout<<setw(4)<<setfill(' ')<<i;
        cout<<". ";
        switch(i%3){
            case 0:
                moveDisk(aux,des,pegs);
                break;
            case 1:
                moveDisk(source,des,pegs);
                break;
            case 2:
                moveDisk(source,aux,pegs);
                break;
        }
    }
}

void recursive_hanoi(int x, int y, int z, int n, stack<int> pegs[]){
    if(n > 0){
        recursive_hanoi(x,z,y,n-1,pegs);
        pegs[x].pop();
        pegs[z].push(n);
        print(x,z,n,pegs);
        recursive_hanoi(y,x,z,n-1,pegs);
    }
}

int main(){
    cout<<"TOWER OF HANOI"<<endl;
    int n;
    while(n < 1 || n > 10){
        cout<<"Enter the number of disk (N): ";
        cin>>n;
        if(n < 1 || n > 10) cout<<"N should be between 1 and 10\n";
    }
    
    iterative_hanoi(n);
    /*stack<int> pegs[3];
    for(int i = n; i > 0; i--) pegs[A].push(i);
    recursive_hanoi(A,B,C,n, pegs);*/
}