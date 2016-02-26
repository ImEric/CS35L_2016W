#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>


int frob_cmp(const void* a, const void* b);

int num_of_cmp;

//Main function
int main(int argc, char **argv)
{
    num_of_cmp = 0;
    char ch;
    int char_count = 0;
    int word_count = 0;
    bool isRegularFile = false;

    char **words; 
    char *new_word;

    struct stat fstat;

    if(S_ISREG(fstat.st_mode)){
        isRegularFile = true;
        words = malloc(fstat.st_size*sizeof(char*));
        new_word = malloc(fstat.st_size*sizeof(char));
    }else{
        words = malloc(word_count *sizeof(char*));
        new_word = malloc(char_count*sizeof(char));
    }

    
    
    //read from stdin
    while (read(0, &ch, 1))
    {
        
        //check if not space
        if (ch != ' ')
        {
            
            char_count++;
           
            //reallocate memory
            if(!isRegularFile)
                new_word = realloc(new_word, char_count * sizeof(char));

            new_word[char_count - 1] = ch;
            
 
        }
        //otherwise
        else
        {
            //check if is leading space
            if (word_count == 0 && char_count == 0)
            {
                //ignore
                continue;
            }
            else
            {
                //add char to current word
                char_count++;
                if(!isRegularFile)
                    new_word = realloc(new_word, char_count * sizeof(char));
                
                new_word[char_count - 1] = ch;
                //reset char_count
                char_count = 0;
                
                //add current word to array of words
                word_count++;
                if(!isRegularFile)
                    words = realloc(words, word_count * sizeof(char*));
                
                words[word_count - 1] = new_word;
                
                //free and reallocate new_word
                new_word = malloc(fstat.st_size * sizeof(char));
                
            }
           
        }
       
    }
    //words not end with space needs to append a space
    if (char_count != 0 && new_word[char_count - 1] != ' ')
    {
        //add ' ' to new_word
        char_count++;
        if(!isRegularFile)
            new_word = realloc(new_word, char_count * sizeof(char));
        new_word[char_count - 1] = ' ';

        //add current word to words
        word_count++;
        if(!isRegularFile)
            words = realloc(words, word_count * sizeof(char*));
        words[word_count - 1] = new_word;
    }
    
    //sorting
    qsort(words, word_count, sizeof(char*), frob_cmp);
    
    
    //printing the result
    int i, j;
    for(i = 0; i < word_count; i++) {
        for(j = 0; words[i][j] != ' '; j++)
            write(1,&(words[i][j]),1);
        write(1,&(words[i][j]),1);//print the space
    }
    
    /*if(words) {
        //Free memory allocated by words array
      int i;
      for(i = 0; i < word_count; i++)
            free(words[i]);
        free(words);
        
    }
    */
    

    fprintf(stderr, "\nComparisons: %d\n", num_of_cmp);
    
    exit(0);
}

//Compare functions

int frob_cmp(const void* a, const void* b)
{
    num_of_cmp++;
    
    const char *w1 = *(const char**) a;
    const char *w2 = *(const char**) b;
    
    int itr1 = 0;
    int itr2 = 0;
    
    while(w1[itr1] != ' ' && w2[itr2] != ' ' && w1[itr1] == w2[itr2]){
        itr1++;
        itr2++;
    }
    
    return (w1[itr1] ^ 42) - (w2[itr2] ^ 42);
    
}



