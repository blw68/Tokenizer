/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
  char *newStr;
  char ** arr;
  int index;
  int numTokens;
};

typedef struct TokenizerT_ TokenizerT;

int check0tokens(char * str);
int getState(char c);
int isLetter(char c);
int isDigit(char c);
int isFloat(char c);
int isOctal(char c);
int isHex(char c);
char * identify(char * str);
int hasDot(char * str, int j);
TokenizerT * TKCreate(char * ts);
void TKDestroy(TokenizerT * tk);
char * TKGetNextToken(TokenizerT * tk);

int check0tokens(char * str){
  int i;
  int allSpaces = 0;
  for (i = 0; i < strlen(str); i++){
    if (str[i] == ' '){
      
    }
    else {
      allSpaces = 1;
    }
  }
  return allSpaces;
}

int getState(char c){
  if (isspace(c)){
    return 0;
  }
  else if (isLetter(c) == 1){
    return 1;
  }
  else if (isDigit(c) == 1){
    return 2;
  }
  else {
    return 3;
  }
}

int hasDot(char * str, int j){
  int i;
  for (i = j; i >= 0; i--){
    if (str[i] == 'e' || str[i] == 'E'){
      continue;
    }
    /*
    if ((i == j-1 )&& (str[i] == '.')){
      return 0;
    }
    */
    if (str[i] == '.'){
      return 1;
    }
    if (isDigit(str[i]) == 0){
      return 0;
    }
  }
  return 0;
}

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
  int i;
  int numEntries;
//  char * newStr;
//  newStr = malloc(sizeof(char) * 80);
  TokenizerT * t;
  t = malloc(sizeof(struct TokenizerT_));
  t->newStr = malloc(strlen(ts) * 2); 
  strcpy(t->newStr, "");
