#include <math.h>
#include <stdio.h>

#include "perceptron.h"

//-------------------DEFINITIONS-----------------------

static float sumUpInputNodes(float input[2],Perceptron * perceptron);
static float calculateError(float desiredOutput, float realOutput);

static float sigmoid(float x);
static float derivativeSigmoid(float x);

//------------------NORMAL_FUNCTIONS-----------------------

float feedForward(float input[2],Perceptron * perceptron) {

    float sum = sumUpInputNodes(input,perceptron);
    float y = sigmoid(sum);
    
    return y;
}


void trainPerceptron(float input[2],Perceptron * perceptron, 
        float desiredOutput, float realOutput, float alpha){

    float sum = sumUpInputNodes(input,perceptron);
    float error = calculateError(desiredOutput, realOutput);
    float derivative = derivativeSigmoid(sum);

    for(int i = 0; i < 2; i++) {
        perceptron->weights[i] = perceptron->weights[i] + (alpha * error * derivative * input[i]);
    }
}

//-----------------STATIC_FUNCTIONS-----------------------

static float calculateError(float desiredOutput, float realOutput) {
    return (desiredOutput - realOutput);
}

static float sumUpInputNodes(float input[2],Perceptron * perceptron) {
    float sum = perceptron->offset;

    for(int i = 0; i < 2; i++) {
        sum += (input[i] * perceptron->weights[i]);
    }
    return sum;
}

//--------------SIGMOID-----------------

static float sigmoid(float x) {
    return 1/(1+(powf(E_VALUE,-x)));
}

static float derivativeSigmoid(float x) {
    //Special mathematical property of sigmoid.
    return sigmoid(x) * (1 - sigmoid(x));
}


