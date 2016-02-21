#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

//BTree, insert的时候，先放进叶子，满了就平均拆， 
// 拆完如果影响了上层（node数量超过限制），则先画node（例如，1-3 变成 1 - 2 -2, 画的时候不考虑nonLeaf上的数字，画好之后再看，
//再找右方最小leaf来确定nonleaf node上的数字 这样会比较方便。