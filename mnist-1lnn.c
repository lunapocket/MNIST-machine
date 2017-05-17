#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "mnist-1lnn.h"



/**
 * @DESC: init one neuran, load images to input and make random weights
 */
Neuron * init_neuron(MNIST_setting * setting, MNIST_image image){
	Neuron * target;
	int i;
	int pixel_threshold = 200;
	
	target = (Neuron * )malloc(sizeof(Neuron));

	target->size = setting->num_cols*setting->num_rows;

	target->inputs = (uint8_t *)malloc(sizeof(uint8_t)*target->size);

	

	(uint8_t *)malloc(sizeof(uint8_t)*setting->num_cols*setting->num_rows);

	target->weights = (double *)malloc(sizeof(double)*target->size);
	
	for (int i = 0; i < target->size; ++i)
	{
		*(target->weights+i) = (double)rand()/(double)RAND_MAX;
		*(target->inputs+i) = *(image.pixel + i) < pixel_threshold ? 0 : 1;
	}

	return target;
}

/**
 * @DESC: init layers with an image
 */
Layer * init_layer(MNIST_setting * setting, const MNIST_image image){
	Layer * target;
	int i = 0;
	
	target = (Layer *)malloc(sizeof(Layer));

	for (i = 0; i < 10; ++i)
	{
		target->neurons[i] = *(init_neuron(setting, image));
	}
	
	target->label = image.label;

	return target;
}

/**
 * @DESC: calculate output of a neuron, sigmoid(input * weight)
 */
void predict_prob(Neuron * neuron){
	int i;
	double sum;

	sum = 0;

	for (i = 0; i < neuron->size; ++i)
	{
		sum += *(neuron->inputs + i) * *(neuron->weights + i);
	}
	
	sum = sum / neuron->size;
	sum = 1/(1+exp(-sum));

	neuron->output = sum;
}

void predict_probs(Layer * layer){
	int i;

	for (int i = 0; i < 10; ++i)
	{
		predict_prob(layer->neurons+i);
		// printf("%lf : %d\n", (layer->neurons+i)->output, i);
	}
}

/**
 * updates
 * @param layer layer of neuran
 * @with output probs, 
 */
void update_weights(Layer * layer){
	int i, j; 
	double error;
	int size = layer->neurons->size;

	for (int i = 0; i < 10; ++i)
	{
		error = (i == layer->label) - layer->neurons[i].output;
		
		for (int j = 0; j < size; ++j)
		{
			*((layer->neurons+i)->weights+j) += LEARNING_RATE * error; 
		}
		// printf("error : %lf : %d \n", error, i);
	}
}

// /**
//  * predict what the actual number of the image
//  * @param layer
//  * @return int
//  */
// int predict(Layer * layer);

// *
//  * use static rate to check success rate
//  * @param  layer check layer
//  * @param  init  if initiation, put init = 1 else 0
//  * @return       success rate
 
// double calculate_success_rate(Layer * layer, int init);

// /**
//  * train layers from image sets and get weights
//  * @param  setting    setting of an MNIST sets
//  * @return             get layer with optimized weights
//  */
// Layer * train_layer(MNIST_settings * setting);

// /**
//  * test with given layer
//  * @param  setting image sets
//  * @param  Layer    trained layer
//  * @return          success rate of overall process
//  */
// double test_layer(MNIST_settings * setting, Layer * layer);









