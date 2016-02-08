#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const *one, char const *two)
{ 
  while (1) // loop until return 
    { 
      int  first = (int) *one;
      int  second = (int) *two;
      
      // checking for space character 
      if (first == 32 && second == 32)
        return 0;
      else if (first == 32)
        return -1;
      else if (second == 32)
        return 1;
          
          if ((*one ^ 42) > (*two ^ 42))
            { 
              return 1;
            }
          
          else if ((*one ^ 42) < (*two ^ 42))
            { 
              return - 1;
            }
          // if ((*one ^ 42) == (*two ^ 42))
          // {
          //  return 0;
          // }
      
      one++;
      two++;
    }
}

int wrapfrobcmp(const void* a, const void* b)
{ 
  char const* A = *(char const**)a;
  char const* B = *(char const**)b;
  return frobcmp(A, B);
}


int main()
{
  int buffersize = 2048; // random buffer size
  int count = 0;
  char *array = (char*) malloc(sizeof(char) * buffersize);

  if (array == NULL){
    fprintf(stderr, "Error: can't allocate memory");
    exit(1);
  }

  int character;
  int notempty = 0;
  while(1)
    {
      character = getchar();
      if (character == EOF)
        break;
      notempty = 1;
      array[count++] = (char) character;
      if (count == buffersize){
        array = (char*) realloc(array, buffersize * 2);
        if (array == NULL){
          fprintf(stderr, "Error: can't allocate memory");
          exit(1);
        }
        buffersize *= 2;
      }
    }

  // was an empty file passed
  if (notempty == 0)
    return 0;
  //append space if no space
  if (array[count-1] != ' ')
    array[count++] = ' ';

  int countWords = 0;
  int k = 0;
  while (k < count)
    {  if (array[k] == ' ')
        countWords++;
 k++;
    }
char **pointerArray = (char**) malloc(sizeof(char*) * countWords);
  int *lengths = (int*) malloc(sizeof(int) * countWords);
  if (pointerArray == NULL){
    fprintf(stderr, "Error: can't allocate memory");
    exit(1);
  }
  if (lengths == NULL){
    fprintf(stderr, "Error: can't allocate memory");
    exit(1);
  }


  int pointerArrayindex = 0;
  char *pointerArrayp = array;
  k = 0;
  while (k < countWords)
    {
      if (k == 0 && *pointerArrayp == ' ')
        {
          pointerArray[pointerArrayindex++] = pointerArrayp;
          k++;
          pointerArrayp++;
        }
      pointerArray[pointerArrayindex++] = pointerArrayp;
      while (*pointerArrayp != ' ')
        pointerArrayp++;

      pointerArrayp++;
      k++;
    }

  qsort(pointerArray, pointerArrayindex, sizeof(char*), wrapfrobcmp);
/ I've used the lengths array so that the lengths of the lines when printed are correct 
  int lengthIndex = 0;
  int length = 1;
  k = 0;
  while (k < countWords)
    {
      pointerArrayp = pointerArray[k];
      while (*pointerArrayp != ' ')
        {
          pointerArrayp++;
          length++;
        }
      lengths[lengthIndex++] = length;
      length = 1;
      k++;
    }


  k=0;
  while (k < countWords)
    {
      char *chutiya = pointerArray[k];
      int i = 0;
      for (; i < lengths[k]; i++)
        {
          printf("%c", *chutiya);
          chutiya++;
        }
      k++;
    }
 //free allocated memory
  free(array);
  free(pointerArray);
  free(lengths);
  return 0;
}

