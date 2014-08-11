/*{{{ #include some stuff */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
/*}}}*/

/* Some #defines {{{*/
/* We will #define space names here that corrispond to the numbers {{{*/
#define GO 0
#define RR0 5
#define READING 5
#define STCHARLES 11
#define ELECTRIC 12
#define JAIL 10
#define RR1 15
#define PENNSYLVANIA 15
#define FREEPARKING 20
#define ILLINOIS 24
#define RR2 25
#define BO 25
#define WATER 28
#define RR3 35
#define SHORTLINE 35
#define BOARDWALK 39
/* }}} */

/* Now #define the 'types' used in struct space {{{*/
#define PURPLE	1
#define CCHEST 2
#define TAX 3
#define RAILROAD 4
#define LIGHTBLUE 5
#define CHANCE 6
#define INDIGO 7
#define UTILITY 8
#define ORANGE 9
#define RED 10
#define YELLOW 11
#define GOTOJAIL 12
#define GREEN 13
#define BLUE 14
/* }}} */

/* These are the things that could appear on chance cards {{{ */
#define NEAR_RR -1
#define GOBACK3 -3
#define NULLCARD -10
#define CARD_END -11
/* }}} */

/* Other #defines {{{ */
#define GAME_LENGTH 10 //The default game length
/* }}} */

/* }}} */

/* And some macros... {{{ */
#define roll_dice ((rand() % 6) + (rand() % 6) + 2)
/* }}} */

/* Some structures {{{ */
struct ccard {
	int moveto;
	int ucount;
};

struct space {
	char name[26];
	int value;
	char type;
	int count;
};
/* }}} */

	/* Functions {{{*/
	void mkboard (struct space *);
	void mkdeck (struct ccard *,char);
	int card_move(int,struct ccard *);
	/*}}}*/

/* monopoly.c - Emulate a game of monopoly {{{*/
int main(int argc, char *argv[]){
	/* Declare variables {{{*/
	/* Set up the "board" as an array of spaces */
	struct space board[40];
	int *hit_count[40]; //The default game length

	/* And comunity chest/chance */
	struct ccard chance_deck[17];
	struct ccard *chance_card;
	struct ccard com_deck[17];
	struct ccard *com_card;

	/* And other variables */
	int term_width = 80;
	int laps,game, games=100, game_length=GAME_LENGTH;
	int location; //Where the player is on the board

	int argi,arg_error = 0;
	char *c;

	int count;
	int min_hits, max_hits = 0;
	int export_csv = 0;
	
	/* Initialize the random number generator */
	srand(time(NULL));
	/* }}} */

	/* Check any command line arguments {{{*/
	for (argi = 1; argi < argc && argv[argi][0] == '-'; argi++){
		for (c = &argv[argi][1]; *c != '\0'; c++){
			switch(*c){
			case 'h':
				printf("Usage:\n\tmonopoly [-g <games>] [-l <length>] [-c] [-h]\n");
				return 0;
			case 'g':
 				games = atoi(argv[++argi]);
				break;

			case 'l': 
 				game_length = atoi(argv[++argi]);
				break;

			case 'c':
				export_csv = 1;
				break;

			default:
				printf("Invalid argument: %c\n",*c);
				arg_error = 1;
				break;
			}
		}
	}
	if (arg_error){
		printf("Try `monopoly -h` for help\n");
		return 1;
	}
	/* }}} */

	/* Ok, now its time to set everything up {{{*/
	//Make chance deck
	mkdeck(&chance_deck[0],'?');
	chance_card = &chance_deck[0];
	//Make the comunity chest deck
	mkdeck(&com_deck[0],'$');
	com_card = &com_deck[0];
	//Make the board
	mkboard(&board[0]);
	location = GO;

	for (count = 0; count < 40; count++){
		if (!(hit_count[count]=calloc(game_length,sizeof(int)))){
			printf ("Could not alloc memory for hit_count at line __LINE__\n");
			return 1;
		}
	}
	/* }}} */

	/* Now for the main loop {{{ */
	printf("Playing %d game%s of monopoly (where, in a game, the player passes go %d time%s)\n",games, games>1?"s":"",game_length,game_length>1?"s":"");
	for (game = 0; game < games; game++){
		location=GO;
		laps = 0;
		while (laps < game_length){
			//Move the "piece" forward
			location += roll_dice;

			if (location >= 40){
				laps++;
				location -= 40;
			}

			//Increase all the counters
			board[location].count+=1;
			hit_count[location][laps]+=1;

			/* Check to see if we are on "action" spaces {{{*/
			switch(board[location].type){
			case GOTOJAIL:
				location = JAIL;
				break;
			case CHANCE:
				if ((location = card_move(location,chance_card)) < 0){
					location *= -1;
					//uh ho! we have to re-set the deck
					chance_card = &chance_deck[0];
					location = card_move(location,chance_card);
				}
				chance_card++;
				break;
			case CCHEST:
				if ((location = card_move(location,com_card)) < 0){
					location *= -1;
					//uh ho! we have to re-set the deck
					com_card = &com_deck[0];
					location = card_move(location,com_card);
				}
				com_card++;
				break;
			}
			/* }}} */
		}
	}
	/* }}} */

	/* Print the results {{{ */
	if (export_csv){
		printf("Space,");
		for (count = 1; count <= game_length; count++)
			printf("Lap %d,",count);
		printf("Total\n");

		for (game = 0; game < 40; game++){
			printf("%s,",board[game].name);
			for (count = 0; count < game_length; count++)
				printf("%d,",hit_count[game][count]);
			printf("%d\n", board[game].count);
		}
	} else {
		min_hits = board[0].count;
		max_hits = board[0].count;
		for (count = 0; count < 40; count++){
			if (board[count].count > max_hits)
				max_hits = board[count].count;

			if (board[count].count < min_hits)
				min_hits = board[count].count;
		}

		for (count = 0; count < 40; count++){
			printf("%20s |", board[count].name);
			for (game = 0; game < (int)((board[count].count - min_hits) * ((float)term_width / (max_hits - min_hits))); game++)
				printf("+");
			printf(" (%d)\n",board[count].count);
		}
		printf("Max hits: %d Min hits: %d\n",max_hits,min_hits);
		printf("Each '+' represents %.2f hits (plus an initial correction of %d)\n",
				(max_hits - min_hits) / (float)term_width,min_hits);
	}
	/* }}} */
		
	return 0;
}
/* }}} */

