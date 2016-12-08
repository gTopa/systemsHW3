// Giovanni Topa and Calvin Vuong
// MKS65 pd10
// Work 3
// 10-26-2016

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
  if ( err_message == -1 ) 
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
  
  return random_int;
}

int main() {
  int nums[10];
  int i;
  printf("Generating random numbers:\n");
  
  // populate array
  for ( i = 0; i < 10; i++ ) {
    nums[i] = rand_int();
    printf("random %d: %d\n", i, nums[i]);
  }

  // write entire array to file
  printf("\nWriting numbers to file...\n");
  int file_id = open("./text", O_CREAT | O_WRONLY, 0644);
  if ( file_id == -1 ) 
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
  
  int err_message = write(file_id, &nums, sizeof(nums));;
  if ( err_message == -1 )
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));

  // close file
  err_message = close(file_id);
  if ( err_message == -1 )
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
  
  printf("\nReading numbers from file:\n");
  int buff;
  int nums2[10];
  // open second file for reading
  file_id = open("./text", O_RDONLY);
  if ( file_id == -1 )
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));

  // read the entire array on file and set the new array to its contents
  err_message = read(file_id, &nums2, sizeof(nums2));
  if ( err_message == -1 )
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));

  // print out the second array read from second file
  for ( i = 0; i < 10; i++ )
    printf("random: %d: %d\n", i, nums2[i]);

  err_message = close(file_id);
  if ( err_message == -1 ) 
    printf("!!!!!!!!!!!ERROR!!!!!!!!!!: %s", strerror(errno));
  
  return 0;
}
