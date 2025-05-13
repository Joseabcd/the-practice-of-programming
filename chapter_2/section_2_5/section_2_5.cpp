#include <iostream>


// this is O(n^2)
void slowsort1(int* v,int n){

	int ordering[n];
	int temp[n];

	for(int i=0;i<n;i++){
		temp[i]=v[i];
	}

	for(int i=0; i<n; i++){
		ordering[i]=0;
		for (int j=0; j<n; j++){
			if(v[j]<v[i]){
				ordering[i]++;
			} else{
				if(v[i]==v[j]){
					if(j<i){
						ordering[i]++;
					}
				}
			}
		}
	}

	for(int i=0; i<n;i++){
		for(int j=0; j<n;j++){
			if(i==ordering[j]){
				v[i]=temp[j];
			}
		}
	}

}



int main(){

    // const int n = 20;
    // int a[n] = {4, -6, 32, 5, 5, 5, 0, 210, -210,90,31, 30, 0, 1, -3, 0, 1, 1, 5, -8000};

    const int n = 3;
    int a[n] = {10, -3, 1};

    // const int n = 4;
    // int a[n] = {-12, 10, -3, 1};


    slowsort1(a,n);


    for (int i = 0; i < n; i++){
        std::cout << a[i] << std::endl;
    }
}
