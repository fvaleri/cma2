#include <stdio.h>
#include "word.h"

// static make a variable or function only visible to this module
static int read_char(void) {
    // getchar treats new-line characters and tabs as spaces
    // and returns EOF when it's unable to continue reading
    int ch = getchar();
    if (ch == '\n' || ch == '\t')
        return ' ';
    return ch;
}

int read_word(char *word, int len) {
    int ch, pos = 0;

    while ((ch = read_char()) == ' ')
        ;

    while (ch != ' ' && ch != EOF) {
        if (pos < len)
            word[pos++] = ch;
        ch = read_char();
    }

    word[pos] = '\0';
    return pos;
}
