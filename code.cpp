#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
const string  block="■";
const string  space="  "; 
const int N=22;   		//游戏栏行数
const int M=12;    //游戏栏列数
const int MM=6;     //信息栏列数
const string Side[]={"┄","┆"};   //横栏 
const string Corner[]={"┌","┐","└" ,"┘"}; //竖栏

string g[N][M],gg[N][MM];

struct Point{
	int x,y;
	Point(){}  //constructor
	Point(int _x,int _y):x(_x),y(_y){}
	
	Point operator++(int){
		y++;
		return (*this);
	}
	Point operator--(int){
		y--;
		return (*this);
	}
	Point operator++(){
		x++;
		return (*this);
	}
	bool operator==(const Point& B){
		return x==B.x && y==B.y;
	}
};
//Set Cursor
void setCursor(int x,int y){
	COORD cd={(short int)x,(short int)y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);	
}

//overload version
void setCursor(const Point &p){
	setCursor(2*p.y,p.x);
}
//隐藏光标 
void hideCursor(){
	HANDLE hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hConsoleOutput,&CursorInfo);
	CursorInfo.bVisible=FALSE;  //设置光标可见
	SetConsoleCursorInfo(hConsoleOutput,&CursorInfo); 
}
class Game;
class Block{
	public:
		friend class Game;
		Block();
		Point p;
		bool State[4][4];
		static void stateInit();   //初始化方块状态
		void stateCopy();            //复制方块状态
		void Rotate();             //旋转
		void Show(bool);            //显示方块
	public:
		static string allBlock[7][4];     //标记所有方块
		int id,dir;               //方块状态和方向 
};
//define block 
string Block::allBlock[7][4];
void Block::stateInit(){
//I
    allBlock[0][0] = allBlock[0][2] = "0100 0100 0100 0100";   //4X4方格，每4个一行 
    allBlock[0][1] = allBlock[0][3] = "0000 1111 0000 0000";
    //O
    allBlock[1][0] = allBlock[1][1] = "0000 0110 0110 0000";
    allBlock[1][2] = allBlock[1][3] = "0000 0110 0110 0000";
    //S
    allBlock[2][0] = allBlock[2][2] = "0000 0110 1100 0000";
    allBlock[2][1] = allBlock[2][3] = "0100 0110 0010 0000";
    //Z
    allBlock[3][0] = allBlock[3][2] = "0000 1100 0110 0000";
    allBlock[3][1] = allBlock[3][3] = "0100 1100 1000 0000";
    //T
    allBlock[4][0] = "0000 1110 0100 0000";
    allBlock[4][1] = "0100 1100 0100 0000";
    allBlock[4][2] = "0100 1110 0000 0000";
    allBlock[4][3] = "0100 0110 0100 0000";
    //J
    allBlock[5][0] = "0100 0100 1100 0000";
    allBlock[5][1] = "1000 1110 0000 0000";
    allBlock[5][2] = "1100 1000 1000 0000";
    allBlock[5][3] = "0000 1110 0010 0000";
    //L
    allBlock[6][0] = "0100 0100 0110 0000";
    allBlock[6][1] = "0000 1110 1000 0000";
    allBlock[6][2] = "1100 0100 0100 0000";
    allBlock[6][3] = "0010 1110 0000 0000";
}
Block::Block(){
	id=rand()%7;
	dir=rand()%4;
	p=Point(4,13);  //初始化点的位置
	stateCopy(); 
}
//copy 方块的状态 
void Block::stateCopy(){
	for(int i=0,add=0;i<4;++i,++add)
		for(int j=0;j<4;j++)
			State[i][j]=allBlock[id][dir][i*4+j+add]=='1';
}
//旋转方块 
void Block::Rotate(){
	dir=(dir+1)%4;
	stateCopy();
}
//function Print
template <typename T>
void Print(const Point &p,T data,int wid=0){
	setCursor(p);
	if(wid)
		cout.width(wid);
	cout<<data;
}
void magicShow(const Point &p,bool flag=false,bool info=false){
	if(info || g[p.x][p.y]==space){
		Print(p,flag? block:space);
	}
}
//info 表示是否是信息栏 要打印的方块位置(信息区还是游戏区) 
void Block::Show(bool info=false){
	for(int i=0;i<4;++i)
		for(int j=0;j<4;++j)
			magicShow(Point(p.x+i,p.y+j),State[i][j],info);
}
class Game{
	private:
		int level,score;
		static int level_up[6];             //各level对应的分数
        static int score_up[5];             //消除各行对应要加的分数
        static int tick_cnt[6];  
	public:
		Block runB,nextB;
		Game();             //初始化
		int getTickCount();   //控制下落的时钟 
		void showFrame();     //打印游戏框架
		void checkKey();      //检测键盘响应
		void getNext();       //得到下一个方块
		bool collsionDection(int x,int y); //检测是否出界 
		void Begin();         //游戏开始
		void Over();          //游戏结束 
		bool allSquare(int xx);  //确定某行是否可以消除 
		void removeLine();      //消除某一行   
		int GetScore();       //得到当前分数
		bool changePos(int dx,int dy);  //改变方块 
		bool CanChange(int ,int );  //检测方块是否能被安置
		void PlaceOn();                  //安置方块   
		void Update(int flash_line_cnt);
		void DropDown(int xx);
		void Rotate();                  //旋转方块 
};
int Game::level_up[6]={0,80,180,290,410,700};  //Level
int Game::score_up[5]={0,10,30,50,70};         //Score  
int Game::tick_cnt[6]={0,50,40,30,20,10};      //时钟 

