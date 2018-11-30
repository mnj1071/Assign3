#ifndef HIERARCHYHASH_H
#define HIERARCHYHASH_H

#include <iostream>
#include "FlatHash.h"

class HierarchyHash
{
private:
	unsigned int** hashtable;
	// Variable for overflow handling
	enum overflow_handle flag;
	// Size(range) of full hash table. Initially 1000
	unsigned int table_size;
	// Size of subhash table. Fixed by 100
	unsigned int sub_table_size;
	// Nums of keys
	unsigned int num_of_keys;

public:
    HierarchyHash(enum overflow_handle _flag);
    
    ~HierarchyHash();
    
    unsigned int HashFunction(const int key) { return key % table_size; }
    
    unsigned int GetTableSize() { return table_size; }
    
    unsigned int GetNumofKeys() { return num_of_keys; }
    
    // Return the size of allocated sub hash table
    unsigned int GetAllocatedSize();
    
    // Return time cost
    int Insert(const unsigned int key);
    
    // Return time cost
    int Remove(const unsigned int key);
    
    // Return time cost
    int Search(const unsigned int key);
    
    // Delete tombstomes
    void ClearTombstones();
    
    void Print();
};

HierarchyHash::HierarchyHash(enum overflow_handle _flag)
{
	// Initial map size is 1000
	table_size = 1000;
	// Table size is fixed to 100
	sub_table_size = 100;
	flag = _flag;

	// Write your code
    hashtable = new unsigned int*[10]{NULL};

}

HierarchyHash::~HierarchyHash()
{
	// Write your code
    for(int i=0; i<table_size/sub_table_size; i++) if(!hashtable[i]) delete hashtable[i];
    delete hashtable;
}

unsigned int HierarchyHash::GetAllocatedSize()
{
	// Write your code
    int allocated_size = 0;
    
    for(int i=0; i<table_size/100; i++) if(hashtable[i]) allocated_size++;
    
    return allocated_size*100;
}

int HierarchyHash::Insert(const unsigned int key)
{
	// Write your code
    int i, j, time_cost=0, nth;
    bool first = true, flag_in = false;
    
    if(flag == LINEAR_PROBING){ // LINEAR_PROBING
        nth = (key%table_size)/100;
        
        while(true){
            if(!hashtable[nth]) hashtable[nth] = new unsigned int[sub_table_size]{0};
            for(j=0; j<sub_table_size; j++){
                if(first){
                    j=key%table_size-nth*100;
                    first = false;
                }
                time_cost++;
                if(hashtable[nth][j]==0){
                    hashtable[nth][j] = key;
                    num_of_keys++;
                    break;
                }
            }
            if(j!=sub_table_size) break;
            nth++;
            if(nth==table_size/sub_table_size) nth = 0;
        }
    }
    else if(flag == QUDRATIC_PROBING){ // QUDRATIC_PROBING
        nth = (key%table_size)/100;
        i = key%table_size - nth*100;
        
        for(j=0; j<table_size; j++){
            if(!hashtable[nth]) hashtable[nth] = new unsigned int[sub_table_size]{0};
            
            if(j) i += j*j - (j-1)*(j-1);
            while(i>=sub_table_size){
                nth++;
                i -= sub_table_size;
                if(nth>=table_size/sub_table_size) nth = 0;
            }
            
            if(!hashtable[nth]) hashtable[nth] = new unsigned int[sub_table_size]{0};
            time_cost++;
            if(hashtable[nth][i]==0 || hashtable[nth][i]==1111111){
                hashtable[nth][i] = key;
                num_of_keys++;
                break;
            }
        }
        if(j==table_size){ // QUDRATIC_PROBING -> LINEAR_PROBING
            first = true;
            for(i=(key%table_size)/100; i<table_size/sub_table_size; i++){
                for(j=0; j<sub_table_size; j++){
                    if(first){
                        j = key%table_size - nth*100;
                        first = false;
                    }
                    
                    
                    if(!hashtable[i]) hashtable[nth] = new unsigned int[sub_table_size]{0};
                    if(hashtable[i][j]==0 || hashtable[i][j]==1111111){
                        hashtable[i][j] = key;
                        num_of_keys++;
                        flag_in = true;
                        break;
                    }
                    time_cost++;
                }
                if(flag_in) break;
                if(nth == table_size/sub_table_size) nth = 0;
            }
        }
    }
    
    if(num_of_keys >= 0.8 * table_size){
        unsigned int** new_hashtable = new unsigned int*[table_size*2/sub_table_size]{NULL};
        table_size *= 2;
        unsigned int** temp = hashtable;
        hashtable = new_hashtable;
        
        num_of_keys = 0;
        for(int i=0; i<table_size/2/sub_table_size; i++){
            if(temp[i]){
                for(int k=0; k<sub_table_size; k++){
                    if(temp[i][k] && temp[i][k]!=1111111) time_cost += this->Insert(temp[i][k]);
                }
            }
        }
        for(int i=0; i<table_size/2/sub_table_size; i++) if(!temp[i]) delete temp[i];
        delete temp;
    }
    
    return time_cost;
}

