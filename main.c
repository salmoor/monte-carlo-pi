/**
 * Alemdar Salmoor
 * */
#include "helper.h"
#include <time.h>
#include <stdio.h>

#define H 0.5   /* Horizontal position of the center of the circle */
#define K 0.5   /* Vertical position of the center of the circle */
#define R 0.5   /* Radius of the circle */

float add(float, float);
bool inCircle(float);
float makeShot(float);

int main(int argc, char ** argv){


    //MPI vars
    int size, rank;
    //MPI_Status s;

    //Init
    MPI_Init(&argc, &argv);

    //Start the timer
    double startTime, endTime;
    startTime = MPI_Wtime();
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int numberOfExperiments = atoi(argv[1]);
    

    float * experiments = malloc(numberOfExperiments * sizeof(float));
    srand(time(NULL) + rank);
    experiments = MPI_Map_Func(experiments, numberOfExperiments, &makeShot);
    
    
    float * hits = MPI_Filter_Func(experiments, numberOfExperiments, &inCircle);
    float hitSum = MPI_Fold_Func(hits, numberOfExperiments, 0, &add);
    float hitRatio = hitSum/numberOfExperiments;
    float PI = hitRatio * 4.0;

    
    
    endTime = MPI_Wtime();
    double elapsedTime = endTime - startTime;
    elapsedTime = elapsedTime * 1000.0;

    if (rank == 0)
    {
        printf("PI approximation with %d nodes and %d experiments: %f, Elapsed Time: %lf ms\n", size, numberOfExperiments, PI, elapsedTime);
    }     


    MPI_Finalize();
    return 0;
}

float add(float n1, float n2){ return n1 + n2; }

bool inCircle(float num){ return (num <= R * R) ? true : false; }

float makeShot(float init){

    float x = (float) rand() / (float) RAND_MAX;
    float y = (float) rand() / (float) RAND_MAX;

    return (x-H)*(x-H) + (y-K)*(y-K);

}