/* card_move: Move picece depending on the value of card {{{*/
int card_move(int piece, struct ccard *card){
	switch (card->moveto){
		case NULLCARD:
			break;
		case NEAR_RR:
			while (!((piece == RR0) ||(piece == RR1) ||(piece == RR2) ||(piece == RR3))){
				if (piece > 40)
					piece = 0;
				piece++;
			}
			break;
		case UTILITY:
			while (!((piece == WATER) || (piece == ELECTRIC))){
				if (piece > 40)
					piece = 0;
				piece++;
			}
			break;
		case GOBACK3:
			piece -= 3;
			break;
		case CARD_END:
			return piece * -1;
			break;
		default:
			piece=card->moveto;
	}
	card->ucount++;
	return piece;
}

/* }}} */

/* mkdeck: Make a deck of cards {{{*/
void mkdeck(struct ccard *deck, char type){
	void get_chance(int,struct ccard *);
	void get_cchest(int,struct ccard *);
	int count,card,check_count;
	int used[16];

	for (count = 0; count < 16; count++){
		/* Change this to use pointers to the functions */
		card = rand() % 16;	
		for (check_count=0; check_count < 16; check_count++){
			if (used[check_count] == card){
				card = rand() % 16;
				check_count = -1;
			}
		}

		type == '?'? get_chance(card,deck) : get_cchest(card, deck);
		deck++;
	}
	
	deck->moveto=CARD_END;
	deck->ucount=CARD_END;
}
/* }}} */

