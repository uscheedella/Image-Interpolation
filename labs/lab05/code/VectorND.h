#ifndef __VECTORND_H__
#define __VECTORND_H__

typedef struct VectorND_tag {
	float* data;
	int dimension;
} VectorND;

int allocate_VectorND(VectorND *v, int dimension);

int deallocate_VectorND(VectorND *v);

int rand_fill_VectorND(VectorND *v);

int zero_refill_VectorND(VectorND *v);

#endif
