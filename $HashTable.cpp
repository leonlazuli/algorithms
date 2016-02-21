#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
#include <stack>
#include <queue>
#include <stdexcept>
using namespace std;


// 在用 open addrerssing 的时候要注意，对于某个index，冲突之后，其移动的位置是固定的，
// 并且会在这几个固定的位置中按顺序挪动。 所以当Find的时候，一旦发现了array[newIndex] == NULL
// 那么一定意味着之后的所有挪动位置都为NULL，就可以停止循环了。 并且，记得 ！= NULL的检查也是本来就要的

int index = hash(key);
int newIndex = index;
int i = 1;
while(array[index] != NULL && array[newIndex].key != key)
{
	newindex = index + i * i;
	++i;
}
	