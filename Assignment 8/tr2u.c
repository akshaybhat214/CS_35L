#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//If orig char exists in string, replace with replacement char.
char *replace_str(char *str, char orig, char rep, int size)
{
  int i=0;
  for (i=0; i < size; i++)
    {
      if (str[i]==orig)
	str[i]=rep;
    }

  return str;
}

int main(int argc, char *argv[]){
  
  if ( argc != 3 )
    {
     fprintf(stderr, "Wrong number of arguments.\n");
      return 1;
    }

  char* arg1= argv[1];
  char* arg2= argv[2];
  
  if ( strlen(arg1) != strlen(arg2) ){
    fprintf(stderr, "Arguments are not of the same size.\n");
    return 1;
  }

  int i=0; int c=0; int isRepeated=0;
  for (;i <strlen(arg1)-1 ; i++)
    {
      for (c=i+1; c< strlen(arg1); c++)
	if (arg1[i]==arg1[c]) //Repeats not allowed!!
	  isRepeated=1;
    }

  if ( isRepeated ){
    fprintf(stderr, "Argument 1 cannot have repeated characters\n");
    return 1;
  }
  
  int buffSize=2048;
  int charCount=0;
  char *in= (char*)malloc(buffSize*sizeof(char));

  if (in==NULL){
    fprintf(stderr,"Could not allocate memory.\n");
    exit(1);
  }

  //get input from stdin and store in buffer.
  int bytes_read;
  while (1){
    bytes_read = read(0,in+charCount, 1);
    if (bytes_read == 0)
      break;

    charCount++;
    //if buffer gets full
    if (charCount == buffSize){
      in = (char*)realloc(in, buffSize*2);
      if(in == NULL){
	fprintf(stderr,"Could not allocate memory.\n");
	return 1;
      }
      buffSize += buffSize;
    }
  }

  int j=strlen(arg1);
  int k;
  for (k=0; k < j; k++)
    {
      char char1= arg1[k]; char char2 = arg2[k];
      if (char1 == char2)
	continue;

      //Replace all instances of char1 with char2
      in = replace_str(in ,char1, char2, charCount);
    }

  //write to stdout
  for (i=0;i< charCount; i++)
    write(1, in+i, 1);

  free(in);
}
