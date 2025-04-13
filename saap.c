#include<stdio.h>
#include <windows.h>
#include<stdlib.h>
#include <ctype.h>
#include<conio.h>

HANDLE color;
#define height 20 
#define width 60

int gameover;
int bodyX[100],bodyY[100];
int length;
int x,y,fruitx,fruity;
int score,key,speed=100;
void welcome0(){
    //system("cls");
    printf("\033[?25l");
    for (int i = 8; i >= (-2); i--) {
        system("cls");
        SetConsoleTextAttribute(color, 2);
        printf("\033[1;1H");
        if(i<= -2) printf("\n");
        if(i<= -1) printf("\n");
        if (i <= 0) printf("\t    #################################################################################################################\n");
        if (i <= 1) printf("\n");
        if (i <= 2) printf("\t\t########   ###    ##    ######    ##   ##   ########        ########    ######    ###      ###   ########\n");
        if (i <= 3) printf("\t\t##         ## #   ##   ##    ##   ## ##     ##              ##         ##    ##   ## #    # ##   ##      \n");
        if (i <= 4) printf("\t\t########   ##  #  ##   ## ## ##   ###       ######          ##  ####   ## ## ##   ##  #  #  ##   ######  \n");
        if (i <= 5) printf("\t\t      ##   ##   # ##   ##    ##   ## ##     ##              ##    ##   ##    ##   ##   ##   ##   ##      \n");
        if (i <= 6) printf("\t\t########   ##    ###   ##    ##   ##   ##   ########        ########   ##    ##   ##        ##   ########\n");
        if (i <= 7) printf("\n");
        if (i <= 8) printf("\t    #################################################################################################################\n");
        SetConsoleTextAttribute(color, 7);
        Sleep(60);
    }

    printf("\033[?25h");
}
void welcome(){
    //system("cls");
    printf("\n\n");
    SetConsoleTextAttribute(color, 2);
    printf("\t    #################################################################################################################\n\n");
    printf("\t\t########   ###    ##    ######    ##   ##   ########        ########    ######    ###      ###   ########\n");
    printf("\t\t##         ## #   ##   ##    ##   ## ##     ##              ##         ##    ##   ## #    # ##   ##      \n");
    printf("\t\t########   ##  #  ##   ## ## ##   ###       ######          ##  ####   ## ## ##   ##  #  #  ##   ######  \n");
    printf("\t\t      ##   ##   # ##   ##    ##   ## ##     ##              ##    ##   ##    ##   ##   ##   ##   ##      \n");
    printf("\t\t########   ##    ###   ##    ##   ##   ##   ########        ########   ##    ##   ##        ##   ########\n");
    printf("\n");
    printf("\t    #################################################################################################################\n\n");
    SetConsoleTextAttribute(color, 7);
}
void goodbye(){
    system("cls");
    printf("\n\n");
    SetConsoleTextAttribute(color, 4);
    printf("\t\t    ######################################################################################################\n\n");
    printf("\t\t\t########    ######    ###      ###   ########         #####     ##     ##   ########   #######     \n");
    printf("\t\t\t##         ##    ##   ## #    # ##   ##              ##    ##   ##     ##   ##         ##   ##     \n");
    printf("\t\t\t##  ####   ## ## ##   ##  #  #  ##   ######          ##    ##    ##   ##    ######     ######      \n");
    printf("\t\t\t##    ##   ##    ##   ##   ##   ##   ##              ##    ##     ## ##     ##         ##  ##      \n");
    printf("\t\t\t########   ##    ##   ##        ##   ########         #####        ###      ########   ##   ##     \n");
    printf("\n");
    printf("\t\t    ######################################################################################################\n\n");
    SetConsoleTextAttribute(color, 7);
}
void setup(){
    gameover=0;
    x = width/2;
    y=height/2;
    fruitx = rand() % width;
    fruity = rand() % height;
    while(fruitx == 0){
        fruitx = rand()%width;
    }
    while(fruity == 0)
    {
        fruity = rand() % height;
    }
    score = 0;
    length = 0;
}
void canvas(){
    printf("\033[1;1H");
    printf("\t\t\t\t\t");
    SetConsoleTextAttribute(color, 1);
    for(int i=0;i<width+2;i++)
    {
        printf("-");
    }
    SetConsoleTextAttribute(color, 7);
    printf("\n");
    for(int j=0;j<height+2;j++)
    {
        for(int i =0;i<width+2;i++)
        {
            if(i==0){
                SetConsoleTextAttribute(color, 1);
                printf("\t\t\t\t\t|");
                SetConsoleTextAttribute(color, 7);
            }
            else if(i == width+1){
                SetConsoleTextAttribute(color, 1);
                printf("|");
                SetConsoleTextAttribute(color, 7);
            }
            else if(i == fruitx && j == fruity){
                SetConsoleTextAttribute(color, 13);
                printf("@");
                SetConsoleTextAttribute(color, 7);
            }
            else if(i==x && j== y)
            {   
                SetConsoleTextAttribute(color, 2);
                printf("0");
                SetConsoleTextAttribute(color, 7);
            }
            else {
                int printTail = 0;
                for (int k = 0; k < length; k++) {
                    if (bodyX[k] == i && bodyY[k] == j) {
                        SetConsoleTextAttribute(color, 2);
                        printf("o");
                        SetConsoleTextAttribute(color, 7);
                        printTail = 1;
                        break;
                    }   
                }
                if (!printTail)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("\t\t\t\t\t");
    SetConsoleTextAttribute(color, 1);
    for(int i=0;i<width+2;i++)
    {
        printf("-");
    }
    SetConsoleTextAttribute(color, 7);
    printf("\n");
    printf("Score = %d\n", score);
    printf("Press W, A, S, D to move. Press X to quit.\n");
}
void input(){
    if(kbhit()){
        switch(tolower(getch())){
            case 'a':
            if (key != 2) key = 1;
            break;
            case 'd':
                if (key != 1) key = 2;
                break;
            case 'w':
                if (key != 4) key = 3;
                break;
            case 's':
                if (key != 3) key = 4;
                break;
            case 'x':
                gameover = 1;
                break;
            }
    }
}
void working(){
    int prevX = bodyX[0];
    int prevY = bodyY[0];
    int tempX, tempY;
    bodyX[0] = x;
    bodyY[0] = y;
    for (int i = 1; i <= length; i++) {
        tempX = bodyX[i];
        tempY = bodyY[i];
        bodyX[i] = prevX;
        bodyY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }
    switch (key) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
        }
        if (x < 0 || x >= width || y < 0 || y >= height+2)
            gameover = 1;
        for (int i = 0; i < length; i++) {
            if (bodyX[i] == x && bodyY[i] == y)
                gameover = 1;
        }
        if (x == fruitx && y == fruity) {
            fruitx = rand() % width;
            fruity = rand() % height;
            while (fruitx == 0)
                fruitx = rand() % width;
            while (fruity == 0)
                fruity = rand() % height;
            score += 10;
            length++;
            if(speed>=20){
                speed -= 10;
            }
        }
}
void hideCursor() {
    printf("\033[?25l");
}
void showCursor() {
    printf("\033[?25h");
}
void loader(){
    int j=0;
    printf("\033[?25l");
    while(j!=60){
        printf("\033[1;1H");
        welcome();
        printf("\n");
        SetConsoleTextAttribute(color, 1);
        printf("\t\t\t\t\t[");
        for(int i =0;i<j;i++)
        { 
            printf("=");
        }
        for(int i=j;i<59;i++){
            printf(" ");
        }   
        printf("]");
        SetConsoleTextAttribute(color, 7);
        j++;
        Sleep(50);
    }    
    printf("\033[?25h");
}
int main(){
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    welcome0();
    hideCursor();
    system("cls");
    
    welcome();
    Sleep(200);
    printf("\n\n\t\t\t\t\t\t\t    Press any key to start");
    getch();
    system("cls");
    loader();
    hideCursor();
    setup();
    system("cls");
    while (gameover == 0 ) {
        canvas();
        input();
        working();
        Sleep(speed);
    }
    showCursor();
    goodbye();

    printf("\n\t\t\t\t\t\t\t\tFinal Score: %d\n\n\n", score);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}
