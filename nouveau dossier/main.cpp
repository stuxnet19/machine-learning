
#include "jpg.h"
#include "mnist.h"


float dist_sq(float* v1, float* v2) {
	float d =0;	
	for (int i=0; i<784; i++){
		d += (v1[i]-v2[i])*(v1[i]-v2[i]);
	}	 
	return d;
}


int main(int argc, char** argv)
{

    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");

    for(int i=0; i<10000; i++) {
		int NN;
		float mind = -1;
        for( int j=0; j<60000; j++) {
			float d = dist_sq(test_images[i], images[j]);
       		 if (d<mind || mind==-1) {
				mind = d;
				NN = j;
	   		 }
		}
		int inference = labels[NN];
		save_jpg(test_images[i], 28, 28, "%u/%u.jpg", inference, i);
   }
	 return 0;
}




