// Labyrinth Giuseppe Condorelli
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<sstream>
#include<iomanip>
#include<vector>

using namespace std;

int LAB[30][30];
int LABCOPY[30][30];
int FX[500];
int FY[500];
int xMove[4]; 
int yMove[4];
long close;
long newn;
bool yes;
int N; 
int M;
int trials;
vector<int> rules;
vector<int> nodes;
fstream outShort;
fstream outLong;

void BACK(int u, int v){
    LAB[u][v] = LABCOPY[u][v];
	nodes.push_back(u+1);
	nodes.push_back(v+1);
    int k = 4;
	int r = 0;
    int uu;
    int vv;
    do{
        k--;
		r++;
        uu = u + xMove[k];
        vv = v + yMove[k];
        if( 0 <= uu && uu < M && 0 <= vv && vv < N){
            if(LABCOPY[uu][vv] == LABCOPY[u][v] - 1){
                LAB[uu][vv] = LABCOPY[uu][vv];
                u = uu;
                v = vv;
				rules.push_back(r);
				nodes.push_back(u+1);
				nodes.push_back(v+1);
                k = 4;
				r = 0;
            }
        }
    }while(LABCOPY[u][v] != 2);
}

int Labyrinth(int x, int y){  
    int u,v;
    int wave = 0;
	long tmp;
	x = FX[close];
    y = FY[close];
	outLong<<"WAVE "<<wave<<", label L="<<LABCOPY[x][y];
	outLong<<". Initial position X="<<y+1<<", Y="<<x+1<<", NEWN="<<newn+1<<endl<<endl;
    if(x > 0 && x <= M && y > 0 && y <= N){
        do{
            wave++;
            x = FX[close];
            y = FY[close];
			outLong<<"WAVE "<<wave<<", label L="<<LABCOPY[x][y]<<endl;
			tmp = newn;
			do{
				x = FX[close];
           		y = FY[close];
				outLong<<setfill(' ')<<setw(4)<<"    Close CLOSE="<<close+1<<", X="<<y+1<<", Y="<<x+1<<".\n";
				for(int k = 0; k < 4 && !yes; k++){
					u = x + xMove[k];
					v = y + yMove[k];
					outLong<<setw(8)<<setfill(' ')<<"R"<<k+1<<". X="<<v+1<<", Y="<<u+1<<". ";
					if(LABCOPY[u][v] == 0){
						LABCOPY[u][v] = LABCOPY[x][y] + 1;
						if(u == 0 || u == M - 1 || v == 0 || v == N - 1) yes = true;
						newn++;
						FX[newn] = u;
						FY[newn] = v;
						outLong<<"Free. NEWN="<<newn+1<<".\n";
					}else if(LABCOPY[u][v] == 1){
						outLong<<"Wall.\n";
					}else{
						outLong<<"CLOSED or OPEN.\n";
					}
				}
				close++;
				if(!yes)outLong<<endl;
			}while(close <= tmp && !yes);
        }while(close <= newn && !yes);
    }
    if(yes)BACK(u,v);
    return yes; 
}


void printSolution(){
	cout<<setw(4)<<setfill(' ')<<3.2<<". Path graphically:\n   Y, V ^\n"<<setw(1);
	outLong<<setw(4)<<setfill(' ')<<3.2<<". Path graphically:\n   Y, V ^\n"<<setw(1);
	outShort<<setw(4)<<setfill(' ')<<3.2<<". Path graphically:\n   Y, V ^\n"<<setw(1);
	for (int x = M-1; x >= 0; x--) {
		cout<<"      "<<setw(2)<<x+1<<" |";
		outLong<<"      "<<setw(2)<<x+1<<" |";
		outShort<<"      "<<setw(2)<<x+1<<" |";
		for (int y = 0; y < N; y++){
			cout<<" "<<setw(3)<<LABCOPY[x][y];
			outLong<<" "<<setw(3)<<LABCOPY[x][y];
			outShort<<" "<<setw(3)<<LABCOPY[x][y];
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
	for(int i = 0; i < rules.size(); i++){
		cout<<" R"<<rules[i]<<",";
		outLong<<" R"<<rules[i]<<",";
		outShort<<" R"<<rules[i]<<",";
	}
	cout<<"\n";
	outLong<<"\n";
	outShort<<"\n";
	cout<<setw(4)<<setfill(' ')<<3.4<<". Nodes:";
	outLong<<setw(4)<<setfill(' ')<<3.4<<". Nodes:";
	outShort<<setw(4)<<setfill(' ')<<3.4<<". Nodes:";
	for(int i = nodes.size() - 1; i >= 0; i--){
		cout<<" [X="<<nodes[i]<<",Y=";
		outLong<<" [X="<<nodes[i]<<",Y=";
		outShort<<" [X="<<nodes[i]<<",Y=";
		i--;
		cout<<nodes[i]<<"],";
		outLong<<nodes[i]<<"],";
		outShort<<nodes[i]<<"],";
	}
}

int solLabyrinth(int X, int Y){
	trials = 0;
	
	yMove[0] = -1;
    yMove[1] = 0;
    yMove[2] = 1;
    yMove[3] = 0;
	xMove[0] = 0;
    xMove[1] = -1;
    xMove[2] = 0;
    xMove[3] = 1; 
    FX[0] = X;
    FY[0] = Y;
    close = 0;
    newn = 0;
    yes = false;
    cout<<"PART 1. Data\n";
	outLong<<"PART 1. Data\n";
	outShort<<"PART 1. Data\n";
    LABCOPY[X][Y] = 2;
    cout<<setw(4)<<setfill(' ')<<1.1<<". Labyrinth\n   Y, V ^\n"<<setw(1);
	outLong<<setw(4)<<setfill(' ')<<1.1<<". Path Labyrinth\n   Y, V ^\n"<<setw(1);
	outShort<<setw(4)<<setfill(' ')<<1.1<<". Path Labyrinth\n   Y, V ^\n"<<setw(1);
	for (int x = M-1; x >= 0; x--) {
		cout<<"      "<<setw(2)<<x+1<<" |";
		outLong<<"      "<<setw(2)<<x+1<<" |";
		outShort<<"      "<<setw(2)<<x+1<<" |";
		for (int y = 0; y < N; y++){
			cout<<" "<<setw(3)<<LABCOPY[x][y];
			outLong<<" "<<setw(3)<<LABCOPY[x][y];
			outShort<<" "<<setw(3)<<LABCOPY[x][y];
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

    outLong<<"PART 2. Trace\n";
	if (Labyrinth(X, Y) == 0) {
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
		printSolution();

	return 1;
}



int main(int argc, char* args[]){
    ifstream in(args[1]);
	in>>N;
	in>>M;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            in>>LAB[i][j];
            LABCOPY[i][j] = LAB[i][j];
            }
    }

    int X,Y;
    in>>X;
    in>>Y;

	outShort.open("out-short.txt",fstream::app);
	outLong.open("out-long.txt",fstream::app);
	
    solLabyrinth(Y-1, X-1);
	return 0;
}
