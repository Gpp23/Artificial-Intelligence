#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<iomanip>

using namespace std;

#define dim 26
#define shift 65

bool fact[dim];
vector<char> rules[100];
vector<char> initialFacts;
vector<char> newFacts;
vector<int> path;
char goal;
bool flags[100];
bool flags1[100];
bool flags2[100];
int r;
ifstream in;
ofstream outLong;
ofstream outShort;

void initialize(){
    for(int i = 0; i < r; i++){
        flags[i] = false;
        flags1[i] = false;
        flags2[i] = false;
    }
}

bool end(){
    if(fact[int(goal) - shift]) return true;
    for(int i = 0; i < r; i++) if(!flags[i]) return false;
    return true;
}

bool ForwardChaining(){
    int iteration = 0;
    bool found;
    outLong<<"PART 2. Trace\n";
    bool ruleFound = true;;
    while(!end()){
        if(!ruleFound) break;
        ruleFound = false;
        iteration++;

        outLong<<setw(4)<<setfill(' ')<<"\n    ITERATION "<<iteration<<endl;

        for(int i = 0; i < r; i++){
            outLong<<setw(8)<<setfill(' ')<<" R"<<i+1<<":";
            for(int k = 1; k < rules[i].size(); k++){
                outLong<<rules[i].at(k);
                if(k != rules[i].size() -1)outLong<<",";
            }
            if(!flags[i]){
                found = true;
                int k;
                for(k = rules[i].size()-1; k > 0; k--){
                    if(!fact[(int)rules[i].at(k) - shift]){
                        found = false;
                        break;
                    }
                }
                outLong<<"->"<<rules[i].at(0)<<" ";
                if(found){
                    if(!fact[int(rules[i].at(0)) - shift]){
                        ruleFound = true;
                        newFacts.push_back(rules[i].at(0));
                        fact[int(rules[i].at(0)) - shift] = true;
                        path.push_back(i+1);
                        flags[i] = true;
                        flags1[i] = true;
                        outLong<<"apply. Raise flag1. Facts";
                        for(int j = 0; j < initialFacts.size(); j++){
                            outLong<<" "<<initialFacts.at(j);
                            if(j != initialFacts.size()-1)outLong<<",";
                        }
                        outLong<<" and";
                        for(int j = 0; j < newFacts.size(); j++){
                            outLong<<" "<<newFacts.at(j);
                            if(j != newFacts.size()-1)outLong<<",";
                        }
                        outLong<<".\n";
                        break;
                    }else{
                        outLong<<"not applied, because RHS in facts. Raise flag2.\n";
                        flags[i] = true;
                        flags2[i] = true;
                    }
                }else{
                    outLong<<"not applied, because of lacking "<<rules[i].at(k)<<".\n";
                }
            }else{
                if(flags1[i])outLong<<"->"<<rules[i].at(0)<<" skip, because flag1 raised.\n";
                else outLong<<"->"<<rules[i].at(0)<<" skip, because flag2 raised.\n";
            }
        }
    }
    cout<<"PART 3. Result\n";
    outShort<<"PART 3. Result\n";
    outLong<<"\nPART 3. Result\n";
    if(fact[int(goal) - shift]){
        if(path.size() != 0){
            cout<<setw(8)<<setfill(' ')<<"    1) Goal "<<goal<<" achieved.\n";
            cout<<setw(8)<<setfill(' ')<<"    2) Path";
            outShort<<setw(8)<<setfill(' ')<<"    1) Goal "<<goal<<" achieved.\n";
            outShort<<setw(8)<<setfill(' ')<<"    2) Path";
            outLong<<setw(8)<<setfill(' ')<<"    1) Goal "<<goal<<" achieved.\n";
            outLong<<setw(8)<<setfill(' ')<<"    2) Path";
            for(int i = 0; i < path.size(); i++){
                cout<<" R"<<path.at(i);
                outShort<<" R"<<path.at(i);
                outLong<<" R"<<path.at(i);
                if(i != path.size() - 1){
                    cout<<",";
                    outLong<<",";
                    outShort<<",";
                }
            }
            cout<<".\n";
            outShort<<".\n";
            outLong<<".\n";
        }else{
            cout<<setw(8)<<setfill(' ')<<"    1) Goal "<<goal<<" in facts. Empty path.\n";
            outShort<<setw(8)<<setfill(' ')<<"    1) Goal "<<goal<<" in facts. Empty path.\n";
            outLong<<setw(8)<<setfill(' ')<<"    1) Goal "<<goal<<" in facts. Empty path.\n";
        }
    }else{
        cout<<setw(4)<<setfill(' ')<<"1) Goal "<<goal<<" not achieved.\n";
        outShort<<setw(4)<<setfill(' ')<<"1) Goal "<<goal<<" not achieved.\n";
        outLong<<setw(4)<<setfill(' ')<<"1) Goal "<<goal<<" not achieved.\n";
    }
}


