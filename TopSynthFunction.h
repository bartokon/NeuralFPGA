
#ifndef TopSynthFunction_
#define TopSynthFunction_
#include <iostream>

#include "ap_fixed.h"

typedef float dataType;
typedef float ioDataType;
#define inputsize 2
#define outputsize 2
#define neuronamout 2
void TopFun(ioDataType inputData[inputsize], ioDataType outputData[outputsize], ap_uint<2> instruction);

#endif

