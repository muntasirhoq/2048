#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int nameFlag=0,nameCount=-1,indexl[20];//counting the number of letters of name 
char namestr[20];
char letter[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
int flag=1;//front page display
int flag2,increase=0;//loading show
int a[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};//displaying numbers on the screen
int num1,num2;//picking 2 numbers among 2 and 4 randomly
int b1,c1;//for picking 1st spot randomly
int b2,c2;//for picking 2nd spot randomly
int move=0;//number of moves performed
int i,j,k;
int flag1;//for choosing b1,c1,b2,c2 randomly only 1st 0time when the game starts
int end=0;//indicates the end of the game
int d1,e1;//for putting an 2 in every move in a randomly chosen place
int count=0;//total number of numbers. if count==16 game over
int win=0;//when win==1 the number 2048 has appeared
int endpoint=0;//indicating if any 2 consecutive numbers of 16 filled slot match
int score=0;
int high_score11=0,high_score12=0,high_score13=0,high_score14=0,high_score15=0;//1st 5 high scores in easy mode
int high_score21=0,high_score22=0,high_score23=0,high_score24=0,high_score25=0;//1st 5 high scores in hard mode
char highScore11[100],highScore12[100],highScore13[100],highScore14[100],highScore15[100];//for easy mode printing string
char highScore21[100],highScore22[100],highScore23[100],highScore24[100],highScore25[100];//for hard mode printing string 
char scoreString1[100];//for printing score as a string
char timeString[100];//for printing time as string
int duration11,duration12,duration13,duration14,duration15;//for printing 5 times besides 5 highscores easy mode
char dur11[100],dur12[100],dur13[100],dur14[100],dur15[100];//for printing 5 times as strings besides 5 highscores easy mode
int duration21,duration22,duration23,duration24,duration25;//for printing 5 times besides 5 highscores hard mode
char dur21[100],dur22[100],dur23[100],dur24[100],dur25[100];//for printing 5 times as strings besides 5 highscores hard mode
int animationFlag = 0,animate=0;
char name11[20],name12[20],name13[20],name14[20],name15[20];
char name21[20],name22[20],name23[20],name24[20],name25[20];
FILE *p1;
FILE *hc1;
FILE *hc2;
FILE *p2;
int xx;//including new number 2 or 4 with probability
int tres=0;//second counting
int tLimit=2000;//time limit exceed korle game over
int increase1=0;//to display ending page for sometime before showing highscore
int flag3=0;//for printing highscore and detecting modes
int pause=0;
int ball_y1,ball_x1,ball_x2,ball_y2,ball=0;//coordinate of the ball centre
int dx1=1,dy1=2,dx2=2,dy2=1;

void TIME1()
{
	if(flag2==-2)
	{
		if(flag==3)
			flag3=3;//to generate highscores only once in the end
		if(flag==0)
			flag3=0;//to generate highscores only once in the end
		if(increase1>=3)
			flag2=3;
		increase1++;
	}
}
void TIME()
{
	if(flag2==-1)
	{	
		if(increase>=500)
			flag2=2;//start game after being loaded
		increase=increase+3;
	}
}
void time()
{	
	if((flag==0 || flag==3) && flag2==2 && nameFlag==2)
	{
		tres=tres+1;
		int _a,_i, _c=tres;
		if(_c==0)
		{
			timeString[0]='0';
			timeString[1]='\0';
		}
		else
		{
			for(_i=0;_c;_i++)
			{
				timeString[_i]=(_c%10)+'0';
				_c/=10;
			}
			timeString[_i]='\0';
		}
		_i=0;
		int _j=strlen(timeString)-1;
		for(_i=0;_j>_i;_i++,_j--)
		{
			_a=timeString[_i];
			timeString[_i]=timeString[_j];
			timeString[_j]=_a;
		}
		
	}
}
void scorePrinting()
{
	int _a,_i,_c=score;
	if(_c==0)
	{
		scoreString1[0]='0';
		scoreString1[1]='\0';
	}
	else
	{
		for(_i=0;_c;_i++)
		{
			scoreString1[_i]=(_c%10)+'0';
			_c/=10;
		}
		scoreString1[_i]='\0';
	}
	_i=0;
	int _j=strlen(scoreString1)-1;
	for(_i=0;_j>_i;_i++,_j--)
	{
		_a=scoreString1[_i];
		scoreString1[_i]=scoreString1[_j];
		scoreString1[_j]=_a;
	}

	iText(620,430,"SCORE :", GLUT_BITMAP_HELVETICA_18);
	iText(700,430,scoreString1,GLUT_BITMAP_HELVETICA_18 );
}

void highscorePrinting()
{
	
	if(flag3==3)
	{	
		hc1=fopen("hc1.txt","r");
		fscanf(hc1,"%d",&high_score11);
		fscanf(hc1,"%d",&high_score12);
		fscanf(hc1,"%d",&high_score13);
		fscanf(hc1,"%d",&high_score14);
		fscanf(hc1,"%d",&high_score15);
		fscanf(hc1,"%d",&duration11);
		fscanf(hc1,"%d",&duration12);
		fscanf(hc1,"%d",&duration13);
		fscanf(hc1,"%d",&duration14);
		fscanf(hc1,"%d",&duration15);
		fscanf(hc1,"%s",name11);
		fscanf(hc1,"%s",name12);
		fscanf(hc1,"%s",name13);
		fscanf(hc1,"%s",name14);
		fscanf(hc1,"%s",name15);
		fclose(hc1);
		
		if (score >= high_score11)
		{		
			high_score15=high_score14;
			duration15=duration14;
			strcpy(name15,name14);
			high_score14=high_score13;
			duration14=duration13;
			strcpy(name14,name13);
			high_score13=high_score12;
			duration13=duration12;
			strcpy(name13,name12);
			if(score>high_score11)
			{
				high_score12=high_score11;
				duration12=duration11;
				strcpy(name12,name11);
				high_score11=score;
				duration11=tres;
				strcpy(name11,namestr);
			}
			else if(score== high_score11 && duration11<tres)
			{
				high_score12=high_score11;
				duration12=tres;
				strcpy(name12,namestr);
			}
			else if(score== high_score11 && duration11>=tres)
			{
				high_score12 = high_score11;
				duration12 = duration11;
				strcpy(name12,name11);
				duration11=tres;
				strcpy(name11,namestr);
			}		
		}			
		else if(score>=high_score12 && score<high_score11)
		{
			high_score15=high_score14;
			duration15=duration14;
			strcpy(name15,name14);
			high_score14=high_score13;
			duration14=duration13;
			strcpy(name14,name13);
			if(score>high_score12)
			{
				high_score13=high_score12;
				duration13=duration12;
				strcpy(name13,name12);
				high_score12=score;
				duration12=tres;
				strcpy(name12,namestr);
			}
			else if(score== high_score12 && duration12<tres)
			{
				high_score13=high_score12;
				duration13=tres;
				strcpy(name13,namestr);
			}
			else if(score== high_score12 && duration12>=tres)
			{
				high_score13 = high_score12;
				duration13 = duration12;
				strcpy(name13,name12);
				duration12=tres;
				strcpy(name12,namestr);
			}
		}
		else if(score>=high_score13 && score<high_score12)
		{
			high_score15=high_score14;
			duration15=duration14;
			strcpy(name15,name14);
			if(score>high_score13)
			{
				high_score14=high_score13;
				duration14=duration13;
				strcpy(name14,name13);
				high_score13=score;
				duration13=tres;
				strcpy(name13,namestr);
			}
			else if(score== high_score13 && duration13<tres)
			{
				high_score14=high_score13;
				duration14=tres;
				strcpy(name14,namestr);
			}
			else if(score== high_score13 && duration13>=tres)
			{
				high_score14 = high_score13;
				duration14 = duration13;
				strcpy(name14,name13);
				duration13=tres;
				strcpy(name13,namestr);
			}
		}
		else if(score>=high_score14 && score<high_score13)
		{
			if(score>high_score14)
			{
				high_score15=high_score14;
				duration15=duration14;
				strcpy(name15,name14);
				high_score14=score;
				duration14=tres;
				strcpy(name14,namestr);
			}
			else if(score== high_score14 && duration14<tres)
			{
				high_score15=high_score14;
				duration15=tres;
				strcpy(name15,namestr);
			}
			else if(score== high_score14 && duration14>=tres)
			{
				high_score15 = high_score14;
				duration15 = duration14;
				strcpy(name15,name14);
				duration14=tres;
				strcpy(name14,namestr);
			}
		}
		else if(score>=high_score15 && score<high_score14)
		{
			if(score>high_score15)
			{
				high_score15=score;
				duration15=tres;
				strcpy(name15,namestr);
			}
			else if(score==high_score15 && tres<duration15)
			{
				duration15=tres;
				strcpy(name15,namestr);
			}
		}
	
		hc1=fopen("hc1.txt","w");
		fprintf(hc1,"%d  ",high_score11);
		fprintf(hc1,"%d  ",high_score12);
		fprintf(hc1,"%d  ",high_score13);
		fprintf(hc1,"%d  ",high_score14);
		fprintf(hc1,"%d  ",high_score15);
		fprintf(hc1,"%d  ",duration11);
		fprintf(hc1,"%d  ",duration12);
		fprintf(hc1,"%d  ",duration13);
		fprintf(hc1,"%d  ",duration14);
		fprintf(hc1,"%d  ",duration15);
		fprintf(hc1,"%s  ",name11);
		fprintf(hc1,"%s  ",name12);
		fprintf(hc1,"%s  ",name13);
		fprintf(hc1,"%s  ",name14);
		fprintf(hc1,"%s",name15);
		fclose(hc1);
		hc1=fopen("hc1.txt","r");
		fscanf(hc1,"%s",highScore11);
		fscanf(hc1,"%s",highScore12);
		fscanf(hc1,"%s",highScore13);
		fscanf(hc1,"%s",highScore14);
		fscanf(hc1,"%s",highScore15);
		fscanf(hc1,"%s",dur11);
		fscanf(hc1,"%s",dur12);
		fscanf(hc1,"%s",dur13);
		fscanf(hc1,"%s",dur14);
		fscanf(hc1,"%s",dur15);
		fscanf(hc1,"%s",name11);
		fscanf(hc1,"%s",name12);
		fscanf(hc1,"%s",name13);
		fscanf(hc1,"%s",name14);
		fscanf(hc1,"%s",name15);
		fclose(hc1);
		flag3=5;
	}		
		
		
	if(flag3==0)
	{		
		hc2=fopen("hc2.txt","r");
		fscanf(hc2,"%d",&high_score21);
		fscanf(hc2,"%d",&high_score22);
		fscanf(hc2,"%d",&high_score23);
		fscanf(hc2,"%d",&high_score24);
		fscanf(hc2,"%d",&high_score25);
		fscanf(hc2,"%d",&duration21);
		fscanf(hc2,"%d",&duration22);
		fscanf(hc2,"%d",&duration23);
		fscanf(hc2,"%d",&duration24);
		fscanf(hc2,"%d",&duration25);
		fscanf(hc2,"%s",name21);
		fscanf(hc2,"%s",name22);
		fscanf(hc2,"%s",name23);
		fscanf(hc2,"%s",name24);
		fscanf(hc2,"%s",name25);
		fclose(hc2);
		
		if (score >= high_score21)
		{		
			high_score25=high_score24;
			duration25=duration24;
			strcpy(name25,name24);
			high_score24=high_score23;
			duration24=duration23;
			strcpy(name24,name23);
			high_score23=high_score22;
			duration23=duration22;
			strcpy(name23,name22);
			if(score>high_score21)
			{
				high_score22=high_score21;
				duration22=duration21;
				strcpy(name22,name21);
				high_score21=score;
				duration21=tres;
				strcpy(name21,namestr);
			}
			else if(score== high_score21 && duration21<tres)
			{
				high_score22=high_score21;
				duration22=tres;
				strcpy(name22,namestr);
			}
			else if(score== high_score21 && duration21>=tres)
			{
				high_score22 = high_score21;
				duration22 = duration21;
				strcpy(name22,name21);
				duration21=tres;
				strcpy(name21,namestr);
			}		
		}			
		else if(score>=high_score22 && score<high_score21)
		{
			high_score25=high_score24;
			duration25=duration24;
			strcpy(name25,name24);
			high_score24=high_score23;
			duration24=duration23;
			strcpy(name24,name23);
			if(score>high_score22)
			{
				high_score23=high_score22;
				duration23=duration22;
				strcpy(name23,name22);
				high_score22=score;
				duration22=tres;
				strcpy(name22,namestr);
			}
			else if(score== high_score22 && duration22<tres)
			{
				high_score23=high_score22;
				duration23=tres;
				strcpy(name23,namestr);
			}
			else if(score== high_score22 && duration22>=tres)
			{
				high_score23 = high_score22;
				duration23 = duration22;
				strcpy(name23,name22);
				duration22=tres;
				strcpy(name22,namestr);
			}
		}
		else if(score>=high_score23 && score<high_score22)
		{
			high_score25=high_score24;
			duration25=duration24;
			strcpy(name25,name24);
			if(score>high_score23)
			{
				high_score24=high_score23;
				duration24=duration23;
				strcpy(name24,name23);
				high_score23=score;
				duration23=tres;
				strcpy(name23,namestr);
			}
			else if(score== high_score23 && duration23<tres)
			{
				high_score24=high_score23;
				duration24=tres;
				strcpy(name24,namestr);
			}
			else if(score== high_score23 && duration23>=tres)
			{
				high_score24 = high_score23;
				duration24 = duration23;
				strcpy(name24,name23);
				duration23=tres;
				strcpy(name23,namestr);
			}
		}
		else if(score>=high_score24 && score<high_score23)
		{
			if(score>high_score24)
			{
				high_score25=high_score24;
				duration25=duration24;
				strcpy(name25,name24);
				high_score24=score;
				duration24=tres;
				strcpy(name24,namestr);
			}
			else if(score== high_score24 && duration24<tres)
			{
				high_score25=high_score24;
				duration25=tres;
				strcpy(name25,namestr);
			}
			else if(score== high_score24 && duration24>=tres)
			{
				high_score25 = high_score24;
				duration25 = duration24;
				strcpy(name25,name24);
				duration24=tres;
				strcpy(name24,namestr);
			}
		}
		else if(score>=high_score25 && score<high_score24)
		{
			if(score>high_score25)
			{
				high_score25=score;
				duration25=tres;
				strcpy(name25,namestr);
			}
			else if(score==high_score25 && tres<duration25)
			{
				duration25=tres;
				strcpy(name25,namestr);
			}
		}
	
		hc2=fopen("hc2.txt","w");
		fprintf(hc2,"%d  ",high_score21);
		fprintf(hc2,"%d  ",high_score22);
		fprintf(hc2,"%d  ",high_score23);
		fprintf(hc2,"%d  ",high_score24);
		fprintf(hc2,"%d  ",high_score25);
		fprintf(hc2,"%d  ",duration21);
		fprintf(hc2,"%d  ",duration22);
		fprintf(hc2,"%d  ",duration23);
		fprintf(hc2,"%d  ",duration24);
		fprintf(hc2,"%d  ",duration25);
		fprintf(hc2,"%s  ",name21);
		fprintf(hc2,"%s  ",name22);
		fprintf(hc2,"%s  ",name23);
		fprintf(hc2,"%s  ",name24);
		fprintf(hc2,"%s",name25);
		fclose(hc2);
		hc2=fopen("hc2.txt","r");
		fscanf(hc2,"%s",highScore21);
		fscanf(hc2,"%s",highScore22);
		fscanf(hc2,"%s",highScore23);
		fscanf(hc2,"%s",highScore24);
		fscanf(hc2,"%s",highScore25);
		fscanf(hc2,"%s",dur21);
		fscanf(hc2,"%s",dur22);
		fscanf(hc2,"%s",dur23);
		fscanf(hc2,"%s",dur24);
		fscanf(hc2,"%s",dur25);
		fscanf(hc2,"%s",name21);
		fscanf(hc2,"%s",name22);
		fscanf(hc2,"%s",name23);
		fscanf(hc2,"%s",name24);
		fscanf(hc2,"%s",name25);
		fclose(hc2);
		flag3=5;
	}
}

void iDraw()
{
	iClear();
	if(flag==2)//help page display
	{
		iSetColor(255,255,255);
		iFilledRectangle(512,0,900-512,512);
		iShowBMP(0,0,"pics\\help main.bmp");
		iSetColor(255,255,255);
		iShowBMP(700,200,"pics\\main menu.bmp");
	}
	if(flag==1 || flag2==-1)//display page of the game and loading
	{
		iSetColor(255, 255, 255);
		iFilledRectangle(0,0,900,512);
		if(ball==0)
		{
			srand(time(NULL));
			ball_x1=rand()%700 + 30;
			ball_y1=rand()%400 +30;
			ball_x2=rand()%700 + 30;
			ball_y2=rand()%400 +30;
			ball=1;
		}
		iSetColor(255,128,0);
		iFilledCircle(ball_x1,ball_y1,20);
		iSetColor(0,255,0);
		iFilledCircle(ball_x2,ball_y2,20);
		ball_x1 += dx1;
		ball_y1 += dy1;
		ball_x2 += dx2;
		ball_y2 += dy2;

		if(ball_x1 + 20 >= 900 || ball_x1 - 20 <= 0)
			dx1 = -dx1;
		if(ball_y1 +20 >= 512 || ball_y1 -20 <= 0)
			dy1 = -dy1;
		if(ball_x2 + 20 >= 900 || ball_x2 - 20 <= 0)
			dx2 = -dx2;
		if(ball_y2 +20 >= 512 || ball_y2 -20 <= 0)
			dy2 = -dy2;
		if(ball_x1==ball_x2 && ball_y1==ball_y2)
		{
			dx1=-dx1;
			dy1=-dy1;
			dx2=-dx2;
			dy2=-dy2;
		}

		iShowBMP(200,450,"pics\\easy mode.bmp");
		
		iShowBMP(200,350,"pics\\hard mode.bmp");
		
		iShowBMP(250,250,"pics\\load game easy.bmp");
		iShowBMP(450,250,"pics\\load game hard.bmp");
		
		iShowBMP(200,150,"pics\\help.bmp");

		iSetColor(0,0,160);
		iFilledRectangle(200,100,increase,20);
	}
	if(nameFlag==1 && flag2==2)//page for inputing name
	{
		iSetColor(255,255,255);
		iFilledRectangle(0,0,900,512);
		iSetColor(255,128,0);
		
		iSetColor(0,0,0);
		iFilledRectangle(200,200,512,128);
		iShowBMP(400,400,"pics\\input name.bmp");
		iShowBMP(400,100,"pics\\resume game.bmp");

		if(nameCount>=0)//letters display after each input
		{
			for(i=0;i<=nameCount;i++)
			{
				if (indexl[i] == 0)
					iShowBMP(250+32*i,256,"pics\\A1.bmp");
				if(indexl[i]==1)
					iShowBMP(250+32*i, 256, "pics\\B1.bmp");
				if(indexl[i]==2)
					iShowBMP(250 + 32 * i, 256, "pics\\C1.bmp");
				if(indexl[i]==3)
					iShowBMP(250 + 32 * i, 256, "pics\\D1.bmp");
				if(indexl[i]==4)
					iShowBMP(250 + 32 * i, 256, "pics\\E1.bmp");
				if(indexl[i]==5)
					iShowBMP(250 + 32 * i, 256, "pics\\F1.bmp");
				if(indexl[i]==6)
					iShowBMP(250 + 32 * i, 256, "pics\\G1.bmp");
				if(indexl[i]==7)
					iShowBMP(250 + 32 * i, 256, "pics\\H.bmp");
				if(indexl[i]==8)
					iShowBMP(250 + 32 * i, 256, "pics\\I.bmp");
				if(indexl[i]==9)
					iShowBMP(250 + 32 * i, 256, "pics\\J.bmp");
				if(indexl[i]==10)
					iShowBMP(250 + 32 * i, 256, "pics\\K.bmp");
				if(indexl[i]==11)
					iShowBMP(250 + 32 * i, 256, "pics\\L.bmp");
				if(indexl[i]==12)
					iShowBMP(250 + 32 * i, 256, "pics\\M.bmp");
				if(indexl[i]==13)
					iShowBMP(250 + 32 * i, 256, "pics\\N.bmp");
				if(indexl[i]==14)
					iShowBMP(250 + 32 * i, 256, "pics\\O.bmp");
				if(indexl[i]==15)
					iShowBMP(250 + 32 * i, 256, "pics\\P.bmp");
				if(indexl[i]==16)
					iShowBMP(250 + 32 * i, 256, "pics\\Q.bmp");
				if(indexl[i]==17)
					iShowBMP(250 + 32 * i, 256, "pics\\R.bmp");
				if(indexl[i]==18)
					iShowBMP(250 + 32 * i, 256, "pics\\S.bmp");
				if(indexl[i]==19)
					iShowBMP(250 + 32 * i, 256, "pics\\T.bmp");
				if(indexl[i]==20)
					iShowBMP(250 + 32 * i, 256, "pics\\U.bmp");
				if(indexl[i]==21)
					iShowBMP(250 + 32 * i, 256, "pics\\V.bmp");
				if(indexl[i]==22)
					iShowBMP(250 + 32 * i, 256, "pics\\W.bmp");
				if(indexl[i]==23)
					iShowBMP(250 + 32 * i, 256, "pics\\X.bmp");
				if(indexl[i]==24)
					iShowBMP(250 + 32 * i, 256, "pics\\Y.bmp");
				if(indexl[i]==25)
					iShowBMP(250 + 32 * i, 256, "pics\\Z.bmp");
				if(indexl[i]==26)
					iText(250 + 32 * i, 256,"  ", GLUT_BITMAP_TIMES_ROMAN_24);
			}		
		}	
	}

	if(end==1)//while all the slots have been filled or end option clicked
	{
		if(flag2==-2)//game over display page
		{
			PlaySound("boxing_bell.wav",NULL,SND_ASYNC);
			iShowBMP(200,0,"pics\\game over.bmp");
		}
		if(flag2==3)//hall of fame page display
		{	
			highscorePrinting();
			if(flag==3)//easy mode
			{
				iSetColor(255,255,255);
				iFilledRectangle(0,0,900,512);
				iSetColor(0,0,0);
				iShowBMP(350,430,"pics\\hall of fame.bmp");
				iShowBMP(350,100,"pics\\main menu.bmp");
				iText(620,400,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,400,highScore11,GLUT_BITMAP_HELVETICA_18);
				iText(400,400,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,400,dur11,GLUT_BITMAP_HELVETICA_18);
				iText(100,400,name11,GLUT_BITMAP_HELVETICA_18);
				iText(10,400,"1.",GLUT_BITMAP_HELVETICA_18);

				iText(620,350,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,350,highScore12,GLUT_BITMAP_HELVETICA_18);
				iText(400,350,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,350,dur12,GLUT_BITMAP_HELVETICA_18);
				iText(100,350,name12,GLUT_BITMAP_HELVETICA_18);
				iText(10,350,"2.",GLUT_BITMAP_HELVETICA_18);

				iText(620,300,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,300,highScore13,GLUT_BITMAP_HELVETICA_18);
				iText(400,300,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,300,dur13,GLUT_BITMAP_HELVETICA_18);
				iText(100,300,name13,GLUT_BITMAP_HELVETICA_18);
				iText(10,300,"3.",GLUT_BITMAP_HELVETICA_18);

				iText(620,250,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,250,highScore14,GLUT_BITMAP_HELVETICA_18);
				iText(400,250,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,250,dur14,GLUT_BITMAP_HELVETICA_18);
				iText(100,250,name14,GLUT_BITMAP_HELVETICA_18);
				iText(10,250,"4.",GLUT_BITMAP_HELVETICA_18);

				iText(620,200,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,200,highScore15,GLUT_BITMAP_HELVETICA_18);
				iText(400,200,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,200,dur15,GLUT_BITMAP_HELVETICA_18);
				iText(100,200,name15,GLUT_BITMAP_HELVETICA_18);
				iText(10,200,"5.",GLUT_BITMAP_HELVETICA_18);
			}
			if(flag==0)//hard mode
			{
				iSetColor(255,255,255);
				iFilledRectangle(0,0,900,512);
				iSetColor(0,0,0);
				iShowBMP(350,430,"pics\\hall of fame.bmp");
				iShowBMP(350,100,"pics\\main menu.bmp");
				iText(620,400,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,400,highScore21,GLUT_BITMAP_HELVETICA_18);
				iText(400,400,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,400,dur21,GLUT_BITMAP_HELVETICA_18);
				iText(100,400,name21,GLUT_BITMAP_HELVETICA_18);
				iText(10,400,"1.",GLUT_BITMAP_HELVETICA_18);

				iText(620,350,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,350,highScore22,GLUT_BITMAP_HELVETICA_18);
				iText(400,350,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,350,dur22,GLUT_BITMAP_HELVETICA_18);
				iText(100,350,name22,GLUT_BITMAP_HELVETICA_18);
				iText(10,350,"2.",GLUT_BITMAP_HELVETICA_18);

				iText(620,300,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,300,highScore23,GLUT_BITMAP_HELVETICA_18);
				iText(400,300,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,300,dur23,GLUT_BITMAP_HELVETICA_18);
				iText(100,300,name23,GLUT_BITMAP_HELVETICA_18);
				iText(10,300,"3.",GLUT_BITMAP_HELVETICA_18);

				iText(620,250,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,250,highScore24,GLUT_BITMAP_HELVETICA_18);
				iText(400,250,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,250,dur24,GLUT_BITMAP_HELVETICA_18);
				iText(100,250,name24,GLUT_BITMAP_HELVETICA_18);
				iText(10,250,"4.",GLUT_BITMAP_HELVETICA_18);

				iText(620,200,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,200,highScore25,GLUT_BITMAP_HELVETICA_18);
				iText(400,200,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,200,dur25,GLUT_BITMAP_HELVETICA_18);
				iText(100,200,name25,GLUT_BITMAP_HELVETICA_18);
				iText(10,200,"5.",GLUT_BITMAP_HELVETICA_18);
			}
		}	
	}
	if(win==1)//game won
	{
		if(flag2==-2)//winning page display
		{
			PlaySound("applause3.wav",NULL,SND_ASYNC);
			iShowBMP(0,128,"pics\\sttext.bmp");
			iSetColor(0,0,0);
			iShowBMP(200,0,"pics\\game win.bmp");
		}
		if(flag2==3)//hall of fame
		{
			highscorePrinting();
			if(flag==3)//easy mode
			{	
				iSetColor(255,255,255);
				iText(300,100,"'M' FOR MAIN MENU",GLUT_BITMAP_HELVETICA_18);
				iText(620,400,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,400,highScore11,GLUT_BITMAP_HELVETICA_18);
				iText(400,400,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,400,dur11,GLUT_BITMAP_HELVETICA_18);
				iText(100,400,name11,GLUT_BITMAP_HELVETICA_18);
				iText(10,400,"1.",GLUT_BITMAP_HELVETICA_18);

				iText(620,350,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,350,highScore12,GLUT_BITMAP_HELVETICA_18);
				iText(400,350,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,350,dur12,GLUT_BITMAP_HELVETICA_18);
				iText(100,350,name12,GLUT_BITMAP_HELVETICA_18);
				iText(10,350,"2.",GLUT_BITMAP_HELVETICA_18);

				iText(620,300,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,300,highScore13,GLUT_BITMAP_HELVETICA_18);
				iText(400,300,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,300,dur13,GLUT_BITMAP_HELVETICA_18);
				iText(100,300,name13,GLUT_BITMAP_HELVETICA_18);
				iText(10,300,"3.",GLUT_BITMAP_HELVETICA_18);

				iText(620,250,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,250,highScore14,GLUT_BITMAP_HELVETICA_18);
				iText(400,250,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,250,dur14,GLUT_BITMAP_HELVETICA_18);
				iText(100,250,name14,GLUT_BITMAP_HELVETICA_18);
				iText(10,250,"4.",GLUT_BITMAP_HELVETICA_18);

				iText(620,200,"HIGH SCORE :",GLUT_BITMAP_HELVETICA_18);
				iText(775,200,highScore15,GLUT_BITMAP_HELVETICA_18);
				iText(400,200,"TIME :",GLUT_BITMAP_HELVETICA_18);
				iText(475,200,dur15,GLUT_BITMAP_HELVETICA_18);
				iText(100,200,name15,GLUT_BITMAP_HELVETICA_18);
				iText(10,200,"5.",GLUT_BITMAP_HELVETICA_18);
			}
			if(flag==0)//hard mode
			{
				iSetColor(255,255,255);
				iText(300,100,"'M' FOR MAIN MENU",GLUT_BITMAP_HELVETICA_18);
				iText(620,400,"HIGH SCORE1 :",GLUT_BITMAP_HELVETICA_18);
				iText(775,400,highScore21,GLUT_BITMAP_HELVETICA_18);
				iText(400,400,"TIME1 :",GLUT_BITMAP_HELVETICA_18);
				iText(475,400,dur21,GLUT_BITMAP_HELVETICA_18);

				iText(620,350,"HIGH SCORE2 :",GLUT_BITMAP_HELVETICA_18);
				iText(775,350,highScore22,GLUT_BITMAP_HELVETICA_18);
				iText(400,350,"TIME2 :",GLUT_BITMAP_HELVETICA_18);
				iText(475,350,dur22,GLUT_BITMAP_HELVETICA_18);

				iText(620,300,"HIGH SCORE3 :",GLUT_BITMAP_HELVETICA_18);
				iText(775,300,highScore23,GLUT_BITMAP_HELVETICA_18);
				iText(400,300,"TIME3 :",GLUT_BITMAP_HELVETICA_18);
				iText(475,300,dur23,GLUT_BITMAP_HELVETICA_18);

				iText(620,250,"HIGH SCORE4 :",GLUT_BITMAP_HELVETICA_18);
				iText(775,250,highScore24,GLUT_BITMAP_HELVETICA_18);
				iText(400,250,"TIME4 :",GLUT_BITMAP_HELVETICA_18);
				iText(475,250,dur24,GLUT_BITMAP_HELVETICA_18);

				iText(620,200,"HIGH SCORE5 :",GLUT_BITMAP_HELVETICA_18);
				iText(775,200,highScore25,GLUT_BITMAP_HELVETICA_18);
				iText(400,200,"TIME5 :",GLUT_BITMAP_HELVETICA_18);
				iText(475,200,dur25,GLUT_BITMAP_HELVETICA_18);
			}
		}
	}
	if((flag==0 || flag==3) && flag2==2 && nameFlag==2)//game starts display page of game
	{		
		if(move==0)//1st condition of display after just starting new game
		{	
			if(flag1==0)//so that b1,c1,b2,c2 are chosen only once
			{	
				srand(time(NULL));	
				num1=rand()%2;
				num1=num1*2+2;
				num2=rand()%2;
				num2=num2*2+2;	
				b1=rand();
				b1=b1%4;
				c1=rand();
				c1=c1%4;
				b2=rand();
				b2=b2%4;
				c2=rand();
				c2=c2%4;
				if(b1==b2 && c1==c2)
				{	if(b2<3)
						b2=b2+1;
					if(b2==3)
						b2=b2-1;
				}
				flag1=1;
			}
			a[b1][c1]=num1;//initially ploting 2 random 2 and 4 when move=0
			a[b2][c2]=num2;
			count=2;
		}
		if(tres>=tLimit)//time limit exceeded
		{
			end=1;
			flag2=-2;//game ended
		}
		if(end==0 && win==0)//while game is not over
		{
			iSetColor(157,255,255);
			iFilledRectangle(512,0,900-512,512);	
			iSetColor(0,0,0);
			scorePrinting();
			iText(620,480,"NAME :", GLUT_BITMAP_HELVETICA_18);
			iText(690,480,namestr, GLUT_BITMAP_HELVETICA_18);
			iText(620,400,"TIME : ", GLUT_BITMAP_HELVETICA_18);
			iText(700,400,timeString, GLUT_BITMAP_HELVETICA_18);

			iShowBMP(550,300,"pics\\restart.bmp");
			iShowBMP(700,300,"pics\\end game.bmp");
			iShowBMP(550,200,"pics\\save game.bmp");
			iShowBMP(700,200,"pics\\main menu.bmp");
			iShowBMP(550,100,"pics\\pause game.bmp");
			iShowBMP(700,100,"pics\\resume game.bmp");

			for(i=0;i<=3;i++)
			{
				for(j=0;j<=3;j++)
				{
					if(a[i][j]==0)
					{
						iShowBMP(128*j,128*i,"pics\\1.bmp");
						iSetColor(0,0,0);
						iRectangle(128*j,128*i,128,128);
					}
					if(a[i][j]==2)
					{
						if (i == d1 && j == e1 && animationFlag == 1)
						{
							if (animate >=1 && animate<3)
							{
								iShowBMP(128 * j, 128 * i, "pics\\a.bmp");
							}
							else if (animate >=3 && animate<6)
							{
								iShowBMP(128 * j, 128 * i, "pics\\b.bmp");
							}
							else if (animate >=6 && animate<9)
							{
								iShowBMP(128 * j, 128 * i, "pics\\c.bmp");
							}
							else if (animate >=9 && animate<12)
							{
								iShowBMP(128 * j, 128 * i, "pics\\d.bmp");
							}
							else if (animate >=12 && animate<15)
							{
								iShowBMP(128 * j, 128 * i, "pics\\e.bmp");
							}
							else if (animate >= 15 && animate<18)
							{
								iShowBMP(128 * j, 128 * i, "pics\\f.bmp");
							}
							else if (animate >= 21 && animate<=25)
							{
								iShowBMP(128 * j, 128 * i, "pics\\g.bmp");
							}
							else
							{
								iShowBMP(128 * j, 128 * i, "pics\\2.bmp");
							}
							animate++;
						}
						else
						{
							iShowBMP(128 * j, 128 * i, "pics\\2.bmp");
						}
						
					}
					if(a[i][j]==4)
					{
						if (i == d1 && j == e1 && animationFlag == 1)
						{
							if (animate >= 1 && animate<3)
							{
								iShowBMP(128 * j, 128 * i, "pics\\a.bmp");
							}
							else if (animate >= 3 && animate<6)
							{
								iShowBMP(128 * j, 128 * i, "pics\\b.bmp");
							}
							else if (animate >= 6 && animate<9)
							{
								iShowBMP(128 * j, 128 * i, "pics\\c.bmp");
							}
							else if (animate >= 9 && animate<12)
							{
								iShowBMP(128 * j, 128 * i, "pics\\d.bmp");
							}
							else if (animate >= 12 && animate<15)
							{
								iShowBMP(128 * j, 128 * i, "pics\\e.bmp");
							}
							else if (animate >= 15 && animate<18)
							{
								iShowBMP(128 * j, 128 * i, "pics\\f.bmp");
							}
							else if (animate >= 21 && animate <= 25)
							{
								iShowBMP(128 * j, 128 * i, "pics\\g.bmp");
							}
							else
							{
								iShowBMP(128 * j, 128 * i, "pics\\4.bmp");
							}
							animate++;
							
						}
						else
						{
							iShowBMP(128 * j, 128 * i, "pics\\4.bmp");
						}
						
					}
					if(a[i][j]==8)
					{
						iShowBMP(128*j,128*i,"pics\\8.bmp");
					}
					if(a[i][j]==16)
					{
						iShowBMP(128*j,128*i,"pics\\16.bmp");
					}
					if(a[i][j]==32)
					{
						iShowBMP(128*j,128*i,"pics\\32.bmp");
					}
					if(a[i][j]==64)
					{
						iShowBMP(128*j,128*i,"pics\\64.bmp");
					}
					if(a[i][j]==128)
					{
						iShowBMP(128*j,128*i,"pics\\128.bmp");
					}
					if(a[i][j]==256)
					{
						iShowBMP(128*j,128*i,"pics\\256.bmp");
					}
					if(a[i][j]==512)
					{
						iShowBMP(128*j,128*i,"pics\\512.bmp");
					}
					if(a[i][j]==1024)
					{
						iShowBMP(128*j,128*i,"pics\\1024.bmp");
					}
					if(a[i][j]==2048)
					{
						iShowBMP(128*j,128*i,"pics\\2048.bmp");
					}
				}
			}
			if(pause==2)//game paused
				iShowBMP(200,100,"pics\\pause.bmp");	
		}
		
	}
}

void iMouseMove(int mx, int my)
{

}	

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(end==1 && flag2==3 && (flag==3 || flag==0))//return to main menu from hall of fame
		{
			if((mx>=300 && mx<=300+128) && (my>=100 && my<=164))
			{
				PlaySound("coin_flip.wav",NULL,SND_ASYNC);
				flag=1;
				flag2=0,increase=0;
				for(i=0;i<=3;i++)
					for(j=0;j<=3;j++)
						a[i][j]=0;
				num1=0,num2=0;
				b1=0,c1=0;
				b2=0,c2=0;
				move=0;
				flag1=0;
				end=0;
				d1=0,e1=0;
				count=0;
				win=0;
				endpoint=0;
				score=0;
				high_score11=0,high_score12=0,high_score13=0,high_score14=0,high_score15=0;
				high_score21=0,high_score22=0,high_score23=0,high_score24=0,high_score25=0;
				duration11=0,duration12=0,duration13=0,duration14=0,duration15=0;
				duration21=0,duration22=0,duration23=0,duration24=0,duration25=0;
				animationFlag = 0,animate=0;
				xx=0;
				tres=0;
				tLimit=2000;
				increase1=0;
				flag3=0;
				pause=0;
				nameFlag=0,nameCount=-1;
				for(i=0;i<=10;i++)
					indexl[i]=-1;
				ball_x1=0,ball_x2=0;
				ball_y1=0,ball_y2=0;
				ball=0;
				dx1=1,dy1=2;
				dx2=2,dy2=1;
			}
		}
		if(flag==2 || flag==3 || flag==0)//returning to main menu from help,wasy or hard mode game
		{
			if((mx>=700 && mx<=700+128) && (my>=200 && my<=264))
			{
				PlaySound("coin_flip.wav",NULL,SND_ASYNC);
				flag=1;
				flag2=0,increase=0;
				for(i=0;i<=3;i++)
					for(j=0;j<=3;j++)
						a[i][j]=0;
				num1=0,num2=0;
				b1=0,c1=0;
				b2=0,c2=0;
				move=0;
				flag1=0;
				end=0;
				d1=0,e1=0;
				count=0;
				win=0;
				endpoint=0;
				score=0;
				high_score11=0,high_score12=0,high_score13=0,high_score14=0,high_score15=0;
				high_score21=0,high_score22=0,high_score23=0,high_score24=0,high_score25=0;
				duration11=0,duration12=0,duration13=0,duration14=0,duration15=0;
				duration21=0,duration22=0,duration23=0,duration24=0,duration25=0;
				animationFlag = 0,animate=0;
				xx=0;
				tres=0;
				tLimit=2000;
				increase1=0;
				flag3=0;
				pause=0;
				nameFlag=0,nameCount=-1;
				for(i=0;i<=7;i++)
					indexl[i]=-1;
				ball_x1=0,ball_x2=0;
				ball_y1=0,ball_y2=0;
				ball=0;
				dx1=1,dy1=2;
				dx2=2,dy2=1;
			} 
		}
		if(flag==0 && flag2==2 && nameFlag==2)//saving hard mode
		{
			if((mx>=550 && mx<=550+128) && (my>=200 && my<=264))
			{
				PlaySound(".wav",NULL,SND_ASYNC);
				p1=fopen("save.txt","w");
				for(i=0;i<=3;i++)
				{
					for(j=0;j<=3;j++)
					{
						fprintf(p1, "%d ", a[i][j]);
					}
				}
				fprintf(p1,"%d ",flag);
				fprintf(p1,"%d ",move);
				fprintf(p1,"%d ",flag1);
				fprintf(p1,"%d ",count);
				fprintf(p1,"%d ",end);
				fprintf(p1,"%d ",win);
				fprintf(p1,"%d ",endpoint);
				fprintf(p1,"%d ",score);
				fprintf(p1,"%d ",tres);
				fprintf(p1,"%d ",flag2);
				fprintf(p1,"%d ",nameFlag);
				fprintf(p1,"%s",namestr);
				fclose(p1);
			}
		}
		if(flag==3 && flag2==2 && nameFlag==2)//saving easy mode
		{
			if((mx>=550 && mx<=550+128) && (my>=200 && my<=264))
			{
				PlaySound(".wav",NULL,SND_ASYNC);
				p2=fopen("save1.txt","w");
				for(i=0;i<=3;i++)
				{
					for(j=0;j<=3;j++)
					{
						fprintf(p2, "%d ", a[i][j]);
					}
				}
				fprintf(p2,"%d ",flag);
				fprintf(p2,"%d ",move);
				fprintf(p2,"%d ",flag1);
				fprintf(p2,"%d ",count);
				fprintf(p2,"%d ",end);
				fprintf(p2,"%d ",win);
				fprintf(p2,"%d ",endpoint);
				fprintf(p2,"%d ",score);
				fprintf(p2,"%d ",tres);
				fprintf(p2,"%d ",flag2);
				fprintf(p2,"%d ",nameFlag);
				fprintf(p2,"%s",namestr);
				fclose(p2);
			}
		}
		if(((flag==0) || (flag==3)) && flag2==2 && nameFlag==2)//restarting game from beginning
		{
			if((mx>=550 && mx<=550+128) && (my>=300 && my<=364))
			{
				PlaySound("bubbles_sfx.wav",NULL,SND_ASYNC);
				win=0;
				move=0;//restarts the game while playing
				end=0;//restarts the game even if game is over
				flag1=0;
				score=0;
				tres=0;
				for(i=0;i<=3;i++)
				{
					for(j=0;j<=3;j++)
						a[i][j]=0;
				}
			}
		}
		if(((flag==0) || (flag==3)) && flag2==2 && nameFlag==2)//ending game while playing
		{
			if((mx>=700 && mx<=700+128) && (my>=300 && my<=364))
			{
				end=1;
				flag2=-2;
			}
		}
		if(((flag==0) || (flag==3)) && flag2==2 && nameFlag==2)//resuming game from pause
		{
			if((mx>=700 && mx<=700+128) && (my>=100 && my<=164))
			{
				PlaySound("boxing_bell.wav",NULL,SND_ASYNC);
				iResumeTimer(0);
				pause=0;
			}
		}
		if(((flag==0) || (flag==3)) && flag2==2 && nameFlag==2)//pausing game 
		{
			if((mx>=550 && mx<=550+128) && (my>=100 && my<=164))
			{
				PlaySound("boxing_bell.wav",NULL,SND_ASYNC);
				iPauseTimer(0);
				pause=2;//pauses the game completely. No cheats allowed
			}
		}
		if((mx>=200 && mx<=712) && (my>=450 && my<=514) && flag==1)//easy mode starting main menu
		{
			nameFlag=1;//name input to be taken
			flag=3;
			flag2=-1;
			PlaySound("click_x.wav",NULL,SND_ASYNC);
		}
		if((mx>=200 && mx<=712) && (my>=350 && my<=414) && flag==1)//hard mode starting main menu
		{
			nameFlag=1;
			flag=0;
			flag2=-1;
			PlaySound("click_x.wav",NULL,SND_ASYNC);
		}
		if((mx>=250 && mx<=250+128) && (my>=250 && my<=250+64) && flag==1)//load game easy at the main menu
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			p2=fopen("save1.txt","r");
			for(i=0;i<=3;i++)
			{
				for(j=0;j<=3;j++)
				{
					fscanf(p2, "%d ",&a[i][j]);
				}
			}
			fscanf(p2,"%d",&flag);
			fscanf(p2,"%d",&move);
			fscanf(p2,"%d",&flag1);
			fscanf(p2,"%d",&count);
			fscanf(p2,"%d",&end);
			fscanf(p2,"%d",&win);
			fscanf(p2,"%d",&endpoint);
			fscanf(p2,"%d",&score);
			fscanf(p2,"%d",&tres);
			fscanf(p2,"%d",&flag2);
			fscanf(p2,"%d",&nameFlag);
			fscanf(p2,"%s",namestr);
			fclose(p2);
		}
		if((mx>=450 && mx<=450+128) && (my>=250 && my<=250+64) && flag==1)//load game hard at the main menu
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			p1=fopen("save.txt","r");
			for(i=0;i<=3;i++)
			{
				for(j=0;j<=3;j++)
				{
					fscanf(p1, "%d ",&a[i][j]);
				}
			}
			fscanf(p1,"%d",&flag);
			fscanf(p1,"%d",&move);
			fscanf(p1,"%d",&flag1);
			fscanf(p1,"%d",&count);
			fscanf(p1,"%d",&end);
			fscanf(p1,"%d",&win);
			fscanf(p1,"%d",&endpoint);
			fscanf(p1,"%d",&score);
			fscanf(p1,"%d",&tres);
			fscanf(p1,"%d",&flag2);
			fscanf(p1,"%d",&nameFlag);
			fscanf(p1,"%s",namestr);
			fclose(p1);
		}
		if((mx>=200 && mx<=712) && (my>=150 && my<=214) && flag==1)//going to help page
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			flag=2;
		}
		if(nameFlag==1 && flag2==2 && nameCount!=-1)//finishing name input before 10 chars
		{
			if((mx>=400 && mx<=528) && (my>=100 && my<=164 )) 
			{
				PlaySound("click_x.wav",NULL,SND_ASYNC);
				nameFlag=2;
			}
		}
	}
}

