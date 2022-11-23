#include "parser.h"

Error ok = { ERROR_NONE, "ok"};

// Helper functions
void printTokens(Token* tokens) {
    size_t count = 1;
    while (tokens) {
        printf("Token #%02lu: ", count);
        if (tokens->beginning && tokens->end) {
            printf("%.*s", tokens->end - tokens->beginning, tokens->beginning);
        }
        putchar('\n');
        tokens = tokens->next;
        count++;
    }
}

void printArray(char** array) {
    size_t length = 0;
    char** arrayIt = array;
    char* c = "";
    while (c != '\0') {
        c = array[length];
        length++;
    }
    length -= 1;

    putchar('{');
    for (int i = 0; i < length; i++) {
        if (i == length - 1){
            printf(" '%s' }", array[i]);
            break;
        } else { printf(" '%s',", array[i]); }
    }
    putchar('\n');
}

void freeTokens(Token* tokens) {
    size_t count = 0;
    while (tokens) {
        Token* temp = tokens;
        tokens = tokens->next;
        free(temp);
        count++;
    }
    printf("Freed %lu tokens\n", count);
}

void appendToken(Token** dest, Token src)
{
    Token* temp = createToken();
    temp->beginning = src.beginning;
    temp->end = src.end;
    if (*dest) {
        Token* lastToken = *dest;
        while(lastToken->next) {
            lastToken = lastToken->next;
        }
        lastToken->next = temp;
    } else { *dest = temp; }
}

char** toTokenArray(Token* tokens) {
    Token* tokenIt = tokens;
    size_t count = 0;
    while (tokenIt) {
        tokenIt = tokenIt->next;
        count++;
    }
    char** tokenArray = calloc(count, sizeof(char*));
    tokenIt = tokens;
    count = 0;
    while (tokenIt) {
        tokenArray[count] = getTokenContent(tokenIt);
        tokenIt = tokenIt->next;
        count++;
    }
    tokenArray[count] = '\0';
    return tokenArray;
}

char* getTokenContent(Token* token) {
    size_t tokenLength = token->end - token->beginning;
    char* tokenContent = malloc(tokenLength + 1);
    memcpy(tokenContent, token->beginning, tokenLength);
    tokenContent[tokenLength] = '\0';
    return tokenContent;
}

Token* createToken() {
    Token* token = calloc(1, sizeof(Token));
    assert(token && "Couldn't allocate memory for token");
    return token;
}

Token createLexableToken(char* src) {
    Token token;
    token.next = NULL;
    token.beginning = src;
    token.end = src;
    return token;
}

// Pretty much Lens_r's code
const char* whitespace = " \r\n";
const char* delimiters = " \r\n;,(){}:=";

Error lex(char* src, Token* token) {
    Error err = ok;
    if (!src || !token) { 
        CREATE_ERROR(err, ERROR_ARGS, "Can't lex an empty source.");
        return err;
    }

    token->beginning = src;
    token->beginning += strspn(token->beginning, whitespace);
    token->end = token->beginning;
    if (*(token->end) == '\0') { return err; }

    token->end += strcspn(token->beginning, delimiters);
    if (token->end == token->beginning) {
        token->end += 1;
    }
    return ok;
}

Error parseExpression(char* src, Node* result) {
    Error err = ok;

    Token* tokens = NULL;
    Token currentToken = createLexableToken(src);

    while ((err = lex(currentToken.end, &currentToken)).type == ERROR_NONE) {
        if (currentToken.end - currentToken.beginning == 0) { break; }
        appendToken(&tokens, currentToken);
    }

    // printTokens(tokens);
    Node* rootNode = createNode();
    Token* tokenIt = tokens;
    char** tokenArray = toTokenArray(tokens);
    printArray(tokenArray);

    while(tokenIt) {
        char* tokenContent = getTokenContent(tokenIt);

        if (strcmp(":", tokenContent) == 0) {  
            if (tokenIt->next && strcmp("int", getTokenContent(tokenIt->next)) == 0) {
                printf("Found int declaration\n");
            } else if (tokenIt->next && strcmp("=", getTokenContent(tokenIt->next)) == 0) {
                printf("Found variable assignment\n");
            }
        }

        tokenIt = tokenIt->next;
    }

    freeTokens(tokens);
    return err;
}