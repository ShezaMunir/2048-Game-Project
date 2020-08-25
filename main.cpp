#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int board[4][4];
int saved[4][4];//previous move
int score=0;
int lastscore=0;//score obtained in previous move


void makeboard()//initializes board
{

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            board[i][j]= 0;

}

void viewboard()//displays board
{
    for (int i = 0; i < 4; i++ )
    {
        for (int j=0; j<4; j++)
        {
            if (board[i][j]==0)
            cout << "\t\t"<<setw(8) <<  0;
            else
            cout << "\t\t"<<setw(8)<<board[i][j];
        }
        cout<< endl<<endl;
    }
}


bool checkocc(int line, int column)//checks if position in specific line and column is occupied (i.e non-zero)
{
    if (board[line][column] != 0) return true;
    else return false;
}

void newrandomnum()//generates new number (2 or 4) at random position
{
    int line,column;

    bool occupied = true;

    while (occupied)
    {
        line = (rand() % 4);
        column = (rand() % 4);
        occupied = checkocc(line,column);
    }

    double probabilty = (1.0*rand())/ RAND_MAX;

    if (probabilty<0.80)//80% probability of generating 2
     {
         board[line][column] = 2;
     }
     else //20% probability of generating 4
     {
         board[line][column] = 4;
     }
}

void moveup()
{
    for(int j=0; j<4; j++)
    {
        for (int i=0;i<4;i++)
        {

            if(board[i][j]==0)
            {
                for(int k=i+1; k<4; k++)
                {
                    if(board[k][j])
                    {
                        board[i][j]=board[k][j];
                        board[k][j]=0;
                        break;
                    }
                }
            }
        }
    }
}
void sumup()
{
    for(int j=0; j<4; j++)
    {
        for (int i=0;i<3;i++)
        {
            if(board[i][j]&&board[i][j]==board[i+1][j])
            {
                board[i][j] += board[i+1][j];
                board[i+1][j]=0;
                lastscore=board[i][j];
                score+=lastscore;
            }
        }
    }
}

void movedown()
{
    for(int j=0; j<4; j++)
    {
        for (int i=3;i>=0;i--)
        {

            if(board[i][j]==0)
            {
                for(int k=i-1; k>=0; k--)
                {
                    if(board[k][j])
                    {
                        board[i][j]=board[k][j];
                        board[k][j]=0;
                        break;
                    }
                }
            }
        }
    }
}
void sumdown()
{
    for(int j=0; j<4; j++)
    {
        for (int i=3;i>0;i--)
        {
            if(board[i][j]&&board[i][j]==board[i-1][j])
            {
                board[i][j] += board[i-1][j];
                board[i-1][j]=0;
                lastscore=board[i][j];
                score+=lastscore;

            }
        }
    }
}

void moveleft()
{
    for(int i=0; i<4; i++)
    {
        for (int j=0;j<4;j++)
        {
            if(board[i][j]==0)
            {
                for(int k=j+1; k<4; k++)
                {
                    if(board[i][k])
                    {
                        board[i][j]=board[i][k];
                        board[i][k]=0;
                        break;
                    }
                }
            }
        }
    }
}

void sumleft()
{
    for(int i=0; i<4; i++)
    {
        for (int j=0;j<3;j++)
        {
            if(board[i][j] && board[i][j]==board[i][j+1])
            {
                board[i][j] += board[i][j+1];
                board[i][j+1]=0;
                lastscore=board[i][j];
                score+=lastscore;
            }
        }
    }
}

void moveright()
{
    for(int i=0; i<4; i++)
    {
        for (int j=3;j>=0;j--)
        {
            if(board[i][j]==0)
            {
                for(int k=j-1; k>=0; k--)
                {
                    if(board[i][k])
                    {
                        board[i][j]=board[i][k];
                        board[i][k]=0;
                        break;
                    }
                }
            }
        }
    }
}

void sumright()
{
    for(int i=0; i<4; i++)
    {
        for (int j=3;j>0;j--)
        {
            if(board[i][j] && board[i][j]==board[i][j-1])
            {
                board[i][j] += board[i][j-1];
                board[i][j-1]=0;
                lastscore=board[i][j];
                score+=lastscore;
            }
        }
    }
}

void makesaved()//keeps the last move saved
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            saved[i][j]= board[i][j];
}

bool checkmovement()//checks if a move has taken place
{ for(int i=0 ; i<4; i++)
    {
        for(int j=0; j<4;j++)
        {
            if(saved[i][j]!=board[i][j])
            {
                return true;
            }
        }
    }
    return false;
}
void undo()//undoes the last move and subtracts last score from current score
{
    for(int i=0; i<4; i++)
    {
        for (int j=0;j<4;j++)
        {
            board[i][j] = saved[i][j];
        }
    }
    score-=lastscore;
}


