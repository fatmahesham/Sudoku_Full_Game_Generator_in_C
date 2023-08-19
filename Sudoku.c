/*
*
*
*       By Sara Sobhy & Fatma Hesham
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>    //  header file for gotoxy

char sudoku_Game[9][9];
char sudoku_UserSol[9][9];
char sudoku_RightSol[9][9]= {     {'1','2','3','4','5','6','7','8','9'},
    {'4','5','6','7','8','9','1','2','3'},
    {'7','8','9','1','2','3','4','5','6'},
    {'2','3','4','5','6','7','8','9','1'},
    {'5','6','7','8','9','1','2','3','4'},
    {'8','9','1','2','3','4','5','6','7'},
    {'3','4','5','6','7','8','9','1','2'},
    {'6','7','8','9','1','2','3','4','5'},
    {'9','1','2','3','4','5','6','7','8'}
};


COORD coord= {0,0}; // this is global variable

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void array_print(char arr[][9])
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,0xFC);
    int i=0,j=0,k=0;
    for(k=0;k<9;k++)
    {
        SetConsoleTextAttribute(hConsole,0xF0);
        printf("   %d",k);  // index of columns
        SetConsoleTextAttribute(hConsole,0xFC);
    }
    for(i=0; i<9; i++)
    {
        printf("\n |---|---|---|---|---|---|---|---|---|\n");
        SetConsoleTextAttribute(hConsole,0xF0);
        printf("%d",i);   //index of row
        SetConsoleTextAttribute(hConsole,0xFC);
        printf("|");
        for(j=0; j<9; j++)
        {
            if(arr[i][j]=='?')
            {
                printf("   |");
            }
            else
            {
                if(sudoku_Game[i][j]=='?')
                {
                    SetConsoleTextAttribute(hConsole,0xF1);
                    printf(" %c ",arr[i][j]);
                    SetConsoleTextAttribute(hConsole,0xFC);
                }
                else
                    printf(" %c ",arr[i][j]);
                printf("|");
            }
        }
    }
    printf("\n |---|---|---|---|---|---|---|---|---|\n");
}

void copy_CharArr1_to_CharArr2(char arr1[][9], char arr2[][9])
{
    int i,j;
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            arr2[i][j]=arr1[i][j];
}

void write_rules()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,0xF1);
    printf("RULES OF SUDOKU-GAME\n");
    printf("*********************\n");
    printf(" 1- Use numbers from 1 to 9 to fill the board\n");
    printf(" 2- Repetitions are prohibited for the same row, the same column and the same square\n\n\n");
    Sleep(5000);
    printf("REDAY?");
    Sleep(1000);
    system("cls");
}

void shuffle(char quiz[][9])
{
    srand(time(NULL));
    int offset=0; //it is added to the remainder by 3 to keep the changed rows or columns in
    //the same block(square 3x3

    /* shuffle columns  */
    int i,j;
    for(i=0; i<9; i++)
    {
        int k=rand()%3;
        for(j=0; j<9; j++)
        {
            char temp =quiz[j][i];
            quiz[j][i]=quiz[j][k+offset];
            quiz[j][k+offset]=temp;
        }
        if(i%3==2)
            offset+=3;
    }

    /* shuffle rows  */
    offset=0;
    for(i=0; i<9; i++)
    {
        int l=rand()%3;
        for(j=0; j<9; j++)
        {
            char temp=quiz[i][j];
            quiz[i][j]=quiz[l+offset][j];
            quiz[l+offset][j]=temp;
        }
        if(i%3==2)
            offset+=3;
    }

    /* replace every number with another */
    char num[9]= {'1','2','3','4','5','6','7','8','9'};
    for(i=0; i<9; i++)
    {
        int n=rand()%9;
        char temp=num[i];
        num[i]=num[n];
        num[n]=temp;
    }
}
int make_quiz(char quiz[][9])
{
    int hidden_Num;
    printf("Enter a number of hidden places (number from 1 to 64)\n");
    while (1)
    {
        scanf("%d", &hidden_Num);
        if(hidden_Num>64 || hidden_Num<1 )
        {
            printf("Out Of Boud number\n");
            printf("Please,enter another one\n");
        }
        else
            break;
    }
    /* ************************************* HIDE NUMERS ****************************************** */
    int num[81]; //indeces array
    int i,j;
    for(j=0; j<81; j++)
        num[j]=j;

    /* shuffle the array */
    srand(time(NULL));
    for(i=0; i<81; i++)
    {
        int n=rand()%81;
        int temp=num[i];
        num[i]=num[n];
        num[n]=temp;
    }

    /* Choose the places with the unknown values */
    int firstPlaceIndex;
    // firstPlaceIndex is the index of the begin of the sequence we use from num array

    firstPlaceIndex=rand()%(81-hidden_Num);
    int index=num[firstPlaceIndex];  //index is a number between 0 and 80
    for(i=0; i<hidden_Num; i++)
    {
        int row=index/9;
        int column=index%9;
        quiz[row][column]='?';
        index=num[firstPlaceIndex+i+1];
    }
    return hidden_Num;
}
int soduko_check2(char arr[][9],char arr1[][9],int row,int col,int r,int c,int num)
{
    //This function is for checking if a number is repeated in the square(made up of 3*3 spaces) or not.
    int i=0,j=0,flag=1,n=0;
    arr[r][c]=num+'0';
    for(i=row-3; (i<row)&&(flag!=0); i++)
    {
        for(j=col-3; (j<col)&&(flag!=0); j++)
        {
            if((i==r)&&(j==c))
            {
                continue;
            }
            if(arr[i][j]!=arr[r][c])
            {
                flag=1;
            }
            else
            {
                flag=0;
                printf("Unfortunately,this number is repeated\n");
                if(arr1[i][j]=='?')
                {
                    printf("Please enter zero or one\n");
                    printf("Note that if a zero number is selected, the last entered number will be deleted\n");
                    printf("If only one number is selected, the duplicate number that was previously entered will be deleted\n");
                    scanf("%d",&n);
                    if(n==0)
                    {
                        arr[r][c]='?';
                    }
                    else
                    {
                        arr[i][j]='?';
                    }
                }
                else
                {
                    printf("Unfortunately,this number can not be deleted,so the last entered number is deleted\n");
                    arr[r][c]='?';
                }
            }
        }
    }
    return flag;
}
int sudoku_check(char arr[][9],char arr1[][9],int r,int c,int num)
{
    int i=0,j=0,flag=1,n=0;
    if(arr[r][c]=='?')
    {
        arr[r][c]=num+'0';
        for(j=0; (j<9)&&(flag!=0); j++) //This loop is for checking if a number is repeated in the row or not.
        {
            if(j==c)
            {
                continue;
            }
            if(arr[r][j]!=arr[r][c])
            {
                flag=1;
            }
            else
            {
                flag=0;
                printf("Unfortunately,this number is repeated\n");
                if(arr1[r][j]=='?')
                {
                    printf("Please enter zero or one\n");
                    printf("Note that if a zero number is selected, the last entered number will be deleted\n");
                    printf("If only one number is selected, the duplicate number that was previously entered will be deleted\n");
                    scanf("%d",&n);
                    if(n==0)
                    {
                        arr[r][c]='?';
                    }
                    else
                    {
                        arr[r][j]='?';
                    }
                }
                else
                {
                    printf("Unfortunately,this number can not be deleted,so the last entered number is deleted\n");
                    arr[r][c]='?';
                }
            }
        }
        for(i=0; (i<9)&&(flag!=0); i++) //This loop is for checking if a number is repeated in the column or not.
        {
            if(i==r)
            {
                continue;
            }
            if(arr[i][c]!=arr[r][c])
            {
                flag=1;
            }
            else
            {
                flag=0;
                printf("Unfortunately,this number is repeated\n");
                if(arr1[i][c]=='?')
                {
                    printf("Please enter zero or one\n");
                    printf("Note that if a zero number is selected, the last entered number will be deleted\n");
                    printf("If only one number is selected, the duplicate number that was previously entered will be deleted\n");
                    scanf("%d",&n);
                    if(n==0)
                    {
                        arr[r][c]='?';
                    }
                    else
                    {
                        arr[i][c]='?';
                    }
                }
                else
                {
                    printf("Unfortunately,this number can not be deleted,so the last entered number is deleted\n");
                    arr[r][c]='?';
                }
            }
        }
        if((r<3)&&(flag!=0))
        {
            if(c<3)
            {
                flag=soduko_check2(arr,arr1,3,3,r,c,num);
            }
            else if((c>=3)&&(c<6))
            {
                flag=soduko_check2(arr,arr1,3,6,r,c,num);
            }
            else
            {
                flag=soduko_check2(arr,arr1,3,9,r,c,num);
            }
        }
        if((r>=3)&&(r<6)&&(flag!=0))
        {
            if(c<3)
            {
                flag=soduko_check2(arr,arr1,6,3,r,c,num);
            }
            else if((c>=3)&&(c<6))
            {
                flag=soduko_check2(arr,arr1,6,6,r,c,num);
            }
            else
            {
                flag=soduko_check2(arr,arr1,6,9,r,c,num);
            }
        }
        if((r>=6)&&(r<9)&&(flag!=0))
        {
            if(c<3)
            {
                flag=soduko_check2(arr,arr1,9,3,r,c,num);
            }
            else if((c>=3)&&(c<6))
            {
                flag=soduko_check2(arr,arr1,9,6,r,c,num);
            }
            else
            {
                flag=soduko_check2(arr,arr1,9,9,r,c,num);
            }
        }
    }
    else
    {
        printf("Error you can not enter the number in this field\n");
        flag=0;
    }
    return flag;
}
void sudoku_play(char arr[][9],char arr1[][9],int count)
{
    int index_row=0,index_col=0, num=0;
    while(count!=0)
    {
        printf("Enter the row and column\n");
        scanf("%d%d",&index_row,&index_col);
        printf("Enter a number from one to nine\n");
        scanf("%d",&num);
        if(sudoku_check(arr,arr1,index_row,index_col,num))
        {
            array_print(arr);
            count--;
        }
        else
        {
            Sleep(5000);
            array_print(arr);
        }
    }
    if(count==0)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,0xF2);
        printf("\n************ congratulations ************\n");
        SetConsoleTextAttribute(hConsole,0xFC);
    }
}
int play_again()
{
    char ch;
    printf("\n\nDo you want to play again?\n");
    printf("If yes enter y, if enter any letter else\n\n");
    scanf(" %c", &ch);
    if(ch=='y')
        return 1;
    else
        return 0;
}
int main()
{
    system("COLOR F1");
    write_rules();
    do
    {
        shuffle(sudoku_RightSol);
        copy_CharArr1_to_CharArr2(sudoku_RightSol,sudoku_Game);
        int hidden_num_count=make_quiz(sudoku_Game);
        copy_CharArr1_to_CharArr2(sudoku_Game,sudoku_UserSol);
        array_print(sudoku_Game);
        sudoku_play(sudoku_UserSol, sudoku_Game, hidden_num_count);
    }
    while(play_again());

    return 0;
}