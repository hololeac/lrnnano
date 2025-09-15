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

//TODO: when you type and line is finished and you go to the next - don't append the existing one, insert a new line with memmove
void add_ch(text_t *content, char ch, int row, int col) {
    if (content == NULL) {
        return;
    }

    if (content->len == content->count) {
        content = add_more_lines(content);
    }

    line_t *ln = content->lines[row];

    //TODO: add line in the top of the file feature

    //TODO: weird behaviour if previous line is full but new line is present and you keep typing untill the next line is full.
    //TODO: same as above but also weird even before the next line is full
    //TODO: add text on the 2nd line, 3d one is being rewritten, then reappears and text is being appended. seems the same bug for all 3
    if (ln != NULL && ln->count < ln->len) {
        memmove(ln->line + col + 1, ln->line + col, (size_t)ln->count - col + 1);
        ln->line[col] = ch;
        ln->count++;
    } else if (ln == NULL) {
        char *str = calloc(2, sizeof(char));
        str[0] = ch;
        add_line(str, content);
        free(str);
    } else if (ln->count == ln->len) {
        int new_len = ln->len + 64;
        char *tmp = realloc(ln->line, sizeof(char) * new_len);
        memmove(tmp + col + 1, tmp + col, strlen(tmp) - col);
        tmp[col] = ch;

        if (tmp == NULL) {
            return;
        }

        ln->count++;
        ln->line = tmp;
        ln->len = new_len;
    }
}