void Game::removeLine(){
	vector<int> flash_line;                                 //用来储存要消去的行号
    auto it=flash_line.begin();
    for(int i=0;i<4;i++)
        if(allSquare(i+runB.p.x))
            flash_line.push_back(i+runB.p.x);
    if(flash_line.empty())
        return ;
    int flash_times = 5;
    while(flash_times--)                                    //闪
    {
        for(it=flash_line.begin();it!=flash_line.end();it++)
            for(int j=1;j<M-1;j++)
                magicShow(Point(*it,j),flash_times&1,true);
        Sleep(60);
    }
    for(it=flash_line.begin();it!=flash_line.end();it++)    //消去某行后，将上面的信息向下移动
        DropDown(*it);
    it = flash_line.end()-1;
    for(int i=1;i<=*it;i++)
        for(int j=1;j<M-1;j++)
            magicShow(Point(i,j),g[i][j]==block,true);     //更新要消去的最后一行上方的信息
    Update(flash_line.size());
    flash_line.clear();
}
//检测位置是否能被改变 
bool Game::CanChange(int dx=0,int dy=0)
{
    const int x = runB.p.x , y = runB.p.y;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
           if(runB.State[i][j] && (collsionDection(i+x+dx,j+y+dy) || g[i+x+dx][j+y+dy]==block))
                return false;
    return true;
}
void Game::Rotate(){
	for(int i=0;i<3;i++){
		runB.Rotate();
		if(CanChange()){
			runB.Show();
			return;
		}
	}
} 
void Game::DropDown(int xx){
    for(int i=xx;i>1;i--)
        for(int j=1;j<M-1;j++)
            g[i][j] = g[i-1][j];
    for(int j=1;j<M-1;j++)
        g[1][j]=space;
}
void Game::Update(int flash_line_cnt){
    score += score_up[flash_line_cnt];
    Print(Point(13,14),score);
    if(level<6 && score>=level_up[level])
        Print(Point(10,14),++level,2);
}
Game::Game():level(1),score(0){
	for(int i=0;i<N;++i){
		for(int j=0;j<M;++j)
			g[i][j]="  ";
		for(int j=0;j<MM;++j)
			gg[i][j]="  ";
	}
	//画游戏栏的横框
   for(int i=1;i<M;++i)
		g[0][i]=g[N-1][i]=Side[0];
	//画信息栏的横框
	for(int i=1;i<MM;++i)
		gg[0][i]=gg[N-1][i]=Side[0];
	
	//画竖栏
	for(int i=1;i<N;i++)
		g[i][0]=g[i][M-1]=gg[i][0]=gg[i][MM-1]=Side[1];			
	//画四个边角 
	g[0][0]=gg[0][0]=Corner[0];  //左上角
	g[0][M-1]=gg[0][MM-1]=Corner[1]; //右上角 
	g[N-1][0]=gg[N-1][0]=Corner[2];//左下角 
	g[N-1][M-1]=gg[N-1][MM-1]=Corner[3];//右下角 

}
//时钟
int Game::getTickCount(){
	return tick_cnt[level];	
} 

