#include "Random.h"
//===============================================================
int Random::valueBetweenInts(int min, int max){
	srand(rand() ^ time(NULL));

	return rand() % (max - min + 1) + min;
}
//===============================================================