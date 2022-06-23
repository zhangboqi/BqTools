#include <stdio.h>
#include "BqArray.h"
using namespace bq;
int main() {

	BqArray<int> bqArray(4);
	bqArray.Push(1);
	bqArray.Push(2);
	bqArray.Push(3);
	bqArray.Push(4);
	printf("%d\n", bqArray.Contains(6) );
	return 0;
}