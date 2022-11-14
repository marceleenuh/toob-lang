#include "parser.h"

Error ok = { ERROR_NONE, "ok"};

Token createLexableToken(char* src) {
    Token r;
    r.next = NULL;
    r.beginning = src;
    r.end = src;
    return r;
}

// Pretty much Lens_r's code
const char* whitespace = " ;\r\n";
const char* delimiters = " ;\r\n,(){}:=";

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

Error parseExpression(char* src) {
    Token token = createLexableToken(src);
    Error err = ok;

    while ((err = lex(token.end, &token)).type == ERROR_NONE) {
        if (token.end - token.beginning == 0) { break; }
        printf("Lexed: %.*s\n", token.end - token.beginning, token.beginning);
    }
    return err;
}