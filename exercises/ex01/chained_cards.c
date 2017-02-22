/*  Written by Joseph Lee - adapted from code on page 37 of Head First C
*	chained_cards.c is a program that functions as a card counter for blackjack
*	it gets the card name from the user (1-9, 'J','Q','K') and increments a counter
*	up if card is 3, 4, 5, or 6 and down if face card
*	run by calling gcc chained_cards.c -o chained_cards && ./chained_cards
*	from command prompt in the same directory as this file is stored in
*/

/*	include header files: */
#include <stdio.h>
#include <stdlib.h>
/*	define globals */
int count=0;
char card_name[3];
/* 
*	Declare function prototypes
*	tell compiler that these user defined functions will be used
*/
void get_card_name(char *card_name);
int define_val(char *card_name);
void define_count(int *val);

/*	now the definition of the main function: */
int main()
{
	while(card_name[0] != 'X'){
		get_card_name(card_name);
		if (card_name[0]!='X'){
			int val=define_val(card_name);
			define_count(&val);
		}
	}
	return 0;
}


/*
_____________________________________________________________________________________

Function definitions:
*/

/*
*	This function accepts a pointer towards the global char variable card_name
*	and then updates it via the user input into the command line interface
*/
void get_card_name(char *card_name)
{
	puts("Enter the card_name: ");
	scanf("%2s", card_name);
}


/*
*	This function accepts a pointer towards the global char variable card_name
*	and then returns the coresponding value based on the card name
*/
int define_val(char *card_name)
{
	int value = 0;
	switch(card_name[0]){
		case 'K':
		case 'Q':
		case 'J':
			value = 10;
			break;
		case 'A':
			value = 11;
			break;
		case 'X':
			break;
		default:
			value = atoi(card_name);
		}
	return value;
}


/*
*	This function accepts a pointer towards an int val and then increments the global
*	counter accordingly.  The function also prints the current count.
*/
void define_count(int *val)
{
	if (*val<1 || *val>10){
		puts("Card value is out of the range, please start over");
	}
	if ((*val > 2) && (*val < 7)) {
		count++;
	} 
	else if (*val == 10){
		count--;
	}
	printf("Current count: %i/n", count);
}


