#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed


int ind(int x, int y, int z, int n) {
    return (x + n) * (2 * n + 1) * (2 * n + 1) + (y + n) * (2 * n + 1) + (z + n);
	// return (2 * n + 1) * (2 * n + 1) * (2 * n + 1) + x + y + z;
}

void one_particle(int *grid, int n)
{

    int x = 0;
    int y = 0;
    int z = 0;

    for (int i = 0; i < n; i++) {

        int random = rand() % 6;

        if (random == 0) {
            x++; 
        } else if (random == 1) {
            x--;
        } else if (random == 2) {
            y++;
        } else if (random == 3) {
            y--;
        } else if (random == 4) {
            z++;
        } else if (random == 5) {
            z--;
        }
    }
	// int ind = (x + n) * (2 * n + 1) * (2 * n + 1) + (y + n) * (2 * n + 1) + (z + n);
	int idx = ind(x, y, z, n);
	//printf("idx: %d\n", idx);
	grid[idx]++;


}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir

double density(int *grid, int n, double r)
{
    int count = 0;
    int tot = 0;
    double rSquare = (r * n) * (r * n);
	//printf("radius sq = %f\n", rSquare);

    for (int x = -n; x <=n; x++) {
        for (int y = -n; y <= n; y++) {
            for (int z = -n; z <= n; z++) {

                double totaldist = x * x + y * y + z * z;
                
                if (totaldist <= rSquare) {	
                    count = count + grid[ind(x, y, z, n)];
                }
                
                tot = tot + grid[ind(x, y, z, n)];

				//printf("totaldist = %f\n", totaldist);
				//printf("grid at %d = %d\n", ind(x, y, z, n), grid[(x, y, z, n)]);
            }
        }
    }
	//printf("total = %d, count = %d\n", total, count);
    return (double) count / tot;
    
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below

	// int grid;
	int range = (2 * n + 1); 
    int size = range * range * range;
    int *grid = (int*) malloc(size * sizeof(int));



	if (grid == NULL) {
		printf("Memory alloc failed");
		exit(1);
	}

	for(int i = 1; i<=m; i++) {
		one_particle(grid, n);
	}

	print_result(grid, n);
	//fill in some code below

	free(grid);


}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);

	// free(grid);

	return 0;
}
