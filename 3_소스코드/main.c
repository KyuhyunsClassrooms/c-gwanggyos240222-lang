#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_LIVES 6

char *words[] = {"apple", "banana", "orange", "grape", "melon", "peach"};

struct Hangman {
    char *word;
    char guessed[27];
    int lives;
};

void display_word(char *word, char *guessed) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr(guessed, word[i]))
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n");
}

int main() {
    srand(time(0));

    struct Hangman game;
    game.word = words[rand() % 6];
    game.lives = MAX_LIVES;
    game.guessed[0] = '\0';

    printf("=== 행맨 게임 ===\n");

    while (game.lives > 0) {
        printf("\n단어: ");
        display_word(game.word, game.guessed);
        printf("남은 목숨: %d\n", game.lives);

        char guess;
        printf("글자를 입력하세요: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (strchr(game.guessed, guess)) {
            printf("이미 입력한 글자입니다.\n");
            continue;
        }

        int len = strlen(game.guessed);
        game.guessed[len] = guess;
        game.guessed[len + 1] = '\0';

        if (strchr(game.word, guess)) {
            printf("정답입니다!\n");
        } else {
            game.lives--;
            printf("틀렸습니다.\n");
        }

        int correct = 1;
        for (int i = 0; game.word[i] != '\0'; i++) {
            if (!strchr(game.guessed, game.word[i])) {
                correct = 0;
                break;
            }
        }

        if (correct) {
            printf("\n축하합니다! 단어 '%s'를 맞추셨습니다!\n", game.word);
            return 0;
        }
    }

    printf("\n아쉽네요... 정답은 '%s'였습니다.\n", game.word);
    return 0;
}
