#include<iostream>
#include<vector>


void quicksort(std::vector<float> &a){
    // my attempt

    if (a.size()<=1) {
        return;
    }

    std::vector<float> little_ones, big_ones;

    for (int p = 0; p < a.size(); p++) {

        little_ones.clear();
        big_ones.clear();

        std::vector<float> b, c;

        for (int i = 0; i < a.size(); i++){
            if (a[i] < a[p]) {
                little_ones.push_back(a[i]);
            } else{
                if (a[i] >= a[p]) {
                    big_ones.push_back(a[i]);
                }
            }
        }

        if (little_ones.size() == 0 || big_ones.size() == 0) {
            continue; // change of pivot
        } 
    
        quicksort(little_ones);
        quicksort(big_ones);

        a = little_ones;
        a.insert(a.end(), big_ones.begin(), big_ones.end());
        return;

        // here if all the elements of the input are the same, then the number of iterations is going to be,
        // literally, n^2...

    }
    
}


void swap(int* v, int i, int j){
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


void quicksort2(int* v, int n){
    // the implementation from the book
    int i, last;

    if (n<=1) { //nothing to do
        return;
    }

    swap(v, 0, rand() % n); // move pivot elem to v[0]
    last = 0;
    for (i = 1; i < n; i++) { // partition
        if (v[i] < v[0]){
            swap(v, ++last, i);
        }
    }
    swap(v, 0, last); // restore pivot
    quicksort2(v, last); // recursively sort
    quicksort2(v+last+1, n-last-1);
}


void quicksort_iterative(int* v, int n){
    // the iterative implementation for exercise 2-1 from the book
    int i, last;

    if (n<=1) { //nothing to do
        return;
    }

    int np = 1; // the number of partitions
    std::vector<int> lengths = {n}; // the length of each partition

    int max_iter=100000;
    int iter_count =0;

    while(np < n && iter_count <= max_iter){

        iter_count++;

        int beginning = 0;  // position where the current partition begins. First partition starts at zero

        std::vector<int> lengths_next_iter;
        int np_next_iter=np;

        for (int i = 0; i < np; i++){

            if (lengths[i]==1) {
                beginning += 1;
                lengths_next_iter.push_back(1);
                continue;
            }

            if (lengths[i]==0) {
                continue;
            }

            int last = beginning;
            int pivot_position = rand() % lengths[i];

            swap(v, beginning, beginning + pivot_position); // move pivot elem to the start of this partition

            for (int j = beginning + 1; j < beginning + lengths[i]; j++) {
                if(v[j] < v[beginning]){
                    swap(v, ++last, j);
                }
            }

            swap(v, beginning, last); // restore pivot

            lengths_next_iter.push_back((last+1)-beginning);  // the length of the small ones plus the pivot

            if(beginning+lengths[i]-(last+1)!=0){
                lengths_next_iter.push_back(beginning+lengths[i]-(last+1));
                np_next_iter+=1;
            }

            beginning += lengths[i];

        }

        lengths = lengths_next_iter;
        np=np_next_iter;
        lengths_next_iter.clear();

    }
}


int main(){

    // std::vector<float> a = {90, 4., 160, 6.5, 2.,-10., -10,-10, 90, -100, 2, 9, 78,-7.001,-7.01, 0.,200, 0., -1.75, 8.,-300};
    // std::vector<float> a = {4, -6, 32, 5, 5, 5, 0, 210, -210,90,31, 30, 0, 1, -3, 0, 1, 1, 5, -8000};

    // const int n = 10;
    // int a[n] = {4, 6, 0, 1, -3, 0, 1, 1, 5, 2};

    const int n = 20;
    int a[n] = {4, -6, 32, 5, 5, 5, 0, 210, -210,90,31, 30, 0, 1, -3, 0, 1, 1, 5, -8000};

    // const int n = 1;
    // int a[n] = {4};

    // const int n = 10;
    // int a[n] = {0,0,0,0,0,0,0,0,0,0};

    // const int n = 0;
    // int a[n] = {};

    // const int n = 2;
    // int a[n] = {1000,-1000};

    // const int n = 11;
    // int a[n] = {-1000,-2,-5,-7,-3,-1000,-4567,0,0,0,-234};

    // const int n = 9;
    // int a[n] = {4, 1, 2, 2, 1, 1, 1, 1, 1};


    // quicksort2(a,n);
    // for (int i = 0; i < a.size(); i++){
    //     std::cout << a[i] << std::endl;
    // }
    // std::cout << std::endl;


    quicksort_iterative(a, n);
    for (int i = 0; i < n; i++){
        std::cout << a[i] << std::endl;
    }

    return 0;
}
