typedef struct Error {
    enum ErrorType {
        ERROR_NONE = 0,
        ERROR_SYNTAX,
        ERROR_TYPE,
        ERROR_GENERIC
    } type;
    char* msg;
} Error;