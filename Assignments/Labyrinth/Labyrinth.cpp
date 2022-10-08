// Labyrinth Giuseppe Condorelli
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<sstream>
#include<iomanip>
#include <vector>

using namespace std;


int N; 
int M;
int trials;
fstream outShort;
fstream outLong;
vector<int> rules;
vector<int> nodes;
int ans;


int Labyrinth(int x, int y, int movei, int sol[30][30],int xMove[], int yMove[]);


void printSolution(int sol[30][30]){
	cout<<setw(4)<<setfill(' ')<<3.2<<". Path graphically:\n   Y, V ^\n"<<setw(1);
	outLong<<setw(4)<<setfill(' ')<<3.2<<". Path graphically:\n   Y, V ^\n"<<setw(1);
	outShort<<setw(4)<<setfill(' ')<<3.2<<". Path graphically:\n   Y, V ^\n"<<setw(1);
	for (int x = M-1; x >= 0; x--) {
		cout<<"      "<<setw(2)<<x+1<<" |";
		outLong<<"      "<<setw(2)<<x+1<<" |";
		outShort<<"      "<<setw(2)<<x+1<<" |";
		for (int y = 0; y < N; y++){
			cout<<" "<<setw(3)<<sol[x][y];
			outLong<<" "<<setw(3)<<sol[x][y];
			outShort<<" "<<setw(3)<<sol[x][y];
		}
		cout<<endl;
		outLong<<endl;
		outShort<<endl;
    }
	cout<<"	 ";
	outLong<<"          ";
	outShort<<"          ";
	for(int i = 0; i <= N*4; i++){
		cout<<"-";
		outLong<<"-";
		outShort<<"-";
	}
	cout<<"> X, U\n          ";
	outLong<<"> X, U\n          ";
	outShort<<"> X, U\n          ";
	for(int i = 0; i < N; i++){
		cout<<" "<<setw(3)<<i+1;
		outLong<<" "<<setw(3)<<i+1;
		outShort<<" "<<setw(3)<<i+1;
	}
	cout<<endl;
	outLong<<endl;
	outShort<<endl;

    cout<<setw(4)<<setfill(' ')<<3.3<<". Rules:";
	outLong<<setw(4)<<setfill(' ')<<3.3<<". Rules:";
	outShort<<setw(4)<<setfill(' ')<<3.3<<". Rules:";
    for (int i = 0; i < rules.size(); i++){
        cout<<" R"<<rules[i];
        outLong<<" R"<<rules[i];
        outShort<<" R"<<rules[i];
        if(i < rules.size() - 1){
            cout<<",";
            outLong<<",";
            outShort<<",";
        }
    }
    cout<<".\n";
    outLong<<".\n";
    outShort<<".\n";

    cout<<setw(4)<<setfill(' ')<<3.4<<". Nodes:";
	outLong<<setw(4)<<setfill(' ')<<3.4<<". Nodes:";
	outShort<<setw(4)<<setfill(' ')<<3.4<<". Nodes:";
    for (int i = 0; i < nodes.size(); i+=2){
        cout<<" [X="<<nodes[i]<<",Y="<<nodes[i+1]<<"]";
        outLong<<" [X="<<nodes[i]<<",Y="<<nodes[i+1]<<"]";
        outShort<<" [X="<<nodes[i]<<",Y="<<nodes[i+1]<<"]";
        if(i < rules.size() - 2){
            cout<<",";
            outLong<<",";
            outShort<<",";
        }
    }
    cout<<".\n";
    outLong<<".\n";
    outShort<<".\n";
}

