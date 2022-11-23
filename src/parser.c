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

    printTokens(tokens);

    Node* rootNode = createNode();
    Token* tokenIt = tokens;
    
    while(tokenIt) {
        tokenIt = tokenIt->next;
    }

    freeTokens(tokens);
    return err;
}