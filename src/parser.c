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
    size_t length = arrayLength(array);

    putchar('{');
    for (int i = 0; i < length; i++) {
        if (i == length - 1){
            printf(" '%s' }", array[i]);
            break;
        } else { printf(" '%s',", array[i]); }
    }
    putchar('\n');
}

size_t freeTokens(Token* tokens) {
    size_t count = 0;
    while (tokens) {
        Token* temp = tokens;
        tokens = tokens->next;
        free(temp);
        count++;
    }
    return count;
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

size_t arrayLength(char** array) {
    size_t length = 0;
    char* c = "";
    while (c != '\0') {
        c = array[length];
        length++;
    }
    return length-1;
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

bool consistsOf(char* str, char* accept) {
    size_t length = strlen(str);
    size_t span = strspn(str, accept);
    return length == span;
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
    char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Error err = ok;

    Token* tokens = NULL;
    Token currentToken = createLexableToken(src);
    size_t tokenCount = 0;

    while ((err = lex(currentToken.end, &currentToken)).type == ERROR_NONE) {
        if (currentToken.end - currentToken.beginning == 0) { break; }
        appendToken(&tokens, currentToken);
        tokenCount++;
    }

    // printTokens(tokens);
    Node* rootNode = createNode();
    Token* tokenIt = tokens;
    char** tokenArray = toTokenArray(tokens);

    while(tokenIt) {
        char* tokenContent = getTokenContent(tokenIt);
        char* nextTokenContent;
        if (tokenIt->next)
            nextTokenContent = getTokenContent(tokenIt->next);

        if (strcmp(":", tokenContent) == 0) {  
            if (nextTokenContent && strcmp("int", nextTokenContent) == 0) {
                printf("Found int declaration\n");
            }
        }

        if (strcmp("=", tokenContent) == 0) {  
            if (nextTokenContent && consistsOf(nextTokenContent, "0123456789")) {
                printf("Found int assignment: %s\n", nextTokenContent);
            }
        }

        tokenIt = tokenIt->next;
    }

    printf("Freed %lu tokens\n", freeTokens(tokens));
    printf("Freed %lu nodes\n", freeNode(rootNode));
    return err;
}