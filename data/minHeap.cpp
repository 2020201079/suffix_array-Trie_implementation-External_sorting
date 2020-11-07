//need min heap of a pair<ll,int> number,blocknumber
#include<iostream>
#include<vector>
#define ll long long int
using namespace std;

template <typename T> 
class MinHeap{
    private:
        vector<T> A;
        void minHeapify(int index){
            int l = 2*index+1;
            int r = 2*index+2;
            int smallest = index;
            if(l<A.size() && A[l]<A[smallest])
                smallest = l;
            if(r<A.size() && A[r]<A[smallest])
                smallest = r;
            if(smallest != index){
                T temp = A[smallest];
                A[smallest] = A[index];
                A[index] = temp;
                minHeapify(smallest);
            }
        }
    public:
        MinHeap(vector<T> input){
            A = input;
            for(int i=input.size()/2;i>=0;i--)
                minHeapify(i);
        }
        void printHeap(){
            for(T value:A){
                cout<<value<<" ";
            }
            cout<<endl;
        }
        int getSize(){
            return A.size();
        }
        T heapExtractMin(){
            if(A.size() == 0){
                perror("Heap is empty");
            }
            T minValue = A[0];
            A[0] = A[A.size()-1];
            A.pop_back();
            minHeapify(0);
            return minValue;
        }

        void insert(T value){
            A.push_back(value);
            for(int i=A.size()/2;i>=0;i--)
                minHeapify(i);
        }
};

int main(){
    auto h = MinHeap<int>({6,3});
    vector<int> input = {8,9,10,34,2,0};
    for(int num:input)
        h.insert(num);
    h.printHeap();
    while(h.getSize() != 0)
        cout<<h.heapExtractMin()<<" ";
    cout<<endl;

}