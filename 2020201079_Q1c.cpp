#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<climits>
#define ll long long int

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

vector<long long int> buildSuffixArray(std::string& input){
    long long int n = input.size();
    vector<SuffixArrayNode> suffixes(n);
    vector<long long int> result(n);

    //initializing the suffixes vector with rank and next rank (implies string of size 2)
    for(long long int i=0;i<n;i++){
        suffixes[i].index = i;
        suffixes[i].rank[0] = input[i] - 'a';
        if(i+1<n)
            suffixes[i].rank[1] = input[i+1] - 'a';
        else
            suffixes[i].rank[1] = -1;
    }

    sort(suffixes.begin(),suffixes.end(),cmpSuffixArrayNodes);

    vector<long long int> ind(n); // need this array for setting the rank[1] later
    // rank[0] we just compare with prev element in sorted if equal then rank is same
    //otherwise just the sum of prev rank

    //k is from 4 because we already constructed for k=2
    for(long long int k=4;k<2*n;k=k*2){

        long long int rank = 0;
        long long int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = rank;

        for(long long int i=1;i<n;i++){
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

        for(long long int i=0;i<n;i++){
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
    for(long long int i=0;i<n;i++)
        result[i] = suffixes[i].index;
    
    return result;
}

vector<long long int> getInvSuffix(vector<long long int>& suffixArray){
    vector<long long int> result(suffixArray.size(),0);
    for(int i=0;i<suffixArray.size();i++)
        result[suffixArray[i]]=i;
    return result;
}

vector<long long int> getLCP(string& input,vector<long long int> suffixArray){
    vector<long long int> result(suffixArray.size(),0);

    vector<long long int> invSuffixArray = getInvSuffix(suffixArray);

    int k=0;
    for(int i=0;i<suffixArray.size();i++){
        if(invSuffixArray[i] == suffixArray.size()-1){ //
            k=0;
            continue;
        }
        int j = suffixArray[invSuffixArray[i]+1];
        while(i+k<suffixArray.size() && j+k<suffixArray.size() && input[i+k]==input[j+k])
            k++;
        result[invSuffixArray[i]] = k;
        if(k>0)
            k--;
    }
    return result;
}


string reverseString(string& input){
    string result="";
    for(int i=input.size()-1;i>=0;i--){
        result.push_back(input[i]);
    }
    return result;
}

// building segment tree for finding min
void build(ll si,ll ss,ll se,vector<ll>& arr,vector<ll>& segmentTree){
    if(ss==se){
        segmentTree[si] = arr[ss];
    }
    else{
        ll mid=(ss+se)/2;
        build(si*2+1,ss,mid,arr,segmentTree);
        build(si*2+2,mid+1,se,arr,segmentTree);
        segmentTree[si] = min(segmentTree[si*2+1],segmentTree[si*2+2]);
    }
}

ll getMin(ll si,ll ss,ll se,ll qs,ll qe,vector<ll>& segmentTree){
    if(qs>se || qe<ss){ // no overlapping
        return LLONG_MAX;
    }
    else if(ss>=qs && se<=qe){ //segment is inside query
        return segmentTree[si];
    }
    else{ //semi overlap need to call on both children
        int mid = (ss+se)/2;
        return min(getMin(2*si+1,ss,mid,qs,qe,segmentTree),getMin(2*si+2,mid+1,se,qs,qe,segmentTree));
    }
}

int main(){
    string input;
    cin>>input;
    long long int n=input.size();
    string reverseInput = reverseString(input);
    string modifiedInput = input+"#"+reverseInput;
    //modifiedInput = "abrakadabra";
    cout<<"modified input : "<<modifiedInput<<endl;

    auto sa=buildSuffixArray(modifiedInput);

    auto lcp = getLCP(modifiedInput,sa);

    vector<ll> segmentTree(4*lcp.size());
    
    build(0,0,lcp.size()-1,lcp,segmentTree);

    vector<long long int> invSuffixArray = getInvSuffix(sa);

    //get even longest first
    ll evenPalSize = LLONG_MIN;
    for(ll i=1;i<n;i++){
        ll otherStringIndex = (2*n)-(i-1);
        ll saIndex1 = invSuffixArray[i];
        ll saIndex2 = invSuffixArray[otherStringIndex];
        if(saIndex1 > saIndex2){
            ll temp =saIndex2;
            saIndex2 = saIndex1;
            saIndex1 = temp;
        }
        //cout<<"idx1: "<<saIndex1<<" idx2: "<<saIndex2<<" Min is "<<getMin(0,0,lcp.size()-1,saIndex1,saIndex2-1,//segmentTree)<<endl;
        evenPalSize = max(getMin(0,0,lcp.size()-1,saIndex1,saIndex2-1,segmentTree),evenPalSize);
    }
    cout<<"even max size : "<<(2*evenPalSize)<<endl;

    ll oddPalSize = LLONG_MIN;
    for(ll i=1;i<n;i++){
        ll saIndex1 = invSuffixArray[i+1];
        ll saIndex2 = invSuffixArray[(2*n)-(i-1)];
        if(saIndex1 > saIndex2){
            ll temp =saIndex2;
            saIndex2 = saIndex1;
            saIndex1 = temp;
        }
        oddPalSize = max(getMin(0,0,lcp.size()-1,saIndex1,saIndex2-1,segmentTree),oddPalSize);
    }
    cout<<"odd size : "<<(2*oddPalSize)+1<<endl;

    cout<<"Max size is "<<max((2*oddPalSize)+1,(2*evenPalSize))<<endl;
}