//  printf("newStr %s\n", t->newStr);
  char temp[80];

  char prev = ts[0];
  for (i = 0; i < strlen(ts); i++){
    printf("%d %c%d %c%d\n", i, prev, getState(prev), ts[i], getState(ts[i]));
    if (i == 0){
      temp[0] = ts[i];
      temp[1] = 0;
      strcat(t->newStr, temp); 
    }
    else if (getState(prev) == 1 && getState(ts[i]) == 2){
      if (prev == 'e' || prev == 'E'){
        if (hasDot(ts, i) == 1){
            temp[0] = ts[i];
            temp[1] = 0;
            strcat(t->newStr, temp);
            continue;
        }
        else {
          strcat(t->newStr, " ");
          temp[0] = ts[i];
          temp[1] = 0;
          strcat(t->newStr, temp);
          printf("added, ts[i] = %c\n", ts[i]);
          continue;
        }
      }
      if (prev == 'x' || prev == 'X'){
        if (i > 1){
          if (ts[i-2] == '0'){
            temp[0] = ts[i];
            temp[1] = 0;
            strcat(t->newStr, temp);
          }
        }
        else {
          strcat(t->newStr, " ");
          temp[0] = ts[i];
          temp[1] = 0;
          strcat(t->newStr, temp); 
        }
      }
      else {
        strcat(t->newStr, " ");
        temp[0] = ts[i];
        temp[1] = 0;
        strcat(t->newStr, temp); 
      }
    }
    else if (getState(prev) == 1 && getState(ts[i]) == 3){
      strcat(t->newStr, " ");
      temp[0] = ts[i];
      temp[1] = 0;
      strcat(t->newStr, temp); 
    }
    else if (getState(prev) == 2 && getState(ts[i]) == 1){
      if (prev == '0'){
        if (ts[i] == 'x' || ts[i] == 'X'){
          temp[0] = ts[i];
          temp[1] = 0;
          strcat(t->newStr, temp);
        }
        else {
          strcat(t->newStr, " ");
          temp[0] = ts[i];
          temp[1] = 0;
          strcat(t->newStr, temp);
        }
      }
      else if (ts[i] == 'e' || ts[i] == 'E'){
        temp[0] = ts[i];
        temp[1] = 0;
        strcat(t->newStr, temp);
        /*
        if (hasDot(ts, i) == 1){
          temp[0] = ts[i];
          temp[1] = 0;
          strcat(t->newStr, temp);
        }
        else {
          strcat(t->newStr, " ");
          temp[0] = ts[i];
          temp[1] = 0;
          strcat(t->newStr, temp);
        }
        */
      }
      else {
        strcat(t->newStr, " ");
        temp[0] = ts[i];
        temp[1] = 0;
        strcat(t->newStr, temp); 
      }
    }
    else if (getState(prev) == 2 && getState(ts[i]) == 3){
      if (ts[i] == '.'){
        temp[0] = ts[i];
        temp[1] = 0;
        strcat(t->newStr, temp);
      }
      else {
        strcat(t->newStr, " ");
        temp[0] = ts[i];
        temp[1] = 0;
        strcat(t->newStr, temp); 
      }
    }
    else if (getState(prev) == 3 && getState(ts[i]) == 1){
      strcat(t->newStr, " ");
      temp[0] = ts[i];
      temp[1] = 0;
      strcat(t->newStr, temp); 
    }
    else if (getState(prev) == 3 && getState(ts[i]) == 2){
      if (prev == '.'){
        temp[0] = ts[i];
        temp[1] = 0;
        strcat(t->newStr, temp);
      }
      else{
        strcat(t->newStr, " ");
        temp[0] = ts[i];
        temp[1] = 0;
        strcat(t->newStr, temp); 
      }
    }
    else if (getState(prev) == 0 && getState(ts[i]) == 1){
      strcat(t->newStr, " ");
      temp[0] = ts[i];
      temp[1] = 0;
      strcat(t->newStr, temp); 
    }
    else if (getState(prev) == 0 && getState(ts[i]) == 2){
      strcat(t->newStr, " ");
      temp[0] = ts[i];
      temp[1] = 0;
      strcat(t->newStr, temp); 
    }
    else if (getState(prev) == 0 && getState(ts[i]) == 3){
      strcat(t->newStr, " ");
      temp[0] = ts[i];
      temp[1] = 0;
      strcat(t->newStr, temp); 
    }
    else {
      temp[0] = ts[i];
      temp[1] = 0;
      strcat(t->newStr, temp); 
    }
    prev = ts[i];
    printf("%s\n", t->newStr);
  }

//  printf("should be more than 9 %d\n", 2 * strlen(t->newStr));

  numEntries = 2 * strlen(t->newStr);
  t->arr = malloc(sizeof(char *) * numEntries);
  for (i = 0; i < numEntries; i++){
    t->arr[i] = malloc(sizeof(char) * strlen(t->newStr) + 50); 
  }

  t->index = 0;
  t->numTokens = 0;
  /*
  t->arr = malloc(sizeof(char*) * strlen(t->newStr));
  for (i = 0; i < 200; i++){
    t->arr[i] = malloc(strlen(t->newStr) * 2);
  }
  */

  char * pch;
  pch = strtok(t->newStr, " ");
  while (pch != NULL){
//    printf("%s \"%s\"\n", identify(pch), pch);
    strcpy(t->arr[t->numTokens], identify(pch));
    strcat(t->arr[t->numTokens], "\"");
    strcat(t->arr[t->numTokens], pch);
    strcat(t->arr[t->numTokens], "\"");
    pch = strtok(NULL, " ");
    t->numTokens++;
  }
  return t;
  return NULL;
}

int isLetter(char c){
  // return 1 if c is a letter, 0 otherwise
  if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' || c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z'){
    return 1;
  }
  if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' || c == 'H' || c == 'I' || c == 'J' || c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'O' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' || c == 'U' || c == 'V' || c == 'W' || c == 'X' || c == 'Y' || c == 'Z'){
    return 1;
  }
  return 0;
}

