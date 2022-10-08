#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<iomanip>

using namespace std;

#define dim 26
#define shift 65

int tries;
bool cycle[26];
bool facts[26];
vector<char> rules[100];
vector<char> initialFacts;
vector<char> foundFacts;
vector<int> path;
char goal;
int r;
ifstream in;
ofstream outLong;
ofstream outShort;

void initialize(){
    for(int i = 0; i < r; i++){
        cycle[i] = false;
        facts[i] = false;
    }
}

bool isInitial(char fact){
    for(int i = 0; i < initialFacts.size(); i++){
        if(initialFacts.at(i) == fact) return true;
    }
    return false;
}

void clearPath(){
    vector<char> tmp;
    bool flag = true;
    for(int i = path.size()-1; i >= 0; i--){
        flag = false;
        //cout<<"Putting R: "<<path.at(i)<<" ";
        tmp.push_back(path.at(i));
        //cout<<"Fact: "<<rules[path.at(i)-1].at(0)<<endl;

        for(int j = 1; j < rules[path.at(i)-1].size(); j++){
            if(!isInitial(rules[path.at(i)-1].at(j))){
                flag = true;
                break;
            }
        }
        if(!flag) break;
    }
    path.clear();
    for(int i = tmp.size()-1; i >= 0; i--) path.push_back(tmp.at(i));
}

void printRule(int i){
    outLong<<"Find R"<<i+1<<":";
    for(int j = rules[i].size() - 1; j > 0; j--){
        outLong<<rules[i].at(j);
        if(j != 1) outLong<<",";
    }
    outLong<<"->"<<rules[i].at(0)<<". New goals";
    for(int j = 1; j < rules[i].size(); j++){
        outLong<<" "<<rules[i].at(j);
        if(j != rules[i].size() - 1) outLong<<",";
    }
    outLong<<".\n";
}

void printVector(vector<char> A){
    for(int i = 0; i < A.size(); i++){
        outLong<<" "<<A.at(i);
        if(i != A.size()-1) outLong<<",";
    }
}

bool BackwardChaining(char actualGoal, int n){
    vector<char> tmpFacts;
    bool yes = true;
    outLong<<setw(2)<<setfill(' ')<<tries<<") ";

    for(int i = 0; i < n; i++) outLong<<"-";
    outLong<<"Goal "<<actualGoal<<". ";


    if(!cycle[actualGoal - shift] || facts[actualGoal - shift]){
        
        cycle[actualGoal - shift] = true;

        if(facts[actualGoal-shift]){ //if inferred

            if(isInitial(actualGoal)){
                outLong<<"Fact (initial), as facts";

                printVector(initialFacts);
                
            }else{
                outLong<<"Fact (earlier inferred), as facts";
                
                printVector(initialFacts);

                outLong<<" and";
                
                printVector(foundFacts);
            }

            outLong<<". Back, OK."<<endl;

            return true;

        }else{

            bool foundRules = false;

            for(int i = 0; i < r; i++){
                yes = true;
                if(rules[i].at(0) == actualGoal){
                    tries++;

                    foundRules = true;

                    printRule(i);

                    for(int j = 1; j < rules[i].size(); j++){
                        if(BackwardChaining(rules[i].at(j), n+1)){
                            if(!isInitial(rules[i].at(j))){
                                facts[rules[i].at(j) - shift] = true;
                            }
                        }else{
                            yes = false;
                        }
                        tries++;
                    }
                    
                    if(yes){
                        foundFacts.push_back(actualGoal);
                        outLong<<setw(2)<<setfill(' ')<<tries<<") ";
                        for(int i = 0; i < n; i++) outLong<<"-";
                        outLong<<"Goal "<<actualGoal<<". Fact (presently inferred).";
                        printVector(initialFacts);

                        outLong<<" and";
                
                        printVector(foundFacts);

                        outLong<<". Back, OK."<<endl;

                        cycle[actualGoal - shift] = false;
                        path.push_back(i+1);
                        return true;
                    }
            
                    outLong<<setw(2)<<setfill(' ')<<tries<<") ";
                    for(int i = 0; i < n; i++) outLong<<"-";
                    outLong<<"Goal "<<actualGoal<<". ";
                }
            }
            if(!foundRules) outLong<<"No rules. Back, FAIL.\n";
            else outLong<<"No more rules. Back, FAIL.\n";
            foundFacts.clear();
        }
        cycle[actualGoal - shift] = false;

    }else{
        //Cycle
        foundFacts.clear();
        outLong<<"Cycle. Back, FAIL.\n";
        return false;
    }
    return false;
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
        facts[int(tmp.at(i) - shift)] = true;
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
    tries = 1;

    outLong<<"PART 2. Trace\n";

    if(BackwardChaining(goal,0)){

        if(path.size() != 0){
            
            clearPath();

            cout<<"\nPART 3. Results\n";
            cout<<"  1) Goal Z achieved.\n  2) Path:";
            outShort<<"\nPART 3. Results\n";
            outShort<<"  1) Goal Z achieved.\n  2) Path:";
            outLong<<"\nPART 3. Results\n";
            outLong<<"  1) Goal Z achieved.\n  2) Path:";
            for(int i = 0; i < path.size(); i++){
                cout<<" R"<<path.at(i);
                outLong<<" R"<<path.at(i);
                outShort<<" R"<<path.at(i);
                if(i != path.size()-1){
                    cout<<",";
                    outLong<<",";
                    outShort<<",";
                }
            }
            cout<<".\n";
            outShort<<".\n";
            outLong<<".\n";
        }else{
            cout<<"\nPART 3. Results\n";
            cout<<"  1) Goal Z among facts. Empty path.\n";
            outShort<<"\nPART 3. Results\n";
            outShort<<"  1) Goal Z among facts. Empty path.\n";
            outLong<<"\nPART 3. Results\n";
            outLong<<"  1) Goal Z among facts. Empty path.\n";
        }
    }else{
        cout<<"\nPART 3. Results\n";
        cout<<"  1) Goal Z not achieved. No path.\n";
        outShort<<"\nPART 3. Results\n";
        outShort<<"  1) Goal Z not achieved. No path.\n";
        outLong<<"\nPART 3. Results\n";
        outLong<<"  1) Goal Z not achieved. No path.\n";
    }
}