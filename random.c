#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int rand_int() {
  int random_int = 0;
  int file_id = open("/dev/random", O_RDONLY);
  int err_message = read(file_id, &random_int, 4);
  if ( err_message == -1 || file_id == -1) {
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
    return -1;
  }

  err_message = close(file_id);
  if ( err_message == -1 ) {
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
  }

  return random_int;
}

int main() {

  int nums[10];
  int i;
  printf("Generating random numbers:\n");
  for ( i = 0; i < 10; i++ ) {
    nums[i] = rand_int();
    printf("random %d: %d\n", i, nums[i]);
  }

  printf("\nWriting numbers to file...\n");
  int file_id = open("./text", O_CREAT|O_WRONLY, 0644);
  if ( file_id == -1 ) {
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
  }
  int err_message;
  for ( i = 0; i < 10; i++ ) {
    err_message = write(file_id, &nums[i], sizeof(int));
    if ( err_message == -1 ) {
      printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
    }
  }
  close(file_id);

  printf("\nReading numbers from file\n");

  int buff;
  int nums2[10];
  file_id = open("./text", O_RDONLY);
  if ( file_id == -1 ) {
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
  }
  for ( i = 0; i < 10; i++ ) {
    err_message = read(file_id, &buff, sizeof(int));
    if ( err_message == -1 ) {
      printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
    }
    nums2[i]=buff;
    printf("random %d: %d\n", i, nums2[i]);
  }
  err_message = close(file_id);
  if ( err_message == -1 ) {
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
  }
  
  return 0;
}
