/*{{{ #include some stuff */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <unistd.h>
#include <sys/ioctl.h>
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
#define PURPLE	101
#define CCHEST 102
#define TAX 103
#define RAILROAD 104
#define LIGHTBLUE 105
#define CHANCE 106
#define INDIGO 107
#define UTILITY 108
#define ORANGE 109
#define RED 110
#define YELLOW 111
#define GOTOJAIL 112
#define GREEN 113
#define BLUE 114
/* }}} */

/* These are the things that could appear on chance cards {{{ */
#define NEAR_RR -1
#define GOBACK3 -3
#define NULLCARD -10
#define CARD_END -11
/* }}} */

/* Other #defines {{{ */
#define GAME_LENGTH 10 //The default game length
#define max(a, b) ((a) > (b)? (a) : (b))
#define min(a, b) ((a) < (b)? (a) : (b))
/* }}} */

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
	int land_count;
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
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	int term_width = w.ws_col - 42;
	int laps,game, games=1000000, game_length=GAME_LENGTH;
	int location; //Where the player is on the board
	int new_location;
	int d1, d2, double_count = 0;
	int show_land_counts = 1;
	int show_total_counts = 1;

	int argi,arg_error = 0;
	char *c;

	int count;
	int min_hits, max_hits = 0;
	float total_hits = 0;
	struct space *cur_space;
	
	srand(time(NULL));
	setlocale(LC_NUMERIC, "");

	/* Check any command line arguments {{{*/
	for (argi = 1; argi < argc && argv[argi][0] == '-'; argi++){
		for (c = &argv[argi][1]; *c != '\0'; c++){
			switch(*c){
			case 'h':
				printf("usage: %s [-g <games>] [-l <length>] [-t|-T] [-h]\n", argv[0]);
				printf("-t: show only total counts\n");
				printf("-T: show only land counts\n");
				return 0;

			case 'g':
				games = atoi(argv[++argi]);
				break;

			case 'l': 
				game_length = atoi(argv[++argi]);
				break;

			case 't': 
				show_land_counts = 0;
				show_total_counts = 1;
				break;

			case 'T': 
				show_land_counts = 1;
				show_total_counts = 0;
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
	/* }}} */

	/* Now for the main loop {{{ */
	printf("Playing %'d game%s of monopoly (where, in a game, the player passes go %'d time%s)\n",games, games>1?"s":"",game_length,game_length>1?"s":"");
	for (game = 0; game < games; game++){
		location=GO;
		laps = 0;
		while (laps < game_length){
			//Move the "piece" forward
			d1 = rand() % 6 + 1;
			d2 = rand() % 6 + 1;

			if (d1 == d2 && location != JAIL) {
				double_count += 1;
			} else {
				double_count = 0;
			}

			if (double_count >= 3) {
				//Move to jail on three doubles in a row. Assumes that the
				//player will always pay $50 to leave jail on the first roll
				//(as opposed to waiting for doubles).
				location = JAIL;
				double_count = 0;
			} else {
				location += d1 + d2;
				if (location >= 40){
					laps++;
					location -= 40;
				}
			}

			/* Check to see if we are on "action" spaces {{{*/
			new_location = location;
			switch(board[location].type){
			case GOTOJAIL:
				new_location = JAIL;
				break;
			case CHANCE:
				while ((new_location = card_move(location, chance_card)) < 0) {
					chance_card = &chance_deck[0];
				}
				chance_card++;
				break;
			case CCHEST:
				while ((new_location = card_move(location,com_card)) < 0) {
					com_card = &com_deck[0];
				}
				com_card++;
				break;
			}

			//Increase all the counters
			board[location].land_count += 1;
			board[new_location].count += 1;
			location = new_location;
			/* }}} */
		}
	}
	/* }}} */

	/* Print the results {{{ */
	min_hits = board[0].count;
	max_hits = board[0].count;
	for (count = 0; count < 40; count++){
		if (board[count].count > max_hits)
			max_hits = board[count].count;

		if (board[count].count < min_hits)
			min_hits = board[count].count;

		total_hits += board[count].count;
	}

	int diff;
	float cur_step;
	float tick_step = max_hits / (float)term_width;
	for (count = 0; count < 40; count++) {
		cur_space = &board[count];
		int min_count = min(cur_space->count, cur_space->land_count);
		int max_count = max(cur_space->count, cur_space->land_count);
		int count_to_show = (
			show_land_counts && show_total_counts? max_count :
			show_land_counts? cur_space->land_count :
			cur_space->count
		);
		printf("%20s |", cur_space->name);
		for (cur_step = 0; cur_step < count_to_show; cur_step += tick_step) {
			printf(
				cur_step < cur_space->count && cur_step < cur_space->land_count? "-" :
				cur_step < cur_space->count? (cur_space->type == JAIL? "x" : "=") :
				cur_step < cur_space->land_count? ">" :
				"?"
			);
		}
		if (min_count < count_to_show)
			printf(" %0.01f%% (%s%0.01f%%)",
					min_count / total_hits * 100,
					(count_to_show - min_count) > 0? "+" : "",
					(count_to_show - min_count) / total_hits * 100);
		printf(" %0.01f%%\n", count_to_show / total_hits * 100);
	}
	printf("\n");
	printf("Legend:\n");
	printf("=: the player ended their turn on this space\n");
	printf(">: the player landed on this space but moved before ending their turn\n");
	printf("-: both of the above\n");
	printf("x: the player was put into jail\n");

	printf("\n");
	printf("Max hits: %'d (%0.1f%%) Min hits: %'d (%0.1f%%)\n",
			max_hits, max_hits / total_hits * 100,
			min_hits, min_hits / total_hits * 100);
	printf("Each '-' represents %'0.1f turns\n",
			tick_step);
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
	putme->land_count = 0;

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
