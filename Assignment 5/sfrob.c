#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)

void error_msg();

int frob_cmp(const void* a, const void* b);

//Main function
int main(int argc, char **argv)
{
    
    char ch;
    int char_count = 0;
    int word_count = 0;
    char **words = malloc(word_count * sizeof(char*)); //2D array
    char *new_word = malloc(char_count * sizeof(char));
    
    //read from stdin
    while ((ch = getchar()) != EOF)
    {
        
        //check if not space
        if (ch != ' ')
        {
            
            char_count++;
           
            //reallocate memory
            new_word = realloc(new_word, char_count * sizeof(char));
            
            //use try and catch for exception handling
            TRY{
                new_word[char_count - 1] = ch;
            }CATCH{
                error_msg();
            }ETRY;
 
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
                new_word = realloc(new_word, char_count * sizeof(char));
                
                TRY{
                    new_word[char_count - 1] = ch;
                }CATCH{
                    error_msg();
                }ETRY;
                
                //reset char_count
                char_count = 0;
                
                //add current word to array of words
                word_count++;
                words = realloc(words, word_count * sizeof(char*));
                
                TRY{
                    words[word_count - 1] = new_word;
                }CATCH{
                    error_msg();
                }ETRY;
                
                
                //free and reallocate new_word
                //new_word = malloc(char_count * sizeof(char));
                char *tmp = malloc(char_count*sizeof(char));
                new_word = tmp;
            }
           
        }
       
    }
    //words not end with space needs to append a space
    if (char_count != 0 && new_word[char_count - 1] != ' ')
    {
        //add ' ' to new_word
        char_count++;
        new_word = realloc(new_word, char_count * sizeof(char));
        
        TRY{
            new_word[char_count - 1] = ' ';
        }CATCH{
            error_msg();
        }ETRY;
        
        
        //add current word to words
        word_count++;
        words = realloc(words, word_count * sizeof(char*));
        
        TRY{
            words[word_count - 1] = new_word;
        }CATCH{
            error_msg();
        }ETRY;
        
    }
    
    //sorting
    qsort(words, word_count, sizeof(char*), frob_cmp);
    
    
    //printing the result
    int i, j;
    for(i = 0; i < word_count; i++) {
        for(j = 0; words[i][j] != ' '; j++)
            printf("%c", words[i][j]);
        printf("%c", words[i][j]);//print the space
    }
    
    if(words) {
        /* Free memory allocated by words array*/
        for(int i = 0; i < word_count; i++)
            free(words[i]);
        free(words);
        
    }
    
    exit(0);


}

//Compare functions

int frob_cmp(const void* a, const void* b)
{
    
    
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



void error_msg()
{
    
    fprintf(stderr, "Memory allocation Error.\n");
    exit(1);
    
}