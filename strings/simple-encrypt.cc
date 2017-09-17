#include <stdio.h>
#include <string.h>
#include <ctype.h>

int valid(char cd, char init, char end ){
  
  if(cd >= init && cd <= end)
    return 1; 

  return 0; 
}

int limit(char rotated, int is_upper){
  
  char end   = is_upper?'Z':'z'; 
  char start = is_upper?'A':'a'; 


  if(rotated > end){
    return (rotated % end) + (start-1);
  }

  return rotated; 
}


void encrypt(const char* str, int k,  int size){
  char encrypted[k]; 

  for(int i=0; i<=size; i++){
    char candidate = str[i]; 
    if( valid(candidate, 'a', 'z') || valid(candidate, 'A', 'Z') )
    {
      
      encrypted[i] = limit((candidate + k), candidate == toupper(candidate)); 

    }
    else
      encrypted[i] = candidate; 
  }
  
  printf("word-> %s  encrypted-> %s",str,  encrypted);

}

int main(){
  
  const char *s = "%$#$@#?1223232DEEZZZZmiddle-Outz92121"; 
  int len = strlen(s);

  printf("-> %s %d \n", s, len);

  encrypt(s, 2, len);

  

  return 0; 
}
