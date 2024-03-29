#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

class SuffixArrayNode{
    public:
        int index;
        int rank[2];
};

bool cmpSuffixArrayNodes(SuffixArrayNode a,SuffixArrayNode b){
    if(a.rank[0] == b.rank[0]){
        return a.rank[1] < b.rank[1];
    }
    else{
        return a.rank[0]<b.rank[0];
    }
}

vector<int> buildSuffixArray(std::string& input){
    int n = input.size();
    vector<SuffixArrayNode> suffixes(n);
    vector<int> result(n);

    //initializing the suffixes vector with rank and next rank (implies string of size 2)
    for(int i=0;i<n;i++){
        suffixes[i].index = i;
        suffixes[i].rank[0] = input[i] - 'a';
        if(i+1<n)
            suffixes[i].rank[1] = input[i] - 'a';
        else
            suffixes[i].rank[1] = -1;
    }

    sort(suffixes.begin(),suffixes.end(),cmpSuffixArrayNodes);

    vector<int> ind(n); // need this array for setting the rank[1] later
    // rank[0] we just compare with prev element in sorted if equal then rank is same
    //otherwise just the sum of prev rank

    //k is from 4 because we already constructed for k=2
    for(int k=4;k<2*n;k=k*2){

        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = rank;

        for(int i=1;i<n;i++){
            if(suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i-1].rank[1]){
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else{
                rank += 1;
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            ind[suffixes[i].index] = i;
        }

        for(int i=0;i<n;i++){
            int nextIndex = suffixes[i].index + k/2;
            if(nextIndex < n){
                suffixes[i].rank[1] = suffixes[ind[nextIndex]].rank[0];
            }
            else{
                suffixes[i].rank[1] = -1;
            }
        }
        sort(suffixes.begin(),suffixes.end(),cmpSuffixArrayNodes);
    }
    for(int i=0;i<n;i++)
        result[i] = suffixes[i].index;
    
    return result;
}

int main(){
    string input;
    cin>>input;
    auto sa=buildSuffixArray(input);
    for(int i:sa)
        cout<<i<<" ";
    cout<<endl;
}