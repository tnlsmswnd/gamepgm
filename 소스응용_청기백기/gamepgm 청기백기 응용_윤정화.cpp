#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void gotoxy(int x, int y);
void game_control(int order, char name[7], char sol[][10], double check[][10], int quest);
void display_result(int user, int order[], double check[][10], char name[][7], char sol[][10], int quest);
void display_rule(void);

int main(void)
{
	system("color F1"); //메인색상 변경 
	
	int i, user_number, quest_number, rnd, temp;
	int order[4]={0, 1, 2, 3};
	char solution[4][10]={0}; 
	double time_check[4][10]={0};
	char user_name[4][7];
	srand(time(NULL));

	printf("청기/백기 게임\n\n");
	printf("게임에 참가할 인원수를 입력하고 Enter>");
	scanf("%d", &user_number);
	printf("\n문제의 개수를 입력하고 Enter>");
	scanf("%d", &quest_number);

	for(i=0;i<user_number;i++)
	{
		printf("%d번 참가자의 이름을 입력하고 Enter>", i+1);
		scanf("%s", &user_name[i]);
	}
	printf("만약 한글을 사용하였다면 영문키로 바꾸십시오.\n");
	printf("아무키나 누르시오.\n");
	getch();
   printf("\n게임의 순서는 다음과 같습니다. \n");
   for(i=0;i<user_number;i++)
   {
 		rnd=rand()%user_number;
		temp=order[i];
		order[i]=order[rnd];
		order[rnd]=temp;
   }
   for(i=0;i<user_number;i++)
   {
		printf("%d번 : %s\n", i+1, user_name[order[i]]);
   }
   printf("아무키나 누르시오.\n");
   getch();

   for(i=0;i<user_number;i++)
	game_control(order[i], user_name[order[i]], solution, 
		time_check, quest_number);

   printf("\n\n");
   printf("모든 게임이 끝났습니다. \n");
   printf("아무키나 누르면 결과를 표시합니다. \n");
   getch();
   display_result(user_number, order, time_check, user_name, 
	solution, quest_number);
   getch();
   return 0;
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//게임 컨트롤  
void game_control(int order, char name[7], char sol[][10], double check[][10], int quest)
{
   char *flag[]={"청기", "백기"};
   char *question[]={"내려!", "올려!", "내리지말고", "올리지말고"};
   clock_t start, end;
   int i, rnd[4];
   char key;
   system("cls");
   gotoxy(1, 3);
   printf("%s님 순서입니다. 키 조작은 다음과 같습니다.", name);
   display_rule();
   for(i=0;i<quest;i++)
   {
  		system("cls");
		rnd[0]=rand()%2;
		rnd[1]=rand()%4;
		start=clock();
		gotoxy(5, 10);
		if (rnd[1]>1)
		{
		       rnd[2]=rand()%2;
		       rnd[3]=rand()%2;
		       printf("%d: %s %s %s %s", i+1, flag[rnd[0]], question[rnd[1]], flag[rnd[2]], question[rnd[3]]);
	  	}
		else
		printf("%d: %s %s", i+1, flag[rnd[0]], question[rnd[1]]);
	    	key=getch();
		end=clock();
		check[order][i]=(double)(end-start)/CLK_TCK;
		//정답확인  
		if (rnd[1]>1)
		{
			if ((rnd[2]==0) && (rnd[3]==0) && (key=='z'))
				sol[order][i]=1;
			else if ((rnd[2]==0) && (rnd[3]==1) && (key=='a'))	
				sol[order][i]=1;
			else if ((rnd[2]==1) && (rnd[3]==0) && (key=='m'))	
				sol[order][i]=1;
			else if ((rnd[2]==1) && (rnd[3]==1) && (key=='k'))	
		        sol[order][i]=1; //정답  
			else
				sol[order][i]=0; //오답  
		}
		else			
		{
			if ((rnd[0]==0) && (rnd[1]==0) && (key=='z'))
				sol[order][i]=1;
			else if ((rnd[0]==0) && (rnd[1]==1) && (key=='a'))	
				sol[order][i]=1;
			else if ((rnd[0]==1) && (rnd[1]==0) && (key=='m'))	
				sol[order][i]=1;
			else if ((rnd[0]==1) && (rnd[1]==1) && (key=='k'))	
				sol[order][i]=1; //정답 
			else
				sol[order][i]=0; //오답  
		}
    
   // 각 문제당 결과 출력 
        if (sol[order][i] == 1) 
		{
            // 정답: 초록색 배경과 소리
            system("color 2F");
            printf("정답입니다!\n");
            Beep(1000, 300);  // 정답 소리
        } 
		else 
		{
            // 오답: 빨간색 배경과 소리
            system("color 4F");
            printf("오답입니다!\n");
            Beep(500, 300);  // 오답 소리
        }

        Sleep(1000);

        // 화면을 다시 원래대로 돌려놓기
        system("color F1");  // 기본 색상
    } 
}

void display_result(int user, int order[], double check[][10], char name[][7], char sol[][10], int quest)
{
   int i, j, result[4]={0};
   double min_time[4]={0};
   int winner_index = 0;  // 승자의 인덱스
   system("cls");
   
   printf("       ");
   for(i=0;i<user;i++)
	printf("%8s  ", name[order[i]]);
   printf("\n");
   
   for(j=0;j<quest;j++)
   {
		printf("    %d번 : ", j+1);
		for(i=0;i<user;i++)
		{   
			if (sol[order[i]][j]  && check[order[i]][j]<1)
			{
				printf("O");
				result[order[i]]+=1;
			}
			else
				printf("X");
			printf("%5.2f     ",check[order[i]][j]);
			if ((sol[order[i]][j]==1) && (check[order[i]][j]<1))
				min_time[order[i]]+=check[order[i]][j];
		}
		printf("\n");
   }
   
   printf("\n");
   printf("맞은개수:");
   for(i=0;i<user;i++)
	 printf("%7d    ", result[order[i]]);
   printf("\n");
   printf("소요시간:");
   for(i=0;i<user;i++)
	 printf("%7.2f    ", min_time[order[i]]);
   printf("\n");
   
   for (i = 1; i < user; i++)
    {
        if (result[order[i]] > result[order[winner_index]])
        {
            winner_index = i;
        }
        else if (result[order[i]] == result[order[winner_index]])
        {
            // 동점일 경우, 소요 시간이 적은 사람이 승리
            if (min_time[order[i]] < min_time[order[winner_index]])
            {
                winner_index = i;
            }
        }
    }

    // 승자 발표
    printf("\n승자는 %s입니다. 종료하려면 아무키나 누르시오.\n", name[order[winner_index]]);
}

void display_rule(void)
{
	gotoxy(1,4);
	printf("게임시작전까지 키를 누르지 마세요!");
	gotoxy(1, 6);
	printf("청기 올려 : a    백기 올려 : k");
	gotoxy(1, 7);
	printf("청기 내려 : z    백기 내려 : m");
	Sleep(2000);
	gotoxy(1, 8);
	printf("5초 후에 게임을 시작합니다. 준비하세요.");
	Sleep(5000);

	// 콘솔 입력 버퍼를 비우기 
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}
