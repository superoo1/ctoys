//
// Created by vincent on 2020/1/15.
//
#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <ctype.h>

char *line;
static int st_pos = 0;

static int ahead_token_exit;

static Token ahead_token;

void my_get_token(Token *token) {
    if (ahead_token_exit) {
        *token = ahead_token;
        ahead_token_exit = 0;
    } else {
        get_token(token);
    }
}

void unget_token(Token *token) {
    ahead_token = *token;
    ahead_token_exit = 1;
}

double parse_primary_expression() {
    Token token;
    my_get_token(&token);
    if (token.kind == NUMBER_TOKEN) {
        return token.value;
    }

}


double parse_term() {
    double v1;
    double v2;
    v1 = parse_primary_expression();
    Token token;
    printf("%f",st_pos);

    for (;;) {
        my_get_token(&token);
        if (token.kind != MUL_OPERATOR_TOKEN ) {
            unget_token(&token);
            break;
        }
        v2 = parse_primary_expression();
        if(token.kind == MUL_OPERATOR_TOKEN ) {
            v1 *= v2;
        }

    }
    return v1;

}


double parse_expression() {
    double v1, v2;
    v1 = parse_term();
    Token token;
    for (;;) {
        my_get_token(&token);
        v2 = parse_term();
        if (token.kind != ADD_OPERATOR_TOKEN &&token.kind!=SUB_OPERATOR_TOKEN) {
            unget_token(&token);
            break;
        }
        if (token.kind == ADD_OPERATOR_TOKEN) {
            v1 += v2;
        }
    }
    return v1;

}


void set_line(char buf[]) {
    line = buf;
}


void get_token(Token *token) {
    int t_pos = 0;
    token->kind = BAD_TOKEN;
    while (token->kind != END_OF_LINE_TOKEN) {
        char current_char = line[st_pos];
        token->str[t_pos] = current_char;
        printf("%c", current_char);
        if (isdigit(current_char)) {
            token->kind = IN_PART_INT_TOKEN;
        }
        if (token->kind == IN_PART_INT_TOKEN && !isdigit(current_char)) {
            sscanf(token->str, "%lf", &token->value);
            token->kind = NUMBER_TOKEN;
            return;
        } else if (st_pos >= MAX_TOKEN_SIZE || current_char == '\n') {
            token->kind = END_OF_LINE_TOKEN;
            return;
        } else if (current_char == '+') {
            token->kind = ADD_OPERATOR_TOKEN;
            t_pos++;
            st_pos++;

            return;
        } else if (current_char == '-') {
            token->kind = SUB_OPERATOR_TOKEN;
            t_pos++;
            st_pos++;

            return;
        } else if (current_char == '*') {
            token->kind = MUL_OPERATOR_TOKEN;
            t_pos++;
            st_pos++;
            return;
        }

        t_pos++;
        st_pos++;

    }

}


int main() {
    char buf[1024];
    fgets(buf, 1024, stdin);
    set_line(buf);
    double v1;
//    Token token;
    for (;;) {
        v1 = parse_expression();
        printf("%f", v1);
        break;
    }
    return 0;
}








