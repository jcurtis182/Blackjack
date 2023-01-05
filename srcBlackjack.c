#include<stdio.h>

#include<string.h>
#include<time.h>

#define DECK_SIZE 52

void titleScreen(); 					//Title Screen
void mainMenu(); 					//Main Menu
void menuDeck(); 					//Menu to change deck size
void Game(); 						//where the magic happens
void playerChoice(); 				//takes player input
void defineValue(); 				//finds card value and adds to player		
void restartGame(); 				//Restart or quit options; prints current session's score
void hit();							//User hit function, adds a card to total score
void stand(); 						//User stand function, keeps current score and begins Dealer turn
void initializeDeck(); 				//fills up deck with cards
void displayDeck(); 				//shows current card
void dealerTurn(); 					//where Dealer takes turn and declares winner
void dealerHit(); 					//determines whether Dealer should hit or stand

int menuScreen = 0, cardsDrawn = 0, playerPoints = 0, dealerPoints = 0, activePlayer = 0, dealerCardRevealed = 0, pWinCount = 0, pTieCount = 0, pLossCount = 0, pShuffleCount = 0;
int amountOfDecks = 1;

struct deck { 						//structure for initializing deck
	char* value;
	char suit[20];
};

typedef struct deck Deck;			//arrays used to fill deck
char* value[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
char suit[4][20] = { "Clubs", "Diamonds", "Hearts", "Spades" };

void shuffleDeck(Deck[]); 			//shuffles deck
Deck deck[DECK_SIZE] = { "", "" }; 				

void main() {
	int option; 					//takes input

	initializeDeck(); 				//making deck
	shuffleDeck(deck); 				//shuffling

	titleScreen(); 						//launches title screen and subsequently everything else

}

void titleScreen()
{
	printf("\n>>-----BLACKJACK----->\n");
	printf("Type a number to continue:\n");
	printf("1: Enter the game.\n");

	int option;
	scanf("%d", &option);			//reads user input

	switch (option)
	{
	case 1:							//user enters '1'
		mainMenu(); 					//opens main menu
		break;

	default:						
		printf("\n");				
		titleScreen();
		break;
	}
}

void mainMenu()
{
	printf("\n1: Start a Game\n");
	printf("2: Deck Count: %d\n", amountOfDecks);
	printf("3: Title Screen\n");

	int option;					
	scanf("%d", &option);			//reads user input

	switch (option)
	{
	case 1:							//user enters '1'
		printf("\n");
		Game();						//starts a game
		break;

	case 2:							//user enters '2'
		menuDeck();					//opens Deck menu
		break;

	case 3:							//user enters '3'
		printf("\n");
		titleScreen();					//goes back to Title Screen
		break;

	default:
		printf("\n");
		mainMenu();
		break;
	}
}

void menuDeck()
{
	printf("\n1: Single Deck\n");
	printf("2: Two Decks\n");
	printf("3: Three Decks\n");
	printf("4: Four Decks\n");

	int option;
	scanf("%d", &option);

	switch (option)
	{
	case 1:
		printf("[!] Single Deck Selected\n");
		amountOfDecks = 1;
		mainMenu();
		break;

	case 2:
		printf("[!] Two Decks Selected\n");
		amountOfDecks = 2;
		mainMenu();
		break;

	case 3:
		printf("[!] Three Decks Selected\n");
		amountOfDecks = 3;
		mainMenu();
		break;

	case 4:
		printf("[!] Four Decks Selected\n");
		amountOfDecks = 4;
		mainMenu();
		break;

	default:
		printf("[!] Single Deck Selected\n");
		amountOfDecks = 1;
		mainMenu();
		break;
	}
}


void Game()
{
	int option;

	cardsDrawn = 0;
	playerPoints = 0;
	dealerPoints = 0;
	dealerCardRevealed = 0;

	printf("****Instructions****\n");
	printf("1.  Hit\n");
	printf("2. Stand\n");
	printf("********************\n\n");

	printf("Dealer draws\n");
	activePlayer = 0;
	displayDeck(); 													//Dealer starting hand
	defineValue();
	cardsDrawn++; 
	printf(" Face-Down Card\n");
	printf("Dealer has %d points shown.\n\n", dealerPoints);			//Dealer starting total
	defineValue();
	cardsDrawn++; 
	
	printf("You have: \n");
	activePlayer = 1;												//Player starting hand
	displayDeck(); 						
	defineValue();
	cardsDrawn++; 
	displayDeck(); 						
	defineValue();
	cardsDrawn++; 
	printf("You have %d points.\n\n", playerPoints);					//Player starting total

	if (dealerPoints == 21 && playerPoints == 21) {								//Double blackjack 
		printf("[!] Dealer reveals BlackJack! It's...a tie? Unlucky...\n");
		pTieCount++;
		restartGame();
	}
	else if (dealerPoints == 21) {												//Dealer blackjack 
		printf("[!] Dealer has BlackJack. You lose!\n");
		pLossCount++;
		restartGame();
	}
	else if (playerPoints == 21) {												//Player blackjack 
		printf("[!] You got a BlackJack! You win!\n");
		pWinCount++;
		restartGame();
	}

	playerChoice();
}

void playerChoice()
{
	int option;

	printf("It is your turn:\n");					//Player options during turn
	scanf("%d", &option);
	switch (option) {
	case 1:
		hit();
		break;
	case 2:
		stand();
		break;
	default:
		hit();
		break;
	}
}


void defineValue()
{
	if (activePlayer == 0) {
		if (strcmp(deck[cardsDrawn].value, "Two") == 0) {
			dealerPoints += 2;
		}
		else if (strcmp(deck[cardsDrawn].value, "Three") == 0) {
			dealerPoints += 3;
		}
		else if (strcmp(deck[cardsDrawn].value, "Four") == 0) {
			dealerPoints += 4;
		}
		else if (strcmp(deck[cardsDrawn].value, "Five") == 0) {
			dealerPoints += 5;
		}
		else if (strcmp(deck[cardsDrawn].value, "Six") == 0) {
			dealerPoints += 6;
		}
		else if (strcmp(deck[cardsDrawn].value, "Seven") == 0) {
			dealerPoints += 7;
		}
		else if (strcmp(deck[cardsDrawn].value, "Eight") == 0) {
			dealerPoints += 8;
		}
		else if (strcmp(deck[cardsDrawn].value, "Nine") == 0) {
			dealerPoints += 9;
		}
		else if (strcmp(deck[cardsDrawn].value, "Ten") == 0) {
			dealerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].value, "Jack") == 0) {
			dealerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].value, "Queen") == 0) {
			dealerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].value, "King") == 0) {
			dealerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].value, "Ace") == 0) {
			if (dealerPoints <= 10) {
				dealerPoints += 11;
			}
			else {
				dealerPoints += 1;
			}

		}
	}
	else if (activePlayer == 1) {
		if (strcmp(deck[cardsDrawn].value, "Two") == 0) {
			playerPoints += 2;
		}
		else if (strcmp(deck[cardsDrawn].value, "Three") == 0) {
			playerPoints += 3;
		}
		else if (strcmp(deck[cardsDrawn].value, "Four") == 0) {
			playerPoints += 4;
		}
		else if (strcmp(deck[cardsDrawn].value, "Five") == 0) {
			playerPoints += 5;
		}
		else if (strcmp(deck[cardsDrawn].value, "Six") == 0) {
			playerPoints += 6;
		}
		else if (strcmp(deck[cardsDrawn].value, "Seven") == 0) {
			playerPoints += 7;
		}
		else if (strcmp(deck[cardsDrawn].value, "Eight") == 0) {
			playerPoints += 8;
		}
		else if (strcmp(deck[cardsDrawn].value, "Nine") == 0) {
			playerPoints += 9;
		}
		else if (strcmp(deck[cardsDrawn].value, "Ten") == 0) {
			playerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].value, "Jack") == 0) {
			playerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].value, "Queen") == 0) {
			playerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].value, "King") == 0) {
			playerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].value, "Ace") == 0) {
			if (playerPoints <= 10) {
				playerPoints += 11;
			}
			else {
				playerPoints += 1;
			}
		}
	}
}

