#include "tokeniser.c"

typedef struct
{

} Statement;

typedef struct
{
    Statement **statements;
    int numStatements;
} Program;

Statement *_parseSTATEMENT(char **tokens, int numTokens)
{
    printf("New statement with tokens:\n");
    for (int i = 0; i < numTokens; i++)
    {
        printf("%s ", tokens[i]);
    }
    printf("\n");

    return NULL;
}

Program *_parsePROGRAM(char **tokens, int numTokensToParse)
{

    Program *program = malloc(sizeof(Program));
    program->statements = NULL;
    program->numStatements = 0;

    char **tokenStatementStart = tokens;
    int lengthStatement = 0;

    for (int i = 0; i < numTokensToParse; i++)
    {

        // we encounter a normal token within a statement
        if (strcmp(tokens[i], "\n") != 0)
        {
            lengthStatement++;

            // continue to the next token if there are any
            if (i != numTokensToParse - 1)
                continue;
        }

        // this happens when we have an empty statement (blank line)
        if (lengthStatement == 0)
        {
            tokenStatementStart++; // we skip this useless new line character
            continue;
        }

        // parse statement and add it to the list
        Statement *statement = _parseSTATEMENT(tokenStatementStart, lengthStatement);
        program->statements = realloc(program->statements, (program->numStatements + 1) * sizeof(Statement *));
        program->statements[program->numStatements] = statement;
        program->numStatements++;

        // reset for next statement parsing
        tokenStatementStart = tokenStatementStart + lengthStatement + 1; // the extra one is for the separator \n
        lengthStatement = 0;
    }

    return program;
}

/*

Here is the grammar of a leo program:

program := [statement]
statement := expression | assignment
expression :=   LITTERAL |
                identifier |
                '(' expression ')' |
                expression '+' expression |
                expression '-' expression |
                expression '/' expression |
                expression '*' expression |

assignment := identifier '=' expression
*/
Program *parseTokens(tokenResult *tokenResult)
{
    Program *program = _parsePROGRAM(tokenResult->tokens, tokenResult->numTokens);

    return program;
}
