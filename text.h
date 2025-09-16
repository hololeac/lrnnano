#pragma once

extern int max_x;
extern int max_y;

typedef struct {
    char *line;
    int len;
    int count;
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
void add_ch(text_t* content, char ch, int row, int col);
