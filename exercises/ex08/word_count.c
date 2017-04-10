void read_words (FILE *f) {
    char x[1024];
    /* assumes no word exceeds length of 1023 */
    while (fscanf(f, " %1023s", x) == 1) {
        puts(x);
    }
}
