
/*#include "jpg.h"
#include "mnist.h"



int main(int argc, char** argv)
{
    if(argc < 3) {fprintf(stderr, "Please provide two a mnist file\n"); exit(1); }
    string path = argv[1];
		string path_labels = argv[2]

    float** data = read_mnist(path);
	float* labels = read_labels(path-labels);

    for(int i=0; i<60000; i++) {
        printf("%u\n", i, (int)labels[i]);
        save_jpg(data[i], 28, 28, "%u/%04u.jpg", (int)labels[i], i/1000, i%1000);
    }
    return 0;
}
*/

#include "jpg.h"
#include "mnist.h"

float dist(float* v1, float* v2){
	int i;
	float d=0;
	for (i=0; i<784; i++){
		d+= (v1[i]-v2[i])*(v1[i]-v2[i]);
	}
	return d;
}


int main(){
	float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");

    for(int i=0; i<10000; i++) {
		printf("%u\n", i);
		float mind= -1;
		int NN;
		for (int j=0; j<60000; j++){
			float d = dist(test_images[i], images[j]);
			if (d<mind || mind==-1){
				mind = d;
				NN = j;
			}
		}int inference = labels[NN];
		save_jpeg(test_images[i], 28, 28, "%u/%u.jpg", inference, i);
	}
	
    return 0;
}





