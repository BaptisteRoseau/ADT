#ifndef NNET_HPP
#define NNET_HPP

#include <cstdio>
#include <vector>
 
#define DEFAULT_LAYERSIZE 32
#define DEFAULT_LAYERAMOUNT 3

class NNet {
    private:
        FILE *weigthFile = NULL;
        std::vector<double> weights;
        std::vector<std::vector<double>> synapses;

        double sigmoid(double x);

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
         * @param synapsesLayerSize The length of an intermediate layer (32 by default)
         * @param synapsesLayerAmount The amount of intermediate layers (3 by default)
         */
        NNet(const unsigned int inputLenght,
             const unsigned int outputLength,
             const unsigned int synapsesLayerSize = DEFAULT_LAYERSIZE,
             const unsigned int synapsesLayerAmount = DEFAULT_LAYERAMOUNT);
        /**
         * @brief Destroy the NNet object
         * 
         */
        ~NNet();
};

#endif // NNET_HPP