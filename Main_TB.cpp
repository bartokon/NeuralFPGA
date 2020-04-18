#include <iostream>
#include "TopSynthFunction.h"


using namespace std;


int main(){

	float locbuffer[2] = {0.05, 0.10};
	float outputDataa[2] = {50.0};

	TopFun(locbuffer, outputDataa);

	cout << endl;
	cout << "OutputData 1: " << outputDataa[0] << endl;
	cout << "OutputData 2: " << outputDataa[1] << endl;

return 0;
}

