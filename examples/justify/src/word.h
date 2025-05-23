// the WORD_H macro protects word.h from being included more than once
// it is a good practice to protect all headers file this way
#ifndef WORD_H
#define WORD_H

/*
 * Reads the next word from the input and stores it in word.
 * Makes word empty if no word could be read because of EOF.
 * Truncates the word if its length exceeds len.
 * Returns the number of characters stored.
 */
int read_word(char *word, int len);

#endif
