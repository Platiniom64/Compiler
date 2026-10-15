#ifndef tokeniser
#define tokeniser

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct  {
    char** tokens;
    int numTokens;
} tokenResult;

/*
This method takes a stream (file pointer) and creates a list of tokens
*/
tokenResult tokenise(FILE *fptr)
{

    // accumulate tokens found
    tokenResult result;
    result.numTokens = 0;
    result.tokens = NULL;

    char c = fgetc(fptr);
    while (true)
    {
        if (c == EOF)
        {
            break;
        }

        else if (isalpha(c))
        {
            char *newtoken = malloc(100);

            // create the new token
            int idx = 0;
            do
            {
                newtoken[idx] = c;

                idx++;
                c = fgetc(fptr);
            } while (isalpha(c));

            newtoken[idx] = '\0'; // null terminated string !

            // add it to the list
            result.tokens = realloc(result.tokens, (result.numTokens + 1) * sizeof(char *));
            result.tokens[result.numTokens] = newtoken;
            result.numTokens++;
        }
        else if (isdigit(c))
        {
            char *newtoken = malloc(100);

            // create the new token
            int idx = 0;
            do
            {
                newtoken[idx] = c;

                idx++;
                c = fgetc(fptr);
            } while (isdigit(c));

            newtoken[idx] = '\0'; // null terminated string !

            // add it to the list
            result.tokens = realloc(result.tokens, (result.numTokens + 1) * sizeof(char *));
            result.tokens[result.numTokens] = newtoken;
            result.numTokens++;
        }
        else if (c == '\n' || c == '(' || c == ')' || c == '=' || c == '+' || c == '-'|| c == '/' || c == '*')
        {
            // create new token
            char *newtoken = malloc(2 * sizeof(char));
            newtoken[0] = c;
            newtoken[1] = '\0';

            // add it to the list
            result.tokens = realloc(result.tokens, (result.numTokens + 1) * sizeof(char *));
            result.tokens[result.numTokens] = newtoken;
            result.numTokens++;

            // continue to the next loop
            c = fgetc(fptr);
            continue;
        }

        else
        {
            c = fgetc(fptr);
        }
    }

    return result;
}


#endif