void applymove(char dir)
{
    switch(dir)
    {
    case 'a':
        {
            lastscore=0;
            makesaved();
            moveleft();
            sumleft();
            moveleft();
            break;
        }
    case 's':
        {
            lastscore=0;
            makesaved();
            movedown();
            sumdown();
            movedown();
            break;
        }
    case 'd':
        {
            lastscore=0;
            makesaved();
            moveright();
            sumright();
            moveright();
            break;
        }
    case 'w':
        {
            lastscore=0;
            makesaved();
            moveup();
            sumup();
            moveup();
            break;
        }
    case 'u':
        {
            undo();
            break;
        }
    case 'r':
        {
         break;
        }
    case 'q':
        {
            break;
        }

    default: cout << "Enter valid move." <<endl<<endl;

    }
}

bool wincheck()//checks if win condition is fulfilled
{   int max_num=0;

    for (int i=0; i<4;i++)
        for(int j=0;j<4;j++)
    {
        if (board[i][j]>max_num)
            max_num=board[i][j];
    }
    if (max_num==2048)
    {
        cout<<"You've won!"<<endl;

        return 1;
    }
    else return 0;
}

bool check_empty()//checks if there is an unfilled space(i.e a 0)
{
    for (int i=0; i<4;i++)
        for(int j=0;j<4;j++)
        {
            if(board[i][j]==0)
                return true;

        }
        return false;
}

bool game_over()//checks if game-over conditions are fulfilled
{
    bool over=true;
	for(int i=0;i<4;i++)
		for(int j=0;j<3;j++)
            {
			if(board[i][j]==board[i][j+1])
			{
                over=0;
                return over;
			}
            }

    for(int i=0;i<3;i++)
        for(int j=0;j<4;j++)
			{
            if(board[i][j]==board[i+1][j])
            {
                over=0;
                return over;
            }
			}

	return over;
}
bool losecheck()//checks if losing conditions are fulfilled
{
    if(!check_empty())
        if(game_over())
        {
            cout<<"Hard luck. You lost!\n";
            return 1;
        }
    return 0;
}

void breakhs(int high_score,int score)//checks if high score has been broken
{
    if (score>high_score)
    {
        cout<<"You broke the high score! \nHigh score is now: " << score<<endl <<endl;
    }
    else
    {
        cout<<"You did not break the high score.\n";
    }
}

int main()
{
    char dir;
    int oldhs=0, high_score=0;

    srand(time(0));

    ofstream store_h_s;
    ifstream file;
    store_h_s.open("high_score.txt",ios::app);//opens file to append new scores
    file.open("high_score.txt",ios::in);//opens file to take inputs from it

    while(file>>oldhs)//takes in each input from the file
    {
        if(oldhs>high_score)
        {
            high_score=oldhs;
        }
    }


    restart://label for goto function
    cout << "\t\t\t\t\t\t\t2048"<<endl<<"Your score: " << score <<endl << "High score: "<< high_score<<endl ;
    makeboard();
    newrandomnum();
    newrandomnum();
    viewboard();
    cout << "Press: \n\'w\' to move up\n\'s\' to move down\n\'d\' to move right\n\'a\' to move left\n\'u\' to undo move\n\'q\' to quit."<<endl<<endl;



    while(dir!='q')
    {
        if (wincheck())
            {
                breakhs(high_score, score);
                store_h_s<<score<<endl;return 1;
            }
        if (losecheck())
            {
                breakhs(high_score, score);
                store_h_s<<score<<endl;return 1;
            }
        cout << "Enter move: ";
        cin >> dir;

        applymove(dir);
        if (dir=='a'||dir=='s'||dir=='d'||dir=='w'||dir=='u')
            {
                system("cls");//clears screen for each iteration
                if (checkmovement()&&dir!='q') newrandomnum();
                cout << "\t\t\t\t\t\t\t2048"<<endl << "Your score: " << score <<endl<< "High score: "<< high_score<<endl;
                viewboard();

                cout << "Press: \n\'w\' to move up\n\'s\' to move down\n\'d\' to move right\n\'a\' to move left\n\'u\' to undo move\n\'r\' to restart\n\'q\' to quit."<<endl<<endl;
            }
            if(dir=='r')//for restart
            {
                score=0;
                system("cls");
                goto restart;
            }
    }


    breakhs(high_score, score);
    store_h_s<<score<<endl;
    store_h_s.close();
}
