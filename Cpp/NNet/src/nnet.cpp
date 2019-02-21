#include "nnet.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

/* Set of colors for printf */
#define RED     "\033[31m"
#define RESET   "\033[0m"


void exit_error(const char *message, const char *function){
    fprintf(stderr, RED"%s in %s"RESET, message, function);
    exit(EXIT_FAILURE);
}

/*
===================================================================================
                                    PRIVATE
===================================================================================
*/

inline double sigmoid(double x){
    return 1 / (1 + exp(-x));
}

void computeSynapse(double& synapse, unsigned int layer, unsigned int index){

}


/*
===================================================================================
                                    PUBLIC
===================================================================================
*/

/* Constructors and Destructors */

NNet::NNet(char *weight_file){

}

NNet::NNet(const unsigned int inputLenght,
           const unsigned int outputLength,
           const unsigned int synapsesLayerLength,
           const unsigned int synapsesLayerAmount){
    _inputLenght         = inputLenght;
    _outputLength        = outputLength;
    _synapsesLayerLength = synapsesLayerLength;
    _synapsesLayerAmount = synapsesLayerAmount + 1;  /* add output */


    unsigned int i;
    unsigned int j;
    unsigned int k;
    /* Synapses memory allocation */
    _outputLayer = new double[_outputLength]; /* output layer */
    _synapses    = new double*[_synapsesLayerAmount - 1];
    for (i = 0; i < _synapsesLayerAmount - 1; i++){
        _synapses[i] = new double[_synapsesLayerLength];
    }

    /* Weigths memory allocation */
    _weights = new double**[_synapsesLayerAmount];
    /* Input to layer 1 */
    _weights[0] = new double*[_synapsesLayerLength];
    for (j = 0; j < _synapsesLayerLength; j++){
        _weights[0][j] = new double[_inputLenght];
        for (k = 0; k < _inputLenght; k++){
            _weights[0][j][k] = (double) rand() / RAND_MAX;
        }
    }
    /* Middle layers */
    for (i = 1; i < _synapsesLayerAmount - 1; i++){
        _weights[i] = new double*[_synapsesLayerLength];
        for (j = 0; j < _synapsesLayerLength; j++){
            _weights[i][j] = new double[_synapsesLayerLength];
            for (k = 0; k < _synapsesLayerLength; k++){
                _weights[i][j][k] = (double) rand() / RAND_MAX;
            }
        }
    }
    /* Last layer to output layer */
    _weights[_synapsesLayerAmount - 1] = new double*[_outputLength];
    for (j = 0; j < _outputLength; j++){
        _weights[_synapsesLayerAmount - 1][j] = new double[_synapsesLayerLength];
        for (k = 0; k < _synapsesLayerLength; k++){
            _weights[_synapsesLayerAmount - 1][j][k] = (double) rand() / RAND_MAX;
        }
    }
}

NNet::~NNet(){
    unsigned int i;
    unsigned int j;
    /* Freeing synapses */
    for (i = 0; i < _synapsesLayerAmount - 1; i++){
       delete[] _synapses[i];
    }
    delete[] _synapses;
    delete[] _outputLayer;

    /* Freeing weigths */
    for (i = 0; i < _synapsesLayerAmount; i++){
        for (j = 0; j < _synapsesLayerLength; j++){
            delete[] _weights[i][j];
        }
        delete[] _weights[i];
    }
    delete[] _weights;
}

/* Public methods */ 