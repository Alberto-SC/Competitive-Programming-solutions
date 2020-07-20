#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv){
  if(argc == 1) fprintf(stderr, "no method");
  else if(!strcmp(argv[1], "random")){
    if(argc < 5) fprintf(stderr, "not enough arguments");
    else {
      int seed = atoi(argv[2]);
      srand(seed);
      int d = atoi(argv[3]);
      int lim = atoi(argv[4]);
      printf("7\n");
      for(int i = 0; i < 7; ++i)
      printf("%d %d %d %d\n", rand()%lim, rand()%lim, rand()%lim, d);
    }
  } else {
    fprintf(stderr, "invalid method");
  }

}
