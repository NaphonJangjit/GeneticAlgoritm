#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ROWS 4
#define COLS 4

void copyArray(int arr[][COLS],int arr2[][COLS]){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            arr2[i][j] = arr[i][j];
        }
    }
}

void copyArray2(int arr[ROWS],int arr2[ROWS]){
    for(int i = 0; i < ROWS; i++){
        arr2[i] = arr[i];
    }
}

void printIndividuals(int individuals[][COLS], int rows){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < COLS; j++){
            printf("%d," ,individuals[i][j]);
        }
        printf("\n");
    }
}

void findF_obj(int absa[4], int individuals[][4] ,int a, int b, int c, int d, int answer, int *zeroPosition){
    for(int i = 0; i < 4; i++){
        absa[i] = abs(individuals[i][0] * a + individuals[i][1] * b + individuals[i][2] * c + individuals[i][3] * d - answer);
        if(absa[i] == 0){
            *zeroPosition = i;
        }
    }
}

void geneticAlgorithm(int individuals[4][4], int absa[], int product[][4], int answer){
    printf("Setting up\n");
    float fitness[4];
    float totalFitness = 0.0;
    for(int i = 0; i < 4; i++){
        fitness[i] = 1.0/(1.0+absa[i]);
        totalFitness += fitness[i];
    }
    float p[4];
    for(int i = 0; i < 4; i++){
        p[i] = fitness[i]/totalFitness;
    }
    
    float C[4];
    C[0] = p[0];
    for(int i = 1; i < 4; i++){
        C[i] = p[i] + C[i-1];
    }
    float R[4];
    for(int i = 0; i < 4; i++){
        double randed = (double) rand() / RAND_MAX;
        R[i] = randed;
    }

    int selection[4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(R[i] <= C[j]){
                selection[i] = j;
                break;
            }
        }
    }
    printf("Select\n");
    int nIndividuals[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            nIndividuals[i][j] = individuals[selection[i]][j];
        }
    }

    //Corss Over
    printf("Corssing Over\n");
    float crossOVRate = .3;
    int CRate[4];
    int it = 0;
    for(int i = 0; i < 4; i++){
        double rate = (double) rand() / RAND_MAX;
        if(rate < crossOVRate){
            CRate[i] = 1;
            it++;
        }else {
            CRate[i] = 0;
        }
    }
    int CorssPosition[it];
    for(int i = 0; i < it; i++){
        CorssPosition[i] = rand() % 3 + 1; //1-3
    }
    int nnIndividuals[4][4];
    int iteration = 0;
    for(int i = 0; i < 4; i++){
        if (CRate[i] == 1) {
            int chromosome1[4];
            copyArray2(nIndividuals[i], chromosome1);
            int chromosome2[4];
            if ((i + 1) == 4) {
                copyArray2(nIndividuals[0], chromosome2);
            } else {
                copyArray2(nIndividuals[i + 1], chromosome2);
            }
            for (int j = 0; j < CorssPosition[iteration]; j++) { //3
                nnIndividuals[i][j] = chromosome1[j];
            }
            for (int j = CorssPosition[iteration]; j < 4; j++) { //3->4
                nnIndividuals[i][j] = chromosome2[j];
            }
            iteration++;
        } else {
            for (int j = 0; j < 4; j++) {
                nnIndividuals[i][j] = nIndividuals[i][j];
            }
        }
    }
    //end of cross over
    printf("\n");
    //mutation
    printf("Mutating\n");
    float mutationRate = 0.5;
    int totalGene = ROWS*COLS;
    int toMutate = totalGene*mutationRate;

    for(int i = 0; i < toMutate; i++){
        int x = rand() % 4;
        int y = rand() % 4;
        int result = rand() % answer + 1;
        nnIndividuals[x][y] = result;
    }
    copyArray(nnIndividuals, product);
}

void start(int a, int b, int c, int d, int answer){
    int individuals[4][4];
    srand((unsigned)time(NULL));
    for(int i = 0; i < 4; i++){
         for(int j = 0; j < 4; j++){
            individuals[i][j] = rand() % abs(answer) + 1;
         }
    }
    int zeroPosition = -1;
    int product[4][4] = {0};
    int attemp = 0;
    do{
        printf("Attemps: %d\n", ++attemp);
        int absa[4];
        printf("Finding F_obj\n");
        findF_obj(absa, individuals, a, b, c, d, answer, &zeroPosition);
        geneticAlgorithm(individuals, absa, product, answer);
        copyArray(product, individuals);
        findF_obj(absa, individuals, a, b, c, d, answer, &zeroPosition);
    }while (zeroPosition < 0);
    printf("Final answer: \n");
    for(int i = 0; i < 4; i++){
        printf("%d ", product[zeroPosition][i]);
    }
}



int main(){
    int a,b,c,d,answer;
    printf("Input Coefficients: \n");
    printf("    A: ");
    scanf("%d", &a);
    printf("    B: ");
    scanf("%d", &b);
    printf("    C: ");
    scanf("%d", &c);
    printf("    D: ");
    scanf("%d", &d);
    printf("Answer: ");
    scanf("%d", &answer);
    start(a,b,c,d,answer);
    return 0;
}




