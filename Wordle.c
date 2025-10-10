
/* Konstanter för färgkodning*/
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define CYAN "\033[32m"
#define RESET "\33[0m"

/* Bibblotek */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_NUM_WORDS 30

/* Variabler för hela programmet*/
char guess[50];
const int buffer = 50;
int iterations = 0;
int tries = 5;
char words[TOTAL_NUM_WORDS][6] = {"HELLO", "WATER", "MUSIC", "HOUSE", "APPLE",
                                  "CEASE", "SINCE", "APPLE", "QUIRK", "WALTZ",
                                  "GREEN", "LIGHT", "HAPPY", "CHAIR", "SMILE",
                                  "LUCID", "RELIC", "BREAD", "SWIRL", "HEART",
                                  "DANCE", "FLARE", "STONE", "RIVER", "FLINT",
                                  "NIGHT", "CLOUD", "DREAM", "JIFFY", "CRAVE"
                                };
char *secret_word;

/* Funktions deklerationer */
void upper_word(char *word);
int check_word(char *secret_word, char guess[]);
void count_letters(char *word, int letter_count[]);

/* Main-programmet */
int main() {
    
    srand(time(NULL));
    secret_word = words[rand() % TOTAL_NUM_WORDS];

    while (iterations < tries) {
        
        int result = 0;
        printf(RESET "Enter a 5-letter word: "); 
        fgets(guess, buffer, stdin);
        upper_word(guess);
        
        result = check_word(secret_word, guess);


        if(result == 5) { // Ifall spelaren gissar rätt
            printf("Good job! You found the right word!\n");
            break;
        } 
        else if (iterations == (tries - 1)) // Ifall spelaren gissar fel alla gånger
        {
                printf("Too bad! The word was:\n");
                printf(CYAN "%s\n" RESET, secret_word);
                break;
        }

        iterations++;
    }

    printf("Finished!\n");
    printf("Press enter to finish the program... ");
    getchar();
    return 0;
}

/* Funktions defentioner */

// Gör så att ett ord ALLTID bara har stora bokstäver
void upper_word(char *word) {
     
    int letter_int;
    

    for (int i = 0 ; i < 5 ; i++) {
        letter_int = word[i];

        if (letter_int >= 97) {
            
            letter_int -= 32;
            word[i] = letter_int;
        }
    }
}   

// Funktion för att kolla på spelarens gissning
int check_word(char *secret_word, char *guess)
{
    if (strlen(guess) > 6) {
        printf(RED "Too long word!\n" RESET);
        return -1;
    } else if (strlen(guess) < 6 ) {
        printf(RED "Too short word!\n" RESET);
        return -1;
    }

    /* Status
        - g : Grön (Rätt bokstav, rätt plats)
        - y: Gul (Rätt bokstav men fel position)
        - 0: Röd (Helt fel) 
    */
    // Deklarera status-array och sätt alla till 0, översätts sedan till Grön, Gul eller ingenting
    char status[5];
    for (int i = 0 ; i < 5 ; i++) {
        status[i] = '0';
    }

    /* En array som representerar antalet bokstäver i alfabetet från a-z (26 bokstäver)
       0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
       A B C D E F G H I J K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
       0 0 0 0 0 0 0 0 0 0 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
    */
    int letter_count[26];
    for (int i = 0 ; i < 26 ; i++) {
        letter_count[i] = 0;
    }

    /* Funktion som räknar ut hur många bokstäver det är på ett ord */
    count_letters(secret_word, letter_count);
    
    int correct_guess_count = 0;

    printf("\n");
    // Koll för g-bokstäver
    for (int i = 0 ; i < 5 ; i++) {
        if (guess[i] == secret_word[i]) {
            status[i] = 'g';
            correct_guess_count++;
            letter_count[(int)secret_word[i] - (int)'A']--;
        }
        
    }
    

    // Koll för y-bokstäver
    for (int i = 0 ; i < 5 ; i++) {
        for (int l = 0 ; l < 5 ; l++) {
            if ((status[i] != 'g') && (letter_count[(int)secret_word[l] - (int)'A'] > 0) && (guess[i] == secret_word[l])) {
                status[i] = 'y';
                letter_count[(int)secret_word[l] - (int)'A']--;
                break;
            }
        }
    }

    printf("Results:\n");

    for (int res = 0 ; res < 5 ; res++) {
        if (status[res] == 'g') {
            printf(GREEN "%c" RESET, guess[res]);
        } 
        else if (status[res] == 'y') {
            printf(YELLOW "%c" RESET, guess[res]);
        }
        else {
            printf(RED "%c" RESET, guess[res]);
        }
    }
    printf("\n");
    return correct_guess_count;
}

/* Mindre funktioner finns här! */

/**
 * count_letters(): Funktion som räknar hur många bokstäver det är på ett ord
 * 
 * @param word 
 * @param letter_count 
 */
void count_letters(char *word, int letter_count[]) {

    int letter_ASCII;

    for (int i = 0 ; i < 5 ; i++) {
        letter_ASCII = word[i];
        letter_count[letter_ASCII - (int)'A']++;
    }

}