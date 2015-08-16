#include "Random.h"

float Random::valueBetween(float min, float max) {
	return (((float) arc4random() / 0xFFFFFFFFu) * (max - min)) + min;
}
