#include <stdio.h>
#include <string.h>

typedef enum {
	TOK_LPAREN, TOK_RPAREN,
	TOK_LBRACE, TOK_RBRACE,
	TOK_SEMICOLON,
	TOK_PLUS, TOK_MINUS,
	TOK_STAR, TOK_SLASH,

	TOK_ASSIGN, TOK_EQ,
	TOK_BANG, TOK_NEQ,
	TOK_LT, TOK_LTE,
	TOK_GT, TOK_GTE,

	// literal nd indentifier
	TOK_IDENT,
	TOK_INT_LIT,

	TOK_KW_INT,
	TOK_KW_RETURN,
	TOK_KW_IF,

	TOK_ERROR,
	TOK_EOF
} TokenType;

typedef struct {
	TokenType type;
	const char *start;
	int length;
	int line;
} Token;

typedef struct {
	const char *start;
	const char *current;
	int line;
} Lexer;

void lexerInit(Lexer *l, const char *source) {
	l->start=source;
	l->current=source;
	l->line=1;
}

static bool isAtEnd(Lexer *l) {
	return *l->current=='\0';
}

static char peek(Lexer *l) {
	return *l->current;
}

// to check the next char (eg: to determine if / or //)
static char peekNext(Lexer *l) {
	if(isAtEnd(l)) return '\0';
	return *(l->current+1);
}

static bool matchExpected(Lexer *l, char expected) {
	if(isAtEnd(l)) return false;
	if(*l->current!=expected) return false;
	l->current++;
	return true;
}

