#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define MAX(a,b) (a>b)?a:b
//struct ChessMove;

class game
{
protected:
    int move_numbers;//回合,即move_number,不要定义成private,不好用;
    bool is_game_over;
public:
    enum Who {NEUTRAL, PLAYER1, PLAYER2, COMPUTER};
    enum GAME_MODE {DEFAULT, PVP, PVC};
    
    Who firstmover, next_mover;//对象,玩游戏的人;
    GAME_MODE gamemode;//枚举常量,实现模式选择;

    game();
    int is_legal(int a,int b );

    virtual ~game();
    virtual Who play() = 0;
};
game::game()//初始化
{
    move_numbers = 0;
    is_game_over = false;
}
game::~game()//析构函数,没什么可填的,结束游戏会直接重新开始,不考虑回合制;
{
}
int game::is_legal(int a,int b )//判断输入合法性;
{
    //a,b---分别代表列数从哪开始和结束;
    //用户输入会大1,要减掉;
    int choice = 0;
    char input[32];
    while (choice < a || choice > b)
    {
        cin.getline(input,30);
        choice = atoi(input);
        if (choice < a || choice > b) cout<<"输入错误! 重新输入!"<<endl;
    }
    return choice;
}

struct C4_Move//记录移动的哪一列,功能类似most_recent_column;
{
    int col;
};

class Connect4 : public game
{
private:
    int rowNum;//行 = 6;
    int colNum;//列 = 7;

    int data[6][7];
    int many_used[7];

    C4_Move* history_moves;//用于存储每次对哪列进行的操作;

    void player_move();
    bool c_find_1_to_win(int check);

    bool find_other_best(int check);
    void computer_move();
    bool make_move(C4_Move&);

