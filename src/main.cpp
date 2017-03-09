
#include "jpg.h"
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
