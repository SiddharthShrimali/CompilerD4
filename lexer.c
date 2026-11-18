#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

static char advanceChar(Lexer *l) {
	char c=*l->current;
	l->current++;
	return c;
}

static Token makeToken(Lexer *l, TokenType type) {
	Token token;
	token.type=type;
	token.start=l->start;
	token.length=(int)(l->current - l->start); // to handle 'ptrdiff_t'
	token.line=l->line;
	return token;
}

static Token errorToken(Lexer *l, const char *message) {
	Token token;
	token.type=TOK_ERROR;
	token.start=message;
	token.length=(int)strlen(message);
	token.line=l->line;
	return token;
}

Token scanToken(Lexer *l) {
	for(;;) {
		l->start=l->current;

		if(isAtEnd(l)) return makeToken(l, TOK_EOF);

		char c=advanceChar(l);

		switch(c) {
			// skip space and tab space
			case ' ':
			case '\t':
				break;

			case '\n':
				l->line++;
				break;

			// single chars
			case '(': return makeToken(l, TOK_LPAREN);
			case ')': return makeToken(l, TOK_RPAREN);
			case '{': return makeToken(l, TOK_LBRACE);
			case '}': return makeToken(l, TOK_RBRACE);
			case ';': return makeToken(l, TOK_SEMICOLON);
			case '+': return makeToken(l, TOK_PLUS);
			case '-': return makeToken(l, TOK_MINUS);
			case '*': return makeToken(l, TOK_STAR);

			// division/comment
			case '/':
				if(matchExpected(l, '/')) {
					while(peek(l)!='\n'&&!isAtEnd(l)) {
						advanceChar(l);
					}
					continue;
				}
				return makeToken(l, TOK_SLASH);
		}
		return makeToken(l, "Unexpected character");
	}
}