    void display_status();
    void display_info();
    void restart();
    Who win_check(Who last_mover);

public:
    virtual Who play();
    Connect4();
    virtual ~Connect4();
};
Connect4::Connect4() {//初始化;
    memset(data, 0, sizeof(data));
    memset(many_used, 0, sizeof(many_used));
	colNum = 7;
	rowNum = 6;
    firstmover = NEUTRAL;
    gamemode = DEFAULT;
    history_moves = NULL;
}
Connect4::~Connect4()
{
}
void Connect4::restart()
{	int i,j;
    for ( i = 0; i< rowNum; i++)
    {
        for ( j = 0;j<colNum; j++)
        {
            data[i][j] = 0;
        }
    }
    for ( i = 0; i<6*7; i++)
    {
        history_moves[i].col = 0;
    }
    for ( i = 0; i<colNum; i++)
    {
        many_used[i] = 0;
    }
}
game::Who Connect4::play()
{
    cout<<"欢迎来到四子棋游戏!"<<endl;
    cout<<"选择游戏模式: \n- 1. PvC(人机大战) \n- 2. PvP(人人对抗). "<<endl;
    int choice = is_legal(1,2);
    if (choice == 1) {
        gamemode = PVC;
        cout<<"游戏 模式: Player v.s. Computer"<<endl;
        cout<<"谁先走棋? \n- 1. Player \n- 2. Computer"<<endl;
        choice = is_legal(1,2);
        if (choice == 1) {
            firstmover = PLAYER1;
        }
        else firstmover = COMPUTER;
    }
    else {
        gamemode = PVP;
        cout<<"游戏 模式: Player v.s. Player"<<endl;
        cout<<"谁先走棋? \n- 1. Player1 \n- 2. Player2"<<endl;
        choice = is_legal(1,2);
        if(choice == 1){
            firstmover = PLAYER1;
        }
        else firstmover = PLAYER2;
    }

    history_moves = new C4_Move [rowNum * colNum];//记录每一次的移动;

    restart();
    //游戏开始;
    next_mover = firstmover;
    Who winner;
    cout<<"游戏开始!"<<endl;
    while(!is_game_over)
    {
        move_numbers++;
        display_info();
        Who last_mover = next_mover;
        if (next_mover == PLAYER1)
        {
            if (gamemode == PVC) {
                cout<<"Player's turn: "; 
                player_move();
                next_mover = COMPUTER;
            }
            else if (gamemode == PVP) {
                cout<<"Player 1's turn: ";
                player_move();
                next_mover = PLAYER2;
            }
        }
        else if (next_mover == PLAYER2)
        {
            cout<<"Player 2's turn: ";
            player_move();
            next_mover = PLAYER1;
        }
        else if (next_mover == COMPUTER)
        {
            cout<<"Computer's turn: ";
            computer_move();
            next_mover = PLAYER1;
        }
        //每下一步棋,就要执行一个win_check(),判断winner
        winner = win_check(last_mover);

        //这是额外的判断;
        if (move_numbers == rowNum * colNum) is_game_over = true;
    }
    display_info();

    delete[] history_moves;

    return winner;
}
void Connect4::display_status() //打印棋盘
{
    cout<<endl;

    int SPACE_NUM = 10;
    int current_row = 1;
	int i,j,k,m;
    //@,1 for firstmover
    for ( i = rowNum - 1; i >= 0; i--)//一行一行的输出,从上到下;
    {
        for ( k = 0; k < SPACE_NUM; k++) cout<<' ';//调整输出格式;
        for ( j = 0; j < colNum; j++) {
            if (data[i][j] == 1) cout << '@' << ' ';
            else if (data[i][j] == 2) cout << '$' << ' ';
            else cout << '.' << ' ';
        }
        if(current_row == 1) {
            cout<<"   @: ";
            if (gamemode == PVP)
            {
                if (firstmover == PLAYER1) cout<<"Player 1";
                else if (firstmover == PLAYER2) cout<<"Player 2";
            }
            else if (gamemode == PVC)
            {
                if (firstmover == PLAYER1) cout<<"Player";
                else if (firstmover == COMPUTER) cout<<"Computer";
            }
        }
        if(current_row == 2){
            cout<<"   $: ";
            if (gamemode == PVP)
            {
                if (firstmover == PLAYER1) cout<<"Player 2";
                else if (firstmover == PLAYER2) cout<<"Player 1";
            }
            else if (gamemode == PVC)
            {
                if (firstmover == PLAYER1) cout<<"Computer";
                else if (firstmover == COMPUTER) cout<<"Player";
            }
        }
        current_row++;
        cout<<endl;
    }
    for ( k = 0; k < SPACE_NUM; k++) cout<<' ';
    for ( m = 0; m < colNum - 1; m++) cout<<"--";
    cout<<'-';
    cout<<endl;
    for ( k = 0; k < SPACE_NUM; k++) cout<<' ';
    if (colNum < 10) {
        for ( m = 0; m < colNum; m++) cout<<m+1<<' ';
    }
    cout<<endl;
}
void Connect4::display_info()
{
    display_status();
    cout<<"Round(回合): "<< move_numbers<<endl;
    cout<<"棋谱: ";
    //因为是数组,下标从0开始,而我们输出默认从1开始;
    //额外需要+1;
    for (int i = 0; i < move_numbers - 1; i++) cout<<history_moves[i].col + 1<<' ';
    cout<<endl;
}
bool Connect4::make_move(C4_Move& tmove)//修改棋盘
{
    if (many_used[tmove.col] >= rowNum) {cout<<"wrong"<<endl;return false;   }
    else if(tmove.col >= colNum)     {cout<<"wrong"<<endl;return false;}
    else {
        if (next_mover == firstmover) data[many_used[tmove.col]++][tmove.col] = 1;

        else data[many_used[tmove.col]++][tmove.col] = 2;

        history_moves[move_numbers-1] = tmove;

        return true;
    }
}
void Connect4::player_move()//玩家下棋;
{
    int choice = is_legal(1,colNum);
    C4_Move usr_move = {choice-1};
    bool flag = make_move(usr_move);
    while(!flag)//第一次输入不成功执行该循环;
    {
        cout<<"错误移动! 重新尝试! ";
        choice = is_legal(1,colNum);
        usr_move.col = choice-1;//下标从0开始,虽然用户输入从1开始;
        flag = make_move(usr_move);
    }
}
bool Connect4::c_find_1_to_win(int check)
{
    C4_Move cmove;
    int i,j;
    for( i = 0; i < rowNum - 3; i++)
    {
        for( j = 0; j < colNum - 3; j++)
        {
            //谁先走,谁就是@
            if (data[i][j] == check && data[i+1][j+1] == check && data[i+2][j+2] == check && data[i+3][j+3] == 0 && data[i+2][j+3] != 0) 
            {                      //       *
                cmove.col = j + 3; //     @ &
                make_move(cmove);  //   @ & &
                return true;       // @ & & &
            }
            if (data[i][j] == check && data[i+1][j+1] == check && data[i+2][j+2] == 0 && data[i+3][j+3] == check && data[i+1][j+2] != 0) 
            {                      //       @
                cmove.col = j + 2; //     * &
                make_move(cmove);  //   @ & &
                return true;       // @ & & &
            }
            if (data[i][j] == check && data[i+1][j+1] == 0 && data[i+2][j+2] == check && data[i+3][j+3] == check && data[i][j+1] != 0) 
            {                      //       @
                cmove.col = j + 1; //     @ &
                make_move(cmove);  //   * & &
                return true;       // @ & & &
            }
            if (data[i][j] == 0  && data[i+1][j+1] == check && data[i+2][j+2] == check && data[i+3][j+3] == check && (i==0 ||( i>=1 && data[i-1][j] != 0))) 
            {                      //       @
                cmove.col = j + 3; //     @ &
                make_move(cmove);  //   @ & &
                return true;       // *  & & &
            }
            if (data[i+3][j] == 0 && data[i+2][j+1] == check && data[i+1][j+2] == check && data[i][j+3] == check && data[i+2][j] != 0) 
            {                      // *
                cmove.col = j;     // & @
                make_move(cmove);  // & & @ 
                return true;       // & & & @
            }
            if (data[i+3][j] == check && data[i+2][j+1] == 0 && data[i+1][j+2] == check && data[i][j+3] == check && data[i+1][j+1] != 0) 
            {                      // @
                cmove.col = j+1;   // & *
                make_move(cmove);  // & & @ 
                return true;       // & & & @
            }
            if (data[i+3][j] == check && data[i+2][j+1] == check && data[i+1][j+2] == 0 && data[i][j+3] == check && data[i][j+2] != 0) 
            {                      // @
                cmove.col = j+2;   // & @
                make_move(cmove);  // & & * 
                return true;       // & & & @
            }
            if (data[i+3][j] == check && data[i+2][j+1] == check && data[i+1][j+2] == check && data[i][j+3] == 0 && (i==0 || (i>=1 && data[i-1][j+3] != 0))) 
            {                      // @
                cmove.col = j;     // & @
                make_move(cmove);  // & & @ 
                return true;       // & & & *
            }
        }
    }
    for ( i = 0; i< rowNum ;i++) {
        for ( j =0; j < colNum -3;j++) {
            if(data[i][j] == 0 && data[i][j+1] == check && data[i] [j+2] == check && data[i][j+3] == check && (i == 0 || (i>0 && data[i-1][j] != 0))) {
                // * @ @ @
                cmove.col = j;
                make_move(cmove);
                return true;
            }
            if(data[i][j] == check && data[i][j+1] == 0 && data[i][j+2] == check && data[i][j+3] == check && (i == 0 || (i>0 && data[i-1][j+1] != 0))) {
                // @ * @ @
                cmove.col = j+1;
                make_move(cmove);
                return true;
            }
            if(data[i][j] == check && data[i][j+1] == check && data[i][j+2] == 0 && data[i][j+3] == check && (i == 0 || (i>0 && data[i-1][j+2] != 0))) {
                // @ @ * @
                cmove.col = j+2;
                make_move(cmove);
                return true;
            }
            if(data[i][j] == check && data[i][j+1] == check && data[i] [j+2] == check && data[i][j+3] == 0 && (i == 0 || (i>0 && data[i-1][j+3] != 0))) {
                // @ @ @ *
                cmove.col = j+3;
                make_move(cmove);
                return true;
            }
        }
    }
    for ( i = 0; i < rowNum - 3; i++)
    {
        for ( j = 0 ; j < colNum ; j++)
        {
            if (data[i][j]==check && data[i+1][j]==check  && data[i+2][j] == check && data[i+3][j] == 0){
                cmove.col = j;
                make_move(cmove);
                return true;
            }
        }
    }
    return false;
}

