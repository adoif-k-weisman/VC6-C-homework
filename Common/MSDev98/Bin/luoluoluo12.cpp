#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define MAX(a,b) (a>b)?a:b

class game
{
protected:
    int move_numbers;
    bool is_game_over;
public:
    enum Who {NEUTRAL, PLAYER1, PLAYER2, COMPUTER};
    enum GAME_MODE {DEFAULT, PVP, PVC};
    
    Who firstmover, nextmover;
    GAME_MODE gamemode;//ʵ��ģʽѡ��;

    game();
    int is_legal(int a,int b );

    virtual ~game();
    virtual Who play() = 0;
};
game::game()//��ʼ��
{
    move_numbers = 0;
    is_game_over = false;
}
game::~game()
{
}
int game::is_legal(int a,int b )//�ж�����Ϸ���;
{
    int choice = 0;
    char input[32];
    while (choice < a || choice > b)
    {
        cin.getline(input,30);
        choice = atoi(input);
        if (choice < a || choice > b) cout<<"INPUT ERROR! re-input!"<<endl;
    }
    return choice;
}

struct Movements//��¼�ƶ�����һ��;
{
    int col;
};

class Connect4 : public game
{
private:
    int rowNum;
    int colNum;

    int data[6][7];
    int many_used[7];

    Movements* history_moves;//���ڴ洢ÿ�ζ����н��еĲ���;

    void make_human_move();
    bool only_one_win(int check);

    bool computer_best_move(int check);
    void make_computer_move( );
    bool make_move(Movements&);