/* get_chance: Get the value of a chance card {{{*/
void get_chance(int number, struct ccard *card){
	switch (number){
	case 0:
	case 1: //Nearest Railroad
		card->moveto =	NEAR_RR;
		card->ucount = 	0;
		break;
	case 2: //St Charles Place
		card->moveto =	STCHARLES;
		card->ucount =	0;
		break;
	case 3: //Nearest Utility
		card->moveto =	UTILITY;
		card->ucount =	0;
		break;
	case 4: //Go back 3
		card->moveto =	GOBACK3;
		card->ucount =	0;
		break;
	case 5: //Boardwalk
		card->moveto = BOARDWALK;
		card->ucount = 0;
		break;
	case 6: //Illinois
		card->moveto = ILLINOIS;
		card->ucount = 0;
		break;
	case 7: //Go
		card->moveto = GO;
		card->ucount = 0;
		break;
	case 8: //Jail
		card->moveto = JAIL;
		card->ucount = 0;
		break;
	case 9: //Reading
		card->moveto = READING;
		card->ucount = 0;
		break;
	default:
		card->moveto = NULLCARD;
		card->ucount = 0;
	}
}
/* }}} */

/* get_cchest: Get the value of a comunity chest card {{{*/
void get_cchest(int number, struct ccard *card){
	switch (number) {
	case 0:
		card->moveto = GO;
		card->ucount = 0;
		break;
	case 1:
		card->moveto = JAIL;
		card->ucount = 0;
		break;
	default:
		card->moveto = -10;
		card->ucount = 0;
	}
}
/* }}} */

/* mkboard: Fill board with spaces {{{*/
void mkboard (struct space *board){
	void get_space(int, struct space *);
	int count;

	for (count = 0; count < 40; count++){
		get_space(count, board);
		board++;
	}
}
/* }}} */

