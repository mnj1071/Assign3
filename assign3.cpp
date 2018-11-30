#include <iostream>
#include <stdint.h>

#define INT2VOIDP(i) (void*)(uintptr_t)(i)

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

class NRKFlat : public FlatHash
{
private:
    // counter array
    unsigned int* counters;
    
public:
    NRKFlat(enum overflow_handle _flag);
    
    ~NRKFlat();
    
    // Hash function
    unsigned int MurmurHash2(const void* key);
    
    void GetMMHashValue(const unsigned int key, int& h1, int& h2, int& h3);
    
    bool Filter(const unsigned int key);
    
    // Overwriting
    int Insert(const unsigned int key);
    
    // Overwriting
    int Remove(const unsigned int key);
    
    // Overwriting
    int Search(const unsigned int key);
};

NRKFlat::NRKFlat(enum overflow_handle _flag) : FlatHash(_flag)
{
    // Write your code
    counters = new unsigned int[this->GetTableSize()]{0};
}

NRKFlat::~NRKFlat()
{
    // Write your code
    delete counters;
    
}

unsigned int NRKFlat::MurmurHash2(const void* key){
    int len = 4;
    unsigned int seed = 2018;
    
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    
    unsigned int h = seed ^ len;
    
    const unsigned char * data = (const unsigned char *)key;
    
    while(len >= 4)
    {
        unsigned int k = *(unsigned int *)data;
        
        k *= m;
        k ^= k >> r;
        k *= m;
        
        h *= m;
        h ^= k;
        
        data += 4;
        len -= 4;
    }
    
    switch(len)
    {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
            h *= m;
    };
    
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    
    return h;
}

void NRKFlat::GetMMHashValue(const unsigned int key, int& h1, int& h2, int& h3)
{
    // You can use h1, h2 and h3 as hashing results which you have to use to decide counter locations
    h1 = MurmurHash2(INT2VOIDP(&key));
    h2 = MurmurHash2(INT2VOIDP(&h1));
    h3 = MurmurHash2(INT2VOIDP(&h2));
}

bool NRKFlat::Filter(const unsigned int key)
{
    // You can use h1, h2 and h3 as hashing results which you have to use to decide counter locations
    int h1, h2, h3, s;
    GetMMHashValue(key, h1, h2, h3);
    
    // Write your code
    s = this->GetTableSize();
    if(counters[h1%s] && counters[h2%s] && counters[h3%s]) return true;
    else return false;
    
}

int NRKFlat::Insert(const unsigned int key)
{
    // Write your code
    int time_cost = 0, prev = GetTableSize(), h1, h2, h3, s, i, k;
    
    time_cost += FlatHash::Insert(key);
    
    GetMMHashValue(key, h1, h2, h3);
    counters[h1%prev]++;
    counters[h2%prev]++;
    counters[h3%prev]++;
    
    s = this->GetTableSize();
    if(prev != s){
        unsigned int* new_counters = new unsigned int[this->GetTableSize()*2]{0};
        unsigned int* temp;
        
        for(i=0; i<s; i++){
            
        }
        
        temp = counters;
        counters = new_counters;
        delete temp;
    }
    
    return time_cost;
}

int NRKFlat::Remove(const unsigned int key)
{
    // Write your code
    int time_cost = 0;
    
    if(!(this->Filter(key))) return 0;
    time_cost += FlatHash::Remove(key);
    
    return time_cost;
}

int NRKFlat::Search(const unsigned int key)
{
    // Write your code
    int time_cost = 0;
    
    if(!(this->Filter(key))) return 0;
    time_cost += FlatHash::Search(key);
    
    return time_cost;
}

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

