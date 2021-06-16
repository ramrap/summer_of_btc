#include <iostream>
 
//  remove_if, sort, min, max, reverse,  merge, binary_search, is_sorted, unique, replace_if, count, push_heap, pop_heap, make_heap
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
// .push, .pop, .front, .back
#include <queue>
// .front, .back, .push_back, push_front, pop_back, pop_front, .at (slow)
#include <deque>
// map<string, int> m; m["x"] = 2; auto it = m.find("x"); it != m.end(); it->second; m.erase(it); m.erase("x");
#include <map>
// can take custom binary cmp function, 
// set<string> a; a.insert("f"); set<string>iterator it = a.find("f); it != a.end(); *it; a.erase("f");
#include <set> 
#include <cstdio> // printf, scanf // scanf("%d", &i); // read integer
#include <stdlib.h>
#include <unordered_map>
#include <assert.h> // assert
#include <utility> // pair, make_pair
#include <functional>
#include <string> 
#include <stack> // .pop .push .size .top .empty
#include <math.h> // cos, sin, tan, acos, asin, atan2, exp, log, log10, log2, pow, sqrt, hypot, cell, floor, round, fabs, abs
 
using namespace std;
#define speed ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long int
#define fo(i,n) for(int i=0;i<n;i++)
#define fab(i,a,b) for(int i=a;i<b;i++)
#define rfo(i,n) for(int i=n;i>0;i--)
 
//pair
#define pii pair<int,int>
#define F first
#define S second
 
// vector
#define vll vector<ll>
#define pb(x) push_back(x)
 
using namespace std;

const int MAX_WEIGHT_LIMIT = 4000000;




 


struct Transaction{
    string id;
    int weight ;
    int fees ;
    vector<string>parents;
};

unordered_map<string,Transaction> transactions;


 

void read_csv(string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    vector<pair<string, vector<string>>> result;

    // Create an input filestream
    ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    string val;
    int first=1;
    while(getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);
        
        // Keep track of the current column index
        int colIdx = 0;
        
        // Extract each integer
        int index=0;
        Transaction trans;
        
        // cout<<line<<endl;
        while(getline(ss,val,',')){

            if(first){
                first=0;
                break;
            }
            // cout<<index<<"-"<<val<<" ";
           
            if(index ==0){
                trans.id = val;
                
            }
            else if(index == 1){
                trans.fees = stoi(val);
            }
            else if(index == 2){
                trans.weight = stoi(val);
            }
            else if(index == 3){
                string paren;
                vector<string> parents;
                if(val != ""){
                    stringstream par_ss(val);

                    while(getline(par_ss,paren,';')){
                        parents.push_back (paren);
                    }
                }

                trans.parents = parents;
            }


            index++;
            
        
            // if(ss.peek() == ',') ss.ignore();
            
        }
        // cout<<endl;
        // cout<<trans.id<<" "<<trans.parents
        transactions[trans.id] = trans;
        
    }

    // Close file
    myFile.close();

    // return result;
}



int main(){
	speed;
	
	string file_name ;
    file_name = "mempool.csv";

    read_csv(file_name);


    for (auto a: transactions){
        cout<<a.second.id<<" "<<a.second.weight<<" "<<a.second.fees<<endl;
        for(auto e:a.second.parents){
            cout<<e<< " ";
        }
        cout<<endl;

    }


    return 0;
}
 
 