int main(int argc, char* args[]){
    in.open(args[1]);
    outLong.open("out-long.txt");
    outShort.open("out-short.txt");
    string tmp;
    for(int i = 0; i < 3; i++) getline(in,tmp);
    r = 0;
    getline(in,tmp);
    initialize();
    do{
        for(int i = 0; i < tmp.length(); i+=2){
            rules[r].push_back(tmp.at(i));
        }
        r++;
        if(!getline(in,tmp))break;
    }while(!tmp.empty());
    getline(in,tmp); //2) Facts
    getline(in,tmp);
    for(int i = 0; i < tmp.length(); i+=2){
        initialFacts.push_back(tmp.at(i));
        fact[int(tmp.at(i) - shift)] = true;
    }
    getline(in, tmp);
    getline(in, tmp);
    in>>goal;

    cout<<"PART 1. Data\n\n";
    cout<<setw(8)<<setfill(' ')<<"    1) Rules\n";
    outShort<<"PART 1. Data\n\n";
    outShort<<setw(8)<<setfill(' ')<<"    1) Rules\n";
    outLong<<"PART 1. Data\n\n";
    outLong<<setw(8)<<setfill(' ')<<"    1) Rules\n";
    for(int i = 0; i < r; i++){
        cout<<setw(8)<<setfill(' ')<<"R"<<i+1<<":";
        outShort<<setw(8)<<setfill(' ')<<"R"<<i+1<<":";
        outLong<<setw(8)<<setfill(' ')<<"R"<<i+1<<":";
        for(int k = 1; k < rules[i].size(); k++){
            cout<<" "<<rules[i].at(k);
            outShort<<" "<<rules[i].at(k);
            outLong<<" "<<rules[i].at(k);
            if(k != rules[i].size() -1){
                cout<<",";
                outShort<<",";
                outLong<<",";
            }
        }
        cout<<" -> "<<rules[i].at(0)<<endl;
        outShort<<" -> "<<rules[i].at(0)<<endl;
        outLong<<" -> "<<rules[i].at(0)<<endl;
    }
    cout<<setw(4)<<setfill(' ')<<"    2) Facts";
    outShort<<setw(4)<<setfill(' ')<<"    2) Facts";
    outLong<<setw(4)<<setfill(' ')<<"    2) Facts";
    for(int j = 0; j < initialFacts.size(); j++){
        cout<<" "<<initialFacts.at(j);
        outShort<<" "<<initialFacts.at(j);
        outLong<<" "<<initialFacts.at(j);
        if(j != initialFacts.size()-1)outLong<<",";
    }
    cout<<setw(4)<<setfill(' ')<<"\n    3) Goal "<<goal<<".\n\n";
    outShort<<setw(4)<<setfill(' ')<<"\n    3) Goal "<<goal<<".\n\n";
    outLong<<setw(4)<<setfill(' ')<<"\n    3) Goal "<<goal<<".\n\n";
    ForwardChaining();
}