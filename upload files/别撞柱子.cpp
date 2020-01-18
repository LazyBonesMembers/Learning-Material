#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<conio.h>

#define N 4 //控制玩家的x坐标 

using namespace std;

char a[40][20]; 
double timestart;//开始时间 
int d;//难度选择
int nowy=10;//当前玩家y坐标 
int number = 0;

struct s {
	int difficulty;
	int point;
}player[50];

void build()
{
	srand((unsigned)time(NULL));
	bool dire = rand() % 2;
	int l = rand() % 8 + 5;//长度 

	if (dire)
	{
		for (int i = 0; i < l; i++)
		{
			a[39][i] = '|';//生成上柱子
		}
	}
	else
	{
		for (int i = 19; 19 - i < l; i--)
		{
			a[39][i] = '|';//生成下柱子 
		}
	}
}

void move()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if(a[0][j]=='|')//到头了 
			{
				a[0][j]=' ';
			}
			else if (a[j][i]=='|')
			{
				a[j][i] = ' ';//清除原来的
				a[j-1][i] = '|';//向前推一个
			}
		}
	}
}

void flush()
{
	system("cls");
	cout<<"############################################"<<endl;//上边界框 
	for (int i = 0; i < 20; i++)
	{
		//cout<<i+10;
		cout<<"# ";//左边界框 
		for (int j = 0; j < 40; j++)
		{
			if(j==N&&i==nowy)
			{
				cout<<"*";
			}
			else
			{
				cout << a[j][i];
			}
		}
		cout <<" #"<< endl;//右边界框 
	}
	cout<<"############################################"<<endl;//下边界框 
	cout << "time:" << " " << time(NULL) - timestart;
}


void score()
{
	system("cls");
	cout << endl << endl << endl;
	int max=0; 
	for(int i=1;i<=number;i++)
	{
		cout << "                    " << "第"<<i<<"局" << endl ;
		cout << "                        " << "难度："<<player[i].difficulty<<endl; 
		cout << "                        " << "得分："<<player[i].point << endl << endl;
		max=((player[i].point>max)?player[i].point:max);//比较最大值 
	}
	cout << "                        " << "最高分："<< max << endl << endl;
	system("pause");
	system("cls");
}

void end()
{
	system("cls");
	flush();
	cout<<endl<<"you lose!"<<endl;
	player[number].point= time(NULL) - timestart;//对分数进行赋值 
	system("pause");
	system("cls");
	score();
	return;
}





void welcome()
{
	system("cls");
	cout << endl << endl << endl;
	cout <<"                    " << "欢迎进入游戏“别撞柱子�" << endl<<endl;
	cout << "                  " << "作者：广外lazybones编程社�" << endl << endl;
	system("pause");
	system("cls");
}

void rule()//输出规则并输入难度 
{
	system("cls");
	cout << endl << endl << endl;
	cout << "                    " << "请按上键向上,下键向下,右键悬停" << endl << endl;
	cout << "                        " << "使飞机避开移动的柱子" << endl << endl;
	//cout << "                            " << "空格键可暂停" << endl << endl;
	cout << "                      " << "现在，请输入难度：1—5" << endl << endl;
	cout << "                            ："  ;
	cin >> d;
	player[number].difficulty = d;//对结构体内难度进行赋值
	d = 100 - d * 15;//对d进行速度间隔处理（通过调整这里的数值可以调整游戏速度） 
	system("cls");
	return;
}

void clean()//清空二维数组 
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			a[j][i]=' ';
		}
	}
	return;
}


int main()
{
	welcome();
	
	while (1)
	{
		LOOP1://新一局的开始，违规地用了一个goto 
		number++;//局数加一 
		clean();//将二维数组清空 
		rule();
		timestart = time(NULL);
		

		int process=0;
		while (1)
		{
			process++;
			if (process%10 == 0)//生成柱子速度控制 
			{
				build();
			}
			
			move();//移动柱子 
			
			
			bool flag = 1;//用来检测是否按下，但是由于缓冲区无法清空的原因似乎并没有什么用 
			long int cl = clock();//这个是用检测检测时间的，在这段时间（d毫秒内）会等待用户的输入，其他时间则执行其他代码 
			while ((flag = (clock() - cl <= d)) && !_kbhit());//如果有键按下或时间超过自动前进时间间隔则终止循环
			
			char key; 
			if (flag)
			{
				key = _getch();
			}
			
			
			else
			{
				switch(key)
				{
					case 80://向上 
						if(a[N][nowy+1]==' ')
						{
							a[N][nowy]=' ';
							nowy++;
							a[N][nowy]='*';
							break;
						}
						else
						{
							end();
							goto LOOP1;
						}
					case 72://向下 
						if(a[N][nowy-1]==' ')
						{
							a[N][nowy]=' ';
							nowy--;
							a[N][nowy]='*';
							break;
						}
						else
						{
							
						}
						break;
					default://按了其他的,停在那里 
						if(a[N][nowy]=='|')
						{
							end();
							goto LOOP1;
						}
						break;
				}
			}
			
			flush();//刷新屏幕
		}

	}
	return 0; 
}
