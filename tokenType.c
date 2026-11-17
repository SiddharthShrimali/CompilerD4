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
