{\rtf1\ansi\ansicpg949\cocoartf1671
{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;\f1\fswiss\fcharset0 Helvetica;\f2\fnil\fcharset0 Menlo-Italic;
\f3\fnil\fcharset129 AppleSDGothicNeo-Regular;}
{\colortbl;\red255\green255\blue255;\red244\green255\blue231;\red19\green16\blue18;\red220\green43\blue69;
\red249\green100\blue114;\red255\green255\blue255;\red149\green126\blue241;\red108\green121\blue134;\red214\green255\blue159;
\red252\green186\blue205;\red148\green146\blue226;}
{\*\expandedcolortbl;;\csgenericrgb\c95612\c100000\c90618;\csgenericrgb\c7467\c6325\c7211\c51783;\csgenericrgb\c86375\c16729\c26932;
\csgenericrgb\c97741\c39237\c44644;\csgenericrgb\c100000\c99997\c99999;\csgenericrgb\c58418\c49485\c94528;\csgenericrgb\c42394\c47462\c52518;\csgenericrgb\c83900\c100000\c62158;
\csgenericrgb\c98824\c72798\c80415;\csgenericrgb\c57890\c57072\c88737;}
\paperw11900\paperh16840\margl1440\margr1440\vieww13280\viewh14580\viewkind0
\deftab593
\pard\tx593\pardeftab593\pardirnatural\partightenfactor0

\f0\fs24 \cf2 \cb3 #include \cf4 <iostream>
\f1 \cf0 \

\f0 \cf2 #include \cf4 <stdint.h>
\f1 \cf0 \
\

\f0 \cf2 #define INT2VOIDP(i) (void*)(uintptr_t)(i)
\f1 \cf0 \
\

\f0 \cf5 enum\cf6  overflow_handle \{
\f1 \cf0 \

\f0 \cf6 	LINEAR_PROBING = \cf7 0\cf6 ,
\f1 \cf0 \

\f0 \cf6 	QUDRATIC_PROBING
\f1 \cf0 \

\f0 \cf6 \};
\f1 \cf0 \
\

\f0 \cf5 class\cf6  FlatHash
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf5 private\cf6 :
\f1 \cf0 \

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6 * hashtable;
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Variable for overflow handling
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 enum\cf6  \cf9 overflow_handle\cf6  flag;
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Size of hash table
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6  table_size;
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Nums of keys
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6  num_of_keys;
\f1 \cf0 \
\

\f0 \cf5 public\cf6 :
\f1 \cf0 \

\f0 \cf6 	FlatHash(\cf5 enum\cf6  \cf9 overflow_handle\cf6  _flag);
\f1 \cf0 \
\

\f0 \cf6 	~FlatHash();
\f1 \cf0 \
\

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6  HashFunction(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key) \{ \cf5 return\cf6  key % \cf9 table_size\cf6 ; \}
\f1 \cf0 \
\

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6  GetTableSize() \{ \cf5 return\cf6  \cf9 table_size\cf6 ; \}
\f1 \cf0 \
\

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6  GetNumofKeys() \{ \cf5 return\cf6  \cf9 num_of_keys\cf6 ; \}
\f1 \cf0 \
\

\f0 \cf6 	
\f2\i \cf8 // Return time cost
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 int\cf6  Insert(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \
\

\f0 \cf6 	
\f2\i \cf8 // Remove function in lecture. Return time cost
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 int\cf6  Remove(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \
\

\f0 \cf6 	
\f2\i \cf8 // Return time cost
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 int\cf6  Search(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \
\

\f0 \cf6 	\cf5 void\cf6  Print();
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 void\cf6  ClearTombstones();
\f1 \cf0 \

\f0 \cf6 \};\
\
\cf5 class\cf6  HierarchyHash
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf5 private\cf6 :
\f1 \cf0 \

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6 ** hashtable;
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Variable for overflow handling
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 enum\cf6  \cf9 overflow_handle\cf6  flag;
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Size(range) of full hash table. Initially 1000
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6  table_size;
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Size of subhash table. Fixed by 100
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6  sub_table_size;
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Nums of keys
\f1\i0 \cf0 \

\f0 \cf6 	\cf5 unsigned\cf6  \cf5 int\cf6  num_of_keys;
\f1 \cf0 \
\

\f0 \cf5 public\cf6 :
\f1 \cf0 \

\f0 \cf6     HierarchyHash(\cf5 enum\cf6  \cf9 overflow_handle\cf6  _flag);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     ~HierarchyHash();
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6  HashFunction(\cf5 const\cf6  \cf5 int\cf6  key) \{ \cf5 return\cf6  key % \cf9 table_size\cf6 ; \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6  GetTableSize() \{ \cf5 return\cf6  \cf9 table_size\cf6 ; \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6  GetNumofKeys() \{ \cf5 return\cf6  \cf9 num_of_keys\cf6 ; \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Return the size of allocated sub hash table
\f1\i0 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6  GetAllocatedSize();
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Return time cost
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  Insert(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Return time cost
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  Remove(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Return time cost
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  Search(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Delete tombstomes
\f1\i0 \cf0 \

\f0 \cf6     \cf5 void\cf6  ClearTombstones();
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 void\cf6  Print();
\f1 \cf0 \

\f0 \cf6 \};\
\
\cf5 class\cf6  NRKFlat : \cf5 public\cf6  \cf10 FlatHash
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf5 private\cf6 :
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // counter array
\f1\i0 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6 * counters;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf5 public\cf6 :
\f1 \cf0 \

\f0 \cf6     NRKFlat(\cf5 enum\cf6  \cf9 overflow_handle\cf6  _flag);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     ~NRKFlat();
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Hash function
\f1\i0 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6  MurmurHash2(\cf5 const\cf6  \cf5 void\cf6 * key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 void\cf6  GetMMHashValue(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key, \cf5 int\cf6 & h1, \cf5 int\cf6 & h2, \cf5 int\cf6 & h3);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 bool\cf6  Filter(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Overwriting
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  Insert(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Overwriting
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  Remove(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Overwriting
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  Search(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key);
\f1 \cf0 \

\f0 \cf6 \};
\f1 \cf0 \
\

\f0 \cf10 HierarchyHash\cf6 ::HierarchyHash(\cf5 enum\cf6  \cf9 overflow_handle\cf6  _flag)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Initial map size is 1000
\f1\i0 \cf0 \

\f0 \cf6 	\cf9 table_size\cf6  = \cf7 1000\cf6 ;
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Table size is fixed to 100
\f1\i0 \cf0 \

\f0 \cf6 	\cf9 sub_table_size\cf6  = \cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6 	\cf9 flag\cf6  = _flag;
\f1 \cf0 \
\

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf9 hashtable\cf6  = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 *[\cf7 10\cf6 ]\{\cf5 NULL\cf6 \};
\f1 \cf0 \
\

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf10 HierarchyHash\cf6 ::~HierarchyHash()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ; i++) \cf5 if\cf6 (!\cf9 hashtable\cf6 [i]) \cf5 delete\cf6  \cf9 hashtable\cf6 [i];
\f1 \cf0 \

\f0 \cf6     \cf5 delete\cf6  \cf9 hashtable\cf6 ;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 unsigned\cf6  \cf5 int\cf6  \cf10 HierarchyHash\cf6 ::GetAllocatedSize()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  allocated_size = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 /\cf7 100\cf6 ; i++) \cf5 if\cf6 (\cf9 hashtable\cf6 [i]) allocated_size++;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  allocated_size*\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 HierarchyHash\cf6 ::Insert(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  i, j, time_cost=\cf7 0\cf6 , nth;
\f1 \cf0 \

\f0 \cf6     \cf5 bool\cf6  first = \cf5 true\cf6 , flag_in = \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 LINEAR_PROBING\cf6 )\{ 
\f2\i \cf8 // LINEAR_PROBING
\f1\i0 \cf0 \

\f0 \cf6         nth = (key%\cf9 table_size\cf6 )/\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 while\cf6 (\cf5 true\cf6 )\{
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (!\cf9 hashtable\cf6 [nth]) \cf9 hashtable\cf6 [nth] = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 [\cf9 sub_table_size\cf6 ]\{\cf7 0\cf6 \};
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (j=\cf7 0\cf6 ; j<\cf9 sub_table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (first)\{
\f1 \cf0 \

\f0 \cf6                     j=key%\cf9 table_size\cf6 -nth*\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6                     first = \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][j]==\cf7 0\cf6 )\{
\f1 \cf0 \

\f0 \cf6                     \cf9 hashtable\cf6 [nth][j] = key;
\f1 \cf0 \

\f0 \cf6                     \cf9 num_of_keys\cf6 ++;
\f1 \cf0 \

\f0 \cf6                     \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (j!=\cf9 sub_table_size\cf6 ) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6             nth++;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (nth==\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ) nth = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf5 else\cf6  \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 QUDRATIC_PROBING\cf6 )\{ 
\f2\i \cf8 // QUDRATIC_PROBING
\f1\i0 \cf0 \

\f0 \cf6         nth = (key%\cf9 table_size\cf6 )/\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6         i = key%\cf9 table_size\cf6  - nth*\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (j=\cf7 0\cf6 ; j<\cf9 table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (!\cf9 hashtable\cf6 [nth]) \cf9 hashtable\cf6 [nth] = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 [\cf9 sub_table_size\cf6 ]\{\cf7 0\cf6 \};
\f1 \cf0 \

\f0 \cf6             
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (j) i += j*j - (j-\cf7 1\cf6 )*(j-\cf7 1\cf6 );
\f1 \cf0 \

\f0 \cf6             \cf5 while\cf6 (i>=\cf9 sub_table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                 nth++;
\f1 \cf0 \

\f0 \cf6                 i -= \cf9 sub_table_size\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (nth>=\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ) nth = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (!\cf9 hashtable\cf6 [nth]) \cf9 hashtable\cf6 [nth] = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 [\cf9 sub_table_size\cf6 ]\{\cf7 0\cf6 \};
\f1 \cf0 \

\f0 \cf6             time_cost++;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][i]==\cf7 0\cf6  || \cf9 hashtable\cf6 [nth][i]==\cf7 1111111\cf6 )\{
\f1 \cf0 \

\f0 \cf6                 \cf9 hashtable\cf6 [nth][i] = key;
\f1 \cf0 \

\f0 \cf6                 \cf9 num_of_keys\cf6 ++;
\f1 \cf0 \

\f0 \cf6                 \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (j==\cf9 table_size\cf6 )\{ 
\f2\i \cf8 // QUDRATIC_PROBING -> LINEAR_PROBING
\f1\i0 \cf0 \

\f0 \cf6             first = \cf5 true\cf6 ;
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (i=(key%\cf9 table_size\cf6 )/\cf7 100\cf6 ; i<\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6                 \cf5 for\cf6 (j=\cf7 0\cf6 ; j<\cf9 sub_table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                     \cf5 if\cf6 (first)\{
\f1 \cf0 \

\f0 \cf6                         j = key%\cf9 table_size\cf6  - nth*\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6                         first = \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6                     \}
\f1 \cf0 \

\f0 \cf6                     
\f1 \cf0 \

\f0 \cf6                     
\f1 \cf0 \

\f0 \cf6                     \cf5 if\cf6 (!\cf9 hashtable\cf6 [i]) \cf9 hashtable\cf6 [nth] = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 [\cf9 sub_table_size\cf6 ]\{\cf7 0\cf6 \};
\f1 \cf0 \

\f0 \cf6                     \cf5 if\cf6 (\cf9 hashtable\cf6 [i][j]==\cf7 0\cf6  || \cf9 hashtable\cf6 [i][j]==\cf7 1111111\cf6 )\{
\f1 \cf0 \

\f0 \cf6                         \cf9 hashtable\cf6 [i][j] = key;
\f1 \cf0 \

\f0 \cf6                         \cf9 num_of_keys\cf6 ++;
\f1 \cf0 \

\f0 \cf6                         flag_in = \cf5 true\cf6 ;
\f1 \cf0 \

\f0 \cf6                         \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6                     \}
\f1 \cf0 \

\f0 \cf6                     time_cost++;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (flag_in) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (nth == \cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ) nth = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 num_of_keys\cf6  >= \cf7 0.8\cf6  * \cf9 table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6         \cf5 unsigned\cf6  \cf5 int\cf6 ** new_hashtable = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 *[\cf9 table_size\cf6 *\cf7 2\cf6 /\cf9 sub_table_size\cf6 ]\{\cf5 NULL\cf6 \};
\f1 \cf0 \

\f0 \cf6         \cf9 table_size\cf6  *= \cf7 2\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 unsigned\cf6  \cf5 int\cf6 ** temp = \cf9 hashtable\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf9 hashtable\cf6  = new_hashtable;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf9 num_of_keys\cf6  = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 /\cf7 2\cf6 /\cf9 sub_table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (temp[i])\{
\f1 \cf0 \

\f0 \cf6                 \cf5 for\cf6 (\cf5 int\cf6  k=\cf7 0\cf6 ; k<\cf9 sub_table_size\cf6 ; k++)\{
\f1 \cf0 \

\f0 \cf6                     \cf5 if\cf6 (temp[i][k] && temp[i][k]!=\cf7 1111111\cf6 ) time_cost += \cf5 this\cf6 ->\cf10 Insert\cf6 (temp[i][k]);
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 /\cf7 2\cf6 /\cf9 sub_table_size\cf6 ; i++) \cf5 if\cf6 (!temp[i]) \cf5 delete\cf6  temp[i];
\f1 \cf0 \

\f0 \cf6         \cf5 delete\cf6  temp;
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 HierarchyHash\cf6 ::Remove(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  time_cost = \cf7 0\cf6 , nth, nth2, j, k, a, b;
\f1 \cf0 \

\f0 \cf6     \cf5 bool\cf6  first = \cf5 true\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 LINEAR_PROBING\cf6 )\{
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (nth = (key%\cf9 table_size\cf6 )/\cf7 100\cf6 ; nth<=\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ; nth++)\{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (j=\cf7 0\cf6 ; j<\cf9 sub_table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (first)\{
\f1 \cf0 \

\f0 \cf6                     j = key%\cf9 table_size\cf6  - nth*\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6                     first = \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6                 
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][j]==key)\{
\f1 \cf0 \

\f0 \cf6                     \cf9 hashtable\cf6 [nth][j] = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6                     \cf9 num_of_keys\cf6 --;
\f1 \cf0 \

\f0 \cf6                     k = j;
\f1 \cf0 \

\f0 \cf6                     nth2 = nth;
\f1 \cf0 \

\f0 \cf6                     j++;
\f1 \cf0 \

\f0 \cf6                     \cf5 while\cf6  (\cf9 hashtable\cf6 [nth][j]) \{
\f1 \cf0 \

\f0 \cf6                         \cf5 if\cf6 (j==\cf9 sub_table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                             nth++;
\f1 \cf0 \

\f0 \cf6                             j = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6                         \}
\f1 \cf0 \

\f0 \cf6                         
\f1 \cf0 \

\f0 \cf6                         \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][j]%\cf9 table_size\cf6 <=key%\cf9 table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                             \cf9 hashtable\cf6 [nth][k] = \cf9 hashtable\cf6 [nth][j];
\f1 \cf0 \

\f0 \cf6                             \cf9 hashtable\cf6 [nth][j] = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6                             k=j;
\f1 \cf0 \

\f0 \cf6                             nth2 = nth;
\f1 \cf0 \

\f0 \cf6                         \}
\f1 \cf0 \

\f0 \cf6                         j++;
\f1 \cf0 \

\f0 \cf6                     \}
\f1 \cf0 \

\f0 \cf6                     
\f1 \cf0 \

\f0 \cf6                     \cf5 for\cf6 (a=\cf7 0\cf6 ; a<\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ; a++)\{
\f1 \cf0 \

\f0 \cf6                         \cf5 if\cf6 (\cf9 hashtable\cf6 [a])\{
\f1 \cf0 \

\f0 \cf6                             \cf5 for\cf6 (b=\cf7 0\cf6 ; b<\cf9 sub_table_size\cf6 ; b++)\{
\f1 \cf0 \

\f0 \cf6                                 \cf5 if\cf6 (\cf9 hashtable\cf6 [a][b]) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6                             \}
\f1 \cf0 \

\f0 \cf6                             \cf5 if\cf6 (b == \cf9 sub_table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                                 \cf5 delete\cf6  \cf9 hashtable\cf6 [a];
\f1 \cf0 \

\f0 \cf6                                 \cf9 hashtable\cf6 [a] = \cf5 NULL\cf6 ;
\f1 \cf0 \

\f0 \cf6                             \}
\f1 \cf0 \

\f0 \cf6                         \}
\f1 \cf0 \

\f0 \cf6                     \}
\f1 \cf0 \

\f0 \cf6                     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf5 else\cf6  \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 QUDRATIC_PROBING\cf6 )\{
\f1 \cf0 \

\f0 \cf6         nth = (key%\cf9 table_size\cf6 )/\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 int\cf6  i = key%\cf9 table_size\cf6  - nth*\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 while\cf6  (nth<\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ) \{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (j=\cf7 1\cf6 ; j<\cf9 sub_table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][i]==key)\{
\f1 \cf0 \

\f0 \cf6                     \cf9 hashtable\cf6 [nth][i] = \cf7 1111111\cf6 ;
\f1 \cf0 \

\f0 \cf6                     \cf9 num_of_keys\cf6 --;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6                 
\f1 \cf0 \

\f0 \cf6                 i += j*j;
\f1 \cf0 \

\f0 \cf6                 \cf5 while\cf6 (i>=\cf9 sub_table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                     i -= \cf9 sub_table_size\cf6 ;
\f1 \cf0 \

\f0 \cf6                     nth++;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             nth++;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (nth == \cf9 table_size\cf6 /\cf9 sub_table_size\cf6 )\{ 
\f2\i \cf8 // QUDRATIC_PROBING -> LINEAR_PROBING
\f1\i0 \cf0 \

\f0 \cf6             \cf5 for\cf6 (j=\cf7 0\cf6 ; j<\cf9 sub_table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][j]==key)\{
\f1 \cf0 \

\f0 \cf6                     \cf9 hashtable\cf6 [nth][j] = \cf7 1111111\cf6 ;
\f1 \cf0 \

\f0 \cf6                     \cf9 num_of_keys\cf6 --;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 for\cf6 (a=\cf7 0\cf6 ; a<\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ; a++)\{
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (\cf9 hashtable\cf6 [a])\{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (b=\cf7 0\cf6 ; b<\cf9 sub_table_size\cf6 ; b++)\{
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [a][b]) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (b == \cf9 sub_table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                 \cf5 delete\cf6  \cf9 hashtable\cf6 [a];
\f1 \cf0 \

\f0 \cf6                 \cf9 hashtable\cf6 [a] = \cf5 NULL\cf6 ;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 HierarchyHash\cf6 ::Search(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  time_cost = \cf7 0\cf6 , nth, i, j;
\f1 \cf0 \

\f0 \cf6     \cf5 bool\cf6  first = \cf5 true\cf6 , flag_in = \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 LINEAR_PROBING\cf6 )\{
\f1 \cf0 \

\f0 \cf6         nth = (key%\cf9 table_size\cf6 )/\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 while\cf6 (\cf5 true\cf6 )\{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (i=\cf7 0\cf6 ; i<\cf9 sub_table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (first)\{
\f1 \cf0 \

\f0 \cf6                     i = key%\cf9 table_size\cf6 -nth*\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6                     first = \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (!\cf9 hashtable\cf6 [nth] || \cf9 hashtable\cf6 [nth][i]==\cf7 0\cf6 ) \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][i]==key)\{
\f1 \cf0 \

\f0 \cf6                     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             nth++;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (nth == \cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ) nth = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf5 else\cf6  \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 QUDRATIC_PROBING\cf6 )\{
\f1 \cf0 \

\f0 \cf6         nth = (key%\cf9 table_size\cf6 )/\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 int\cf6  i = key%\cf9 table_size\cf6  - nth*\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 while\cf6  (nth<\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (j=\cf7 1\cf6 ; j<\cf9 sub_table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][i]==key)\{
\f1 \cf0 \

\f0 \cf6                     flag_in = \cf5 true\cf6 ;
\f1 \cf0 \

\f0 \cf6                     \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6                 
\f1 \cf0 \

\f0 \cf6                 i += j*j - (j-\cf7 1\cf6 )*(j-\cf7 1\cf6 );
\f1 \cf0 \

\f0 \cf6                 \cf5 while\cf6 (i>=\cf9 sub_table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                     i -= \cf9 sub_table_size\cf6 ;
\f1 \cf0 \

\f0 \cf6                     nth++;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (flag_in) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6             nth++;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (nth == \cf9 table_size\cf6 /\cf9 sub_table_size\cf6 )\{ 
\f2\i \cf8 // QUDRATIC_PROBING -> LINEAR_PROBING
\f1\i0 \cf0 \

\f0 \cf6             nth = (key%\cf9 table_size\cf6 )/\cf7 100\cf6 ;
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (j=\cf7 0\cf6 ; j<\cf9 sub_table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [nth][j]==key) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (nth == \cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ) nth = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\
\

\f0 \cf5 void\cf6  \cf10 HierarchyHash\cf6 ::ClearTombstones()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6 ** temp;
\f1 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6 ** new_hashtable = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 *[\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ]\{\cf5 NULL\cf6 \};
\f1 \cf0 \

\f0 \cf6     \cf5 int\cf6  i, j;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     temp = \cf9 hashtable\cf6 ;
\f1 \cf0 \

\f0 \cf6     \cf9 hashtable\cf6  = new_hashtable;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 for\cf6 (i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (temp[i])\{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (j=\cf7 0\cf6 ; j<\cf9 sub_table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (temp[i][j] && temp[i][j]!=\cf7 1111111\cf6 ) \cf5 this\cf6 ->\cf10 Insert\cf6 (temp[i][j]);
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 delete\cf6  temp;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 void\cf6  \cf10 HierarchyHash\cf6 ::Print()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Print valid key pair for each sub hash table - subtable_id:[index1:key1,index2:key2]
\f1\i0 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Seperate each sub table by endl
\f1\i0 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // e.g., 0:[1:3,3:7,5:1]
\f1\i0 \cf0 \

\f0 \cf6 	
\f2\i \cf8 //       1:[101:2,192:10]
\f1\i0 \cf0 \

\f0 \cf6 	
\f2\i \cf8 //       9:[902:90,938:82]
\f1\i0 \cf0 \
\

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 bool\cf6  first = \cf5 true\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 /\cf9 sub_table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (\cf9 hashtable\cf6 [i])\{
\f1 \cf0 \

\f0 \cf6             \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << i << \cf4 ":["\cf6 ;
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (\cf5 int\cf6  k=\cf7 0\cf6 ; k<\cf9 sub_table_size\cf6 ; k++)\{
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [i][k] && \cf9 hashtable\cf6 [i][k]!=\cf7 1111111\cf6 )\{
\f1 \cf0 \

\f0 \cf6                     \cf5 if\cf6 (!first) \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << \cf4 ","\cf6 ;
\f1 \cf0 \

\f0 \cf6                     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << k+i*\cf7 100\cf6  << \cf4 ":"\cf6  << \cf9 hashtable\cf6 [i][k];
\f1 \cf0 \

\f0 \cf6                     first = \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << \cf4 "]"\cf6  << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;
\f1 \cf0 \

\f0 \cf6             first = \cf5 true\cf6 ;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \
\
\

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf10 FlatHash\cf6 ::FlatHash(\cf5 enum\cf6  \cf9 overflow_handle\cf6  _flag)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Initial table size is 1000	
\f1\i0 \cf0 \

\f0 \cf6 	\cf9 table_size\cf6  = \cf7 1000\cf6 ;
\f1 \cf0 \

\f0 \cf6 	\cf9 num_of_keys\cf6  = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6 	\cf9 flag\cf6  = _flag;
\f1 \cf0 \
\

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf9 hashtable\cf6  = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 [\cf7 1000\cf6 ]\{\cf7 0\cf6 \};
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf10 FlatHash\cf6 ::~FlatHash()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 delete\cf6  \cf9 hashtable\cf6 ;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 FlatHash\cf6 ::Insert(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // You have to implement two overflow handling by using flag
\f1\i0 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  j=\cf7 0\cf6 , time_cost=\cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 LINEAR_PROBING\cf6 )\{ 
\f2\i \cf8 // LINEAR_PROBING
\f1\i0 \cf0 \

\f0 \cf6         time_cost++;
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6  (j=\cf7 0\cf6 ; \cf9 hashtable\cf6 [(key+j)%\cf9 table_size\cf6 ]; j++) time_cost++;
\f1 \cf0 \

\f0 \cf6         \cf9 hashtable\cf6 [(key+j)%\cf9 table_size\cf6 ] = key;
\f1 \cf0 \

\f0 \cf6         \cf9 num_of_keys\cf6 ++;
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf5 else\cf6  \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 QUDRATIC_PROBING\cf6 )\{
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6  (j=\cf7 0\cf6 ; j<\cf9 table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6             time_cost++;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (\cf9 hashtable\cf6 [(key+j*j)%\cf9 table_size\cf6 ] == \cf7 0\cf6  || \cf9 hashtable\cf6 [(key+j*j)%\cf9 table_size\cf6 ] == \cf7 1111111\cf6 ) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (j != \cf9 table_size\cf6 ) \cf9 hashtable\cf6 [(key+j*j)%\cf9 table_size\cf6 ] = key;
\f1 \cf0 \

\f0 \cf6         \cf5 else\cf6 \{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6  (j=\cf7 0\cf6 ; \cf9 hashtable\cf6 [(key+j)%\cf9 table_size\cf6 ] && \cf9 hashtable\cf6 [(key+j)%\cf9 table_size\cf6 ] != \cf7 1111111\cf6 ; j++) time_cost++;
\f1 \cf0 \

\f0 \cf6             \cf9 hashtable\cf6 [(key+j)%\cf9 table_size\cf6 ] = key;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         \cf9 num_of_keys\cf6 ++;
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 num_of_keys\cf6  >= \cf7 0.8\cf6  * \cf9 table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6         \cf5 int\cf6  i;
\f1 \cf0 \

\f0 \cf6         \cf5 unsigned\cf6  \cf5 int\cf6 * new_hashtable = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 [(\cf5 int\cf6 )\cf9 table_size\cf6 *\cf7 2\cf6 ]\{\cf7 0\cf6 \};
\f1 \cf0 \

\f0 \cf6         \cf5 unsigned\cf6  \cf5 int\cf6  temp[\cf9 table_size\cf6 ];
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 ; i++) temp[i] = \cf9 hashtable\cf6 [i];
\f1 \cf0 \

\f0 \cf6         \cf5 delete\cf6  \cf9 hashtable\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf9 hashtable\cf6  = new_hashtable;
\f1 \cf0 \

\f0 \cf6         \cf9 num_of_keys\cf6  = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf9 table_size\cf6  *= \cf7 2\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 /\cf7 2\cf6 ; i++) \cf5 if\cf6 (temp[i] && temp[i]!=\cf7 1111111\cf6 ) time_cost += \cf5 this\cf6 ->\cf10 Insert\cf6 (temp[i]);
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 FlatHash\cf6 ::Remove(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  time_cost=\cf7 0\cf6 , i, j, k=\cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 flag\cf6  == \cf9 QUDRATIC_PROBING\cf6 )\{
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6             time_cost++;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (\cf9 hashtable\cf6 [(key+i*i)%\cf9 table_size\cf6  - k*\cf9 table_size\cf6 ] == key)\{
\f1 \cf0 \

\f0 \cf6                 \cf9 hashtable\cf6 [(key+i*i)%\cf9 table_size\cf6  - k*\cf9 table_size\cf6 ] = \cf7 1111111\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \cf9 num_of_keys\cf6 --;
\f1 \cf0 \

\f0 \cf6                 \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (!\cf9 hashtable\cf6 [key%\cf9 table_size\cf6 +i*i]) \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 ((key+i*i)%\cf9 table_size\cf6  - k*\cf9 table_size\cf6  >= \cf9 table_size\cf6 ) k++;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (i==\cf9 table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (j=key%\cf9 table_size\cf6 +\cf7 1\cf6 ; j<\cf9 table_size\cf6 ; j++)\{
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [j]==key)\{
\f1 \cf0 \

\f0 \cf6                     \cf9 hashtable\cf6 [j] = \cf7 1111111\cf6 ;
\f1 \cf0 \

\f0 \cf6                     \cf9 num_of_keys\cf6 --;
\f1 \cf0 \

\f0 \cf6                     \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf5 else\cf6 \{
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (\cf5 int\cf6  i=key%\cf9 table_size\cf6 ; \cf9 hashtable\cf6 [i]; i++)\{
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (\cf9 hashtable\cf6 [i]==key)\{
\f1 \cf0 \

\f0 \cf6                 \cf9 hashtable\cf6 [i] = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6                 
\f1 \cf0 \

\f0 \cf6                 j = i+\cf7 1\cf6 ;
\f1 \cf0 \

\f0 \cf6                 k = i;
\f1 \cf0 \

\f0 \cf6                 \cf5 while\cf6 (\cf9 hashtable\cf6 [j])\{
\f1 \cf0 \

\f0 \cf6                     \cf5 if\cf6 (\cf9 hashtable\cf6 [j]%\cf9 table_size\cf6  <= key%\cf9 table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                         \cf9 hashtable\cf6 [k] = \cf9 hashtable\cf6 [j];
\f1 \cf0 \

\f0 \cf6                         \cf9 hashtable\cf6 [j] = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6                         k = j;
\f1 \cf0 \

\f0 \cf6                     \}
\f1 \cf0 \

\f0 \cf6                     j++;
\f1 \cf0 \

\f0 \cf6                 \}
\f1 \cf0 \

\f0 \cf6                 \cf9 num_of_keys\cf6 --;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6             time_cost++;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (i==\cf9 table_size\cf6 ) i=\cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \
\

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 FlatHash\cf6 ::Search(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  time_cost=\cf7 0\cf6 , i, k=\cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 flag\cf6 ==\cf9 LINEAR_PROBING\cf6 )\{
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (i=key%\cf9 table_size\cf6 ; \cf9 hashtable\cf6 [i]; i++)\{
\f1 \cf0 \

\f0 \cf6             time_cost++;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (\cf9 hashtable\cf6 [i]==key) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (i==\cf9 table_size\cf6 ) i=\cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (\cf9 hashtable\cf6 [i]==\cf7 0\cf6 ) time_cost++;
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf5 else\cf6 \{ 
\f2\i \cf8 // QUDRATIC_PROBING
\f3\i0 \'c0\'cf
\f2\i  
\f3\i0 \'b6\'a7
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6             time_cost++;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (\cf9 hashtable\cf6 [key%\cf9 table_size\cf6 +i*i - k*\cf9 table_size\cf6 ]==key) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (key%\cf9 table_size\cf6 +i*i - k*\cf9 table_size\cf6  >= \cf9 table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6                 k++;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (i==\cf9 table_size\cf6 )\{
\f1 \cf0 \

\f0 \cf6             \cf5 for\cf6 (\cf5 int\cf6  k=key%\cf9 table_size\cf6 +\cf7 1\cf6 ; \cf9 hashtable\cf6 [k]; k++)\{
\f1 \cf0 \

\f0 \cf6                 time_cost++;
\f1 \cf0 \

\f0 \cf6                 \cf5 if\cf6 (\cf9 hashtable\cf6 [k]==key) \cf5 break\cf6 ;
\f1 \cf0 \

\f0 \cf6             \}
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 void\cf6  \cf10 FlatHash\cf6 ::Print()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // Print valid key pair - [index1:key1,index2:key2]
\f1\i0 \cf0 \

\f0 \cf6 	
\f2\i \cf8 // e.g., [1:3,3:7,5:1]
\f1\i0 \cf0 \

\f0 \cf6     \cf5 bool\cf6  comma = \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6 	\cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << \cf4 "["\cf6 ;
\f1 \cf0 \
\

\f0 \cf6 	
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (\cf9 hashtable\cf6 [i] && \cf9 hashtable\cf6 [i]!=\cf7 1111111\cf6 )\{
\f1 \cf0 \

\f0 \cf6             \cf5 if\cf6 (comma) \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << \cf4 ","\cf6 ;
\f1 \cf0 \

\f0 \cf6             \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << i << \cf4 ":"\cf6  << \cf9 hashtable\cf6 [i];
\f1 \cf0 \

\f0 \cf6             comma = \cf5 true\cf6 ;
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \
\

\f0 \cf6 	\cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << \cf4 "]"\cf6  << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 void\cf6  \cf10 FlatHash\cf6 ::ClearTombstones()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6  temp[\cf9 table_size\cf6 ];
\f1 \cf0 \

\f0 \cf6     \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 ; i++) temp[i] = \cf9 hashtable\cf6 [i];
\f1 \cf0 \

\f0 \cf6     \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 ; i++) \cf9 hashtable\cf6 [i] = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 for\cf6 (\cf5 int\cf6  i=\cf7 0\cf6 ; i<\cf9 table_size\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6         \cf5 if\cf6 (temp[i] && temp[i]!=\cf7 1111111\cf6 ) \cf5 this\cf6 ->\cf10 Insert\cf6 (temp[i]);
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf10 NRKFlat\cf6 ::NRKFlat(\cf5 enum\cf6  \cf9 overflow_handle\cf6  _flag) : \cf10 FlatHash\cf6 (_flag)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf9 counters\cf6  = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 [\cf5 this\cf6 ->\cf10 GetTableSize\cf6 ()]\{\cf7 0\cf6 \};
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf10 NRKFlat\cf6 ::~NRKFlat()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 delete\cf6  \cf9 counters\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 unsigned\cf6  \cf5 int\cf6  \cf10 NRKFlat\cf6 ::MurmurHash2(\cf5 const\cf6  \cf5 void\cf6 * key)\{
\f1 \cf0 \

\f0 \cf6     \cf5 int\cf6  len = \cf7 4\cf6 ;
\f1 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6  seed = \cf7 2018\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  m = \cf7 0x5bd1e995\cf6 ;
\f1 \cf0 \

\f0 \cf6     \cf5 const\cf6  \cf5 int\cf6  r = \cf7 24\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 unsigned\cf6  \cf5 int\cf6  h = seed ^ len;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 const\cf6  \cf5 unsigned\cf6  \cf5 char\cf6  * data = (\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 char\cf6  *)key;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 while\cf6 (len >= \cf7 4\cf6 )
\f1 \cf0 \

\f0 \cf6     \{
\f1 \cf0 \

\f0 \cf6         \cf5 unsigned\cf6  \cf5 int\cf6  k = *(\cf5 unsigned\cf6  \cf5 int\cf6  *)data;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         k *= m;
\f1 \cf0 \

\f0 \cf6         k ^= k >> r;
\f1 \cf0 \

\f0 \cf6         k *= m;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         h *= m;
\f1 \cf0 \

\f0 \cf6         h ^= k;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         data += \cf7 4\cf6 ;
\f1 \cf0 \

\f0 \cf6         len -= \cf7 4\cf6 ;
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 switch\cf6 (len)
\f1 \cf0 \

\f0 \cf6     \{
\f1 \cf0 \

\f0 \cf6         \cf5 case\cf6  \cf7 3\cf6 : h ^= data[\cf7 2\cf6 ] << \cf7 16\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 case\cf6  \cf7 2\cf6 : h ^= data[\cf7 1\cf6 ] << \cf7 8\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf5 case\cf6  \cf7 1\cf6 : h ^= data[\cf7 0\cf6 ];
\f1 \cf0 \

\f0 \cf6             h *= m;
\f1 \cf0 \

\f0 \cf6     \};
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     h ^= h >> \cf7 13\cf6 ;
\f1 \cf0 \

\f0 \cf6     h *= m;
\f1 \cf0 \

\f0 \cf6     h ^= h >> \cf7 15\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  h;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 void\cf6  \cf10 NRKFlat\cf6 ::GetMMHashValue(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key, \cf5 int\cf6 & h1, \cf5 int\cf6 & h2, \cf5 int\cf6 & h3)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // You can use h1, h2 and h3 as hashing results which you have to use to decide counter locations
\f1\i0 \cf0 \

\f0 \cf6     h1 = \cf10 MurmurHash2\cf6 (\cf9 INT2VOIDP\cf6 (&key));
\f1 \cf0 \

\f0 \cf6     h2 = \cf10 MurmurHash2\cf6 (\cf9 INT2VOIDP\cf6 (&h1));
\f1 \cf0 \

\f0 \cf6     h3 = \cf10 MurmurHash2\cf6 (\cf9 INT2VOIDP\cf6 (&h2));
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 bool\cf6  \cf10 NRKFlat\cf6 ::Filter(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // You can use h1, h2 and h3 as hashing results which you have to use to decide counter locations
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  h1, h2, h3, s;
\f1 \cf0 \

\f0 \cf6     \cf10 GetMMHashValue\cf6 (key, h1, h2, h3);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     s = \cf5 this\cf6 ->\cf10 GetTableSize\cf6 ();
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (\cf9 counters\cf6 [h1%s] && \cf9 counters\cf6 [h2%s] && \cf9 counters\cf6 [h3%s]) \cf5 return\cf6  \cf5 true\cf6 ;
\f1 \cf0 \

\f0 \cf6     \cf5 else\cf6  \cf5 return\cf6  \cf5 false\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 NRKFlat\cf6 ::Insert(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  time_cost = \cf7 0\cf6 , prev = \cf10 GetTableSize\cf6 (), h1, h2, h3, s, i, k;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     time_cost += \cf10 FlatHash\cf6 ::\cf10 Insert\cf6 (key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf10 GetMMHashValue\cf6 (key, h1, h2, h3);
\f1 \cf0 \

\f0 \cf6     \cf9 counters\cf6 [h1%prev]++;
\f1 \cf0 \

\f0 \cf6     \cf9 counters\cf6 [h2%prev]++;
\f1 \cf0 \

\f0 \cf6     \cf9 counters\cf6 [h3%prev]++;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     s = \cf5 this\cf6 ->\cf10 GetTableSize\cf6 ();
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (prev != s)\{
\f1 \cf0 \

\f0 \cf6         \cf5 unsigned\cf6  \cf5 int\cf6 * new_counters = \cf5 new\cf6  \cf5 unsigned\cf6  \cf5 int\cf6 [\cf5 this\cf6 ->\cf10 GetTableSize\cf6 ()*\cf7 2\cf6 ]\{\cf7 0\cf6 \};
\f1 \cf0 \

\f0 \cf6         \cf5 unsigned\cf6  \cf5 int\cf6 * temp;
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         \cf5 for\cf6 (i=\cf7 0\cf6 ; i<s; i++)\{
\f1 \cf0 \

\f0 \cf6             
\f1 \cf0 \

\f0 \cf6         \}
\f1 \cf0 \

\f0 \cf6         
\f1 \cf0 \

\f0 \cf6         temp = \cf9 counters\cf6 ;
\f1 \cf0 \

\f0 \cf6         \cf9 counters\cf6  = new_counters;
\f1 \cf0 \

\f0 \cf6         \cf5 delete\cf6  temp;
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 NRKFlat\cf6 ::Remove(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  time_cost = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (!(\cf5 this\cf6 ->\cf10 Filter\cf6 (key))) \cf5 return\cf6  \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     time_cost += \cf10 FlatHash\cf6 ::\cf10 Remove\cf6 (key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}
\f1 \cf0 \
\

\f0 \cf5 int\cf6  \cf10 NRKFlat\cf6 ::Search(\cf5 const\cf6  \cf5 unsigned\cf6  \cf5 int\cf6  key)
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Write your code
\f1\i0 \cf0 \

\f0 \cf6     \cf5 int\cf6  time_cost = \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 if\cf6 (!(\cf5 this\cf6 ->\cf10 Filter\cf6 (key))) \cf5 return\cf6  \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6     time_cost += \cf10 FlatHash\cf6 ::\cf10 Search\cf6 (key);
\f1 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  time_cost;
\f1 \cf0 \

\f0 \cf6 \}\
\
\cf5 int\cf6  main()
\f1 \cf0 \

\f0 \cf6 \{
\f1 \cf0 \

\f0 \cf6     \cf10 NRKFlat\cf6  fh(\cf9 LINEAR_PROBING\cf6 );
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << \cf4 "fh, linear probing insert test"\cf6 <<\cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 3\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 7\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 1003\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 2
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 2003\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 3
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 2006\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 3006\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 3
\f1\i0 \cf0 \

\f0 \cf6     fh.\cf10 Print\cf6 ();   
\f2\i \cf8 // [3:3,4:1003,5:2003,6:2006,7:7,8:3006]
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 6\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 4
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 3003\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 8
\f1\i0 \cf0 \

\f0 \cf6     fh.\cf10 Print\cf6 ();   
\f2\i \cf8 // [3:3,4:1003,5:2003,6:2006,7:7,8:3006,9:6,10:3003]
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh.\cf10 Insert\cf6 (\cf7 5003\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 9
\f1\i0 \cf0 \

\f0 \cf6     fh.\cf10 Print\cf6 ();   
\f2\i \cf8 // [3:3,4:1003,5:2003,6:2006,7:7,8:3006,9:6,10:3003,11:5003]
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf10 NRKFlat\cf6  fh1(\cf9 QUDRATIC_PROBING\cf6 );
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh1.\cf10 Insert\cf6 (\cf7 1008\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh1.\cf10 Insert\cf6 (\cf7 8009\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh1.\cf10 Insert\cf6 (\cf7 2001\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh1.\cf10 Insert\cf6 (\cf7 5008\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 3
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh1.\cf10 Insert\cf6 (\cf7 6008\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 4
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh1.\cf10 Insert\cf6 (\cf7 4009\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 2
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh1.\cf10 Insert\cf6 (\cf7 9\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;        
\f2\i \cf8 // 3
\f1\i0 \cf0 \

\f0 \cf6     fh1.\cf10 Print\cf6 ();    
\f2\i \cf8 // [1:2001,8:1008,9:8009,10:4009,12:5008,13:9,17:6008]
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf10 NRKFlat\cf6  fh2(\cf9 QUDRATIC_PROBING\cf6 );
\f1 \cf0 \

\f0 \cf6     \cf5 int\cf6  a = \cf7 1\cf6 ;
\f1 \cf0 \

\f0 \cf6     \cf5 for\cf6 (\cf5 int\cf6  i = \cf7 0\cf6 ; i < \cf7 157\cf6 ; i++)\{
\f1 \cf0 \

\f0 \cf6         fh2.\cf10 Insert\cf6 (a);
\f1 \cf0 \

\f0 \cf6         a+=\cf7 1000\cf6 ;
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh2.\cf10 Insert\cf6 (a+=\cf7 1000\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;  
\f2\i \cf8 // 247
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh2.\cf10 Insert\cf6 (a+=\cf7 1000\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;  
\f2\i \cf8 // 249
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh2.\cf10 Insert\cf6 (a+=\cf7 1000\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;  
\f2\i \cf8 // 1002
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << fh2.\cf10 Insert\cf6 (a+=\cf7 1000\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;  
\f2\i \cf8 // 1003
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf10 NRKFlat\cf6  hh(\cf9 LINEAR_PROBING\cf6 );
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 3\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;         
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 7\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;         
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 103\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;       
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 903\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;       
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 99\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;        
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 1099\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 2
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 98\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;        
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 1098\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 4
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Search\cf6 (\cf7 100\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;       
\f2\i \cf8 // 3
\f1\i0 \cf0 \

\f0 \cf6     hh.\cf10 Print\cf6 ();   
\f2\i \cf8 // 0:[3:3,7:7,98:98,99:99]
\f1\i0 \cf0 \

\f0 \cf6     
\f2\i \cf8 // 1:[100:1099,101:1098,103:103]
\f1\i0 \cf0 \

\f0 \cf6     
\f2\i \cf8 // 9:[903:903]
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Remove\cf6 (\cf7 1099\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 2??
\f1\i0 \cf0 \

\f0 \cf6     hh.\cf10 Print\cf6 ();   
\f2\i \cf8 // 0:[3:3,7:7,98:98,99:99]
\f1\i0 \cf0 \

\f0 \cf6     
\f2\i \cf8 // 1:[100:1098,103:103]
\f1\i0 \cf0 \

\f0 \cf6     
\f2\i \cf8 // 9:[903:903]
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Remove\cf6 (\cf7 1098\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;       
\f2\i \cf8 // 3
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Remove\cf6 (\cf7 103\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;        
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     hh.\cf10 Print\cf6 ();   
\f2\i \cf8 // 0:[3:3,7:7,98:98,99:99]
\f1\i0 \cf0 \

\f0 \cf6     
\f2\i \cf8 // 9:[903:903]
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 Insert\cf6 (\cf7 1903\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;       
\f2\i \cf8 // 2
\f1\i0 \cf0 \

\f0 \cf6     \cf5 for\cf6  (\cf5 int\cf6  i = \cf7 500\cf6 ; i < \cf7 1300\cf6 ; i++)
\f1 \cf0 \

\f0 \cf6     \{
\f1 \cf0 \

\f0 \cf6         hh.\cf10 Insert\cf6 (i);
\f1 \cf0 \

\f0 \cf6     \}
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 GetTableSize\cf6 () << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 2000
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << hh.\cf10 GetNumofKeys\cf6 () << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;     
\f2\i \cf8 // 806
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << \cf4 "nh, linear probing insert test"\cf6 <<\cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;
\f1 \cf0 \
\

\f0 \cf6     \cf10 NRKFlat\cf6  nh(\cf9 QUDRATIC_PROBING\cf6 );
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 3\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 7\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 1003\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 2
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 2003\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 4
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 2006\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 3006\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 3
\f1\i0 \cf0 \

\f0 \cf6     nh.\cf10 Print\cf6 ();   
\f2\i \cf8 // [3:3,4:1003,6:2006,7:7,10:3006,12:2003]
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // True Negative
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Search\cf6 (\cf7 1\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 0
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // Insert for False Positive Example
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 155\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ; 
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 13\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ; 
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Insert\cf6 (\cf7 111\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ; 
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     
\f2\i \cf8 // False Positive
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Search\cf6 (\cf7 1\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     
\f2\i \cf8 // True Positive
\f1\i0 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Search\cf6 (\cf7 2003\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;   
\f2\i \cf8 // 4
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf11 \cb3 std\cf6 \cb3 ::\cf11 \cb3 cout\cf6 \cb3  << nh.\cf10 Remove\cf6 (\cf7 7\cf6 ) << \cf11 \cb3 std\cf6 \cb3 ::\cf9 endl\cf6 ;      
\f2\i \cf8 // 1
\f1\i0 \cf0 \

\f0 \cf6     nh.\cf10 Print\cf6 ();   
\f2\i \cf8 // [3:3,4:1003,6:2006,10:3006,12:2003,13:13,111:111,155:155]
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     nh.\cf10 ClearTombstones\cf6 ();
\f1 \cf0 \

\f0 \cf6     nh.\cf10 Print\cf6 ();   
\f2\i \cf8 // [3:3,4:1003,6:2006,7:3006,12:2003,13:13,111:111,155:155]
\f1\i0 \cf0 \

\f0 \cf6     
\f1 \cf0 \

\f0 \cf6     \cf5 return\cf6  \cf7 0\cf6 ;
\f1 \cf0 \
\

\f0 \cf6 	\cf5 return\cf6  \cf7 0\cf6 ;
\f1 \cf0 \

\f0 \cf6 \}\
\
}