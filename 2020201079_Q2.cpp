#include<iostream>
#include<cmath>
#include<vector>

using namespace std;
typedef long long ll;

class TrieNode{
    public:
        TrieNode* left;
        TrieNode* right;
};

void insert(ll n,TrieNode* head){
    auto curr = head;
    int s = sizeof(ll)*8; //converting to bits
    for(ll i=s-1;i>=0;i--){
        int bit = (n>>i)&1;
        if(bit==0){
            if(curr->left == nullptr)
                curr->left = new TrieNode();
            curr = curr->left;
        }
        else{
            if(curr->right == nullptr)
                curr->right = new TrieNode();
            curr = curr->right;
        }
    }
}

 ll getMaxXor(ll n,TrieNode* head){
     ll ans = 0;
     TrieNode* curr = head;
     for(ll j=sizeof(ll)*8-1;j>=0;j-- ){
         ll bit = (n>>j)&1;
         if(bit==0){
             if(curr->right != nullptr){
                 curr = curr->right;
                 ans += pow(2,j);
             }
             else{
                 curr = curr->left;
             }
         }
         else{//bit is one. Wanna go towards left (opposite side)
             if(curr->left != nullptr){
                 curr = curr->left;
                 ans += pow(2,j);
             }
             else{
                 curr = curr->right;
             }
         }
     }
     return ans;
}

int main(){
    int n,q;cin>>n>>q;
    vector<int> arr(n);
    TrieNode* head = new TrieNode();
    for(int i=0;i<n;i++){
        cin>>arr[i];
        insert(arr[i],head);
    }
    for(int i=0;i<q;i++){
        ll x;cin>>x;
        cout<<getMaxXor(x,head)<<std::endl;
    }
}