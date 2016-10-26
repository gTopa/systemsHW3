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

  if ( err_message == -1 ) {
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
    return -1;
  }

  close(file_id);
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
  int file_id = open("./text", O_CREAT|O_APPEND|O_APPEND, 0644);
  for ( i = 0; i < 10; i++ ) {
    write(file_id, &nums[i], sizeof(int));
  }
  close(file_id);

  printf("\nReading numbers from file\n");

  int buff;
  int nums2[10];
  file_id = open("./text", O_RDONLY);
  for ( i = 0; i < 10; i++ ) {
    read(file_id, &buff, sizeof(int));
    nums2[i]=buff;
    printf("random %d: %d\n", i, buff);
  }
  close(file_id);
  
  
  
  //  printf("%d\n", rand_int());

  return 0;
}
