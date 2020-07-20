#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static char s[256];

int main(int argc, char **argv){
  int n; scanf("%d",&n);
  while (n--){
    uint64_t v; scanf("%"SCNu64,&v);
    for (int i=255; i--;){
      s[i]='0'|(v%3);
      v/=3;
      if (!v){
        puts(s+i);
        break;
      }
    }
  }
  return 0;
}
