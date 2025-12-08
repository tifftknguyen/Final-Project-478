// Giselle Hernandez 
// Tiffany Nguyen
// CECS 478 Final Project 
 
// Format String Guardian :
// Using AST-based static scanner to test for unsafe string formatting 
// As stated in our final proposal

// libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h> 

// UTILITY FUNC

char *trim_whitespace(char *line) {
    while (*line != '\0' && isspace((unsigned char)*line)) {
        line++;
    }
    return line;
}

int exec_code(char *line, int *in_multiline_cmt) {
    char *trimmed = trim_whitespace(line);

    // SKIP EMPTY LINES
    if (*trimmed == '\0' || *trimmed == '\n') {
        return 0;
    }

    // CHECK IF INSIDE MULTI-LINE COMMENT
    if (*in_multiline_cmt) {
        char *end_pos = strstr(line, "*/");
        if (end_pos != NULL) {
            *in_multiline_cmt = 0;
\            return exec_code(end_pos + 2, in_multiline_cmt);
        }
        return 0; // INSIDE MUTLI-LINE CMT
    }

    // CHECK START OF MULTI-LINE CMT
    if (strstr(trimmed, "/*") == trimmed) {
        char *end_pos = strstr(line, "*/");
        if (end_pos == NULL) {
            *in_multiline_cmt = 1;
            return 0; // STARTS A MULTI-LINE CMT, ASSUME REST IS CMT
        }
        return exec_code(end_pos + 2, in_multiline_cmt);
    }

    // CHECK SINGLE-LINE CMT
    if (strstr(trimmed, "//") == trimmed) {
        return 0;
    }

    if (*trimmed == '#') {
        return 0;
    }

    return 1;
}

// SEC CHECKS 

int check_format_n(const char *line, const char *filename, int line_number) {
    const char *functions[] = {"printf(", "fprintf(", "sprintf(", "snprintf(", "syslog("};

    if (strstr(line, "%n") != NULL) {
        for (size_t i = 0; i < sizeof(functions) / sizeof(functions[0]); i++) {
            if (strstr(line, functions[i]) != NULL) {
                printf("[WARNING] %s:%d  VULNERABILITY: %%n FOUND IN FMT STR (BEWARE OF HACKERS & CRACKERS).\n",
                       filename, line_number);
                return 1;
            }
        }
    }
    return 0;
}

int check_non_literal_printf(const char *line, const char *filename, int line_number) {
    char temp_line[512];
    strcpy(temp_line, line);
    
    char *pos = strstr(temp_line, "printf(");
    if (pos == NULL) {
        pos = strstr(temp_line, "fprintf("); 
    }

    if (pos != NULL) {
        pos += (strstr(pos, "printf(") != NULL) ? strlen("printf(") : strlen("fprintf(");

        // SKIP SPACES & TABS AFTER (
        while (*pos != '\0' && isspace((unsigned char)*pos)) {
            pos++;
        }

        // IF FIRST NON-WHITESPACE CHAR ISN'T A QUOTE, WARN
        if (*pos != '"' && *pos != '\0') {
            printf("[WARNING] %s:%d  VULNERABILITY: printf/fprintf WITH NON-LITERAL FORMAT (POSSIBLE USER-CONTROLLED INPUT). MITIGATION: USE printf(\"%%s\", input).\n",
                   filename, line_number);
            return 1;
        }
    }
    return 0;
}