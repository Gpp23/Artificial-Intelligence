// Knight Tour Giuseppe Condorelli
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<sstream>
#include<iomanip>
using namespace std;

int trials;
fstream outShort;
fstream outLong;

int solveKTUtil(int x, int y, int movei, int sol[20][20],int xMove[], int yMove[], int N);

int isSafe(int x, int y, int sol[20][20], int N)
{
	return (x >= 0 && x < N && y >= 0 && y < N
			&& sol[x][y] == -1);
}

void printSolution(int sol[20][20], int N)
{
	cout<<setw(4)<<setfill(' ')<<2<<") Path graphically:\n   Y, V ^\n"<<setw(1);
	outLong<<setw(4)<<setfill(' ')<<2<<") Path graphically:\n   Y, V ^\n"<<setw(1);
	outShort<<setw(4)<<setfill(' ')<<2<<") Path graphically:\n   Y, V ^\n"<<setw(1);
	for (int x = N-1; x >= 0; x--) {
		cout<<"      "<<x+1<<" |";
		outLong<<"      "<<x+1<<" |";
		outShort<<"      "<<x+1<<" |";
		for (int y = 0; y < N; y++){
			cout<<" "<<setw(2)<<sol[y][x] + 1;
			outLong<<" "<<setw(2)<<sol[y][x] + 1;
			outShort<<" "<<setw(2)<<sol[y][x] + 1;
		}
		cout<<endl;
		outLong<<endl;
		outShort<<endl;

	}
	cout<<"	";
	outLong<<"         ";
	outShort<<"         ";
	for(int i = 0; i <= N*3; i++){
		cout<<"-";
		outLong<<"-";
		outShort<<"-";
	}
	cout<<"> X, U\n         ";
	outLong<<"> X, U\n         ";
	outShort<<"> X, U\n         ";
	for(int i = 0; i < N; i++){
		cout<<" "<<setw(2)<<i+1;
		outLong<<" "<<setw(2)<<i+1;
		outShort<<" "<<setw(2)<<i+1;
	}
	cout<<endl;
	outLong<<endl;
	outShort<<endl;
}

int solveKT(int N, int X, int Y)
{
	int sol[20][20];
	trials = 0;
	
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			sol[x][y] = -1;

	int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    cout<<"PART 1. Data\n"<<setw(4)<<setfill(' ')<<1<<") Board: "<<N<<"x"<<N<<".\n"<<setw(4)<<setfill(' ')<<2<<") Initial position: X="<<(X+1)<<", Y="<<(Y+1)<<". L="<<1<<".\n";
	outLong<<"PART 1. Data\n"<<setw(4)<<setfill(' ')<<1<<") Board: "<<N<<"x"<<N<<".\n"<<setw(4)<<setfill(' ')<<2<<") Initial position: X="<<(X+1)<<", Y="<<(Y+1)<<". L="<<1<<".\n";
	outShort<<"PART 1. Data\n"<<setw(4)<<setfill(' ')<<1<<") Board: "<<N<<"x"<<N<<".\n"<<setw(4)<<setfill(' ')<<2<<") Initial position: X="<<(X+1)<<", Y="<<(Y+1)<<". L="<<1<<".\n";
	sol[X][Y] = 0;

    outLong<<"PART 2. Trace\n";
	if (solveKTUtil(X, Y, 1, sol, xMove, yMove, N) == 0) {
		cout<<"PART 3. Results\n";
		cout<<setw(4)<<setfill(' ')<<1<<") Path does not exist. Trials="<<trials;
		outLong<<"\nPART 3. Results\n";
		outLong<<setw(4)<<setfill(' ')<<1<<") Path does not exist. Trials="<<trials;
		outShort<<"\nPART 3. Results\n";
		outShort<<setw(4)<<setfill(' ')<<1<<") Path does not exist. Trials="<<trials;
		outLong.close();
		return 0;
	}
	else
		cout<<"PART 3. Results\n";
		cout<<setw(4)<<setfill(' ')<<1<<") Path is found. Trials="<<trials<<".\n";
		outLong<<"PART 3. Results\n";
		outLong<<setw(4)<<setfill(' ')<<1<<") Path is found. Trials="<<trials<<".\n";
		outShort<<"PART 3. Results\n";
		outShort<<setw(4)<<setfill(' ')<<1<<") Path is found. Trials="<<trials<<".\n";
		printSolution(sol, N);

	return 1;
}


int solveKTUtil(int x, int y, int movei, int sol[20][20],int xMove[8], int yMove[8], int N)
{   
	int k, next_x, next_y;
	if (movei == N * N)
		return 1;

	for (k = 0; k < 8; k++) {
		trials++;
		if(trials > 1)outLong<<endl;
		outLong<<setw(5)<<setfill(' ')<<trials<<") ";
		for(int i = 1; i < movei; i++){
			outLong<<"-";
		}
		next_x = x + xMove[k];
		next_y = y + yMove[k];
		outLong<<"R"<<k+1<<". U="<<next_x+1<<", V="<<next_y+1<<". L="<<movei+1<<". ";
		if (isSafe(next_x, next_y, sol, N)) {
			sol[next_x][next_y] = movei;
			outLong<<"Free. BOARD["<<next_x+1<<","<<next_y+1<<"]:="<<movei+1<<".";
			if (solveKTUtil(next_x, next_y, movei + 1, sol,xMove, yMove, N)
				== 1){
				return 1;
				}
				
			else{	
			// backtracking
				outLong<<" Backtrack.";
				sol[next_x][next_y] = -1;
			}
		}else{
			if(!(next_x >= 0 && next_x < N && next_y >= 0 && next_y < N)) outLong<<"Out.";
			else outLong<<"Thread.";
		}
	}
	return 0;
}

int main(int argc, char* args[])
{
	outShort.open("out-short.txt",fstream::app);
	outLong.open("out-long.txt",fstream::app);
	solveKT(stoi(args[1]), stoi(args[2]) - 1, stoi(args[3]) - 1);
	return 0;
}

