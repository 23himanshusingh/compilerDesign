#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 10000

char curr_token[MAX_TOKEN_LEN];

typedef enum {false, true} bool;

int is_keyword(char* token) {
    char* keywords[] = {"False", "None", "True", "and", "as", "assert", "break", "class", 
"continue", "def", "del", "elif", "else", "except", "finally", 
"for", "from", "global", "if", "import", "in", "is", "lambda", 
"nonlocal", "not", "or", "pass", "raise", "return", 
"try", "while", "with", "yield","do"};
    int num_keywords = 34;
    int i;
    for (i = 0; i <num_keywords; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_package(char* token) {
    char* packages[] = 
    {"numpy","pandas","pendulum","itertools","collections","math"};
    int num = 6;
    int i;
    for (i = 0; i <num; i++) {
        if (strcmp(token, packages[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
int line=1;
int flag=0;
int indent[MAX_TOKEN_LEN]={0};
int get_next_token(FILE* fp,FILE* out_fp) {
    if (line==1 && flag==0){
        flag=1;
        fprintf(out_fp,"Line number: %d\n\n",line);
    }
    char curr_char;
    int curr_token_pos = 0;
    curr_token[0] = '\0';
    bool in_string = false;
    bool in_comment = false;
    while ((curr_char = fgetc(fp)) != EOF) {
        if (curr_char == '\n') {
            if (in_comment) {
                in_comment = false;
                fprintf(out_fp,"Line number %d contains a comment\n",line);
            }
            
            line+=1;
            fprintf(out_fp,"Line number: %d\n\n",line);
            continue;
        }


        if (in_comment) {
            continue;
        }
        if (isspace(curr_char)) {
            if (in_string) {
                curr_token[curr_token_pos++] = curr_char;
            }
            else if (in_comment) {
                    in_comment = false;
            }
            else{
                indent[line]++;
            }
            continue;
        }
        if (curr_char == '#') {
            if (in_string) {
                curr_token[curr_token_pos++] = curr_char;
                continue;
            } else {
                in_comment = true;
                continue;
            }
        }
        curr_token[curr_token_pos++] = curr_char;
        if (curr_char == '"' || curr_char == '\'') {
            if (!in_string) {
                in_string = true;
            } else if (curr_char == curr_token[0]) {
                in_string = false;
                curr_token[curr_token_pos] = '\0';
                fprintf(out_fp,"String: %s\n", curr_token);
                return 1;
            }
        }
        if (in_string) {
            continue;
        }
        if (isalpha(curr_char) || curr_char == '_') {
            while (isalnum(curr_char = fgetc(fp)) || curr_char == '_') {
                curr_token[curr_token_pos++] = curr_char;
            }
            curr_token[curr_token_pos] = '\0';
            if (is_keyword(curr_token)) {
                fprintf(out_fp,"Keyword: %s\n", curr_token);
                if (!strcmp(curr_token,"while") || !strcmp(curr_token,"do") || !strcmp(curr_token,"for")){
                    fprintf(out_fp,"A %s loop starts at line number: %d\n",curr_token,line);
                }
                if (!strcmp(curr_token,"if") || !strcmp(curr_token,"elif") || !strcmp(curr_token,"else")){
                    fprintf(out_fp,"A %s block starts at line number: %d\n",curr_token,line);
                }
            }
            else if(is_package(curr_token)) {
                fprintf(out_fp,"Package: %s\n", curr_token);
            }

            else {
                fprintf(out_fp,"Identifier: %s\n", curr_token);
            }
            ungetc(curr_char, fp);
            return 1;
        }
        if (isdigit(curr_char)) {
            int is_float = 0;
            if (curr_char == '.') {
                is_float = 1;
            }
            while (isdigit(curr_char = fgetc(fp)) || (!is_float && curr_char == '.')) {
                if (curr_char == '.') {
                    is_float = 1;
                }
            curr_token[curr_token_pos++] = curr_char;
        }
        curr_token[curr_token_pos] = '\0';
        if (is_float) {
            fprintf(out_fp,"Floating Point Number: %s\n", curr_token);
        } 
        else {
            fprintf(out_fp,"Number: %s\n", curr_token);
        }   
        ungetc(curr_char, fp);
        return 1;
        }
        if (curr_char == '=') {
            int next_char = fgetc(fp);
            if (next_char == '=') {
                fprintf(out_fp,"Relational Operator(Equal): ==\n");
            } else {
                fprintf(out_fp,"Assignment Operator: =\n");
                ungetc(next_char, fp);
            }
            return 1;
        }
        if (curr_char == '*') {
            int next_char = fgetc(fp);
            if (next_char == '*') {
                fprintf(out_fp,"Arithmetic Operator(Exponentiation): **\n");
            } else {
                fprintf(out_fp,"Arithmetic Operator(Multiplication): *\n");
                ungetc(next_char, fp);
            }
            return 1;
        }
        if (curr_char == '<') {
            int next_char = fgetc(fp);
            if (next_char == '<') {
                fprintf(out_fp,"Bitwise Operator(left shift): <<\n");
            }
            else if (next_char == '='){
                fprintf(out_fp,"Relational Operator(less than or equal): <=\n");
            }
            else {
                fprintf(out_fp,"Relational Operator(less than): <\n");
                ungetc(next_char, fp);
            }
            return 1;
        }
        if (curr_char == '>') {
            int next_char = fgetc(fp);
            if (next_char == '>') {
                fprintf(out_fp,"Bitwise Operator(right shift): >>\n");
            }
            else if (next_char == '='){
                fprintf(out_fp,"Relational Operator(greater than or equal): >=\n");
            }
            else {
                fprintf(out_fp,"Relational Operator(greater than): >\n");
                ungetc(next_char, fp);
            }
            return 1;
        }
        if (curr_char == '/') {
            int next_char = fgetc(fp);
            if (next_char == '/') {
                fprintf(out_fp,"Arithmetic Operator(floor division): //\n");
            } else {
                fprintf(out_fp,"Arithmetic Operator(division): /\n");
                ungetc(next_char, fp);
            }
            return 1;
        }
        if (curr_char == '!') {
            int next_char = fgetc(fp);
            if (next_char == '=') {
                fprintf(out_fp,"Relational Operator(not equal): !=\n");
            } else {
                fprintf(out_fp,"Unknown character: !\n");
                ungetc(next_char, fp);
            }
            return 1;
        }
        if (curr_char == ':') {
            int next_char = fgetc(fp);
            if (next_char == '=') {
                fprintf(out_fp,"Operator: :=\n");
            } else {
                fprintf(out_fp,"Delimeter(Colon): :\n");
                ungetc(next_char, fp);
            }
            return 1;
        }
if (curr_char == '+') {
    fprintf(out_fp, "Arithmetic Operator(addition): +\n");
} else if (curr_char == '-') {
    fprintf(out_fp, "Arithmetic Operator(subtraction): -\n");
} else if (curr_char == '%') {
    fprintf(out_fp, "Arithmetic Operator(Modulus): %%\n");
} else if (curr_char == '&') {
    fprintf(out_fp, "Logical Operator(AND): &\n");
} else if (curr_char == '|') {
    fprintf(out_fp, "Logical Operator(OR): |\n");
} else if (curr_char == '^') {
    fprintf(out_fp, "Logical Operator(XOR): ^\n");
} else if (curr_char == '~') {
    fprintf(out_fp, "Logical Operator(NOT): ~\n");
}
return 1;
if (curr_char == '(') {
    fprintf(out_fp, "Delimiter(left open parenthesis): (\n");
} else if (curr_char == ')') {
    fprintf(out_fp, "Delimiter(right open parenthesis): )\n");
} else if (curr_char == '[') {
    fprintf(out_fp, "Delimiter(left closed parenthesis): [\n");
} else if (curr_char == ']') {
    fprintf(out_fp, "Delimiter(right closed parenthesis): ]\n");
} else if (curr_char == ',') {
    fprintf(out_fp, "Delimiter(comma): ,\n");
} else if (curr_char == ':') {
    fprintf(out_fp, "Delimiter(colon): :\n");
} else if (curr_char == '.') {
    fprintf(out_fp, "Delimiter(dot): .\n");
} else if (curr_char == ';') {
    fprintf(out_fp, "Delimiter(semicolon): ;\n");
} else if (curr_char == '\\') {
    fprintf(out_fp, "Delimiter: \\\n");
} else if (curr_char == '{') {
    fprintf(out_fp, "Delimiter(left curly braces): {\n");
} else if (curr_char == '}') {
    fprintf(out_fp, "Delimiter(right curly braces): }\n");
} 
        
fprintf(out_fp,"Unknown character: %c\n", curr_char);
        return 1;
}
    return 0;
}
int main() {
    FILE* fp = fopen("program.txt", "r");
    FILE* out_fp = fopen("output.txt", "w");
    while (get_next_token(fp,out_fp)) { }
    fclose(fp);
    fclose(out_fp);
    for (int i=0;i<line;i++){
        printf("%d ",indent[i]);
    }
    printf("\n");
    return 0;
}