void Game::showFrame(){
	//打印主框架 
	for(int i=0;i<N;++i){
		for(int j=0;j<M;++j)
			cout<<g[i][j];
		for(int j=0;j<MM;++j)
			cout<<gg[i][j];
		cout<<endl;
	}
	//打印各种信息
	Print(Point(2,13)," Next");
	Print(Point(9,13)," Level");
	Print(Point(10,14),level,2);
	Print(Point(12,13)," Score");
	Print(Point(13,14),score,2);
	Print(Point(20,13)," Mark");
}
void Game::getNext(){
	runB=nextB;
	runB.p=Point(1,5);
	nextB=Block();
	
	nextB.Show(true);	
	runB.Show();
}

void Game::Begin(){
	showFrame();  //打印主框架
	
	nextB=Block();   //产生信息栏的方块 
	getNext();
	
	int flash_times=1000;
	while(!kbhit() && flash_times--){
		Print(Point(9,1),flash_times&1? "                   " :" * * * * * * * * * ");
		Print(Point(10,1),flash_times&1? "                   ":"* Anykey to start *");
		Print(Point(11,1),flash_times&1? "                   ":" * * * * * * * * * ");
		Sleep(100);
	}
	getch();
	Print(Point(9,1), "                    ");
	Print(Point(10,1),"                    ");
	Print(Point(11,1),"                    ");	 
}
//检测是否出界 
inline bool Game::collsionDection(int x,int y){
	return x>=N-1 || x<=0 ||y<=0 || y>=M-1;  //如果出界 return true 
}

//安置方块 
bool Game::changePos(int dx,int dy)
{
    if(!CanChange(dx,dy))
        return false;
    const int x = runB.p.x , y = runB.p.y;
    if(dx==1)                                     //处理最后那行的显示
    {
        for(int j=0;j<4;j++)
            magicShow(Point(x,y+j));
        ++runB.p;
    }
    else if(dy == 1)                                //+1
    {
        for(int i=0;i<4;i++)
            magicShow(Point(x+i,y));
        runB.p++;
    }
    else if(dy == -1)                               //+2
    {
        for(int i=0;i<4;i++)
            magicShow(Point(x+i,y+3));
        runB.p--;
    }
    runB.Show();
    return true;
}
//检测键盘输入 
void Game::checkKey(){
	char ch='\0';
	for(int i=0;i<2;++i)
		if(kbhit()){
			ch=getch();
			if(ch!=-32){
				if(ch==' ')
					getch();	
			}
			if(ch==72)
				Rotate();
			if(ch==75)
				changePos(0,-1);
			if(ch==77)
				changePos(0,1);
			if(ch==80)
				changePos(1,0);
		}
}
void Game::PlaceOn()
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(runB.State[i][j])
                g[runB.p.x+i][runB.p.y+j]=block;
}
//游戏结束 
void Game::Over(){
	Print(Point(9,1), " * * * * * * * * * ");
	Print(Point(10,1),"*    Game Over    *");
	Print(Point(11,1)," * * * * * * * * * ");
}
//检测某行是否可消除 
bool Game::allSquare(int xx){
	for(int i=1;i<M-1;++i)
		if(g[xx][i]!=block)
			return false;
	return true;
}
Game G;
int main(int argc,char **argv){
	Block::stateInit();
	hideCursor();
	srand(time(NULL));
	G.Begin();
	//游戏主循环 
	while(1){
		int tickTime=0;
		while(++tickTime<G.getTickCount()){
			G.checkKey();
			Sleep(20);
		}
		if(!G.changePos(1,0)){
			if(G.runB.p==Point(1,5)){
				G.Over();
				break;
			}
			G.PlaceOn();
			G.removeLine();
            G.getNext();
		}
	}
	return 0;
}
