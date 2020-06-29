/**
 * Alemdar Salmoor
 * */
#include <stdlib.h>
#include <stdbool.h>

#include "mpi.h"

void computeOffsetAndOperations(int numShots, int node_size, int ** output, int ** offset){

    (*output) = malloc(node_size * sizeof(int));
    (*offset) = malloc(node_size * sizeof(int));

    int experimentsPerEach = numShots/node_size;
    int surplus = numShots % node_size;

    int sumSoFar = 0;

    for (size_t i = 0; i < node_size; i++)
    {
        (*offset)[i] = sumSoFar;

        if(i < surplus)
            (*output)[i] = experimentsPerEach + 1;
        else
            (*output)[i] = experimentsPerEach;

        sumSoFar += (*output)[i];
    }
    
}

float *MPI_Map_Func(float *arr, int size, float (*func)(float)){

    //MPI vars
    int node_size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &node_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int * experimentsPerEach;
    int * offset;
    computeOffsetAndOperations(size, node_size, &experimentsPerEach, &offset);

    float * globalOutput = malloc(size * sizeof(float));
    float * localOutput = malloc(experimentsPerEach[rank] * sizeof(float));

    for (size_t i = 0; i < experimentsPerEach[rank]; i++)
    {
        localOutput[i] = (*func)(arr[offset[rank] + i]);
    }

    MPI_Allgatherv(localOutput, experimentsPerEach[rank], MPI_FLOAT, globalOutput, experimentsPerEach, offset, MPI_FLOAT, MPI_COMM_WORLD);

    return globalOutput;
    
}


float MPI_Fold_Func(float *arr, int size, float intial_value, float (*func)(float, float)){

    //MPI vars
    int node_size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &node_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int * experimentsPerEach;
    int * offset;
    computeOffsetAndOperations(size, node_size, &experimentsPerEach, &offset);

    float * globalOutput = malloc(node_size * sizeof(float));
    float output = intial_value;

    for (size_t i = 0; i < experimentsPerEach[rank]; i++)
    {
        output = (*func)(output, arr[offset[rank] + i]);
    }

    MPI_Allgather(&output, 1, MPI_FLOAT, globalOutput, 1, MPI_FLOAT, MPI_COMM_WORLD);

    output = 0;

    for (size_t i = 0; i < node_size; i++)
    {
        output = (*func)(output, globalOutput[i]);
    }

    return output;

}


float * MPI_Filter_Func(float *arr, int size, bool (*pred)(float)){

    //MPI vars
    int node_size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &node_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int * experimentsPerEach;
    int * offset;
    computeOffsetAndOperations(size, node_size, &experimentsPerEach, &offset);

    float * globalOutput = malloc(size * sizeof(float));
    float * localOutput = malloc(experimentsPerEach[rank] * sizeof(float));

    for (size_t i = 0; i < experimentsPerEach[rank]; i++)
    {
        localOutput[i] = (float) (*pred)(arr[offset[rank] + i]);
    }

    MPI_Allgatherv(localOutput, experimentsPerEach[rank], MPI_FLOAT, globalOutput, experimentsPerEach, offset, MPI_FLOAT, MPI_COMM_WORLD);

    return globalOutput;

}
