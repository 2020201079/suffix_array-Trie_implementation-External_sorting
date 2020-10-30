#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

class SuffixArrayNode{
    public:
        pair<int,int> p;
        int index;
    SuffixArrayNode(int index,pair<int,int> p){
        this->index = index;
        this->p = p;
    }
    void printNode(){
        cout<<"("<<p.first<<","<<p.second<<")"<<endl;
    }

    bool operator < (const SuffixArrayNode& sa) const{
        if(p.first < sa.p.first)
            return true;
        else if(p.first == sa.p.first){
            if(p.second < sa.p.second)
                return true;
            
        }
    }
};

vector<int> createSuffixArray(string input){
    int n = input.size();
    vector<int> currRanks;
    for(char i:input)
        currRanks.push_back(i-'a');
    for(int i=0;i<n;i=pow(2,i)){
        i++;
        vector<SuffixArrayNode> currTuples;
        for(int j=0;j<n;j++){
            if(j+i<n)
                currTuples.push_back(SuffixArrayNode(j,{currRanks[j],currRanks[j+i]}));
            else
                currTuples.push_back(SuffixArrayNode(j,{currRanks[j],-1}));
        }
        for(auto t: currTuples){
            t.printNode();
        }
    }
}
int main(){
    string input = "banana";
    vector<int> suffixArray = createSuffixArray(input);
}