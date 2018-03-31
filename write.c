#include "stdio.h"

int main() {
  FILE *fp;
  fp=fopen("/tmp/ult.log", "w");
  if(fp == NULL) {
    return -1;
  }

  int distance = 100; // current distance
  int speed = 333; // current speed
  int num_photos = 1; // number of photos it recorded. start from 0.
  fprintf(fp, "%d, %d, %d", num_photos, distance, speed);

  fclose(fp);

  return 0;
}
