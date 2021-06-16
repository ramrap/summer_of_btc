#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <cstdio> // printf, scanf // scanf("%d", &i); // read integer
#include <stdlib.h>
#include <unordered_map>
#include <utility>  // pair, make_pair


using namespace std;
#define speed ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)


const int MAX_WEIGHT_LIMIT = 4000000;

struct Transaction
{
    string id;
    int weight;
    int fees;
    vector<string> parents;

    bool operator<(const Transaction &t) const
    {
        return this->id < t.id;
    }
};

unordered_map<string, Transaction> transactions;
set<string> completed_transaction;
multiset<pair<float, Transaction>, greater<pair<float, Transaction>>> all_transaction;

// reading and storing data from file
void read_csv(string filename)
{
    // Create an input filestream
    ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open())
        throw runtime_error("Could not open file");

    // Helper vars
    string line, val;
    int first = 1;
    while (getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);
        // Keep track of the current column index
        // Extract each integer
        int index = 0;
        Transaction trans;
        while (getline(ss, val, ','))
        {
            if (first)
            {
                break;
            }
            if (index == 0)
            {
                trans.id = val;
            }
            else if (index == 1)
            {
                trans.fees = stoi(val);
            }
            else if (index == 2)
            {
                trans.weight = stoi(val);
            }
            else if (index == 3)
            {
                string paren;
                vector<string> parents;
                if (val != "")
                {
                    stringstream par_ss(val);

                    while (getline(par_ss, paren, ';'))
                    {
                        parents.push_back(paren);
                    }
                }
                trans.parents = parents;
            }

            index++;
        }
        if (first)
        {
            first = 0;
            continue;
        }
        transactions[trans.id] = trans;
    }

    myFile.close();
}


void writeFile(string FileName, vector<string> final_transactions)
{
    ofstream myfile;
    myfile.open(FileName);
    for (auto id : final_transactions)
    {
        myfile << id << endl;
    }
}


//Arranging Transaction according to fees/weight
void parseData()
{

    for (auto trans : transactions)
    {
        all_transaction.insert(make_pair((trans.second.fees * 1.0) / trans.second.weight, trans.second));
    }
}

//Function to check if current Transaction is safe to add or not
bool isSafe(Transaction t, long long cur_weight)
{
    if (t.weight + cur_weight > MAX_WEIGHT_LIMIT)
    {
        return false;
    }
    for (auto parent : t.parents)
    {
        if (completed_transaction.find(parent) == completed_transaction.end())
        {
            return false;
        }
    }
    return true;
}

void findTransactions(vector<string> &final_transactions, long long &cur_weight, long long &cur_fees)
{
    while (all_transaction.size())
    {

        bool check = 1;
        auto element_removed = all_transaction.begin();
        for (auto it = all_transaction.begin(); it != all_transaction.end(); it++)
        {
            pair<float, Transaction> t = *it;
            if (isSafe(t.second, cur_weight))
            {
                final_transactions.push_back(t.second.id);
                completed_transaction.insert(t.second.id);
                cur_weight += t.second.weight;
                cur_fees += t.second.fees;
                check = 0;
                all_transaction.erase(it);

                break;
            }
        }
        if (check)
        {
            break;
        }
    }
}

int main()
{
    speed;

    string file_name;
    file_name = "mempool.csv";

    read_csv(file_name);
    parseData();

    long long cur_weight = 0;// variables to store weight and fees 
    long long cur_fees = 0;
    vector<string> final_transactions; // vector to store final list of transactions

    findTransactions(final_transactions, cur_weight, cur_fees);

    cout << "Total Fees=> " << cur_fees << endl;
    cout << "Total Weight=> " << cur_weight << endl;
    writeFile("block.txt", final_transactions);

    return 0;
}
