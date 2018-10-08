#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void   print_game_rules (void);
int    roll_dice (void);
double get_bank_balance(void);
double get_wager_amount (double);
int    calcluate_sum_dice (int, int);
int    check_if_point ( int add_subtract, int sum);
int    initial_check_loss_or_win (int sum_of_dice);
int    succesive_loss_or_neither (int sum, int point);
double adjust_bank_balance ( double balance, double wager, int add_subtract );
double succesive_rolls ( double balance, int point, int add_subtract, double wager );


int main (void)
{
    int die_roll1, die_roll2, point = 0, sum_of_roll, add_subtract = 0;
    double initial_balance = 0.0, wager = 0.0;

    print_game_rules();

    printf ("Please enter an initial bank balance for wagering: $");

    initial_balance = get_bank_balance();


while ( initial_balance > 0)
    {
        point = 0;
        printf ("Current Balance: $%.2f\n", initial_balance);
        printf ("Enter amount you want to wager: $");
        wager = get_wager_amount (initial_balance);

        //Rolls the dice
        printf ("Rolling dice...\n");
        die_roll1 = roll_dice();
        printf ("Roll Dice #1: %d\n", die_roll1);
        printf ("Rolling dice...\n");
        die_roll2 = roll_dice();
        printf ("Roll Dice #2: %d\n", die_roll2);

        sum_of_roll = calcluate_sum_dice(die_roll1, die_roll2);
        printf ("Sum of rolls: %d\n", sum_of_roll);

        add_subtract = initial_check_loss_or_win (sum_of_roll);

        point = check_if_point (add_subtract, sum_of_roll);

        initial_balance = succesive_rolls( initial_balance, point, add_subtract, wager );
    }

    return 0;

}





void print_game_rules (void)
{
    char space = 'a';

    printf ("The rules for craps are as follows:\n\n");
    printf ("A player rolls two dice. Each die has six faces. These faces contain 1, 2, 3, 4, 5 and 6 spots. After the die have come to rest, the sum of the spots are calculated.\n");
    printf ("If the sum is 7 or 11 on the first throw, the player wins. If the sum is 2, 3, or 12 on the first throw (called craps), the player loses.\n");
    printf ("If the sum is 4, 5, 6, 8, 9 or 10 on the first throw, then that sum becomes the players point.\n");
    printf ("To win, they must keep rolling the dice until they make their point. The player loses if they roll a 7 before making their point.\n\n\n");

    printf ("Please press space and then enter to continue...\a");
    scanf ("%c", &space);

    if (space == ' ')
    {
        printf ("\n");
        return;
    }
}

double get_bank_balance (void)
{
    double balance = 0.0;

    scanf ("%lf", &balance);

    //Ensures program continues only if postive balance is entered
    while (balance < 0) {
        printf ("Error! Please enter a balance above zero!\n");
        printf ("Please enter an initial bank balance for wagering: $");
        scanf ("%lf", &balance);
    }

    return balance;
}

double get_wager_amount (double balance)
{
    double wager = 0.0;
    scanf ("%lf", &wager);

    if ( wager > balance )
    {
        while ( wager > balance )
        {
            printf ("Your waging more money than you have. Please enter an amount less than or equal to your balance: $");
            scanf ("%lf", &wager);
        }
        return wager;
    }
    else if ( wager <= 0)
    {
        while ( wager <= 0)
        {
            printf ("Please wage an amount above 0: $\n");
            scanf ("%lf", &wager);
        }
        return wager;
    }

    return wager;
}

int roll_dice (void)
{
    int result;

    sleep(2);
    srand(time(0));
    result = (rand() % 6) + 1;

    return result;
}

int calcluate_sum_dice ( int die1, int die2 )
{
    int result = 0;

    result = die1 + die2;

    return result;
}

int initial_check_loss_or_win ( int sum_of_dice)
{
    if ( sum_of_dice == 7 || sum_of_dice == 11)
    {
        printf ("Congrats! You won!\n");
        return 1;
    }
    else if ( sum_of_dice == 2 || sum_of_dice == 3 || sum_of_dice == 12)
    {
        printf ("Bummer. You lost dude.\n");
        return 0;
    }
    else
    {
        printf ("%d is your point.\n", sum_of_dice);
        return -1;
    }

    return 0;
}

int check_if_point ( int add_subtract, int sum)
{
    if ( add_subtract == -1)
    {
        return sum;
    }
    else
        return 0;
}

int succesive_loss_or_neither (int sum, int point)
{
    if ( sum == 7)
    {
        printf ("You lose!\n");
        return 0;
    }
    else if ( sum == point)
    {
        printf ("You win!\n");
        return 1;
    }
    else
    {
        printf ("%d is your point. ", point);
        printf ("Keep rolling!\n");
        return -1;
    }
}

double adjust_bank_balance ( double balance, double wager, int add_subtract )
{
    double new_balance = 0.0;

    switch ( add_subtract )
    {
        case 1:
            new_balance = balance + wager;
            printf ("$%.2f + $%.2f = $%.2f\n", balance, wager, new_balance);
            break;

        case 0:
            new_balance = balance - wager;
            printf ("$%.2f - $%.2f = $%.2f\n", balance, wager, new_balance);
            break;

        case -1:
            printf ("Your balance is the same: $%.2f\n", balance);
            return balance;

        default:
            break;

    }

    return new_balance;
}

double succesive_rolls ( double balance, int point, int add_subtract, double wager )
{
    int die_roll1, die_roll2, sum_of_roll;

    if ( point > 0)
        while ( add_subtract == -1 )
        {
            printf ("Rolling dice...\n");
            die_roll1 = roll_dice();
            printf ("Roll Dice #1: %d\n", die_roll1);
            printf ("Rolling dice...\n");
            die_roll2 = roll_dice();
            printf ("Roll Dice #2: %d\n", die_roll2);
            sum_of_roll = calcluate_sum_dice(die_roll1, die_roll2);
            printf ("Sum of rolls: %d\n", sum_of_roll);

            add_subtract = succesive_loss_or_neither (sum_of_roll, point);
            balance = adjust_bank_balance (balance, wager, add_subtract);

        }
    else
    {
            balance =  adjust_bank_balance (balance, wager, add_subtract);

            return balance;
    }

    return balance;

}
