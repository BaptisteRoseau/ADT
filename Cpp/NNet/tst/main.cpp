#include "../src/nnet.h"

int main(){
    NNet n1 = NNet(10, 10, 10, 10);
    NNet *n2 = new NNet(10, 10, 10, 10); 

    delete n2;

    return 0;
}