int solLabyrinth(int X, int Y, int sol[30][30]){
	trials = 0;
	
	int xMove[4] = {-1, 0, 1, 0};
	int yMove[4] = {0, -1, 0, 1};

    cout<<"PART 1. Data\n";
	outLong<<"PART 1. Data\n";
	outShort<<"PART 1. Data\n";

    cout<<setw(4)<<setfill(' ')<<1.1<<". Labyrinth\n   Y, V ^\n"<<setw(1);
	outLong<<setw(4)<<setfill(' ')<<1.1<<". Path Labyrinth\n   Y, V ^\n"<<setw(1);
	outShort<<setw(4)<<setfill(' ')<<1.1<<". Path Labyrinth\n   Y, V ^\n"<<setw(1);
	for (int x = M-1; x >= 0; x--) {
		cout<<"      "<<setw(2)<<x+1<<" |";
		outLong<<"      "<<setw(2)<<x+1<<" |";
		outShort<<"      "<<setw(2)<<x+1<<" |";
		for (int y = 0; y < N; y++){
			cout<<" "<<setw(3)<<sol[x][y];
			outLong<<" "<<setw(3)<<sol[x][y];
			outShort<<" "<<setw(3)<<sol[x][y];
		}
		cout<<endl;
		outLong<<endl;
		outShort<<endl;
    }
    cout<<"	 ";
	outLong<<"          ";
	outShort<<"          ";
	for(int i = 0; i <= N*4; i++){
		cout<<"-";
		outLong<<"-";
		outShort<<"-";
	}
	cout<<"> X, U\n          ";
	outLong<<"> X, U\n          ";
	outShort<<"> X, U\n          ";
	for(int i = 0; i < N; i++){
		cout<<" "<<setw(3)<<i+1;
		outLong<<" "<<setw(3)<<i+1;
		outShort<<" "<<setw(3)<<i+1;
	}
	cout<<endl;
	outLong<<endl;
	outShort<<endl;

    cout<<setw(4)<<setfill(' ')<<1.2<<". Initial position: X="<<(Y+1)<<", Y="<<(X+1)<<". L="<<2<<".\n";
    outLong<<setw(4)<<setfill(' ')<<1.2<<". Initial position: X="<<(Y+1)<<", Y="<<(X+1)<<". L="<<2<<".\n";
    outShort<<setw(4)<<setfill(' ')<<1.2<<". Initial position: X="<<(Y+1)<<", Y="<<(X+1)<<". L="<<2<<".\n";

    sol[X][Y] = 2;

    outLong<<"PART 2. Trace\n";
	if (Labyrinth(X, Y, 3, sol, xMove, yMove) == 0) {
		cout<<"PART 3. Results\n";
		cout<<setw(4)<<setfill(' ')<<3.1<<". Path does not exist. Trials="<<trials;
		outLong<<"\nPART 3. Results\n";
		outLong<<setw(4)<<setfill(' ')<<3.1<<". Path does not exist. Trials="<<trials;
		outShort<<"\nPART 3. Results\n";
		outShort<<setw(4)<<setfill(' ')<<3.1<<". Path does not exist. Trials="<<trials;
		outLong.close();
		return 0;
	}
	else
		cout<<"PART 3. Results\n";
		cout<<setw(4)<<setfill(' ')<<3.1<<". Path is found.\n";
		outLong<<" Terminal.\nPART 3. Results\n";
		outLong<<setw(4)<<setfill(' ')<<3.1<<". Path is found.\n";
		outShort<<"\nPART 3. Results\n";
		outShort<<setw(4)<<setfill(' ')<<3.1<<". Path is found.\n";
		printSolution(sol);

	return 1;
}


int Labyrinth(int x, int y, int movei, int sol[30][30],int xMove[4], int yMove[4]){   
	int k, next_x, next_y;
	if (x == 0 || y ==  0 || x == M-1 || y == N-1)
		return 1;

	for (k = 0; k < 4; k++) {
		trials++;
		if(trials > 1)outLong<<endl;
		outLong<<setw(5)<<setfill(' ')<<trials<<") ";
		for(int i = 1; i < movei-2; i++){
			outLong<<"-";
		}
		next_x = x + yMove[k];
		next_y = y + xMove[k];
		if (sol[next_x][next_y] == 0) {
            outLong<<"R"<<k+1<<". U="<<next_x+1<<", V="<<next_y+1<<". ";
            rules.push_back(k+1);
			sol[next_x][next_y] = movei;
			outLong<<"Free. L:=L+1="<<movei<<" LAB["<<next_y+1<<","<<next_x+1<<"]:="<<movei<<".";
            nodes.push_back(next_y+1);
            nodes.push_back(next_x+1);
			if (Labyrinth(next_x, next_y, movei + 1, sol,xMove, yMove) == 1){
				return 1;
				}else{	
                outLong<<endl;
                outLong<<"       ";
                for(int i = 1; i < movei-2; i++){
			        outLong<<"-";
		            }
                rules.pop_back();
                nodes.pop_back();
                nodes.pop_back();
				outLong<<"Backtrack. from X="<<next_y+1<<", Y="<<next_x+1<<", L="<<movei<<". LAB["<<next_y+1<<","<<next_x+1<<"]:="<<sol[next_y][next_x]<<". L:=L-1="<<movei-1<<".";
				sol[next_x][next_y] = ans;
			}
		}else{
            outLong<<"R"<<k+1<<". U="<<next_y+1<<", V="<<next_x+1<<". ";
			if(sol[next_x][next_y] == 1) outLong<<"Wall.";
			else outLong<<"Thread.";
		}
	}
	return 0;
}

int main(int argc, char* args[]){
    ifstream in(args[1]);
    int LAB[30][30];
	in>>N;
	in>>M;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++)in>>LAB[i][j];
    }

	

    int X,Y;
    in>>X;
    in>>Y;

    rules = vector<int>();
    nodes = vector<int>();
    nodes.push_back(X);
    nodes.push_back(Y);
	outShort.open("out-short.txt",fstream::app);
	outLong.open("out-long.txt",fstream::app);
	ans = -2;
	do{
		cout<<"Do you want with -1 or 0\n";
		cin>>ans;
	}while(ans != -1 && ans != 0);
	

    solLabyrinth(Y-1, X-1, LAB);
	return 0;
}
