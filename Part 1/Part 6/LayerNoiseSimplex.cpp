#include "LayerNoiseSimplex.h"
constexpr fp MAX_NOISE_OUTPUT = 1;
constexpr fp NOISE_MULT = 1.0f / MAX_NOISE_OUTPUT;//multiply output by this to map from -1 to 1
LayerNoiseSimplex::LayerNoiseSimplex(uint seed, fp* OctaveWeights, const int Octaves, fp min, fp max, fp Frequency)
{
	fp TotalWeight = 0;
	BaseNoise = new SimplexNoise(seed);//initialize base noise
	//sum weights
	for (int i = 0; i < Octaves; i++)
	{
		TotalWeight += OctaveWeights[i];
	}

	//map weights
	fp mid = (min + max) * .5f;
	this->OutputPlus = mid;
	fp amplitude = max - mid;
	fp mult = amplitude * NOISE_MULT / TotalWeight;
	for (int i = 0; i < Octaves; i++)
	{
		OctaveWeights[i] *= mult;
	}
	this->Octaves = Octaves;
	this->OctaveWeights = OctaveWeights;
	this->Frequency = Frequency;
}

fp* LayerNoiseSimplex::Evaluate(int X, int Y, const int w, const int l)
{
	const int size = w * l;
	fp* OutputValues = new fp[size];
	fp* ptr = OutputValues;
	int EndX = X + w;
	int EndY = Y + l;
	for (int aY = Y; aY < EndY; aY++)
	{
		for (int aX = X; aX < EndX; aX++)
		{
			fp val = OutputPlus;
			fp freq = Frequency;
			for (int i = 0; i < Octaves; i++)
			{
				val += OctaveWeights[i] * BaseNoise->noise2(aX * freq, aY * freq);
				freq *= 2.0f;
			}
			*ptr++ = val;
		}
	}
	return OutputValues;
}
fp LayerNoiseSimplex::Evaluate(int aX, int aY)
{
	fp val = OutputPlus;
	fp freq = Frequency;
	for (int i = 0; i < Octaves; i++)
	{
		val += OctaveWeights[i] * BaseNoise->noise2(aX * freq, aY * freq );
		freq *= 2.0f;
	}
	return val;
}