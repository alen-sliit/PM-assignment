#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROUNDS 13
#define DICE 5
#define CATEGORIES 8

void rollDice(int dice[]);
int humanTurn(int dice[]);
int chooseCategory();
int getScore(int countOne, int countTwo, int countThree, int countFour, int countFive, int Category);
int calculateScore(int dice[], int category);
int getScoreAKind(int count, int Category);
int getCardCount(int dice[], int Category);


// Scoring categories
enum Categories { ONES = 1, TWOS, THREES, FOURS, FIVES, SIXES, THREE_OF_A_KIND, FOUR_OF_A_KIND, FULL_HOUSE, SMALL_STRAIGHT, LARGE_STRAIGHT, YAHTZEE, CHANCE };


int main() {
    int humanScore = 0, computerScore = 0;
    int dice[DICE];
    
    printf("Welcome to Two-Player Yahtzee (Human vs Computer)");

    //Rounds 13
    for(int rounds; rounds < ROUNDS; rounds++){
        printf("Human's turn:\n");
        humanScore += humanTurn(dice);
        system("clear");
        printf("Human's total score: %d\n", humanScore);
        printf("\nComputer's turn:\n");
         
    }
    return 0;
}

void rollDice(int dice[]) {
    printf("Rolled dice: ");
    for (int i = 0; i < DICE; i++) {
        dice[i] = (rand() % 6) + 1;
        printf("%d ", dice[i]);
    }
    printf("\n");
}

int humanTurn(int dice[]) {
    rollDice(dice);
    int reroll[DICE];
    int rerolls;
    
    for (int roll = 0; roll < 2; roll++) {  // Allow 2 rerolls (3 rolls total)
        printf("Do you want to re-roll? (0: No, 1: Yes): ");
        scanf("%d", &rerolls);
        
        if (rerolls == 0) 
            break;
        
        for (int i = 0; i < DICE; i++) {
            printf("Keep die %d? (0: Re-roll, 1: Keep): ", dice[i]);
            scanf("%d", &reroll[i]);
        }
        printf("Rolled dice: ");
        for (int i = 0; i < DICE; i++) {
            if (reroll[i] == 0) {
                dice[i] = (rand() % 6) + 1;  // Re-roll the selected dice
            }
            printf("%d ", dice[i]);
        }
        printf("\n");
        
    }
    return (calculateScore(dice, chooseCategory()));
}

// Choose scoring category for human player
int chooseCategory() {
    int category;
    printf(" 1 for ONES\n 2 for TWOS\n 3 for THREES\n 4 for FOURS\n 5 for FIVES\n 6 for SIXES\n 7 for THREE OF A KIND\n 8 for FOUR OF A KIND\n 9 for FULL HOUSE\n 10 for SMALL STRAIGHT\n 11 for LARGE STRAIGHT\n 12 for YAHTZEE\n 13 for CHANCE\n Choose a category to score: ");
    scanf("%d", &category);
    return category;
}

int chooseWinner(int humanPoints, int computerPoints){
    if (humanPoints > computerPoints) {
        printf("\nHuman wins with a score of %d vs %d!\n", humanPoints, computerPoints);
    } else if (humanPoints < computerPoints) {
        printf("\nComputer wins with a score of %d vs %d!\n", computerPoints, humanPoints);
    } else {
        printf("\nIt's a tie! Both players scored %d!\n", humanPoints);
    }

}

int calculateScore(int dice[], int category) {
    int score = 0;
    int countOne = 0;
    int countTwo = 0;
    int countThree = 0;
    int countFour = 0;
    int countFive = 0;
    int diffDices[5];
    switch (category) {
        case ONES:
        case TWOS:
        case THREES:
        case FOURS:
        case FIVES:
        case SIXES:
            for (int i = 0; i < DICE; i++) {
                if (dice[i] == category) {
                    score += dice[i];
                }
            }
            break;
        case THREE_OF_A_KIND:
            countOne, countTwo, countThree, countFour, countFive, category = getCardCount(dice, category);
            score += getScoreAKind(countThree, category);
            break;
        case FOUR_OF_A_KIND: 
            countOne, countTwo, countThree, countFour, countFive, category = getCardCount(dice, category);
            score += getScoreAKind(countFour, category);
            break;
        case FULL_HOUSE:
        case SMALL_STRAIGHT:
        case LARGE_STRAIGHT:
        case YAHTZEE:
        case CHANCE:
            for (int i = 0; i < DICE; i++) {
                score += dice[i];
            }
            break;
        // Add other cases for Three of a Kind, Full House, etc.
        default:
            printf("Choose a valid category\n");
        

    }
    return score;
}

int getCardCount(int dice[], int Category){
    int countOne = 0;
    int countTwo = 0;
    int countThree = 0;
    int countFour = 0;
    int countFive = 0;

    for (int i = 0; i < DICE; i++) {
        switch (dice[i]){
        case 1:
            countOne += 1;
            break;
        case 2:
            countTwo += 1;
            break;
        case 3:
            countThree += 1;
            break;
        case 4:
            countFour += 1;
            break;
        case 5:
            countFive += 1;
            break;
                
        default:
            break;
    }}
    return (countOne, countTwo, countThree, countFour, countFive, Category);
}

int getScoreAKind(int count, int Category){
    if (count == Category)
        return count*Category;
}
