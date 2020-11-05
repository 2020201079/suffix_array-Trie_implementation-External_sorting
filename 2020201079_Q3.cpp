#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<algorithm>

using namespace std;

int partitionSize= 2;
int noOfFilesWritten = 0;

void writeInFile(vector<long long int> block,int blockNumber){
    noOfFilesWritten++;
    string outputFilePath = "data\\output\\output"+to_string(blockNumber)+".txt";
    std::ofstream outFile(outputFilePath);
    for (const auto &e : block) 
        outFile << e << "\n";
}

int main(){
    ifstream file("data\\input\\input10.txt");
    string data = "";
    vector<long long int> currBlock;

    int blockNumber = 0;
    int count = 0;
    cout<<"Printing "<<blockNumber<<" block"<<endl;
    while(getline(file, data,',')) 
    {   
        if(count<partitionSize){
            currBlock.push_back(stoll(data));
            cout << data << endl;
            count++;
        }
        else{
            sort(currBlock.begin(),currBlock.end()); //need to implement merge sort by myself
            writeInFile(currBlock,blockNumber);

            //resetting count and block vector
            count = 0;
            blockNumber++;
            currBlock.clear();
            cout<<"Printing "<<blockNumber<<" block"<<endl;
            currBlock.push_back(stoll(data));
            cout << data << endl;
            count++;
        }
    }
    // the last block needs to be written
    if(!currBlock.empty()){
        sort(currBlock.begin(),currBlock.end());
        writeInFile(currBlock,blockNumber);
    }
    file.close();
}
