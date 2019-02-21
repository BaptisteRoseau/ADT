#ifndef NNET_HPP
#define NNET_HPP

#include <cstdio>
#include <vector>
 
#define DEFAULT_LAYERLENGTH 32
#define DEFAULT_LAYERAMOUNT 2

class NNet {
    private:
        FILE *_weigthFile = NULL;
        unsigned int _inputLenght;
        unsigned int _outputLength;
        unsigned int _synapsesLayerLength;
        unsigned int _synapsesLayerAmount;
        
        double ***_weights;
        double **_synapses;
        double *_outputLayer;

        /**
         * @brief Sigmoid function to bring back real number to [0, 1]
         * 
         * @param x The real number to bring back to [0, 1]
         * @return double The output value, in [0, 1]
         */
        inline double sigmoid(double x);

        void computeSynapse(double& synapse, unsigned int layer);

    public:
        /**
         * @brief Open an existing Neural Network from a .json file.
         * 
         * @param weight_file Path to a .json file containing Neural Network weigths.
         */
        NNet(char *weight_file);
        /**
         * @brief Construct a new NNet object
         * 
         * @param inputLenght The length of the input array (ex: 1920*1080 for a picture)
         * @param outputLength The length of the output array (ex: 2 for a yes/no output)
         * @param synapsesLayerLength The length of an intermediate layer (32 by default)
         * @param synapsesLayerAmount The amount of intermediate layers (3 by default)
         */
        NNet(const unsigned int inputLenght,
             const unsigned int outputLength,
             const unsigned int synapsesLayerLength,
             const unsigned int synapsesLayerAmount);
        /**
         * @brief Destroy the NNet object
         * 
         */
        ~NNet();
};

#endif // NNET_HPP