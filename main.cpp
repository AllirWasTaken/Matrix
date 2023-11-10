#include <iostream>
#include <cstring>
#include <chrono>
#include <ctime>
#include "Matrix.h"

using namespace ALib;
void TestAndSaveGEMM(const char* fileName){
    srand(time(nullptr));
    char* realFileName=(char*)malloc(strlen(fileName)+4);
    strcpy(realFileName,"../");
    strcat(realFileName,fileName);


    FILE *f= fopen(realFileName,"wt");
    free(realFileName);

    std::chrono::time_point<std::chrono::high_resolution_clock> start,end;

    for(int i=0;i<=10;i++){
        int size=i*100;
        if(size==0)size=10;


        std::vector<std::vector<float>> tempMatrix;
        tempMatrix.resize(size);
        for(int y=0;y<size;y++){
            tempMatrix[y].resize(size);
        }

        for(int y=0;y<size;y++){
            for(int x=0;x<size;x++){
                tempMatrix[y][x]=(float)rand();
            }
        }

        Matrix a=tempMatrix;
        Matrix b=a/5;

        start=std::chrono::high_resolution_clock::now();
        Matrix c = a*b;
        end=std::chrono::high_resolution_clock::now();

        size_t time=(end-start).count();
        float ms= (float)time/1000000;
        fprintf(f,"%dx%d %.3lf ms\n",size,size,ms);
    }




    fclose(f);

}





int main() {

    TestAndSaveGEMM("VersionBasic.txt");

    return 0;
}