bool Connect4::find_other_best(int check)
{
	
	
	C4_Move cmove;
    int M_cnt = 0,map[7]= {0};
    int i,j;
	for(i=0;i<colNum;i++){
	if(many_used[i] != 0)
		break;
	else if(i-1 == colNum){
	//零个棋直接随意;
    int choice = rand() % colNum;
    cmove.col = choice;
    bool flag = make_move(cmove);
    while(!flag)
    {
        cout<<"Illegal move! Try again. ";
        choice = rand() % colNum;
        cmove.col = choice;
        flag = make_move(cmove);
    }
    cout<<cmove.col+1<<endl;
	return true;
	}
	
	}
    for(j=0;j<colNum;j++)
    {
        if(many_used[j] >= rowNum)
        {   
			break;
		}
            
        i = many_used[j];// 下标从0开始,应该没问题;

        if (data[i][j]== 0)
            {


                int cnt = 0;
				//check diagnally 1
				//y=x 这个方向;
                int ti = i-1, tj = j-1;
                while (ti >= 0 && tj >= 0 && data[ti][tj] == check) {ti--;tj--;cnt++;}
                
                ti = i+1; tj = j+1;
                while (ti < rowNum && tj < colNum && data[ti][tj] == check) {ti++; tj++; cnt++; }
                M_cnt = MAX(cnt , M_cnt);

                //check diagnally 2
				//y = -x 这条线
                cnt = 0;
                ti = i-1; tj = j+1;
                while(data[ti][tj] == check && ti >= 0 && tj < colNum) {ti--;tj++;cnt++;}
                 

                ti = i+1; tj = j-1;
                while(data[ti][tj] == check && ti < rowNum && tj >= 0 ) {ti++; tj--; cnt++; }
                

                M_cnt = MAX(cnt , M_cnt);

                //check horizontally
				//水平方向;
                cnt = 0;
                tj = j+1;
				//从当前点到右
                while(data[i][tj] == check && tj < colNum){tj++; cnt++; }
            
                tj = j-1;
				//从当前点到左
                while(data[i][tj] == check && tj >= 0) {tj--; cnt++;}
				//没问题,ttj 和 tj 都是表示左右为空的第一列
                M_cnt = MAX(cnt , M_cnt );

                cnt = 0;    
                ti = i-1; tj= j;
                while(ti >= 0 && data[ti][j]==check) {ti--; cnt++;}//往下遍历;
                ti = i+1;
                while(ti < rowNum && data[ti][j] == check) {ti++; cnt++;}

                M_cnt = MAX(cnt , M_cnt);

                map[j] = M_cnt; //记录该列的best 分数;
			
            }
            
    }
    //求出该best列的列数;
    int maxi = 0;
    for(i = 1;i<colNum;i++)
    {
        if(map[maxi] < map[i])
            maxi = i;
    }
    
    cmove.col = maxi;
    make_move(cmove);
    return true;
}


