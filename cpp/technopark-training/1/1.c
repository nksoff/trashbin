#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("[ERROR] expected %d args, %d given \n", 2, argc-1);
        printf("Usage: %s <word> <file>\n", argv[0]);
        return -1;
    }

    char *word = argv[1], *wordcopy = argv[1], *path2file = argv[2];
    int wordlen = 0;
    while(*(wordcopy++)) ++wordlen;

    FILE *file = fopen(path2file, "r");

    if(!file) {
        printf("[ERROR] cannot open file %s\n", path2file);
        return -2;
    }

    int words = 0, parts = 0, match = 1, matchj = 0;
    while(!feof(file)) {
        int s = (unsigned char) getc(file);
        if(s == '\n') {
            ++parts;
            continue;
        }
        else if(ispunct(s) || isspace(s)) {
            if(match && matchj == wordlen) ++words;
            match = 1, matchj = 0;
        }
        else {
            if(!match) continue;
            match = (
                    matchj < wordlen &&
                    ( (int)(unsigned char) word[matchj++] ) == s
                    );
        }
    }

    fclose(file);
    double avg = words/(float)parts;
    printf("%d words/%d parts\n\n%F\n\n", words, parts, avg);

    return 0;
}
