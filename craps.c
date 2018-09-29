#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void   print_game_rules (void);
int    roll_dice (void);
double get_bank_balance(void);
int main (void)
{
    double initial_balance = 0.0;
    print_game_rules();

    printf ("Please enter an initial bank balance for wagering: ");
    initial_balance = get_bank_balance();

    printf ("%f\n", initial_balance);

    printf ("Roll Dice #1: %d\n", roll_dice());
    return 0;
}

void print_game_rules (void)
{
    char space = 'a';

    printf ("The rules for craps are as follows:\n\n");
    printf ("A player rolls two dice. Each die has six faces. These faces contain 1, 2, 3, 4, 5 and 6 spots. After the die have come to rest, the sum of the spots are calculated.\n");
    printf ("If the sum is 7 or 11 on the first throw, the player wins. If the sume is 2, 3, or 12 on the first throw (called craps), the player loses.\n");
    printf ("If the sum is 4, 5, 6, 8, 9 or 10 on the first throw, then that sume becomes the players point.\n");
    printf ("To win, they must keep rolling the dice until they make their point. The player loses if they roll a 7 before making their point.\n\n\n");

    printf ("Please press space  and then enter to continue...");
    scanf ("%c", &space);
    if (space == ' ') {
        printf ("\n");
        return;
    }
}

double get_bank_balance (void)
{
    double balance = 0;

    scanf ("%lf", &balance);

    if ( balance <= 0) {
        printf ("Please enter a balance greater than 0.");
        get_bank_balance();
        }
    else{
        return balance;
        }
    return -1;

}

int roll_dice (void)
{
    int result;

    srand(time(0));

    result = (rand() % 6) + 1;

    return result;
}