void restartGame()
{
	int option;

	shuffleDeck(deck);

	printf("\n[?] Current Score: Wins = %d, Ties = %d, Losses = %d, Salty Shuffles = %d\n", pWinCount, pTieCount, pLossCount, pShuffleCount);
	printf("\n1. Play again\n");
	printf("2. Give it an extra shuffle\n");
	printf("3. Quit to Title\n");
	scanf("%d", &option);

	switch (option)
	{
	case 1:
		Game();
		break;
	case 2:
		shuffleDeck(deck);
		printf("\n[...] Sure, bud, whatever you say.\n");
		pShuffleCount++;
		restartGame();
	case 3:
		titleScreen();
	default:
		Game();
		break;
	}
}


void dealerTurn()
{
	activePlayer = 0;							

	if (dealerCardRevealed == 0) {						//check if first card has been dealt
		printf("Dealer reveals: ");
		printf("%5s of %-12s\n", deck[1].value, deck[1].suit);
		dealerCardRevealed = 1;
	}

		if (dealerPoints < 17) {						//Dealer always hits when < 17
			dealerHit();
		}
		else if (dealerPoints >= 17 && dealerPoints <= 21) {										//Dealer stand mechanic
			printf("Dealer stands, his final score for the round is: %d.\n", dealerPoints);
			
			if (dealerPoints > playerPoints) {
				printf("[!] Dealer wins with : %d!\n", dealerPoints);					//Dealer wins
				pLossCount++;
				restartGame();
			}
			else if (dealerPoints == playerPoints) {								//Dealer and Player tie
				printf("[!] Dealer wins with : %d!\n", dealerPoints);
				pTieCount++;
				restartGame();
			}
			else {																	//Dealer loses
				printf("[!] You win with : %d!\n", playerPoints);
				pWinCount++;
				restartGame();
			}
		}
		else if (dealerPoints > 21) {
			printf("Dealer busts, you win with : %d!\n", playerPoints);
			pWinCount++;
			restartGame();
		}
}

