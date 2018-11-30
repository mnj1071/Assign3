#include "FlatHash.h"
#include "HierarchyHash.h"
#include "NRKFlat.h"

#include <iostream>

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
