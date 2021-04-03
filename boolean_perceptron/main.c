/**
 * Author: Alexander Beiser
 * Date: 20210403
 * What: Perceptron - creating sample data, training the perceptron and showing output.
 * At first one has to specify which kind of perceptron one wants to create
 * Currently there are two possibilities:
 * -0 is AND
 * -1 is OR
 *
 *  Then the training data is created,
 *  after that the perceptron is initialized,
 *  then the perceptron is trained 
 *  and finally the user can check if it works.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "perceptron.h"

static float alpha = 0.1;


/**
 * Boolean values for input are -1 for false and +1 for true.
 */
int main(int argc, char* argv[]) {
    srand((unsigned int) time(NULL));

    if(argc != 1) {
        fprintf(stderr,"Invalid parameters given, exiting!\n");
        return EXIT_FAILURE;
    }


    fprintf(stdout,"Press 0 for AND, 1 for OR, ANY for discard.\n");
    int choose;
    int n = scanf("%d",&choose);
    if(n < 0) {
        fprintf(stderr,"scanf failed\n");
        return EXIT_FAILURE;
    } else if(choose < 0 || choose > 1) {
        fprintf(stdout,"Shutting down\n");
        return EXIT_SUCCESS;
    }

    //Generating test data.
    int samples = 10000;

    float input1[samples];
    float input2[samples];
    float output[samples];

    /*
     * As sigmoid is 0.5 at x=0,
     * the input values are 0 and 1 (boolean),
     * but the output value is 0.5 (false) and 1 (true).
     *
     * When i do this, I don't have to cope with negative values, etc.
     * and makes everyones life easier :-)
     */
    for(int i = 0; i < samples; i++) {
        input1[i] = (float)(rand()) / (float)(RAND_MAX);
        input2[i] = (float)(rand()) / (float)(RAND_MAX);
        output[i] = (float)(rand()) / (float)(RAND_MAX);

        input1[i] = (input1[i] < 0.5f) ? 0.f : 1.f;
        input2[i] = (input2[i] < 0.5f) ? 0.f : 1.f;
        if(choose == 0) {
            output[i] = (input1[i] == 1.f && input2[i] == 1.f) ? 1 : 0.5f;
        } else if(choose == 1) {
            output[i] = (input1[i] == 1.f || input2[i] == 1.f) ? 1 : 0.5f;
        }
        fprintf(stdout,"I1:%f,I2:%f,O:%f\n",input1[i],input2[i],output[i]);
    }


    //--------INIT PERCEPTRON----------------------
    fprintf(stdout,"Initializing initial weight values.\n");

    Perceptron * perceptron;
    perceptron = malloc(sizeof(float) * 3);
    perceptron->offset = 0;
    for(int i = 0; i < 2; i++) {
        int random = rand();
        perceptron->weights[i] = (float)(random) / (float)(RAND_MAX);
        fprintf(stdout,"%f\n",perceptron->weights[i]);
    }

    //--------TRAIN_PERCEPTRON----------------------------
    fprintf(stdout,"Perceptron pre-training: w1: %f, w2: %f\n",perceptron->weights[0],perceptron->weights[1]);
    
    for(int i = 0; i < samples; i++) {
        float input[2];
        input[0] = input1[i];
        input[1] = input2[i];

        float result = feedForward(input,perceptron);
        trainPerceptron(input,perceptron,output[i],result,alpha);
    }
    fprintf(stdout,"Perceptron post-training: w1: %f, w2: %f\n",perceptron->weights[0],perceptron->weights[1]);


    while(1) {
        fprintf(stdout,"Enter first input 0 and 1 and then the desired output.\n");
        float input[2];
        for(int j = 0; j < 2; j++) {
            scanf("%f",&input[j]);
        }
       
        float result = feedForward(input,perceptron);
        int resultBoolean;
        if(result <= 0.75f) {
            resultBoolean = 0;
        } else {
            resultBoolean = 1;
        }
        fprintf(stdout,"After feed forward: %f\n",result); 
        fprintf(stdout,"So logical value is: %d\n",resultBoolean);
    }

}
