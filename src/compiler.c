#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tokeniser.c"
#include "parser.c"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Please provide the .leo file to compile\n");
        return -1;
    }

    char *pathFile = argv[1];
    FILE *fptr = fopen(pathFile, "r");

    if (fptr == NULL)
    {
        perror("Couldn't open the provided file");
        return -1;
    }

    tokenResult tokenResult = tokenise(fptr);

    fclose(fptr);

    printf("finished tokenisation...\n");
    for (int i = 0; i < tokenResult.numTokens; i++)
    {
        if (strcmp(tokenResult.tokens[i], "\n") == 0) {
            printf("token %d : \\n \n", i);
        }
        else {
            printf("token %d : %s \n", i, tokenResult.tokens[i]);
        }
    }

    parseTokens(&tokenResult);

    return 0;
}