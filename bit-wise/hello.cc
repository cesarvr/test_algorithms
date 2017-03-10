#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

void zero(unsigned char *list, int len){
  auto cnt = 0;
  while(cnt++ < len)
    *list++ = 0;
}

template <typename T>
void Print(T* list, int len) {
  cout << "size: " << len << endl;
  auto cnt = 0;
  while(cnt++ < len){ 
    printf("- %d \n", *list++);
  }
}

template <typename T>
int check(T* list, int len){
  cout << "size: " << len << endl;
  auto cnt = 0;

  while(cnt++ < len){ 
    auto packet = *list; 

    for(int i=0; i<8; i++){

     if((packet & 1<<i) == 0){  
      return (--cnt * 8 + i);
     }

    }

    printf("pack- %d \n", *list);
    packet = *list++;
  }

  return -1;
}


int main(){
  int sample[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,30,31,32,33,34, 35};  
  int sampleSize = sizeof(sample) / sizeof(int);
  int packSize = ceil(static_cast<float>(sampleSize) / static_cast<float>(8)); 

  cout << "pack size " << packSize << "->" << ceil(21.0/8.0) << endl;

  Print(sample, sampleSize);
  
  unsigned char *pack = (unsigned char *)malloc(packSize); 

  zero(pack, packSize); 
  
  for(int i = 0; i <= sampleSize; i++) {
    int value = sample[i]; 
    pack[i/8]|= 1 << (value % 8);     
  }

  Print(pack, packSize);

  auto missing = check(pack, packSize); 
  cout << "Missing number is: " << missing << endl;

  free(pack);
};

