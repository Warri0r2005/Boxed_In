/*
ENGGEN131 2024
C Project - Boxed In
Resource file - project2.c

You can use this program to test the functions that you write before grading them with CodeRunner
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

// Function prototype declarations
void MakeBox(char *design, int width, int height);
void PrintRoom(int room[ROWS][COLS]);
void InitialiseRoom(int room[ROWS][COLS], char *layout);
void LocatePerson(int room[ROWS][COLS], int *row, int *col);
void MakeMove(int room[ROWS][COLS], char move, char *allMoves);
int CheckGameOver(int room[ROWS][COLS]);
void UndoMove(int room[ROWS][COLS], char *allMoves);

// When you have completed all of the functions for the project, place them here:

void noCentreBox(char *design, int width, int height);

// Task One ///////////////////////////////////////////////////////////////
void MakeBox(char *design, int width, int height)
{

	if ((width == 1) && (height == 1)) // One by One edge case may not be needed cause of below
	{
		*design = '#';
	}
	else // Check for no centre mark
	{
		noCentreBox(design, width, height);
	}

	if ((height > 2) && (width > 2))
	{
		int centre = 0, xpos, ypos; // Always finds bottom right coord

		xpos = width / 2;
		ypos = height / 2;

		centre = ((ypos) * (width + 1)) + xpos;

		if ((height % 2 == 0) && (width % 2 == 0))
		{
			design[centre] = 'X';
			design[centre - 1] = 'X';
			design[centre - (xpos * 2) - 1] = 'X';
			design[centre - (xpos * 2) - 2] = 'X';
		}
		else if (height % 2 == 0)
		{
			design[centre] = 'X';
			design[centre - (xpos * 2) - 2] = 'X';
		}
		else if (width % 2 == 0)
		{
			design[centre] = 'X';
			design[centre - 1] = 'X';
		}
		else
		{
			design[centre] = 'X';
		}
	}
}

void noCentreBox(char *design, int width, int height)
{
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i == 0) || (i == height - 1))
			{
				if (j == width - 1)
				{
					strcat(design, "#\n");
				}
				else
				{
					strcat(design, "#");
				}
			}
			else if (j == 0)
			{
				strcat(design, "#");
			}
			else if (j == width - 1)
			{
				strcat(design, "#\n");
			}
			else
			{
				strcat(design, " ");
			}
		}
	}
}

// Task Two ///////////////////////////////////////////////////////////////
void PrintRoom(int room[ROWS][COLS])
{
	int i, j;

	for (i = 0; i < ROWS; i++) // Loops over every point in array
	{
		for (j = 0; j < COLS; j++)
		{
			switch (room[i][j])
			{
			case SPACE:
				printf(" ");
				break;

			case WALL:
				printf("#");
				break;

			case TARGET:
				printf("*");
				break;

			case BOX:
				printf("O");
				break;

			case BOX_ON_TARGET:
				printf("@");
				break;

			case PERSON:
				printf("X");
				break;

			case PERSON_ON_TARGET:
				printf("X");
				break;

			default:
				printf("0");
				break;
			}
		}
		printf("\n");
	}
}

// Task Three ///////////////////////////////////////////////////////////////
void InitialiseRoom(int room[ROWS][COLS], char *layout)
{
	int index = 0; // Keep track of num indexs in string
	int lengthOfLay, i, j, digit;

	lengthOfLay = strlen(layout);

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if ((index < lengthOfLay) && (layout[index] != EOF))
			{
				digit = layout[index] - '0';
				room[i][j] = digit;
			}
			else
			{
				room[i][j] = 1;
			}
			index++;
		}
	}
}

// Task Four ///////////////////////////////////////////////////////////////
void LocatePerson(int room[ROWS][COLS], int *row, int *col)
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if ((room[i][j] == PERSON) || (room[i][j] == PERSON_ON_TARGET))
			{
				*row = i;
				*col = j;
			}
		}
	}
}

// Task Five - Task Eight ////////////////////////////////////////////////////////
void MakeMove(int room[ROWS][COLS], char move, char *allMoves)
{
	int posrow, poscol, index;
	LocatePerson(room, &posrow, &poscol);

	switch (move)
	{
	case 'w':
		if (room[posrow][poscol] == PERSON_ON_TARGET) // Target onto
		{
			if (room[posrow - 1][poscol] == SPACE) // Space
			{
				room[posrow][poscol] = TARGET;
				room[posrow - 1][poscol] = PERSON;
				strcat(allMoves, "w0");
			}
			else if (room[posrow - 1][poscol] == TARGET) // Target
			{
				room[posrow][poscol] = TARGET;
				room[posrow - 1][poscol] = PERSON_ON_TARGET;
				strcat(allMoves, "w0");
			}
			else if ((room[posrow - 1][poscol] == BOX) && (room[posrow - 2][poscol] == SPACE)) // + Box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow - 1][poscol] = PERSON;
				room[posrow - 2][poscol] = BOX;
				strcat(allMoves, "w1");
			}
			else if ((room[posrow - 1][poscol] == BOX) && (room[posrow - 2][poscol] == TARGET)) //+ Box onto target
			{
				room[posrow][poscol] = TARGET;
				room[posrow - 1][poscol] = PERSON;
				room[posrow - 2][poscol] = BOX_ON_TARGET;
				strcat(allMoves, "w1");
			}
			else if ((room[posrow - 1][poscol] == BOX_ON_TARGET) && (room[posrow - 2][poscol] == SPACE)) // + Target box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow - 1][poscol] = PERSON_ON_TARGET;
				room[posrow - 2][poscol] = BOX;
				strcat(allMoves, "w1");
			}
			else if ((room[posrow - 1][poscol] == BOX_ON_TARGET) && (room[posrow - 2][poscol] == TARGET)) // + Target box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow - 1][poscol] = PERSON_ON_TARGET;
				room[posrow - 2][poscol] = BOX_ON_TARGET;
				strcat(allMoves, "w1");
			}
		}
		else
		{
			// Space onto:
			if (room[posrow - 1][poscol] == SPACE) // Space
			{
				room[posrow][poscol] = SPACE;
				room[posrow - 1][poscol] = PERSON;
				strcat(allMoves, "w0");
			}
			else if (room[posrow - 1][poscol] == TARGET) // Target
			{
				room[posrow][poscol] = SPACE;
				room[posrow - 1][poscol] = PERSON_ON_TARGET;
				strcat(allMoves, "w0");
			}
			else if ((room[posrow - 1][poscol] == BOX) && (room[posrow - 2][poscol] == SPACE)) // + Box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow - 1][poscol] = PERSON;
				room[posrow - 2][poscol] = BOX;
				strcat(allMoves, "w1");
			}
			else if ((room[posrow - 1][poscol] == BOX) && (room[posrow - 2][poscol] == TARGET)) //+ Box onto target
			{
				room[posrow][poscol] = SPACE;
				room[posrow - 1][poscol] = PERSON;
				room[posrow - 2][poscol] = BOX_ON_TARGET;
				strcat(allMoves, "w1");
			}
			else if ((room[posrow - 1][poscol] == BOX_ON_TARGET) && (room[posrow - 2][poscol] == SPACE)) // + Target box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow - 1][poscol] = PERSON_ON_TARGET;
				room[posrow - 2][poscol] = BOX;
				strcat(allMoves, "w1");
			}
			else if ((room[posrow - 1][poscol] == BOX_ON_TARGET) && (room[posrow - 2][poscol] == TARGET)) // + Target box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow - 1][poscol] = PERSON_ON_TARGET;
				room[posrow - 2][poscol] = BOX_ON_TARGET;
				strcat(allMoves, "w1");
			}
		}

		break;

	case 'a':
		if (room[posrow][poscol] == PERSON_ON_TARGET)
		{
			if (room[posrow][poscol - 1] == SPACE) // Space
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol - 1] = PERSON;
				strcat(allMoves, "a0");
			}
			else if (room[posrow][poscol - 1] == TARGET) // Target
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol - 1] = PERSON_ON_TARGET;
				strcat(allMoves, "a0");
			}
			else if ((room[posrow][poscol - 1] == BOX) && (room[posrow][poscol - 2] == SPACE)) // + Box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol - 1] = PERSON;
				room[posrow][poscol - 2] = BOX;
				strcat(allMoves, "a1");
			}
			else if ((room[posrow][poscol - 1] == BOX) && (room[posrow][poscol - 2] == TARGET)) // + Box onto target
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol - 1] = PERSON;
				room[posrow][poscol - 2] = BOX_ON_TARGET;
				strcat(allMoves, "a1");
			}
			else if ((room[posrow][poscol - 1] == BOX_ON_TARGET) && (room[posrow][poscol - 2] == SPACE)) // + Target box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol - 1] = PERSON_ON_TARGET;
				room[posrow][poscol - 2] = BOX;
				strcat(allMoves, "a1");
			}
			else if ((room[posrow][poscol - 1] == BOX_ON_TARGET) && (room[posrow][poscol - 2] == TARGET)) // + Target box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol - 1] = PERSON_ON_TARGET;
				room[posrow][poscol - 2] = BOX_ON_TARGET;
				strcat(allMoves, "a1");
			}
		}
		else
		{
			if (room[posrow][poscol - 1] == SPACE) // Space
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol - 1] = PERSON;
				strcat(allMoves, "a0");
			}
			else if (room[posrow][poscol - 1] == TARGET) // Target
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol - 1] = PERSON_ON_TARGET;
				strcat(allMoves, "a0");
			}
			else if ((room[posrow][poscol - 1] == BOX) && (room[posrow][poscol - 2] == SPACE)) // + Box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol - 1] = PERSON;
				room[posrow][poscol - 2] = BOX;
				strcat(allMoves, "a1");
			}
			else if ((room[posrow][poscol - 1] == BOX) && (room[posrow][poscol - 2] == TARGET)) // + Box onto target
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol - 1] = PERSON;
				room[posrow][poscol - 2] = BOX_ON_TARGET;
				strcat(allMoves, "a1");
			}
			else if ((room[posrow][poscol - 1] == BOX_ON_TARGET) && (room[posrow][poscol - 2] == SPACE)) // + Target box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol - 1] = PERSON_ON_TARGET;
				room[posrow][poscol - 2] = BOX;
				strcat(allMoves, "a1");
			}
			else if ((room[posrow][poscol - 1] == BOX_ON_TARGET) && (room[posrow][poscol - 2] == TARGET)) // + Target box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol - 1] = PERSON_ON_TARGET;
				room[posrow][poscol - 2] = BOX_ON_TARGET;
				strcat(allMoves, "a1");
			}
		}
		break;

	case 's':
		if (room[posrow][poscol] == PERSON_ON_TARGET)
		{
			if (room[posrow + 1][poscol] == SPACE) // Onto Space
			{
				room[posrow][poscol] = TARGET;
				room[posrow + 1][poscol] = PERSON;
				strcat(allMoves, "s0");
			}
			else if (room[posrow + 1][poscol] == TARGET) // Target
			{
				room[posrow][poscol] = TARGET;
				room[posrow + 1][poscol] = PERSON_ON_TARGET;
				strcat(allMoves, "s0");
			}
			else if ((room[posrow + 1][poscol] == BOX) && (room[posrow + 2][poscol] == SPACE)) // + Box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow + 1][poscol] = PERSON;
				room[posrow + 2][poscol] = BOX;
				strcat(allMoves, "s1");
			}
			else if ((room[posrow + 1][poscol] == BOX) && (room[posrow + 2][poscol] == TARGET)) // + Box onto Target
			{
				room[posrow][poscol] = TARGET;
				room[posrow + 1][poscol] = PERSON;
				room[posrow + 2][poscol] = BOX_ON_TARGET;
				strcat(allMoves, "s1");
			}
			else if ((room[posrow + 1][poscol] == BOX_ON_TARGET) && (room[posrow + 2][poscol] == SPACE)) // + Target box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow + 1][poscol] = PERSON_ON_TARGET;
				room[posrow + 2][poscol] = BOX;
				strcat(allMoves, "s1");
			}
			else if ((room[posrow + 1][poscol] == BOX_ON_TARGET) && (room[posrow + 2][poscol] == TARGET)) // + Target box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow + 1][poscol] = PERSON_ON_TARGET;
				room[posrow + 2][poscol] = BOX_ON_TARGET;
				strcat(allMoves, "s1");
			}
		}
		else
		{
			if (room[posrow + 1][poscol] == SPACE) // Onto Space
			{
				room[posrow][poscol] = SPACE;
				room[posrow + 1][poscol] = PERSON;
				strcat(allMoves, "s0");
			}
			else if (room[posrow + 1][poscol] == TARGET) // Target
			{
				room[posrow][poscol] = SPACE;
				room[posrow + 1][poscol] = PERSON_ON_TARGET;
				strcat(allMoves, "s0");
			}
			else if ((room[posrow + 1][poscol] == BOX) && (room[posrow + 2][poscol] == SPACE)) // + Box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow + 1][poscol] = PERSON;
				room[posrow + 2][poscol] = BOX;
				strcat(allMoves, "s1");
			}
			else if ((room[posrow + 1][poscol] == BOX) && (room[posrow + 2][poscol] == TARGET)) // + Box onto Target
			{
				room[posrow][poscol] = SPACE;
				room[posrow + 1][poscol] = PERSON;
				room[posrow + 2][poscol] = BOX_ON_TARGET;
				strcat(allMoves, "s1");
			}
			else if ((room[posrow + 1][poscol] == BOX_ON_TARGET) && (room[posrow + 2][poscol] == SPACE)) // + Target box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow + 1][poscol] = PERSON_ON_TARGET;
				room[posrow + 2][poscol] = BOX;
				strcat(allMoves, "s1");
			}
			else if ((room[posrow + 1][poscol] == BOX_ON_TARGET) && (room[posrow + 2][poscol] == TARGET)) // + Target box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow + 1][poscol] = PERSON_ON_TARGET;
				room[posrow + 2][poscol] = BOX_ON_TARGET;
				strcat(allMoves, "s1");
			}
		}

		break;

	case 'd':
		if (room[posrow][poscol] == PERSON_ON_TARGET)
		{
			if (room[posrow][poscol + 1] == SPACE) // Space
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol + 1] = PERSON;
				strcat(allMoves, "d0");
			}
			else if (room[posrow][poscol + 1] == TARGET) // Target
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol + 1] = PERSON_ON_TARGET;
				strcat(allMoves, "d0");
			}
			else if ((room[posrow][poscol + 1] == BOX) && (room[posrow][poscol + 2] == SPACE)) // + Box to space
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol + 1] = PERSON;
				room[posrow][poscol + 2] = BOX;
				strcat(allMoves, "d1");
			}
			else if ((room[posrow][poscol + 1] == BOX) && (room[posrow][poscol + 2] == TARGET)) // + Box to target
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol + 1] = PERSON;
				room[posrow][poscol + 2] = BOX_ON_TARGET;
				strcat(allMoves, "d1");
			}
			else if ((room[posrow][poscol + 1] == BOX_ON_TARGET) && (room[posrow][poscol + 2] == SPACE)) // + Target box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol + 1] = PERSON_ON_TARGET;
				room[posrow][poscol + 2] = BOX;
				strcat(allMoves, "d1");
			}
			else if ((room[posrow][poscol + 1] == BOX_ON_TARGET) && (room[posrow][poscol + 2] == TARGET)) // + Target box onto space
			{
				room[posrow][poscol] = TARGET;
				room[posrow][poscol + 1] = PERSON_ON_TARGET;
				room[posrow][poscol + 2] = BOX_ON_TARGET;
				strcat(allMoves, "d1");
			}
		}
		else
		{
			if (room[posrow][poscol + 1] == SPACE) // Space
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol + 1] = PERSON;
				strcat(allMoves, "d0");
			}
			else if (room[posrow][poscol + 1] == TARGET) // Target
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol + 1] = PERSON_ON_TARGET;
				strcat(allMoves, "d0");
			}
			else if ((room[posrow][poscol + 1] == BOX) && (room[posrow][poscol + 2] == SPACE)) // + Box to space
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol + 1] = PERSON;
				room[posrow][poscol + 2] = BOX;
				strcat(allMoves, "d1");
			}
			else if ((room[posrow][poscol + 1] == BOX) && (room[posrow][poscol + 2] == TARGET)) // + Box to target
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol + 1] = PERSON;
				room[posrow][poscol + 2] = BOX_ON_TARGET;
				strcat(allMoves, "d1");
			}
			else if ((room[posrow][poscol + 1] == BOX_ON_TARGET) && (room[posrow][poscol + 2] == SPACE)) // + Target box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol + 1] = PERSON_ON_TARGET;
				room[posrow][poscol + 2] = BOX;
				strcat(allMoves, "d1");
			}
			else if ((room[posrow][poscol + 1] == BOX_ON_TARGET) && (room[posrow][poscol + 2] == TARGET)) // + Target box onto space
			{
				room[posrow][poscol] = SPACE;
				room[posrow][poscol + 1] = PERSON_ON_TARGET;
				room[posrow][poscol + 2] = BOX_ON_TARGET;
				strcat(allMoves, "d1");
			}
		}

		break;

	case 'z':
		UndoMove(room, allMoves);
		break;

	default:
		break;
	}
}

// Task Nine /////////////////////////////////////////////////////////////////
int CheckGameOver(int room[ROWS][COLS])
{
	int i, j, game_over = 0;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if (room[i][j] == 4)
			{
				game_over = 1;
			}
			else if ((room[i][j] == 2) || (room[i][j] == 6))
			{
				return 0;
			}
		}
	}
	return game_over;
}

// Task Ten /////////////////////////////////////////////////////////////////
void UndoMove(int room[ROWS][COLS], char *allMoves)
{
	int posrow, poscol, length;
	LocatePerson(room, &posrow, &poscol);

	length = strlen(allMoves);
	length--;

	switch (allMoves[length - 1])
	{
	case 'w':
		if (room[posrow][poscol] == PERSON_ON_TARGET) // Person on target
		{
			if (room[posrow + 1][poscol] == SPACE) // Space
			{
				room[posrow + 1][poscol] = PERSON;
				room[posrow][poscol] = TARGET;
			}
			else if (room[posrow + 1][poscol] == TARGET) // Target
			{
				room[posrow + 1][poscol] = PERSON_ON_TARGET;
				room[posrow][poscol] = TARGET;
			}
		}
		else // Person on space
		{
			if (room[posrow + 1][poscol] == SPACE) // Space
			{
				room[posrow + 1][poscol] = PERSON;
				room[posrow][poscol] = SPACE;
			}
			else if (room[posrow + 1][poscol] == TARGET) // Target
			{
				room[posrow + 1][poscol] = PERSON_ON_TARGET;
				room[posrow][poscol] = SPACE;
			}
		}

		if (room[posrow][poscol] == TARGET)
		{
			if (room[posrow - 1][poscol] == BOX)
			{
				room[posrow - 1][poscol] = SPACE;
				room[posrow][poscol] = BOX_ON_TARGET;
			}
			else if (room[posrow - 1][poscol] == BOX_ON_TARGET)
			{
				room[posrow - 1][poscol] = TARGET;
				room[posrow][poscol] = BOX_ON_TARGET;
			}
		}
		else
		{
			if (room[posrow - 1][poscol] == BOX)
			{
				room[posrow - 1][poscol] = SPACE;
				room[posrow][poscol] = BOX;
			}
			else if (room[posrow - 1][poscol] == BOX_ON_TARGET)
			{
				room[posrow - 1][poscol] = TARGET;
				room[posrow][poscol] = BOX;
			}
		}

		break;

	case 's':
		if (room[posrow][poscol] == PERSON_ON_TARGET) // Person on target
		{
			if (room[posrow - 1][poscol] == SPACE) // Space
			{
				room[posrow - 1][poscol] = PERSON;
				room[posrow][poscol] = TARGET;
			}
			else if (room[posrow - 1][poscol] == TARGET) // Target
			{
				room[posrow - 1][poscol] = PERSON_ON_TARGET;
				room[posrow][poscol] = TARGET;
			}
		}
		else // Person on space
		{
			if (room[posrow - 1][poscol] == SPACE) // Space
			{
				room[posrow - 1][poscol] = PERSON;
				room[posrow][poscol] = SPACE;
			}
			else if (room[posrow - 1][poscol] == TARGET) // Target
			{
				room[posrow - 1][poscol] = PERSON_ON_TARGET;
				room[posrow][poscol] = SPACE;
			}
		}

		if (room[posrow][poscol] == TARGET)
		{
			if (room[posrow + 1][poscol] == BOX)
			{
				room[posrow + 1][poscol] = SPACE;
				room[posrow][poscol] = BOX_ON_TARGET;
			}
			else if (room[posrow + 1][poscol] == BOX_ON_TARGET)
			{
				room[posrow + 1][poscol] = TARGET;
				room[posrow][poscol] = BOX_ON_TARGET;
			}
		}
		else
		{
			if (room[posrow + 1][poscol] == BOX)
			{
				room[posrow + 1][poscol] = SPACE;
				room[posrow][poscol] = BOX;
			}
			else if (room[posrow + 1][poscol] == BOX_ON_TARGET)
			{
				room[posrow + 1][poscol] = TARGET;
				room[posrow][poscol] = BOX;
			}
		}

		break;

	case 'a':
		if (room[posrow][poscol] == PERSON_ON_TARGET) // Person on target
		{
			if (room[posrow][poscol + 1] == SPACE) // Space
			{
				room[posrow][poscol + 1] = PERSON;
				room[posrow][poscol] = TARGET;
			}
			else if (room[posrow][poscol + 1] == TARGET) // Target
			{
				room[posrow][poscol + 1] = PERSON_ON_TARGET;
				room[posrow][poscol] = TARGET;
			}
		}
		else // Person on space
		{
			if (room[posrow][poscol + 1] == SPACE) // Space
			{
				room[posrow][poscol + 1] = PERSON;
				room[posrow][poscol] = SPACE;
			}
			else if (room[posrow][poscol + 1] == TARGET) // Target
			{
				room[posrow][poscol + 1] = PERSON_ON_TARGET;
				room[posrow][poscol] = SPACE;
			}
		}

		if (room[posrow][poscol] == TARGET)
		{
			if (room[posrow][poscol - 1] == BOX)
			{
				room[posrow][poscol - 1] = SPACE;
				room[posrow][poscol] = BOX_ON_TARGET;
			}
			else if (room[posrow][poscol - 1] == BOX_ON_TARGET)
			{
				room[posrow][poscol - 1] = TARGET;
				room[posrow][poscol] = BOX_ON_TARGET;
			}
		}
		else
		{
			if (room[posrow][poscol - 1] == BOX)
			{
				room[posrow][poscol - 1] = SPACE;
				room[posrow][poscol] = BOX;
			}
			else if (room[posrow][poscol - 1] == BOX_ON_TARGET)
			{
				room[posrow][poscol - 1] = TARGET;
				room[posrow][poscol] = BOX;
			}
		}

		break;

	case 'd':
		if (room[posrow][poscol] == PERSON_ON_TARGET) // Person on target
		{
			if (room[posrow][poscol - 1] == SPACE) // Space
			{
				room[posrow][poscol - 1] = PERSON;
				room[posrow][poscol] = TARGET;
			}
			else if (room[posrow][poscol - 1] == TARGET) // Target
			{
				room[posrow][poscol - 1] = PERSON_ON_TARGET;
				room[posrow][poscol] = TARGET;
			}
		}
		else // Person on space
		{
			if (room[posrow][poscol - 1] == SPACE) // Space
			{
				room[posrow][poscol - 1] = PERSON;
				room[posrow][poscol] = SPACE;
			}
			else if (room[posrow][poscol - 1] == TARGET) // Target
			{
				room[posrow][poscol - 1] = PERSON_ON_TARGET;
				room[posrow][poscol] = SPACE;
			}
		}

		if (room[posrow][poscol] == TARGET)
		{
			if (room[posrow][poscol + 1] == BOX)
			{
				room[posrow][poscol + 1] = SPACE;
				room[posrow][poscol] = BOX_ON_TARGET;
			}
			else if (room[posrow][poscol + 1] == BOX_ON_TARGET)
			{
				room[posrow][poscol + 1] = TARGET;
				room[posrow][poscol] = BOX_ON_TARGET;
			}
		}
		else
		{
			if (room[posrow][poscol + 1] == BOX)
			{
				room[posrow][poscol + 1] = SPACE;
				room[posrow][poscol] = BOX;
			}
			else if (room[posrow][poscol + 1] == BOX_ON_TARGET)
			{
				room[posrow][poscol + 1] = TARGET;
				room[posrow][poscol] = BOX;
			}
		}

		break;

	default:
		break;
	}
	allMoves[length - 1] = '\0';
}

/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd') && (move != 'z'))
	{
		scanf("%c", &move);
	}
	return move;
}

/* Boxed In Game */
int main(void)
{
	char layout[200] = "0011111000111005100010032011001002320100111043010000100011000011111000000000000000000000000000000000";
	int room[ROWS][COLS] = {0};
	char allMoves[1000] = {0};

	printf("ENGGEN131 - C Project 2024\n");
	printf("                          ... presents ...\n");
	printf("   +------+  ____                    _   _____         _ \n");
	printf("  /      /| |  _ \\                  | | |_   _|       | |\n");
	printf(" +------+ | | |_) | _____  _____  __| |   | |  _ __   | |\n");
	printf(" |      | + |  _ < / _ \\ \\/ / _ \\/ _` |   | | | '_ \\  | |\n");
	printf(" |      |/  | |_) | (_) >  <  __/ (_| |  _| |_| | | | |_|\n");
	printf(" +------+   |____/ \\___/_/\\_\\___|\\__,_| |_____|_| |_| (_)\n");
	printf("\n");
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	InitialiseRoom(room, layout);
	PrintRoom(room);
	while (!CheckGameOver(room))
	{
		MakeMove(room, GetMove(), allMoves);
		PrintRoom(room);
	}
	printf("\n\nCONGRATULATIONS!\nGame over!\n");
	printf("Moves: %s", allMoves);
	return 0;
}
