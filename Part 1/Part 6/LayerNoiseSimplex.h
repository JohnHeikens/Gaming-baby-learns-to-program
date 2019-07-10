#pragma once
#include "SimplexNoise.h"//base noise
typedef unsigned int uint;
//#include <glad/glad.h>//typedefs
class LayerNoiseSimplex
{
public:
	LayerNoiseSimplex(uint seed, fp* OctaveWeights, const int Octaves, const fp min, const fp max, const fp Frequency);
	SimplexNoise* BaseNoise;
	int Octaves;
	fp* OctaveWeights;
	fp OutputPlus;//the addition to the output to map it between min and max
	fp Frequency;//the multiplier for the input coordinates
	fp* Evaluate(int X, int Y, int w, int l);
	fp Evaluate(int aX, int aY);
	~LayerNoiseSimplex()
	{
		delete BaseNoise;
		delete[] OctaveWeights;
	}
};