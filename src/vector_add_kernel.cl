




typedef struct s_arr
{
	int			a1;
	int			b1;
	int			c1;
}				t_arr;


__kernel void vector_add(__global const int *A, __global const int *B, __global int *C, t_arr ARR)
{
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 
    // Do the operation
    C[i] = A[i] + B[i];
	printf("%d\n", ARR.a1);
}