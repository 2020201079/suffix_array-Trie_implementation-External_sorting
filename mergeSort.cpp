#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int>& input,int l,int mid,int r){
    cout<<"merge called with l:"<<l<<" mid:"<<mid<<" r:"<<r<<endl;
    vector<int> result(0);
    int i=l;
    int j=mid+1;
    while(i<=mid && j<=r){
        if(input[i]<input[j]){
            result.push_back(input[i]);
            i++;
        }
        else{
            result.push_back(input[j]);
            j++;
        }
    }
    while(i<=mid){
        result.push_back(input[i]);
        i++;
    }
    while(j<=r){
        result.push_back(input[j]);
        j++;
    }
    for(int z=l;z<=r;z++){
        input[z] = result[z-l];
    }
    cout<<"Merge"<<":";
    for(auto n:input)
        cout<<n<<" ";
    cout<<endl;
}
void mergeSortHelper(vector<int>& input,int l,int r){
    cout<<"Merge sort helper l : "<<l<<" r :"<<r<<endl;
    if(l<r){
        int mid = (l+r)/2;
        mergeSortHelper(input,l,mid);
        mergeSortHelper(input,mid+1,r);
        merge(input,l,mid,r);
    }
}
void mergeSort(vector<int>& input){
    mergeSortHelper(input,0,input.size()-1);
}

int main(){
    vector<int> input = {5,9,78,34,56,32,83,14};
    mergeSort(input);
    for(auto n:input)
        cout<<n<<" ";
}