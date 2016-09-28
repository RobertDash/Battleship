#include <iostream>
#include "windows.h"
#include <ctime>

using namespace std;

const int Rows = 10;
const int Cols = 10;

void printBoard (char board[][Cols]);
void generateShip (char board[][Cols], int size);
void checkBoard (char board[][Cols],bool &victory);

int main()
{
	srand(time(NULL));
	char board[Rows][Cols],playerBoard[Rows][Cols];
	int sizeShip, nShips;
	for(int i=0; i<Rows; i++)
	{
		for(int j=0; j<Cols; j++)
		{
			board[i][j]='.';
			playerBoard[i][j] = '.';
		}
	}
	cout<<"Set amount of ships between 1 to 5"<<endl;
		cin>>nShips;
		if(nShips<1 || nShips>5)
		{
	do
	{
		cin.clear();
		cin.ignore();
		cout<<"Set amount of ships between 1 to 5,and please, no alphabets..."<<endl;
		cin>>nShips;
	}while(nShips<1 || nShips>5);
}
	for(int i=1; i<=nShips;i++)
	{
			cout<<"Set the size of this battleship number "<<i<<" between 2 to 5"<<endl;
			cin>>sizeShip;
			if(sizeShip<2 || sizeShip>5)
			{
		do
		{
			cin.clear();
			cin.ignore();
			cout<<"Set the size of this battleship number "<<i<<" between 2 to 5.\nWe know you typed something else."<<endl;
			cin>>sizeShip;
		}while(sizeShip<2 || sizeShip>5);
	}
		generateShip(board,sizeShip);
	}
	int nbomb = 30, iGuess, jGuess;
	bool victory = false;
	if(nShips !=1)
	{
		cout<<"\nThis is the board. There are ";
		cout<<nShips<<" enemy battleships hidden here."<<endl;
	}
	else
	{
		cout<<"\nThis is the board. There are ";
		cout<<nShips<<" enemy battleship hidden here."<<endl;
	}
	cout<<"You have 30 bombs. Make it count."<<endl;
	for (int n=1; n<=nbomb && !victory; n++)
	{
		Bomb:
		printBoard(playerBoard);
		cout<<"\nBomb number "<<n<<". Row: ";
		cin>>iGuess;
		cout<<endl;
		cout<<"Column: ";
		cin>>jGuess;
		
		if(board[iGuess-1][jGuess-1] == 'L')
		{
			cout<<"Hit."<<endl;
			board[iGuess-1][jGuess-1] = '<';
			playerBoard[iGuess-1][jGuess-1] = '<';
		}
		else if(board[iGuess-1][jGuess-1] == 'C')
		{
			cout<<"Hit."<<endl;
			board[iGuess-1][jGuess-1] = '=';
			playerBoard[iGuess-1][jGuess-1] = '=';
		}
		else if(board[iGuess-1][jGuess-1] == 'R')
		{
			cout<<"Hit."<<endl;
			board[iGuess-1][jGuess-1] = '>';
			playerBoard[iGuess-1][jGuess-1] = '>';
		}
		else if(board[iGuess-1][jGuess-1] == 'T')
		{
			cout<<"Hit."<<endl;
			board[iGuess-1][jGuess-1] = '^';
			playerBoard[iGuess-1][jGuess-1] = '^';
		}
			else if(board[iGuess-1][jGuess-1] == 'M')
		{
			cout<<"Hit."<<endl;
			board[iGuess-1][jGuess-1] = '|';
			playerBoard[iGuess-1][jGuess-1] = '|';
		}
			else if(board[iGuess-1][jGuess-1] == 'B')
		{
			cout<<"Hit."<<endl;
			board[iGuess-1][jGuess-1] = 'V';
			playerBoard[iGuess-1][jGuess-1] = 'V';
		}
			else if(board[iGuess-1][jGuess-1] != '.')
		{
			cout<<"You can't bomb a bombed area. Try again."<<endl;
			goto Bomb;
		}
		else
		{
			cout<<"Miss."<<endl;
			board[iGuess-1][jGuess-1] = '0';
			playerBoard[iGuess-1][jGuess-1] = '0';
		}
	}
	victory = true;
	checkBoard(board,victory);
	cout<<"The final board:"<<endl;
	printBoard(board);
	if(victory)
	{
		cout<<"Total destruction. Good job."<<endl;
	}
	else
	{
		cout<<"Some ships escaped. Try again."<<endl;
	}
	system("PAUSE");
	return 0;
}

void printBoard (char board[][Cols])
{
	for (int i=0; i<Rows; i++)
	{
		for (int j=0; j<Cols; j++)
		{
			cout<<board[i][j];
		}
		cout<<endl;
	}
}
void generateShip (char board[][Cols], int size)
{
	int iStart=0, jStart=0, ort;
Randomize:
	do
	{
		iStart = rand()%Rows;
		jStart = rand()%Cols;
		ort = rand()%2;
	}while(board[iStart][jStart] != '.');
	
	if(ort==0)
	{
		while (jStart+size >= Cols)
		{
			jStart = rand()%Cols;
		}
		for(int j=jStart; j<jStart + size; j++)
		{
			if(board[iStart][j] != '.')
			{
				goto Randomize;
			}
		}
		for(int j=jStart; j<jStart+1; j++)
		{
			board[iStart][j] = 'L';
		}
		for(int j=jStart+1; j<jStart + size - 1;j++)
		{
			board[iStart][j] = 'C';
		}
		for(int j=jStart+size-1;j<jStart+size;j++)
		{
			board[iStart][j] = 'R';
		}
	}
	if(ort==1)
	{
		//! go off the board
		while(iStart + size >= Rows)
		{
			iStart = rand()%Rows;
		}
		//! no duplication
		for(int i=iStart; i<iStart + size; i++)
		{
			if(board[i][jStart] != '.')
			{
				goto Randomize;
			}
		}
		for(int i=iStart; i<iStart +1; i++)
		{
			board[i][jStart] = 'T';
		}
		for(int i=iStart+1; i<iStart + size-1; i++)
		{
			board[i][jStart] = 'M';
		}
		for(int i=iStart+size-1; i<iStart + size; i++)
		{
			board[i][jStart] = 'B';
		}
	}
	return;
}
void checkBoard (char board[][Cols],bool &victory)\
{
	for(int i=0; i<Rows; i++)
	{
		for(int j=0; j<Cols; j++)
		{
			if(board [i][j] == 'S')
			{
				victory = false;
			}
		}
	}
}
