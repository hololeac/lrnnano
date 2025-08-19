#include "text.h"
#include "stdlib.h"
#include "string.h"

text_t *initialize_content() {
    line_t **empty_lines = malloc(sizeof(line_t *) * 8);

    if (empty_lines == NULL) {
        exit(1);
    }

    text_t *new_content = malloc(sizeof(text_t));

    if (new_content == NULL) {
        free(empty_lines);
        exit(1);
    }

    new_content->count = 0;
    new_content->len = 8;
    new_content->lines = empty_lines;
    return new_content;
}

text_t *add_more_lines(text_t *content) {
    size_t new_len = content->len + 8;
    line_t **new_lines = realloc(content->lines, new_len * sizeof(line_t *));

    if (new_lines == NULL) {
        free_content(content);
        exit(1);
    }

    content->lines = new_lines;
    content->len += 8;
    return content;
}

void add_line(char *string, text_t *content) {
    if (content == NULL) {
        return;
    }

    if (content->len == content->count) {
        content = add_more_lines(content);
    }

    size_t line_len = strlen(string) + 1;

    line_t *line = malloc(sizeof(line_t));
    char *str = malloc(sizeof(char) * line_len);

    if (line == NULL || str == NULL) {
        free_content(content);
        exit(1);
    }

    strcpy(str, string);
    line->line = str;
    line->len = line_len - 1;


    content->lines[content->count] = line;
    content->count++;
}

void free_content(text_t *content) {
    for (int i = 0; i < content->len; i++) {
        free(content->lines[i]);
    }

    free(content->lines);
    free(content);
}