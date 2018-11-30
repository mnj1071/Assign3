#ifndef FLATHASH_H
#define FLATHASH_H

#include <iostream>

// Flag(hint) for overflow handling
enum overflow_handle {
	LINEAR_PROBING = 0,
	QUDRATIC_PROBING
};

class FlatHash
{
private:
	unsigned int* hashtable;
	// Variable for overflow handling
	enum overflow_handle flag;
	// Size of hash table
	unsigned int table_size;
	// Nums of keys
	unsigned int num_of_keys;

public:
	FlatHash(enum overflow_handle _flag);

	~FlatHash();

	unsigned int HashFunction(const unsigned int key) { return key % table_size; }

	unsigned int GetTableSize() { return table_size; }

	unsigned int GetNumofKeys() { return num_of_keys; }

	// Return time cost
	int Insert(const unsigned int key);

	// Remove function in lecture. Return time cost
	int Remove(const unsigned int key);

	// Return time cost
	int Search(const unsigned int key);

	void Print();
    
    void ClearTombstones();
};

FlatHash::FlatHash(enum overflow_handle _flag)
{
	// Initial table size is 1000	
	table_size = 1000;
	num_of_keys = 0;
	flag = _flag;

	// Write your code
    hashtable = new unsigned int[1000]{0};
}

FlatHash::~FlatHash()
{
	// Write your code
    delete hashtable;
}

int FlatHash::Insert(const unsigned int key)
{
	// You have to implement two overflow handling by using flag
	// Write your code
    int j=0, time_cost=0;
    
    if(flag == LINEAR_PROBING){ // LINEAR_PROBING
        time_cost++;
        for (j=0; hashtable[(key+j)%table_size]; j++) time_cost++;
        hashtable[(key+j)%table_size] = key;
        num_of_keys++;
    }
    else if(flag == QUDRATIC_PROBING){
        for (j=0; j<table_size; j++){
            time_cost++;
            if(hashtable[(key+j*j)%table_size] == 0 || hashtable[(key+j*j)%table_size] == 1111111) break;
        }
        if(j != table_size) hashtable[(key+j*j)%table_size] = key;
        else{
            for (j=0; hashtable[(key+j)%table_size] && hashtable[(key+j)%table_size] != 1111111; j++) time_cost++;
            hashtable[(key+j)%table_size] = key;
        }
        num_of_keys++;
    }
    
    if(num_of_keys >= 0.8 * table_size){
        int i;
        unsigned int* new_hashtable = new unsigned int[(int)table_size*2]{0};
        unsigned int temp[table_size];
        
        for(i=0; i<table_size; i++) temp[i] = hashtable[i];
        delete hashtable;
        hashtable = new_hashtable;
        num_of_keys = 0;
        table_size *= 2;
        for(int i=0; i<table_size/2; i++) if(temp[i] && temp[i]!=1111111) time_cost += this->Insert(temp[i]);
    }
    
    return time_cost;
}

int FlatHash::Remove(const unsigned int key)
{
	// Write your code
    int time_cost=0, i, j, k=0;
    
    if(flag == QUDRATIC_PROBING){
        for(i=0; i<table_size; i++){
            time_cost++;
            if(hashtable[(key+i*i)%table_size - k*table_size] == key){
                hashtable[(key+i*i)%table_size - k*table_size] = 1111111;
                num_of_keys--;
                break;
            }
            
            if(!hashtable[key%table_size+i*i]) return time_cost;
            if((key+i*i)%table_size - k*table_size >= table_size) k++;
        }
        
        if(i==table_size){
            for(j=key%table_size+1; j<table_size; j++){
                time_cost++;
                if(hashtable[j]==key){
                    hashtable[j] = 1111111;
                    num_of_keys--;
                    break;
                }
            }
        }
    }
    else{
        for(int i=key%table_size; hashtable[i]; i++){
            if(hashtable[i]==key){
                hashtable[i] = 0;
                
                j = i+1;
                k = i;
                while(hashtable[j]){
                    if(hashtable[j]%table_size <= key%table_size){
                        hashtable[k] = hashtable[j];
                        hashtable[j] = 0;
                        k = j;
                    }
                    j++;
                }
                num_of_keys--;
            }
            time_cost++;
            if(i==table_size) i=0;
        }
    }

    return time_cost;
}

int FlatHash::Search(const unsigned int key)
{
	// Write your code
    int time_cost=0, i, k=0;
    
    if(flag==LINEAR_PROBING){
        for(i=key%table_size; hashtable[i]; i++){
            time_cost++;
            if(hashtable[i]==key) break;
        }
        if(i==table_size) i=0;
        if(hashtable[i]==0) time_cost++;
    }
    else{ // QUDRATIC_PROBING일 때
        for(i=0; i<table_size; i++){
            time_cost++;
            if(hashtable[key%table_size+i*i - k*table_size]==key) break;
            if(key%table_size+i*i - k*table_size >= table_size){
                k++;
            }
        }
        if(i==table_size){
            for(int k=key%table_size+1; hashtable[k]; k++){
                time_cost++;
                if(hashtable[k]==key) break;
            }
        }
    }
    
    return time_cost;
}

void FlatHash::Print()
{
	// Print valid key pair - [index1:key1,index2:key2]
	// e.g., [1:3,3:7,5:1]
    bool comma = false;
	std::cout << "[";

	// Write your code
    for(int i=0; i<table_size; i++){
        if(hashtable[i] && hashtable[i]!=1111111){
            if(comma) std::cout << ",";
            std::cout << i << ":" << hashtable[i];
            comma = true;
        }
    }

	std::cout << "]" << std::endl;
}

void FlatHash::ClearTombstones()
{
    unsigned int temp[table_size];
    for(int i=0; i<table_size; i++) temp[i] = hashtable[i];
    for(int i=0; i<table_size; i++) hashtable[i] = 0;
    
    for(int i=0; i<table_size; i++){
        if(temp[i] && temp[i]!=1111111) this->Insert(temp[i]);
    }
}

#endif