/* get_space: Get the value of a certan space on the board and put it in putme {{{*/
void get_space(int number,struct space *putme){
	switch (number){
	case 0: //Go
		strcpy(putme->name,"Go");
		putme->value	= 0;
		putme->type	= GO;
		putme->count	= 0;
		break;
	case 1: //Mediteranian
		strcpy(putme->name,"Mediterranean Ave.");
		putme->value	= 60;
		putme->type	= PURPLE;
		putme->count	= 0;
		break;
	case 2:
	case 17:
	case 33: //Community Chest
		strcpy(putme->name,"Community Chest");
		putme->value	= 0;
		putme->type	= CCHEST;
		putme->count	= 0;
		break;
	case 3: //Baltic
		strcpy(putme->name,"Baltic Ave.");
		putme->value	= 60;
		putme->type	= PURPLE;
		putme->count	= 0;
		break;
	case 4: //Income Tax
		strcpy(putme->name,"Income Tax");
		putme->value	= -200;
		putme->type	= TAX;
		putme->count	= 0;
		break;
	case 5: //Reading RR
		strcpy(putme->name,"Reading RR");
		putme->value	= 200;
		putme->type	= RAILROAD;
		putme->count	= 0;
		break;
	case 6: //Oriental
		strcpy(putme->name,"Oriental Ave.");
		putme->value	= 100;
		putme->type	= LIGHTBLUE;
		putme->count	= 0;
		break;
	case 7:
	case 22:
	case 36: //Chance
		strcpy(putme->name,"Chance");
		putme->value	= 0;
		putme->type	= CHANCE;
		putme->count	= 0;
		break;
	case 8: //Vermont
		strcpy(putme->name,"Vermont Ave.");
		putme->value	= 100;
		putme->type	= LIGHTBLUE;
		putme->count	= 0;
		break;
	case 9: //Connecticut
		strcpy(putme->name,"Connecticut Ave.");
		putme->value	= 120;
		putme->type	= LIGHTBLUE;
		putme->count	= 0;
		break;
	case 10: //Jail
		strcpy(putme->name,"Jail");
		putme->value	= 0;
		putme->type	= JAIL;
		putme->count	= 0;
		break;
	case 11: //StCharles
		strcpy(putme->name,"St. Charles Place");
		putme->value	= 140;
		putme->type	= INDIGO;
		putme->count	= 0;
		break;
	case 12: //Electric Co
		strcpy(putme->name,"Electric Company");
		putme->value	= 150;
		putme->type	= UTILITY;
		putme->count	= 0;
		break;
	case 13: //States
		strcpy(putme->name,"States Ave.");
		putme->value	= 140;
		putme->type	= INDIGO;
		putme->count	= 0;
		break;
	case 14: //Verginia
		strcpy(putme->name,"Verginia Ave.");
		putme->value	= 160;
		putme->type	= INDIGO;
		putme->count	= 0;
		break;
	case 15: //Pennsylvania
		strcpy(putme->name,"Pennsylvania RR");
		putme->value	= 200;
		putme->type	= RAILROAD;
		putme->count	= 0;
		break;
	case 16: //StJames Place
		strcpy(putme->name,"St. James Place");
		putme->value	= 180;
		putme->type	= ORANGE;
		putme->count	= 0;
		break;
	case 18: //Tennessee
		strcpy(putme->name,"Tennessee Ave.");
		putme->value	= 180;
		putme->type	= ORANGE;
		putme->count	= 0;
		break;
	case 19: //New York
		strcpy(putme->name,"New York Ave.");
		putme->value	= 200;
		putme->type	= ORANGE;
		putme->count	= 0;
		break;
	case 20: //Free Parking
		strcpy(putme->name,"Free Parking");
		putme->value	= 0;
		putme->type	= FREEPARKING;
		putme->count	= 0;
		break;
	case 21: //Kentucky
		strcpy(putme->name,"Kentucky Ave.");
		putme->value	= 220;
		putme->type	= RED;
		putme->count	= 0;
		break;
	case 23: //Indiana
		strcpy(putme->name,"Indiana Ave.");
		putme->value	= 220;
		putme->type	= RED;
		putme->count	= 0;
		break;
	case 24: //Illinois
		strcpy(putme->name,"Illinois Ave.");
		putme->value	= 240;
		putme->type	= RED;
		putme->count	= 0;
		break;
	case 25: //B&0 RR
		strcpy(putme->name,"B. & O. RR");
		putme->value	= 200;
		putme->type	= RAILROAD;
		putme->count	= 0;
		break;
	case 26: //Atlantic
		strcpy(putme->name,"Atlantic Ave.");
		putme->value	= 260;
		putme->type	= YELLOW;
		putme->count	= 0;
		break;
	case 27: //Ventnor
		strcpy(putme->name,"Ventnor Ave.");
		putme->value	= 260;
		putme->type	= YELLOW;
		putme->count	= 0;
		break;
	case 28: //Water Works
		strcpy(putme->name,"Water Works");
		putme->value	= 150;
		putme->type	= UTILITY;
		putme->count	= 0;
		break;
	case 29: //Marvin Gardens
		strcpy(putme->name,"Marvin Gardens");
		putme->value	= 280;
		putme->type	= YELLOW;
		putme->count	= 0;
		break;
	case 30: //GOTO Jail
		strcpy(putme->name,"Go To Jail");
		putme->value	= 0;
		putme->type	= GOTOJAIL;
		putme->count	= 0;
		break;
	case 31: //Pacific
		strcpy(putme->name,"Pacific Ave.");
		putme->value	= 300;
		putme->type	= GREEN;
		putme->count	= 0;
		break;
	case 32: //North Carolina
		strcpy(putme->name,"North Carolina Ave.");
		putme->value	= 300;
		putme->type	= GREEN;
		putme->count	= 0;
		break;
	case 34: //Pennsylvania
		strcpy(putme->name,"Pennsylvania Ave.");
		putme->value	= 320;
		putme->type	= GREEN;
		putme->count	= 0;
		break;
	case 35: //Short Line
		strcpy(putme->name,"Short Line");
		putme->value	= 200;
		putme->type	= RAILROAD;
		putme->count	= 0;
		break;
	case 37: //Park Place
		strcpy(putme->name,"Park Place");
		putme->value	= 350;
		putme->type	= BLUE;
		putme->count	= 0;
		break;
	case 38: //Luxury Tax
		strcpy(putme->name,"Luxury Tax");
		putme->value	= -75;
		putme->type	= TAX;
		putme->count	= 0;
		break;
	case 39: //Boardwalk
		strcpy(putme->name,"Boardwalk");
		putme->value	= 400;
		putme->type	= BLUE;
		putme->count	= 0;
		break;
	}
}
/* }}} */