void dealerHit()					//Dealer hit mechanic
{
	printf("Dealer has: %d\n", dealerPoints);
	printf("Dealer draws\n");
	displayDeck();
	defineValue();
	cardsDrawn++;

	if (dealerPoints < 17) {			
		dealerHit();
	}
	else {								
		dealerTurn();
	}
}

void stand()						//Player stand mechanic; keeps score and ends turn
{
		printf("You choose to stand, your final score for the round is : %d.\n", playerPoints);
		dealerTurn();
	}


void hit()							//Player hit mechanic; draws new card, adds it to total, and continues based on new score
{
		displayDeck();
		defineValue();
		cardsDrawn++;
		printf("You have %d points.\n\n", playerPoints);


		if (playerPoints > 21) {							//Player busts
			printf("[!] You have bust, Dealer wins!\n");
			pLossCount++;
			restartGame();
		}
		else if (playerPoints == 21) {						//Player gets Blackjack
			printf(">>---Blackjack!--->");
			stand();
		}
		else if (playerPoints < 21) {						//Player can continue
			playerChoice();
		}
}

void displayDeck() {						//Display current card
	printf("%5s of %-12s\n", deck[cardsDrawn].value, deck[cardsDrawn].suit);
}

void shuffleDeck(Deck deck[])				//randomizes the deck
{
	int index = 0;
	Deck temp = { "", "" };
	srand(time(NULL));
	for (int i = 0; i < DECK_SIZE; i++) {
		index = rand() % (DECK_SIZE);
		temp = deck[i];
		deck[i] = deck[index];
		deck[index] = temp;							//temp deck for storing index
	} 
}

void initializeDeck()								//creates deck
{
	for (int i = 0; i < DECK_SIZE; i++) {
		deck[i].value = value[i % 13];
		strncpy(deck[i].suit, suit[i / 13], 9);
	}
}