    void display_status();
    void display_all();
    void restart();
    Who winning(Who last_mover);

public:
    virtual Who play();
    Connect4();
    virtual ~Connect4();
};
Connect4::Connect4() {//��ʼ��;
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
    cout<<"welcome to C4 game!"<<endl;
    cout<<"please choose the game mode you want : \n- 1. PvC(�˻���ս) \n- 2. PvP(���˶Կ�). "<<endl;
    int choice = is_legal(1,2);
    if (choice == 1) {
        gamemode = PVC;
        cout<<"game mode: Player v.s. Computer"<<endl;
        cout<<"who play first? \n- 1. Player \n- 2. Computer"<<endl;
        choice = is_legal(1,2);//�ж�ѡ�����Ϸģʽ�Ƿ���ȷ
        if (choice == 1) {
            firstmover = PLAYER1;
        }
        else firstmover = COMPUTER;
    }
    else {
        gamemode = PVP;
        cout<<"game mode: Player v.s. Player"<<endl;
        cout<<"who play first? \n- 1. Player1 \n- 2. Player2"<<endl;
        choice = is_legal(1,2);
        if(choice == 1){
            firstmover = PLAYER1;
        }
        else firstmover = PLAYER2;
    }

    history_moves = new Movements [42];//��¼ÿһ�ε��ƶ�;

    restart();
    //��Ϸ��ʼ;
    nextmover = firstmover;
    Who winner;
    cout<<"game start!"<<endl;
    while(!is_game_over)
    {
        move_numbers++;
        display_all();
        Who last_mover = nextmover;
        if (nextmover == PLAYER1)
        {
            if (gamemode == PVC) {
                cout<<"Player's turn: "; 
                make_human_move();
                nextmover = COMPUTER;
            }
            else if (gamemode == PVP) {
                cout<<"Player 1's turn: ";
                make_human_move();
                nextmover = PLAYER2;
            }
        }
        else if (nextmover == PLAYER2)
        {
            cout<<"Player 2's turn: ";
            make_human_move();
            nextmover = PLAYER1;
        }
        else if (nextmover == COMPUTER)
        {
            cout<<"Computer's turn: ";
            make_computer_move();
            nextmover = PLAYER1;
        }
        //ÿ��һ����,��Ҫִ��һ��winning(),�ж�winner
        winner = winning(last_mover);

        //���Ƕ�����ж�;
        if (move_numbers == 42) is_game_over = true;
    }
    display_all();

    delete[] history_moves;

    return winner;
}
void Connect4::display_status() //��ӡ����
{
    cout<<endl;

    int SPACE_NUM = 10;
    int current_row = 1;
	int i,j,k,m;
    //@,1 for firstmover
    for ( i = rowNum - 1; i >= 0; i--)
    {
        for ( k = 0; k < SPACE_NUM; k++) cout<<' ';
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
void Connect4::display_all()
{
    display_status();
    cout<<"Round: "<< move_numbers<<endl;
    cout<<"����: ";

    for (int i = 0; i < move_numbers - 1; i++) cout<<history_moves[i].col + 1<<' ';
    cout<<endl;
}
bool Connect4::make_move(Movements& tmove)
{
    if (many_used[tmove.col] >= rowNum) {cout<<"wrong"<<endl;return false;   }
    else if(tmove.col >= colNum)     {cout<<"wrong"<<endl;return false;}
    else {
        if (nextmover == firstmover) data[many_used[tmove.col]++][tmove.col] = 1;

        else data[many_used[tmove.col]++][tmove.col] = 2;

        history_moves[move_numbers-1] = tmove;

        return true;
    }
}
void Connect4::make_human_move()//�������;
{
    int choice = is_legal(1,colNum);
    Movements usr_move = {choice-1};
    bool flag = make_move(usr_move);
    while(!flag)//��һ�����벻�ɹ�ִ�и�ѭ��;
    {
        cout<<"illegal move!Retry! ";
        choice = is_legal(1,colNum);
        usr_move.col = choice-1;//�����±��0��ʼ
        flag = make_move(usr_move);
    }
}
bool Connect4::only_one_win(int check)
{
    Movements cmove;
    int i,j;
    for( i = 0; i < rowNum - 3; i++)
    {
        for( j = 0; j < colNum - 3; j++)
        {
            //�����о�����������
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


bool Connect4::computer_best_move(int check)
{
	
	Movements cmove;
    int M_scores = 0,map[7]= {0};
    int i,j;
	for(i=0;i<colNum;i++){
	if(many_used[i] != 0)
		break;
	else if(i-1 == colNum){
	//�����ֱ������;
    int choice = rand() % colNum;
    cmove.col = choice;
    bool flag = make_move(cmove);
    while(!flag){
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

        i = many_used[j];// �±��0��ʼ,Ӧ��û����;

        if (data[i][j]== 0)
            {
                int scores = 0;
				//check diagnally 1
				//y=x �������;
                int ti = i-1, tj = j-1;
                for(;ti >= 0 && tj >=0 && data[ti][tj] == check;ti--,tj--)
                    scores++;
                ti = i+1; tj = j+1;
                for(;ti < rowNum && tj < colNum && data[ti][tj] == check;ti++,tj++)
                    scores++;
                M_scores = MAX(scores , M_scores);

                //check diagnally 2
				//y = -x ������
                scores = 0;
                ti = i-1; tj = j+1;
                for(;data[ti][tj] == check && ti >= 0 && tj < colNum;ti--,tj++)
                    scores++;                 

                ti = i+1; tj = j-1;

                for(;data[ti][tj] == check && ti < rowNum && tj >= 0;ti++,tj--)
                    scores++;

                M_scores = MAX(scores , M_scores);

                //check horizontally
                scores = 0;
                tj = j+1;
				//�ӵ�ǰ�㵽��
                for(;data[i][tj] == check && tj < colNum;tj++)
                    scores++;
                tj = j-1;
				//�ӵ�ǰ�㵽��
                for(;data[i][tj] == check && tj >= 0;tj--)
                    scores++;
				//ttj �� tj ���Ǳ�ʾ����Ϊ�յĵ�һ��
                M_scores = MAX(scores , M_scores );

                scores = 0;    
                ti = i-1; tj= j;
                for(;ti >= 0 && data[ti][j]==check;ti--)
                    scores++;
                ti = i+1;
                for(;ti < rowNum && data[ti][j] == check;ti++)
                    scores++;
                M_scores = MAX(scores , M_scores);

                map[j] = M_scores; //��¼���е�best ����;
			
            }
            
    }
    //�����best�е�����;
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

void Connect4::make_computer_move()
{


    int check, oppo_check;
    if (firstmover == COMPUTER) {check = 1; oppo_check = 2;}
    else {check = 2; oppo_check = 1; }
    
    //��δ�������������:
    //����ҵ��ҵ�������һ�����Ӯ�ĵط�,��ֱ����������;
    //����ҵ�������һ�����Ӯ�ĵط�,��ֱ�Ӷ�������;
    //finding 1-to-win place 
    if(only_one_win(check) ) {cout<<history_moves[move_numbers-1].col+1<<endl; return;}
    //if opponent's 1-to-win
    //�ҵ����ֵ�ֻ��һ��Ϳ���Ӯ�ĵط��ط�
    if(only_one_win(oppo_check)) {cout<<history_moves[move_numbers-1].col+1<<endl; return;}
    
    if(computer_best_move(check))  {cout<<history_moves[move_numbers-1].col +1<<endl; return;}

    return;
}
game::Who Connect4::winning(Who last_mover)
{
    //����last_mover����ȷ����һ����������Ƿ��Ӯ���ⳡ��Ϸ

    int move_col = history_moves[move_numbers-1].col;
    int move_row = many_used[move_col] - 1;
    //����ϴ������λ��;
    
    int check = data[move_row][move_col];
    //���������λ��;
    
    int t, scores = 0;
    //check horizontally
    t = move_col;
    scores = 0;

    for(;t >= 0 && data[move_row][t] == check;t--)
        scores++;
    t = move_col + 1;

    for(;t < colNum && data[move_row][t] == check;t++)
        scores++;
    if (scores >= 4) {is_game_over = true; return last_mover;}
    //�ж�

    //check verdxcally 
    t = move_row;
    scores = 0;

    for(;t >= 0 && data[t][move_col] == check;t--)
        scores++;
    t = move_row + 1;

    for(;t < rowNum && data[t][move_col] == check;t++)
        scores++;
    if (scores >= 4) {is_game_over = true; return last_mover;}
    
    //check diagnolly 1

    int dx = move_row;
    int dy = move_col;
    scores = 0;
    for(;dx >= 0 && dy >=0 && data[dx][dy] == check;dx--,dy--)
        scores++;
    dx = move_row + 1;
    dy = move_col + 1;
    for(;dx < rowNum && dy < colNum && data[dx][dy] == check;dx++,dy++)
        scores++;
    if (scores >= 4) {is_game_over = true; return last_mover;}

    //check diagnolly 2

    dx = move_row;
    dy = move_col;
    scores = 0;
    for(;dx >= 0 && dy < colNum && data[dx][dy] == check;dx--,dy++)
        scores++;
    dx = move_row + 1;
    dy = move_col - 1;
    for(;dx < rowNum && dy >= 0 && data[dx][dy] == check;dx++,dy--)
        scores++;
    if (scores >= 4) {is_game_over = true; return last_mover;}
    return NEUTRAL;
}
int main()
{
    srand((unsigned int)(time(NULL)));
    Connect4 instance;
    game::Who winner = instance.play();
    //���ʤ���Ľ��;
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
 