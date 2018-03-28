#include "stdio.h"

int main() {
  FILE *fp;
  fp=fopen("/tmp/ult.log", "w");
  if(fp == NULL) {
    return -1;
  }

  int distance = 100; // current distance
  int num_photos = 1; // number of photos it recorded. start from 0.
  fprintf(fp, "%d, %d", num_photos, distance);

  fclose(fp);

  return 0;
}
