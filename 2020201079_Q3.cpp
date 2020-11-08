#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<algorithm>

using namespace std;

#define ll long long int

int partitionSize;
int noOfFilesWritten = 0;

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

void merge(vector<ll>& input,int l,int mid,int r){
    vector<ll> result(0);
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
}
void mergeSortHelper(vector<ll>& input,int l,int r){
    if(l<r){
        int mid = (l+r)/2;
        mergeSortHelper(input,l,mid);
        mergeSortHelper(input,mid+1,r);
        merge(input,l,mid,r);
    }
}
void mergeSort(vector<ll>& input){
    mergeSortHelper(input,0,input.size()-1);
}

string getOutputPathFromBlockNumber(int blockNumber){
    return "data\\output\\output"+to_string(blockNumber)+".txt";
}
void writeInFile(vector<ll> block,int blockNumber){
    noOfFilesWritten++;
    string outputFilePath = getOutputPathFromBlockNumber(blockNumber);
    std::ofstream outFile(outputFilePath);
    for (const auto &e : block) 
        outFile << e << "\n";
    outFile.close();
}

int main(int argc, char *argv[]){
    if(argc != 4){
        cout<<argc;
        cout<<" inputPath outputPath blockSize"<<endl;
        exit(1);
    }
    string inputPath = argv[1];
    //ifstream file("data\\input\\input1000000.txt");
    ifstream file(inputPath);
    //string finalOutputFile = "data\\output\\outputFinal.txt";
    string finalOutputFile = argv[2];
    //partitionSize = 100000;
    partitionSize = stoi(argv[3]);
    string data = "";
    vector<ll> currBlock;

    int blockNumber = 0;
    int count = 0;
    while(getline(file, data,',')) 
    {   
        if(count<partitionSize){
            currBlock.push_back(stoll(data));
            //cout << data << endl;
            count++;
        }
        else{
            mergeSort(currBlock);
            writeInFile(currBlock,blockNumber);

            //resetting count and block vector
            count = 0;
            blockNumber++;
            currBlock.clear();
            //cout<<"Printing "<<blockNumber<<" block"<<endl;
            currBlock.push_back(stoll(data));
            //cout << data << endl;
            count++;
        }
    }
    // the last block needs to be written
    if(!currBlock.empty()){
        mergeSort(currBlock);
        writeInFile(currBlock,blockNumber);
    }
    file.close();

    //have saved all blocks sorted in chunks in output/output{fileNumber}.txt
    //have to sort all the sorted blocks at once now.

    vector<ifstream*> sortedFiles; 
    for(int i=0;i<noOfFilesWritten;i++){
        string filePath = getOutputPathFromBlockNumber(i);
        ifstream* file = new ifstream(filePath);
        sortedFiles.push_back(file);
    }

    //save a pair in heap <ll,in> value,blocknumber need block number for increament of respective ifstream
    vector<pair<ll,int>> firstFileValues;
    for(int i=0;i<sortedFiles.size();i++){
        string output;
        if(getline(*sortedFiles[i],output)){
            firstFileValues.push_back({stoll(output),i});
        }
    }
    //got all the first values in a vector now make them a heap

    
    ofstream finalOutFile(finalOutputFile);
        
    auto h = MinHeap<pair<ll,int>>(firstFileValues);
    while(h.getSize() != 0){
        auto p = h.heapExtractMin();
        //cout<<"value : "<<p.first<<" file : "<<p.second<<endl;
        finalOutFile<<p.first<<"\n";
        string output;
        if(getline(*sortedFiles[p.second],output)){
            h.insert({stoll(output),p.second});
        }
    }
    finalOutFile.close();

    for(int i=0;i<noOfFilesWritten;i++){
        auto f = sortedFiles[i];
        f->close();
        free(sortedFiles[i]);
        string filePath = getOutputPathFromBlockNumber(i);
        remove(filePath.c_str());
    }
}