int HierarchyHash::Remove(const unsigned int key)
{
	// Write your code
    int time_cost = 0, nth, nth2, j, k, a, b;
    bool first = true;
    
    if(flag == LINEAR_PROBING){
        for(nth = (key%table_size)/100; nth<=table_size/sub_table_size; nth++){
            for(j=0; j<sub_table_size; j++){
                if(first){
                    j = key%table_size - nth*100;
                    first = false;
                }
                
                time_cost++;
                if(hashtable[nth][j]==key){
                    hashtable[nth][j] = 0;
                    num_of_keys--;
                    k = j;
                    nth2 = nth;
                    j++;
                    while (hashtable[nth][j]) {
                        if(j==sub_table_size){
                            nth++;
                            j = 0;
                        }
                        
                        if(hashtable[nth][j]%table_size<=key%table_size){
                            hashtable[nth][k] = hashtable[nth][j];
                            hashtable[nth][j] = 0;
                            k=j;
                            nth2 = nth;
                        }
                        j++;
                    }
                    
                    for(a=0; a<table_size/sub_table_size; a++){
                        if(hashtable[a]){
                            for(b=0; b<sub_table_size; b++){
                                if(hashtable[a][b]) break;
                            }
                            if(b == sub_table_size){
                                delete hashtable[a];
                                hashtable[a] = NULL;
                            }
                        }
                    }
                    return time_cost;
                }
            }
        }
    }
    else if(flag == QUDRATIC_PROBING){
        nth = (key%table_size)/100;
        int i = key%table_size - nth*100;
        
        while (nth<table_size/sub_table_size) {
            for(j=1; j<sub_table_size; j++){
                time_cost++;
                if(hashtable[nth][i]==key){
                    hashtable[nth][i] = 1111111;
                    num_of_keys--;
                }
                
                i += j*j;
                while(i>=sub_table_size){
                    i -= sub_table_size;
                    nth++;
                }
            }
            nth++;
        }
        
        if(nth == table_size/sub_table_size){ // QUDRATIC_PROBING -> LINEAR_PROBING
            for(j=0; j<sub_table_size; j++){
                time_cost++;
                if(hashtable[nth][j]==key){
                    hashtable[nth][j] = 1111111;
                    num_of_keys--;
                }
            }
        }
    }
    
    for(a=0; a<table_size/sub_table_size; a++){
        if(hashtable[a]){
            for(b=0; b<sub_table_size; b++){
                if(hashtable[a][b]) break;
            }
            if(b == sub_table_size){
                delete hashtable[a];
                hashtable[a] = NULL;
            }
        }
    }
    return time_cost;
}

int HierarchyHash::Search(const unsigned int key)
{
	// Write your code
    int time_cost = 0, nth, i, j;
    bool first = true, flag_in = false;
    
    if(flag == LINEAR_PROBING){
        nth = (key%table_size)/100;
        while(true){
            for(i=0; i<sub_table_size; i++){
                if(first){
                    i = key%table_size-nth*100;
                    first = false;
                }
                time_cost++;
                if(!hashtable[nth] || hashtable[nth][i]==0) return time_cost;
                if(hashtable[nth][i]==key){
                    return time_cost;
                }
            }
            nth++;
            if(nth == table_size/sub_table_size) nth = 0;
        }
    }
    else if(flag == QUDRATIC_PROBING){
        nth = (key%table_size)/100;
        int i = key%table_size - nth*100;
        
        while (nth<table_size/sub_table_size){
            for(j=1; j<sub_table_size; j++){
                time_cost++;
                if(hashtable[nth][i]==key){
                    flag_in = true;
                    break;
                }
                
                i += j*j - (j-1)*(j-1);
                while(i>=sub_table_size){
                    i -= sub_table_size;
                    nth++;
                }
            }
            if(flag_in) break;
            nth++;
        }
        
        if(nth == table_size/sub_table_size){ // QUDRATIC_PROBING -> LINEAR_PROBING
            nth = (key%table_size)/100;
            for(j=0; j<sub_table_size; j++){
                time_cost++;
                if(hashtable[nth][j]==key) break;
                if(nth == table_size/sub_table_size) nth = 0;
            }
        }
    }
    
    return time_cost;
}


void HierarchyHash::ClearTombstones()
{
    // Write your code
    unsigned int** temp;
    unsigned int** new_hashtable = new unsigned int*[table_size/sub_table_size]{NULL};
    int i, j;
    
    temp = hashtable;
    hashtable = new_hashtable;
    
    for(i=0; i<table_size/sub_table_size; i++){
        if(temp[i]){
            for(j=0; j<sub_table_size; j++){
                if(temp[i][j] && temp[i][j]!=1111111) this->Insert(temp[i][j]);
            }
        }
    }
    
    delete temp;
}

void HierarchyHash::Print()
{
	// Print valid key pair for each sub hash table - subtable_id:[index1:key1,index2:key2]
	// Seperate each sub table by endl
	// e.g., 0:[1:3,3:7,5:1]
	//       1:[101:2,192:10]
	//       9:[902:90,938:82]

	// Write your code
    bool first = true;
    
    for(int i=0; i<table_size/sub_table_size; i++){
        if(hashtable[i]){
            std::cout << i << ":[";
            for(int k=0; k<sub_table_size; k++){
                if(hashtable[i][k] && hashtable[i][k]!=1111111){
                    if(!first) std::cout << ",";
                    std::cout << k+i*100 << ":" << hashtable[i][k];
                    first = false;
                }
            }
            std::cout << "]" << std::endl;
            first = true;
        }
    }


}

#endif