int isDigit(char c){
  if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){
    return 1;
  }
  return 0;
}

int isOctal(char c){
  if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7'){
    return 1;
  }
  return 0;
}

int isHex(char c){
  if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F'){
    return 1;
  }
  return 0;
}

int isFloat(char c){
  if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '.' || c == 'E' || c == 'e' || c == '+' || c == '-'){
    return 1;
  }
  return 0;
}

char * identify(char * token){
  int i;
  int allLets1 = 1;
  int allNums1 = 1;
  int allOctals1 = 1;
  int allHex1 = 1;
  int allFloat1 = 1;
  int numDots = 0;
  int numE = 0;
  int plusMinus = 0;
  int dotIndex = 0;
  int EIndex = 0;

  if (strcmp(token, "(") == 0){
    return "left paren ";
  }
  if (strcmp(token, ")") == 0){
    return "right paren ";
  }
  if (strcmp(token, "[") == 0){
    return "left brace ";
  }
  if (strcmp(token, "]") == 0){
    return "right brace ";
  }
  if (strcmp(token, ".") == 0){
    return "period ";
  }
  if (strcmp(token, "->") == 0){
    return "pointer ";
  }
  if (strcmp(token, "*") == 0){
    return "star ";
  }
  if (strcmp(token, "&") == 0){
    return "bitwise and ";
  }
  if (strcmp(token, "-") == 0){
    return "minus ";
  }
  if (strcmp(token, "!") == 0){
    return "negate ";
  }
  if (strcmp(token, "~") == 0){
    return "bitwise not ";
  }
  if (strcmp(token, "++") == 0){
    return "plusplus ";
  }
  if (strcmp(token, "--") == 0){
    return "minusminus ";
  }
  if (strcmp(token, "/") == 0){
    return "slash ";
  }
  if (strcmp(token, "%") == 0){
    return "mod ";
  }
  if (strcmp(token, "+") == 0){
    return "plus ";
  }
  if (strcmp(token, ">>") == 0){
    return "shiftright ";
  }
  if (strcmp(token, "<<") == 0){
    return "shiftleft ";
  }
  if (strcmp(token, "<") == 0){
    return "less than ";
  }
  if (strcmp(token, ">") == 0){
    return "greater than ";
  }
  if (strcmp(token, "<=") == 0){
    return "less than or equal ";
  }
  if (strcmp(token, ">=") == 0){
    return "greater than or equal ";
  }
  if (strcmp(token, "==") == 0){
    return "equalsequals ";
  }
  if (strcmp(token, "!=") == 0){
    return "notequals ";
  }
  if (strcmp(token, "|") == 0){
    return "bitwise or ";
  }
  if (strcmp(token, "&&") == 0){
    return "logical and ";
  }
  if (strcmp(token, "||") == 0){
    return "logical or ";
  }
  if (strcmp(token, "?") == 0){
    return "true ";
  }
  if (strcmp(token, ":") == 0){
    return "false ";
  }
  if (strcmp(token, "+=") == 0){
    return "plusequals ";
  }
  if (strcmp(token, "-=") == 0){
    return "minusequals ";
  }
  if (strcmp(token, "*=") == 0){
    return "starequals ";
  }
  if (strcmp(token, "/=") == 0){
    return "slashequals ";
  }
  if (strcmp(token, "%=") == 0){
    return "modequals ";
  }
  if (strcmp(token, ">>=") == 0){
    return "bitwise shiftright ";
  }
  if (strcmp(token, "<<=") == 0){
    return "bitwise shiftleft ";
  }
  if (strcmp(token, "&=") == 0){
    return "andequals ";
  }
  if (strcmp(token, "|=") == 0){
    return "orequals ";
  }
  if (strcmp(token, "^=") == 0){
    return "xorequals ";
  }
  if (strcmp(token, ",") == 0){
    return "comma ";
  }

  for (i = 0; i < strlen(token); i++){
    if (token[i] == '.'){
      numDots++;
      dotIndex = i;
    }
    if (token[i] == 'E' || token[i] == 'e'){
      numE++;
      EIndex = i;
    }
    if (token[i] == '+' || token[i] == '-'){
      plusMinus++;
    }
    if (isLetter(token[i]) == 0){
      allLets1 = 0;
    }
    if (isDigit(token[i]) == 0){
      allNums1 = 0;
    }
    if (isOctal(token[i]) == 0){
      allOctals1 = 0;
    }
    if (i != 1 && isHex(token[i]) == 0){
      allHex1 = 0;
    }
    if (isFloat(token[i]) == 0){
      allFloat1 = 0;
    }
  }
  if (allLets1 == 1){
    return "word ";
  }
  if (token[0] == '0' && allOctals1 == 1){
    return "octal constant ";
  }
  if (token[0] == '0'){
    if (token[1] == 'x' || token[1] == 'X'){
      if (allHex1 == 1){
        return "hex constant ";
      }
    }
  }
  if (allFloat1 == 1){
    if (numDots == 1){
      if (numE == 1){
        if (plusMinus < 2){
          if (dotIndex + 1 < EIndex){
            return "float constant ";
          }
        }
      }
    }
  }
  if (allFloat1 == 1){
    if (numDots == 1){
      if (numE == 0){
        if (plusMinus < 2){
          return "float constant ";
        }
      }
    }
  }
  if (allNums1 == 1){
    return "decimal constant ";
  }
  
  return "";
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
  int i;
  for (i = 0; i < tk->numTokens; i++){
    free(tk->arr[i]);
  }
  free(tk->arr);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
//  int i;
  char * ret;
  ret = malloc(sizeof(char) * strlen(tk->newStr) + 50);
  strcpy(ret, "");
//  tk->arr = malloc(sizeof(char *) * strlen(tk->newStr));
//  tk->arr = malloc(200);
//  for (i = 0; i < tk->numTokens; i++){
//    tk->arr[i] = malloc(sizeof(char) * strlen(tk->newStr));
// }
//  printf("%d %d\n", tk->index, tk->numTokens);
  if (tk->index >= tk->numTokens){
    return NULL;
  }
//  printf("ret %s\n", tk->arr[tk->index]);
  strcpy(ret, tk->arr[tk->index]);
  /*
  strcpy(ret, identify(tk->arr[tk->index]));
  strcat(ret, " \"");
  strcat(ret, tk->arr[tk->index]);
  strcat(ret, " \"");
  */

  tk->index++;
  
  return ret;

  return NULL;
}

void TKGetNextToken1( TokenizerT * tk ) {
  char * pch;
  pch = strtok(tk->newStr, " ");
  while (pch != NULL){
    printf("%s \"%s\"\n", identify(pch), pch);
    pch = strtok(NULL, " ");
  }
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
  int i;
  char * orig;
  if (argc != 2){
    fprintf(stderr, "usage: ./tokenizer \"String\"\n");
    exit(0);
  }
  orig = argv[1];
  if (check0tokens(orig) == 0){
    fprintf(stderr, "String must contain at least 1 token\n");
    exit(0);
  }
  printf("orig %s\n", orig);
  TokenizerT * t = TKCreate(orig);
  for (i = 0; i < t->numTokens; i++){
//  for (i = 0; i < sizeof(t->arr); i++){
    printf("%s\n",t->arr[i]);
  }
//  printf("%s\n", t->newStr);
//  TKGetNextToken1(t);
  char * charPtr = NULL;
  while ((charPtr = TKGetNextToken(t)) != NULL){
//    printf("%s %s\n", identify(charPtr), charPtr);
    printf("charPtr %s\n", charPtr);
    free(charPtr);
  }
  TKDestroy(t);
//  printf("%d\n", hasDot("5.2345e10", 6));
  return 0;
}
