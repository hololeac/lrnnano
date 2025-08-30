#include "text.h"
#include "stdlib.h"
#include "string.h"

text_t *initialize_content() {
    line_t **empty_lines = malloc(sizeof(line_t *) * 8);

    if (empty_lines == NULL) {
        exit(1);
    }

    for (int i = 0; i < 8; i++) {
        empty_lines[i] = NULL;
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

    for (int i = content->count - 1; i < content->len; i++) {
        new_lines[i] = NULL;
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

    size_t line_len = strcspn(string, "\r\n");

    line_t *line = malloc(sizeof(line_t));
    char *str = malloc(sizeof(char) * (line_len + 1) * 2);

    if (line == NULL || str == NULL) {
        free(line);
        free(str);
        free_content(content);
        exit(1);
    }

    memcpy(str, string, line_len);
    line->line = str;
    line->len = (line_len + 1) * 2;
    line->count = line_len;


    content->lines[content->count] = line;
    content->count++;
}

void free_content(text_t *content) {
    if (content == NULL) {
        return;
    }
    for (int i = 0; i < content->len; i++) {
        if (content->lines[i]) {
            free(content->lines[i]->line);
            free(content->lines[i]);
        }
    }

    free(content->lines);
    free(content);
}

void add_ch(text_t *content, char ch, int row, int col) {
    if (content == NULL) {
        return;
    }

    line_t *ln = content->lines[row];

    //TODO: when adding to the last line and it is full you can add only 4 chars then it breaks

    //TODO: add line in the top of the file feature
    //TODO: when you type and line is finished an you go to th next - don't append the existing one, insert a new line with memmove
    //TODO: weird behaviour if previous but new line is present and you keep typing untill line has to be widened.
    if (ln != NULL && ln->count < ln->len) {
        memmove(ln->line + col + 1, ln->line + col, (size_t)ln->count - col + 1);
        ln->line[col] = ch;
        ln->count++;
    } else if (ln == NULL) {
        if (content->len == content->count) {
            content = add_more_lines(content);
        } else {
            char string[1];
            string[0] = ch;
            add_line(string, content);
        }
    } else if (ln->count == ln->len) {
        int new_len = ln->len + 64;
        char *tmp = realloc(ln->line, sizeof(char) * new_len);

        if (tmp == NULL) {
            return;
        }

        ln->line = tmp;
        ln->len = new_len;
    }
}