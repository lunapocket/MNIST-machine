/**
 * DESC : processing 1 - layered neural network
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mnist-read.h"

#define LEARNING_RATE 0.05

/**
 * neuron that has input, weight and output
 */

typedef struct Neuron{
	uint8_t * inputs; //28*28 inputs
	double * weights;//28*28 weights
	int size;        //28*28
	double output;   //probability of being certain label
}Neuron;

/**
 * Layer has a neurons and intended answer
 */
typedef struct Layer{
	Neuron neurons[10]; //each neural deals with 0~9
	uint8_t label;
}Layer;


/**
 * @DESC: init one neuran, load images to input and make random weights
 */
Neuron * init_neuran(MNIST_setting * setting);

void update_neuron(Neuron * neuron, MNIST_image image);

/**
 * @DESC: init layers
 */
Layer * init_layer(MNIST_setting * setting);

void update_layer(Layer * layer, MNIST_image image);
/**
 * @DESC: calculate output of a neuron, sigmoid(input * weight)
 */
void predict_prob(Neuron * neuron);

void predict_probs(Layer * layer);

/**
 * updates
 * @param layer layer of neuran
 * @with output probs, 
 */
void update_weights(Layer * layer);

/**
 * predict what the actual number of the image
 * @param layer
 * @return int
 */
int predict(Layer * layer);

/**
 * use static rate to check success rate
 * @param  layer check layer
 * @param  init  if initiation, put init = 1 else 0
 * @return       success rate
 */
double calculate_success_rate(Layer * layer, int init);

/**
 * train layers from image sets and get weights
 * @param  setting    setting of an MNIST sets
 * @return            success rate of overall process
 */
double train_layer(MNIST_setting * setting, Layer * layer);

/**
 * test with given layer
 * @param  setting image sets
 * @param  Layer    trained layer
 * @return          success rate of overall process
 */
double test_layer(MNIST_setting * setting, Layer * layer);