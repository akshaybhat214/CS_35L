//Akshay Bhat
//5-1-2015
//CS35L Lab 5 - HW5

#include <stdio.h>
#include <stdlib.h>

int rot13cmp(const void *a, const void *b){

  //cast pointer to char pointer
  const char *aPtr= *(const char**)a;
  const char *bPtr= *(const char**)b;

  //Ensure we don't go past end of array.
  while(214){
    if (*aPtr == '\n' && *bPtr == '\n')
      return 0;
    else if (*aPtr=='\n')
      return -1;
    else if (*bPtr=='\n')
      return 1;

    char a1 =*aPtr;
    char b1 =*bPtr;

    //Subtract or add to ASCII values to convert in ROT13
    if (a1!= b1){
      if(a1>'@' && a1<'N' || a1>'`' && a1<'n')
	a1+=13;
      else if(a1>'M' && a1<'[' || a1>'m' && a1<'{')
	a1-=13;
      if(b1>'@' && b1<'N' || b1>'`' && b1<'n')
	b1+=13;
      else if(b1>'M' && b1<'[' || b1>'m' && b1<'{')
	b1-=13;

      int diff = a1-b1;
      if (diff!=0)
	return diff; //Only return if different.
    }
    aPtr++; bPtr++;
  }

}
int main(){

  int buffSize=2048;
  int charCount=0;
  char *in= (char*)malloc(buffSize*sizeof(char));
  int inChar;
  int j=0;
  
  if (in==NULL){
     fprintf(stderr,"Could not allocate memory.\n");
     exit(1);
  }

  //get input from stdin and store in buffer.
  while (1){
     inChar = getchar();
     if (inChar == EOF)
       break;

     in[charCount] =(char)inChar; //Cast from int to char
    charCount++;

    //Need to allocate more space if buffer is full.
    if (charCount == buffSize){
      in = (char*)realloc(in, buffSize*2);
      if(in == NULL){
	fprintf(stderr,"Could not allocate memory.\n");
	exit(1);
      }
      buffSize += buffSize;
    }    
  }

  if (charCount<1)
    exit(0);

  if(in[charCount-1]!='\n'){
    
    //If no newline, must append one after
    //ensuring buffer is large enough.
    if (charCount >= buffSize){
      in = (char*)realloc(in, buffSize*2);
      if(in == NULL){
	fprintf(stderr,"Could not allocate sufficient memory.\n");
	exit(1);
      }
      buffSize += buffSize;
    }
    charCount++;
    in[charCount-1]='\n';
  }

  //Count the number of words in the array.
  int wordCount=0;
  for (j=0; j<charCount; j++){
    if(in[j]=='\n')
      wordCount++;
    }

  //Create an array of pointers to the beginning of each
  //word in the array.
  char **words= (char**)malloc(wordCount*sizeof(char*));
  if(words == NULL){
    fprintf(stderr,"Could not allocate sufficient memory.\n");
    exit(1);
  }
 
  //Based on newlines, assign these pointers to words in array.
  words[0] = &in[0];
  int ptrCount=1;

  for (j=0; j<charCount; j++){
    if(in[j]=='\n' && j<charCount-1){
      words[ptrCount]= &in[j+1];
       ptrCount++;
    }
  }

  //Check that there are as many word pointers as there are words.
  if(ptrCount != wordCount){
  fprintf(stderr,"Error creating word pointers.\n");
  exit(1);
  }

  //Sort word pointer using rot13cmp.
  qsort(words, ptrCount, sizeof(char*), rot13cmp);

  //Print out sorted words, via pointer array.
  for (j=0; j<ptrCount; j++){
    char *print= words[j];
    while(214){
      printf("%c",*print);
      if(*print=='\n')
	break;
      print++;
    }  
  }
  
  free(words);
  free(in);
  
  exit(0);
}