void Connect4::computer_move()
{

    int check, oppo_check;
    if (firstmover == COMPUTER) {check = 1; oppo_check = 2;}
    else {check = 2; oppo_check = 1; }
    
    //如何处理三个棋的情况:
    //如果找到我电脑再下一个棋就赢的地方,就直接下在那里;
    //如果找到人再下一个棋就赢的地方,就直接堵在那里;
    //finding 1-to-win place 
    if(c_find_1_to_win(check) ) {cout<<history_moves[move_numbers-1].col+1<<endl; return;}
    //if opponent's 1-to-win
    //找到对手的只下一棋就可以赢的地方地方
    if(c_find_1_to_win(oppo_check)) {cout<<history_moves[move_numbers-1].col+1<<endl; return;}
    
    

    if(find_other_best(check))  {cout<<history_moves[move_numbers-1].col +1<<endl; return;}

    return;
}
game::Who Connect4::win_check(Who last_mover)
{
    //传入last_mover用于确认上一步下棋的人是否会赢得这场游戏

    int last_move_col = history_moves[move_numbers-1].col;
    //相当于most_recent_cloumn,获得上次下棋的列数
    
    int last_move_row = many_used[last_move_col] - 1;
    //即many_used[most_recent_column]获得所在行数;
    
    int check = data[last_move_row][last_move_col];
    //即我下棋的位置;
    
    int t, cnt = 0;
    //check horizontally,水平检查;
    t = last_move_col;
    cnt = 0;
    //用check 去代替用human,或者computer,节省代码;
    while (t >= 0 && data[last_move_row][t] == check) {cnt++; t--; }
    //检查从当前位置到最左边
    t = last_move_col + 1;
    while (t < colNum && data[last_move_row][t] == check) {cnt++; t++; }
    //检查从当前位置到最右边
    if (cnt >= 4) {is_game_over = true; return last_mover;}
    //判断

    //check vertically ,垂直检查
    t = last_move_row;
    cnt = 0;
    while (t >= 0 && data[t][last_move_col] == check) {cnt++; t--; }
    t = last_move_row + 1;
    while (t < rowNum && data[t][last_move_col] == check) {cnt++; t++; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}
    
    //check diagnolly 1
    //从左下到右上,y=x这条斜线;
    int ti = last_move_row;
    int tj = last_move_col;
    cnt = 0;
    while (ti >= 0 && tj >=0 && data[ti][tj] == check) {cnt++; ti--; tj--;}
    ti = last_move_row + 1;
    tj = last_move_col + 1;
    while (ti < rowNum && tj < colNum && data[ti][tj] == check) {cnt++; ti++; tj++; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}

    //check diagnolly 2
    //从左上到右下,即 y=-x 这条斜线
    ti = last_move_row;
    tj = last_move_col;
    cnt = 0;
    while (ti >= 0 && tj < colNum && data[ti][tj] == check) { cnt++; ti--; tj++;}
    ti = last_move_row + 1;
    tj = last_move_col - 1;
    while (ti < rowNum && tj >= 0 && data[ti][tj] == check) { cnt++; ti++; tj--; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}
    return NEUTRAL;
}
int main()
{
    srand((unsigned int)(time(NULL)));
    Connect4 instance;
    game::Who winner = instance.play();
    //输出胜负的结果;
    if (instance.gamemode == game::PVC)
    {
        if (winner == game::PLAYER1) cout<<"Player wins!"<<endl;
        else if (winner == game::COMPUTER) cout<<"Computer wins!"<<endl;
        else if (winner == game::NEUTRAL) cout<<"Draw!"<<endl;
    }
    else if (instance.gamemode == game::PVP){
        if (winner == game::PLAYER1) cout<<"Player 1 wins!"<<endl;
        else if (winner == game::PLAYER2) cout<<"Player 2 wins!"<<endl;
        else if (winner == game::NEUTRAL) cout<<"Draw!"<<endl;
    }
    return 0;
}
 