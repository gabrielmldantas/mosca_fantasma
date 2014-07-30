#include "glutil.h"

float *toGLArray(Vector3 *vectors, int vectorsLength, int *resultLength)
{
	float *array = new float[3 * vectorsLength];
	*resultLength = 0;
	for (int i = 0; i < vectorsLength; i++)
	{
		array[(*resultLength)++] = vectors[i].x();
		array[(*resultLength)++] = vectors[i].y();
		array[(*resultLength)++] = vectors[i].z();
	}
	return array;
}