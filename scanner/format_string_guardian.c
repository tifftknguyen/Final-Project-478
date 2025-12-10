// Giselle Hernandez 
// Tiffany Nguyen
// CECS 478 Final Project 
 
// Format String Guardian:
// Using lightweight scanner to test for unsafe string formatting 

// LIBRARIES 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h> 

// UTILITY FUNCTOIN

// FINDS FIRST NON-WHITESPACE CHAR
char *trim_whitespace(char *line) {
    while (*line != '\0' && isspace((unsigned char)*line)) {
        line++;
    }
    return line;
}

// PERFORMS SIMPLE CHECK
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
            return exec_code(end_pos + 2, in_multiline_cmt);
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

// SECURITY CHECKS 

int check_format_n(const char *line, const char *filename, int line_number) {
    const char *functions[] = {"printf(", "fprintf(", "sprintf(", "snprintf(", "syslog("};

    if (strstr(line, "%n") != NULL) {
        for (size_t i = 0; i < sizeof(functions) / sizeof(functions[0]); i++) {
            if (strstr(line, functions[i]) != NULL) {
                printf("[WARNING] %s:%d  VULNERABILITY: %%n FOUND IN FMT STR (BEWARE OF HACKERS & CRACKERS).",
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

        // IF FIRST NON-WHITESPACE CHAR ISN'T A QUOTE, WARNING
        if (*pos != '"' && *pos != '\0') {
            printf("[WARNING] %s:%d  VULNERABILITY: printf/fprintf WITH NON-LITERAL FORMAT (POSSIBLE HACKER & CRACKER CONTROL).",
                   filename, line_number);
            return 1;
        }
    }
    return 0;
}
    int check_unsafe_io_funcs(const char *line, const char *filename, int line_number){
        int warning_message = 0;

    // GETS() HAS NO BOUND CHECKING
    if (strstr(line, "gets(") != NULL){
        printf("[WARNING] %s: %d VULNERABLE USE OF GETS() CAN LEAD TO BUFFER OVERFLOW DUE TO NO BOUND CHECKS. PLEASE USE FGETS() FOR SAFE, SECURE CODE", 
            filename, line_number);
        warning_message++;
    }

    // STRCPY() WITH NO BOUND CHECKING 
    if (strstr(line, "gets(") != NULL){
        printf("[WARNING] %s: %d VULNERABLE USE OF STRCPY() CAN LEAD TO BUFFER OVERFLOW. PLEASE USE STRNCPY()!", 
            filename, line_number);
        warning_message++;
    }

    //STRCAT() WITH NO BOUND CHECKING 
    if (strstr(line, "strcat(") != NULL && strstr(line, "strncat(") == NULL){
        printf("[WARNING] %s : %d VULNERABLE USE OF STRCAT() DUE TO NO BOUND CHECKING. THIS CAN LEAD TO BUFFER OVERFLOW, PLEASE USE STRNCAT() FOR SAFE, SECURE CODE!",
            filename, line_number);
       warning_message++;
    }

    // SPRINTF() WITHOUT ANY BOUND CHECKS
    if (strstr(line, "sprintf(") != NULL){
        if (strstr(line, "sprintf(") == NULL){
            printf("[WARNING] %s : %d VULNERABLE USE OF SPRINTF() DUE TO NO BOUND CHECKING, THIS CAN LEAD TO BUFFER OVERFLOW. PLEASE USE SNPRINTF() INSTEAD FOR SAFE, SECURE CODE!",
                filename, line_number);
            warning_message++;
        }
    }

    // SCANF WITH NO CONTROL LIMIT 
    if (strstr(line, "scanf(") != NULL){
        char *fmt = strstr(line, "\"%s\"");

        // CHECKING FOR %s 
        if (fmt != NULL){
            printf("[WARNING] %s : %d VULNERABLE USE OF SCANF, USING WITHOUT SETTING LIMIT. PLEASE USE SCANF(%(MAX SIZE -1)s)", 
           filename, line_number);
           warning_message++;
        }
    }
    return warning_message;
    }


    // TO OPEN & READ FILES

    int scan_file(const char *filename){
        FILE *fp;
        char line[512];
        int line_number = 0;
        int warning_counter = 0;
        int multi_line = 0;

        fp = fopen(filename, "r");
        if (fp == NULL){
            perror("ERROR OPENING FILE");
            return -1;
        }

        while (fgets(line, sizeof(line), fp) != NULL){
            line_number++;

            // FILTERING OUR COMMENTS OUT 
            if (!exec_code(line, &multi_line)){
                continue;
            }

            warning_counter += check_format_n(line, filename, line_number);
            warning_counter += check_non_literal_printf(line, filename, line_number);
            warning_counter += check_unsafe_io_funcs(line, filename, line_number);

        }

        fclose(fp);
        return warning_counter;
    }

    int main(int argc, char *argv[]){
        int warnings; 

        if (argc != 2){
            printf("USAGE: %s <tests-directory>\n", argv[0]);
            return -1;
        }
        printf("=== FORMAT STRING GUARDIAN BEGINS ===\n");
        printf("Scanning File: %s", argv[1]);

        warnings = scan_file(argv[1]);

        if (warnings < 0) {
            printf("Error while scanning the file.\n");
            return 1;
        }

        printf("\n=== SCAN SUMMARY ===\n");
        if (warnings == 0) {
            printf("No format-string or buffer overflow problems found. \n\n\n");
        } else {
            printf("Total Warnings: %d  (Check for False positives!) \n\n\n", warnings);
        }

    return 0;
     
    

    }