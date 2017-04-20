#include "jpg.h"
#include "mnist.h"
#include <limits.h>
#include<math.h>
float linear_classifier(float* w , float* x)
{
        float d=0 ;
        for (int i=0 ; i<784;i++){
                d += w[i]*x[i];
        }
        if(d>=0)return 1 ;
        else return -1 ;
}
/*
float dist(float* v1, float* v2){
        int i;
        float d=0;
        for (i=0; i<784; i++){
                d+= (v1[i]-v2[i])*(v1[i]-v2[i]);
        }
        return d;
}
*/

int main(){
        float** images = read_mnist("train-images.idx3-ubyte");
        float* labels = read_labels("train-labels.idx1-ubyte");
        float** test_images = read_mnist("t10k-images.idx3-ubyte");
        float* test_labels = read_labels("t10k-labels.idx1-ubyte");
        float* w = new float[784];
	float* g = new float[784];

//step 1 : initialisation
	for(int i=0 ; i<784 ; i++)w[i]=(float)rand()*2/INT_MAX-1;
float gamma = 0.01 ;
//step 2 : learning(que les données d'aprentissage')
for(int i=0 ; i<60000 ; i++){
	printf("%u\n",i);
	//calcul du gradient(g = y*x si erreur 0 , sinon)
	int prediction = linear_classifier(w,images[i]);
	//for (int j = 0 ; j<784 ; j++)g[j]=0;
	int verite = (labels[i]==1)?1:-1;
	if(verite!=prediction){
		printf("Erreur\n");
		//w(t+1)=w(t)-gamma*y*x
		for(int j=0 ; j<784;j++){
		w[j]=w[j]+gamma*verite*images[i][j];
		}
	}
	// j'ajoute au x actuelle ( w(t+1)= w(t)-gamma*y*x)'
	}
//step 3 : test(que les données de teste)
        
        float E = 0;
        for(int i=0; i<10000 ; i++){
                printf("%u\n",i);
                int inference = linear_classifier(w,test_images[i]);
                save_jpg(test_images[i],28,28,"%u/%u.jpg",inference,i);
        
        if ((inference ==1 && test_labels[i]!=1)||(inference ==-1 && test_labels[i]==1))E++;
        	printf("le pourcentage d'erreur est %f %u ==%u %0.2f %%\n",E,inference,(int)test_labels[i],(E*100)/(i+1));
        }
        /*for(int i=0; i<10000; i++) {
                printf("%u\n", i);
                float mind= -1;
                int NN;
                for (int j=0; j<60000; j++){
                        float d = dist(test_images[i], images[j]);
                        if (d<mind || mind==-1){
                                mind = d;
                                NN = j;
                        }
                }
                
                int inference = labels[NN];
                save_jpeg(test_images[i], 28, 28, "%u/%u.jpg", inference, i);
        }
        */
    return 0;
}









