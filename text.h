#pragma once

typedef struct {
    char *line;
    int len;
} line_t;

typedef struct {
    line_t **lines;
    int count;
    int len;
} text_t;

void add_line(char *string, text_t *content);
text_t *initialize_content();
text_t *add_more_lines(text_t *content);
void free_content(text_t *content);