int main()
{
    NRKFlat fh(LINEAR_PROBING);
    std::cout << "fh, linear probing insert test"<<std::endl;
    std::cout << fh.Insert(3) << std::endl;      // 1
    std::cout << fh.Insert(7) << std::endl;      // 1
    std::cout << fh.Insert(1003) << std::endl;     // 2
    std::cout << fh.Insert(2003) << std::endl;   // 3
    std::cout << fh.Insert(2006) << std::endl;   // 1
    std::cout << fh.Insert(3006) << std::endl;   // 3
    fh.Print();   // [3:3,4:1003,5:2003,6:2006,7:7,8:3006]
    std::cout << fh.Insert(6) << std::endl;      // 4
    std::cout << fh.Insert(3003) << std::endl;   // 8
    fh.Print();   // [3:3,4:1003,5:2003,6:2006,7:7,8:3006,9:6,10:3003]
    std::cout << fh.Insert(5003) << std::endl;   // 9
    fh.Print();   // [3:3,4:1003,5:2003,6:2006,7:7,8:3006,9:6,10:3003,11:5003]
    
    NRKFlat fh1(QUDRATIC_PROBING);
    std::cout << fh1.Insert(1008) << std::endl;     // 1
    std::cout << fh1.Insert(8009) << std::endl;     // 1
    std::cout << fh1.Insert(2001) << std::endl;     // 1
    std::cout << fh1.Insert(5008) << std::endl;     // 3
    std::cout << fh1.Insert(6008) << std::endl;     // 4
    std::cout << fh1.Insert(4009) << std::endl;     // 2
    std::cout << fh1.Insert(9) << std::endl;        // 3
    fh1.Print();    // [1:2001,8:1008,9:8009,10:4009,12:5008,13:9,17:6008]
    
    NRKFlat fh2(QUDRATIC_PROBING);
    int a = 1;
    for(int i = 0; i < 157; i++){
        fh2.Insert(a);
        a+=1000;
    }
    std::cout << fh2.Insert(a+=1000) << std::endl;  // 247
    std::cout << fh2.Insert(a+=1000) << std::endl;  // 249
    std::cout << fh2.Insert(a+=1000) << std::endl;  // 1002
    std::cout << fh2.Insert(a+=1000) << std::endl;  // 1003
    
    NRKFlat hh(LINEAR_PROBING);
    std::cout << hh.Insert(3) << std::endl;         // 1
    std::cout << hh.Insert(7) << std::endl;         // 1
    std::cout << hh.Insert(103) << std::endl;       // 1
    std::cout << hh.Insert(903) << std::endl;       // 1
    std::cout << hh.Insert(99) << std::endl;        // 1
    std::cout << hh.Insert(1099) << std::endl;      // 2
    std::cout << hh.Insert(98) << std::endl;        // 1
    std::cout << hh.Insert(1098) << std::endl;      // 4
    std::cout << hh.Search(100) << std::endl;       // 3
    hh.Print();   // 0:[3:3,7:7,98:98,99:99]
    // 1:[100:1099,101:1098,103:103]
    // 9:[903:903]
    
    std::cout << hh.Remove(1099) << std::endl;      // 2??
    hh.Print();   // 0:[3:3,7:7,98:98,99:99]
    // 1:[100:1098,103:103]
    // 9:[903:903]
    
    std::cout << hh.Remove(1098) << std::endl;       // 3
    std::cout << hh.Remove(103) << std::endl;        // 1
    hh.Print();   // 0:[3:3,7:7,98:98,99:99]
    // 9:[903:903]
    
    std::cout << hh.Insert(1903) << std::endl;       // 2
    for (int i = 500; i < 1300; i++)
    {
        hh.Insert(i);
    }
    std::cout << hh.GetTableSize() << std::endl;     // 2000
    std::cout << hh.GetNumofKeys() << std::endl;     // 806
    
    std::cout << "nh, linear probing insert test"<<std::endl;

    NRKFlat nh(QUDRATIC_PROBING);
    std::cout << nh.Insert(3) << std::endl;      // 1
    std::cout << nh.Insert(7) << std::endl;      // 1
    std::cout << nh.Insert(1003) << std::endl;   // 2
    std::cout << nh.Insert(2003) << std::endl;   // 4
    std::cout << nh.Insert(2006) << std::endl;   // 1
    std::cout << nh.Insert(3006) << std::endl;   // 3
    nh.Print();   // [3:3,4:1003,6:2006,7:7,10:3006,12:2003]
    
    // True Negative
    std::cout << nh.Search(1) << std::endl;   // 0
    
    // Insert for False Positive Example
    std::cout << nh.Insert(155) << std::endl; // 1
    std::cout << nh.Insert(13) << std::endl; // 1
    std::cout << nh.Insert(111) << std::endl; // 1
    
    // False Positive
    std::cout << nh.Search(1) << std::endl;   // 1
    // True Positive
    std::cout << nh.Search(2003) << std::endl;   // 4
    
    std::cout << nh.Remove(7) << std::endl;      // 1
    nh.Print();   // [3:3,4:1003,6:2006,10:3006,12:2003,13:13,111:111,155:155]
    
    nh.ClearTombstones();
    nh.Print();   // [3:3,4:1003,6:2006,7:3006,12:2003,13:13,111:111,155:155]
    
    return 0;

	return 0;
}
