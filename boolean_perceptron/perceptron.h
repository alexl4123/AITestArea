#ifndef PERCEPTRON
#define PERCEPTRON

#define E_VALUE 2.71828f

typedef struct {
    float offset;
    float weights[2];
} Perceptron;

float feedForward(float input[2],Perceptron * perceptron);
void trainPerceptron(float input[2],Perceptron * perceptron, 
        float desiredOutput, float realOutput, float alpha);
 
#endif /* PERCEPTRON */