void iPassiveMouseMove(int mx,int my)
{
	

}

void iKeyboard(unsigned char key)
{
	if(nameFlag==1 && flag2==2)
	{
		if(key==8 && nameCount!=-1)
		{
			namestr[nameCount]='\0';
			nameCount--;
		}
		for(i=0;i<=26;i++)
		{
			if(key==letter[i])
			{
				PlaySound("click_x.wav",NULL,SND_ASYNC);
				nameCount++;
				indexl[nameCount]=i;
				if(letter[i]==' ')
				{
					namestr[nameCount]='_';
					namestr[nameCount+1]='\0';
				}
				else
				{
					namestr[nameCount]=letter[i]-32;
					namestr[nameCount+1]='\0';
				}
				if(nameCount==10)
				{
					nameFlag=2;
				}
			}
		}
	}		
}

void iSpecialKeyboard(unsigned char key)
{	
	if (nameFlag==2 && flag == 0 && move >= 0 && flag2==2 && pause==0 )//indicating start of the game
	{
		if (key == GLUT_KEY_LEFT && win == 0)//in case move is given to the left
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			for (i = 0; i <= 3; i++)
			{
				for (j = 0; j <= 2; j++)
				{
					if (a[i][j]>0 && a[i][j] == a[i][j + 1])//in case 2 numbers side by side are equal
					{
						a[i][j + 1] = 0;//this whole process has to be done 1st under this loop
						a[i][j] = a[i][j] * 2;
						score = score + a[i][j];
						move = move + 1;
						PlaySound("bicycle_bell.wav",NULL,SND_ASYNC);
						if (a[i][j] == 2048)
						{
							win = 1;
							flag2=-2;
							score=score*2;
						}
						count = count - 1;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (j = 3; j >= 1; j--)
				{
					if (a[i][j]>0 && a[i][j - 1] == 0)//in case next to a number is a blank slot
					{
						a[i][j - 1] = a[i][j];
						a[i][j] = 0;
						move = move + 1;
					}
					if (a[i][j]>0 && a[i][j - 1]>0 && a[i][j] != a[i][j - 1])//in case the 2 numbers are not equal
					{
						;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (j = 0; j <= 3; j++)
				{
					for (k = 3; k >= 1; k--)
					{
						if (a[j][k]>0 && a[j][k - 1] == 0)
						{
							a[j][k - 1] = a[j][k];
							a[j][k] = 0;
						}
					}
				}
			}
		}
		if (key == GLUT_KEY_RIGHT && win == 0)
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			for (i = 0; i <= 3; i++)
			{
				for (j = 3; j >= 1; j--)
				{
					if (a[i][j]>0 && a[i][j] == a[i][j - 1])//in case 2 numbers side by side are equal
					{
						a[i][j - 1] = 0;
						a[i][j] = a[i][j] * 2;
						score = score + a[i][j];
						move = move + 1;
						PlaySound("bicycle_bell.wav",NULL,SND_ASYNC);
						if (a[i][j] == 2048)
						{
							win = 1;
							flag2=-2;
							score=score*2;
						}
						count = count - 1;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (j = 0; j <= 2; j++)
				{
					if (a[i][j]>0 && a[i][j + 1] == 0)//in case next to a number is a blank slot
					{
						a[i][j + 1] = a[i][j];
						a[i][j] = 0;
						move = move + 1;
					}
					if (a[i][j]>0 && a[i][j + 1]>0 && a[i][j] != a[i][j + 1])//in case the 2 numbers are not equal
					{
						;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (j = 0; j <= 3; j++)
				{
					for (k = 0; k <= 2; k++)
					{
						if (a[j][k]>0 && a[j][k + 1] == 0)
						{
							a[j][k + 1] = a[j][k];
							a[j][k] = 0;
						}
					}
				}
			}
		}
		if (key == GLUT_KEY_DOWN && win == 0)
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			for (j = 0; j <= 3; j++)
			{
				for (i = 0; i <= 2; i++)
				{
					if (a[i][j]>0 && a[i][j] == a[i + 1][j])//in case 2 numbers side by side are equal
					{
						a[i + 1][j] = 0;
						a[i][j] = a[i][j] * 2;
						score = score + a[i][j];
						move = move + 1;
						PlaySound("bicycle_bell.wav",NULL,SND_ASYNC);
						if (a[i][j] == 2048)
						{
							win = 1;
							flag2=-2;
							score=score*2;
						}
						count = count - 1;
					}
				}
			}
			for (j = 0; j <= 3; j++)
			{
				for (i = 3; i >= 1; i--)
				{
					if (a[i][j]>0 && a[i - 1][j] == 0)//in case next to a number is a blank slot
					{
						a[i - 1][j] = a[i][j];
						a[i][j] = 0;
						move = move + 1;
					}
					if (a[i][j]>0 && a[i - 1][j]>0 && a[i][j] != a[i - 1][j])//in case the 2 numbers are not equal
					{
						;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (k = 0; k <= 3; k++)
				{
					for (j = 3; j >= 1; j--)
					{
						if (a[j][k]>0 && a[j - 1][k] == 0)
						{
							a[j - 1][k] = a[j][k];
							a[j][k] = 0;
						}
					}
				}
			}
		}
		if (key == GLUT_KEY_UP && win == 0)
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			for (j = 0; j <= 3; j++)
			{
				for (i = 3; i >= 1; i--)
				{
					if (a[i][j]>0 && a[i][j] == a[i - 1][j])//in case 2 numbers side by side are equal
					{
						a[i - 1][j] = 0;
						a[i][j] = a[i][j] * 2;
						score = score + a[i][j];
						score = score + a[i][j];
						move = move + 1;
						PlaySound("bicycle_bell.wav",NULL,SND_ASYNC);
						if (a[i][j] == 2048)
						{
							win = 1;
							flag2=-2;
							score=score*2;
						}
						count = count - 1;
					}
				}
			}
			for (j = 0; j <= 3; j++)
			{
				for (i = 0; i <= 2; i++)
				{
					if (a[i][j]>0 && a[i + 1][j] == 0)//in case next to a number is a blank slot
					{
						a[i + 1][j] = a[i][j];
						a[i][j] = 0;
						move = move + 1;
					}
					if (a[i][j]>0 && a[i + 1][j]>0 && a[i][j] != a[i + 1][j])//in case the 2 numbers are not equal
					{
						;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (k = 0; k <= 3; k++)
				{
					for (j = 0; j <= 2; j++)
					{
						if (a[j][k]>0 && a[j + 1][k] == 0)
						{
							a[j + 1][k] = a[j][k];
							a[j][k] = 0;
						}
					}
				}
			}
		}//all the possible moves have been given
	}


	if (flag == 3 && move >= 0 && flag2==2 && pause==0 && nameFlag==2)//indicating start of the game
	{
		if (key == GLUT_KEY_LEFT && win == 0)//in case move is given to the left
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			for (i = 0; i <= 3; i++)
			{
				for (j = 3; j >= 1; j--)
				{
					if (a[i][j]>0 && a[i][j] == a[i][j - 1])//in case 2 numbers side by side are equal
					{
						a[i][j] = 0;//this whole process has to be done 1st under this loop
						a[i][j - 1] = a[i][j - 1] * 2;
						score = score + a[i][j - 1];
						move = move + 1;
						PlaySound("bicycle_bell.wav",NULL,SND_ASYNC);
						if (a[i][j - 1] == 2048)
						{
							win = 1;
							flag2=-2;
							score=score*2;
						}
						count = count - 1;
					}
					if (a[i][j]>0 && a[i][j - 1] == 0)//in case next to a number is a blank slot
					{
						a[i][j - 1] = a[i][j];
						a[i][j] = 0;
						move = move + 1;
					}
					if (a[i][j]>0 && a[i][j - 1]>0 && a[i][j] != a[i][j - 1])//in case the 2 numbers are not equal
					{
						;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (j = 0; j <= 3; j++)
				{
					for (k = 3; k >= 1; k--)
					{
						if (a[j][k]>0 && a[j][k - 1] == 0)
						{
							a[j][k - 1] = a[j][k];
							a[j][k] = 0;
						}
					}
				}
			}
		}
		if (key == GLUT_KEY_RIGHT && win == 0)
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			for (i = 0; i <= 3; i++)
			{
				for (j = 0; j <= 2; j++)
				{
					if (a[i][j]>0 && a[i][j] == a[i][j + 1])//in case 2 numbers side by side are equal
					{
						a[i][j] = 0;
						a[i][j + 1] = a[i][j + 1] * 2;
						score = score + a[i][j + 1];
						move = move + 1;
						PlaySound("bicycle_bell.wav",NULL,SND_ASYNC);
						if (a[i][j + 1] == 2048)
						{
							win = 1;
							flag2=-2;
							score=score*2;
						}
						count = count - 1;
					}
					if (a[i][j]>0 && a[i][j + 1] == 0)//in case next to a number is a blank slot
					{
						a[i][j + 1] = a[i][j];
						a[i][j] = 0;
						move = move + 1;
					}
					if (a[i][j]>0 && a[i][j + 1]>0 && a[i][j] != a[i][j + 1])//in case the 2 numbers are not equal
					{
						;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (j = 0; j <= 3; j++)
				{
					for (k = 0; k <= 2; k++)
					{
						if (a[j][k]>0 && a[j][k + 1] == 0)
						{
							a[j][k + 1] = a[j][k];
							a[j][k] = 0;
						}
					}
				}
			}
		}
		if (key == GLUT_KEY_DOWN && win == 0)
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			for (j = 0; j <= 3; j++)
			{
				for (i = 3; i >= 1; i--)
				{
					if (a[i][j]>0 && a[i][j] == a[i - 1][j])//in case 2 numbers side by side are equal
					{
						a[i][j] = 0;
						a[i - 1][j] = a[i - 1][j] * 2;
						score = score + a[i - 1][j];
						move = move + 1;
						PlaySound("bicycle_bell.wav",NULL,SND_ASYNC);
						if (a[i - 1][j] == 2048)
						{
							win = 1;
							flag2=-2;
							score=score*2;
						}
						count = count - 1;
					}
					if (a[i][j]>0 && a[i - 1][j] == 0)//in case next to a number is a blank slot
					{
						a[i - 1][j] = a[i][j];
						a[i][j] = 0;
						move = move + 1;
					}
					if (a[i][j]>0 && a[i - 1][j]>0 && a[i][j] != a[i - 1][j])//in case the 2 numbers are not equal
					{
						;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (k = 0; k <= 3; k++)
				{
					for (j = 3; j >= 1; j--)
					{
						if (a[j][k]>0 && a[j - 1][k] == 0)
						{
							a[j - 1][k] = a[j][k];
							a[j][k] = 0;
						}
					}
				}
			}
		}
		if (key == GLUT_KEY_UP && win == 0)
		{
			PlaySound("click_x.wav",NULL,SND_ASYNC);
			for (j = 0; j <= 3; j++)
			{
				for (i = 0; i <= 2; i++)
				{
					if (a[i][j]>0 && a[i][j] == a[i + 1][j])//in case 2 numbers side by side are equal
					{
						a[i][j] = 0;
						a[i + 1][j] = a[i + 1][j] * 2;
						score = score + a[i + 1][j];
						move = move + 1;
						PlaySound("bicycle_bell.wav",NULL,SND_ASYNC);
						if (a[i + 1][j] == 2048)
						{
							win = 1;
							flag2=-2;
							score=score*2;
						}
						count = count - 1;
					}
					if (a[i][j]>0 && a[i + 1][j] == 0)//in case next to a number is a blank slot
					{
						a[i + 1][j] = a[i][j];
						a[i][j] = 0;
						move = move + 1;
					}
					if (a[i][j]>0 && a[i + 1][j]>0 && a[i][j] != a[i + 1][j])//in case the 2 numbers are not equal
					{
						;
					}
				}
			}
			for (i = 0; i <= 3; i++)
			{
				for (k = 0; k <= 3; k++)
				{
					for (j = 0; j <= 2; j++)
					{
						if (a[j][k]>0 && a[j + 1][k] == 0)
						{
							a[j + 1][k] = a[j][k];
							a[j][k] = 0;
						}
					}
				}
			}

		}//all the possible moves have been given
	}
	if (count != 16 && pause==0 && nameFlag==2)
	{

		do
		{
			d1 = rand();
			d1 = d1 % 4;
			e1 = rand();
			e1 = e1 % 4;
		} while (a[d1][e1] != 0);
		animationFlag = 1;
		animate = 1;
		xx = rand() % 9 + 1;//probability 6:3
		if (flag == 0)
		{
			if (xx >= 1 && xx <= 6)
				a[d1][e1] = 2;
			else
				a[d1][e1] = 4;
		}
		if (flag == 3)
		{
			if (xx >= 1 && xx <= 6)
				a[d1][e1] = 4;
			else
				a[d1][e1] = 2;
		}
		count = count + 1;
	}
	
	if (count == 16)
	{
		for (i = 0; i <= 3; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				if (a[i][j] == a[i][j + 1])
				{
					endpoint = 1;
					break;
				}
			}
			if (endpoint == 1)
				break;
		}
		if (endpoint == 0)
		{
			for (j = 0; j <= 3; j++)
			{
				for (i = 0; i <= 2; i++)
				{
					if (a[i][j] == a[i + 1][j])
					{
						endpoint = 1;
						break;
					}
				}
				if (endpoint == 1)
					break;
			}
		}
		if (endpoint == 0)
		{
			end = 1;
			flag2=-2;
		}
	}
	endpoint = 0;
}
int main()
{	
	iSetTimer(1000,time);//time counting in seconds
	iSetTimer(0,TIME);//game loading and rectangle going forward
	iSetTimer(100,TIME1);//displaying winning or losing screen for sometime
	iInitialize(900, 512, "Final");
	return 0;
}
