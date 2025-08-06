
/*

░176
▒177
▓178
║186
╗187
╝ 188
╚200
╔201
═205
■ 254
█219
   
╔═════════╗
║   ██   ║
║   ██  ▓▓  ║
║     ▓▓  ║
╚═════════╝
   ---
████████

██
██
██
██
---
██
██████

████
██
██

██████
    ██

  ██
  ██
████

---



    ██
██████

██
██
████

██████
██

████
  ██
  ██
---

  ████
████

██
████
  ██

---  

████
  ████

    ██
  ████
  ██
---

  ██
██████

██
████
██

██████
  ██

  ██
████
  ██
  ---

████
████


████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
████████████████████
<╔════════════════════╗>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║>
<║ . . . . . . . . . .║> 
<╚════════════════════╝>



*/



#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <random>
#include <mutex>
using namespace std;


void clear_screen() {
    cout << "\033[2J\033[1;1H";  
}
void move_cursor_top_left() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int inputkey(){
    
    int ch = _getch(); 
    if (ch == 224) {    
        int arrow = _getch(); 
        switch (arrow) {
            case 72: //up
                return 1;
            case 80: //down
                return 3;
            case 75: //left
                return 2;
            case 77: //right
                return 4;
        }
    }
    if(ch == 13 ||ch == 32){ //enter or space
        return 5;
    }
    if(ch == 99) return 6; //c
    if(ch == 120) return 1; //x (x does the same as up)
    if(ch == 122) return 7; //z
    return -1;
}

bool iseven(int i){
    if(i%2==0) return true;
    else return false;
}

class game{
private:
    int grid[22][10]={0};
    int fixed[22][10]={0};
    mutex grid_mutex;
    mutex fixed_mutex;
    int x1,x2,x3,x4,y1,y2,y3,y4;
    bool gameon=true;
    int alt_piece=-1;
    int current_piece;
    int rotation_state;

    int piecegrid[8][2][4]={
        {{0,0,0,0},{0,0,0,0}},{{1,1,1,1},{0,0,0,0}},{{1,0,0,0},{1,1,1,0}},{{0,0,1,0},{1,1,1,0}},{{0,1,1,0},{1,1,0,0}},{{1,1,0,0},{0,1,1,0}},{{0,1,0,0},{1,1,1,0}},{{0,1,1,0},{0,1,1,0}}
    };

    int rot_I[4][4][2]={
        {{-1,2},{0,1},{1,0},{2,-1}},   //0  
        {{2,1},{1,0},{0,-1},{-1,-2}},  //1  
        {{1,-2},{0,-1},{-1,0},{-2,1}}, //2    
        {{-2,-1},{-1,0},{0,1},{1,2}}   //3  
/*        
        {{2,1},{1,0},{0,-1},{-1,-2}},   0   current rotation = 1   
        {{-1,2},{0,1},{1,0},{2,-1}},    3                     0     se o state for par, soma 1, se for ímpar substrai 1; válido para todas as peças;
        {{-2,-1},{-1,0},{0,1},{1,2}},   2                      3
        {{1,-2},{0,-1},{-1,0},{-2,1}}   1                      2
*/
    };
    int rot_L2[4][4][2]={
        {{0,2},{-1,1},{0,0},{1,-1}},
        {{2,0},{1,1},{0,0},{-1,-1}},
        {{0,-2},{1,-1},{0,0},{-1,1}},
        {{-2,0},{-1,-1},{0,0},{1,1}}
    };
    int rot_L[4][4][2]={
        {{2,0},{-1,1},{0,0},{1,-1}},
        {{0,-2},{1,1},{0,0},{-1,-1}},
        {{-2,0},{1,-1},{0,0},{-1,1}},
        {{0,2},{-1,-1},{0,0},{1,1}}
    };
    int rot_T[4][4][2]={
        {{1,1},{-1,1},{0,0},{1,-1}},
        {{1,-1},{1,1},{0,0},{-1,-1}},
        {{-1,-1},{1,-1},{0,0},{-1,1}},
        {{-1,1},{-1,-1},{0,0},{1,1}}
    };
    int rot_S[4][4][2]={
        {{1,1},{2,0},{-1,1},{0,0}},
        {{1,-1},{0,-2},{1,1},{0,0}},
        {{-1,-1},{-2,0},{1,-1},{0,0}},
        {{-1,1},{0,2},{-1,-1},{0,0}}
    };
    int rot_Z[4][4][2]={
        {{0,2},{1,1},{0,0},{1,-1}},
        {{2,0},{1,-1},{0,0},{-1,-1}},
        {{0,-2},{-1,-1},{0,0},{-1,1}},
        {{-2,0},{-1,1},{0,0},{1,1}}
    };
public: 
  
    void print_game(){
        move_cursor_top_left();
        cout << endl << endl << endl << endl << endl << endl;
        for(int i=0;i<2;i++){
            cout << "                                                     ";
            for(int j=0;j<10;j++){
                if(grid[i][j]==0) cout << "  "; 
                else cout << char(219) << char(219);
            }
            cout << endl;
        }
        for(int i=2;i<22;i++){
            cout << "                                                   <" << char(186);
            for(int j=0;j<10;j++){
                if(grid[i][j]==0) cout << " ."; 
                else cout << char(219) << char(219);
            }
            cout << char(186) << ">";
            
            if(i==2) cout << "  HOLD";
            else if(i==3){
                cout << "  " << char(201);
                for(int j=0;j<8;j++){
                 cout << char(205);
                }
                cout << char(187);
            }
            else if(i==4 || i==5){
                cout << "  " << char(186);
                for(int j=0;j<4;j++){
                    if(piecegrid[alt_piece+1][i-4][j]==1) cout << char(219) << char(219);
                    else cout << " .";
                }
                cout << char(186);
            }
            else if(i==6){
                cout << "  " << char(200);
                for(int j=0;j<8;j++) cout << char(205);
                cout << char(188);
            }
            cout << endl;
        }
        cout << "                                                    " << char(200);
        for(int i=0;i<20;i++) cout << char(205);
        cout << char(188) << endl;
    }




    void piece_gen(int i){
        rotation_state=0;
        int j;    
        if(i==-1){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0,6);
            j = dist(gen);
        }
        else j=i;
        switch(j){
            case 0:
                x1=x2=x3=x4=0;
                y1=3;
                y2=4;
                y3=5;
                y4=6;
                break;
            case 1:
                x1=0;
                x2=x3=x4=1;
                y1=y2=3;
                y3=4;
                y4=5;
                break;                
            case 2:
                x1=0;
                x2=x3=x4=1;
                y1=y4=5;
                y2=3;
                y3=4;
                break;
            case 3:
                x1=x2=0;
                x3=x4=1;
                y1=y4=4;
                y2=5;
                y3=3;
                break;
            case 4:
                x1=x2=0;
                x3=x4=1;
                y1=3;
                y2=y3=4;
                y4=5;
                break;
            case 5:
                x1=0;
                x2=x3=x4=1;
                y1=y3=4;
                y2=3;
                y4=5;
                break;
            case 6:
                x1=x2=0;
                x3=x4=1;
                y1=y3=4;
                y2=y4=5;
                break;
        }
        if(fixed[x1][y1]==0 && fixed[x2][y2]==0 && fixed[x3][y3]==0 && fixed[x4][y4]==0){
            grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=1;
            current_piece=j;
        }
        else{
            gameon= false;
        }
    }
    void gravity(){
        while(gameon){
            Sleep(500);
            lock_guard<std::mutex> lock(grid_mutex);
            if(x1<21 && x2<21 && x3<21 && x4<21 && fixed[x1+1][y1]==0 && fixed[x2+1][y2]==0 && fixed[x3+1][y3]==0 && fixed[x4+1][y4]==0){
                grid[x1++][y1]=grid[x2++][y2]=grid[x3++][y3]=grid[x4++][y4]=0;
                grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=1;
            }
            else{
                fixed[x1][y1]=grid[x1][y1];
                fixed[x2][y2]=grid[x2][y2];
                fixed[x3][y3]=grid[x3][y3];
                fixed[x4][y4]=grid[x4][y4];
                clear_lines();
                piece_gen(-1);
            }
            print_game();
        }
    }



    void piece_control(){
        int l=1;
        while(gameon){
            if(kbhit()){
                lock_guard<std::mutex> lock(grid_mutex);
                int i=inputkey();
                if(i==2 && y1>0 && y2>0 && y3>0 && y4>0 && fixed[x1][y1-1]==0 && fixed[x2][y2-1]==0 && fixed[x3][y3-1]==0 && fixed[x4][y4-1]==0){
                    grid[x1][y1--]=grid[x2][y2--]=grid[x3][y3--]=grid[x4][y4--]=0;
                    grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=1;
                    l=1;
                }
                if(i==4 && y1<9 && y2<9 && y3<9 && y4<9 && fixed[x1][y1+1]==0 && fixed[x2][y2+1]==0 && fixed[x3][y3+1]==0 && fixed[x4][y4+1]==0){
                    grid[x1][y1++]=grid[x2][y2++]=grid[x3][y3++]=grid[x4][y4++]=0;
                    grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=1;
                    l=1;
                }
                if(i==3 && x1<21 && x2<21 && x3<21 && x4<21 && fixed[x1+1][y1]==0 && fixed[x2+1][y2]==0 && fixed[x3+1][y3]==0 && fixed[x4+1][y4]==0){
                    grid[x1++][y1]=grid[x2++][y2]=grid[x3++][y3]=grid[x4++][y4]=0;
                    grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=1;
                    l=1;
                }
                if(i==5 && x1<21 && x2<21 && x3<21 && x4<21 && fixed[x1+1][y1]==0 && fixed[x2+1][y2]==0 && fixed[x3+1][y3]==0 && fixed[x4+1][y4]==0){
                    grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=0;
                    while(x1<21 && x2<21 && x3<21 && x4<21 && fixed[x1+1][y1]==0 && fixed[x2+1][y2]==0 && fixed[x3+1][y3]==0 && fixed[x4+1][y4]==0){ 
                        x1++; x2++; x3++; x4++;
                    }
                    grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=1;
                    fixed[x1][y1]=grid[x1][y1];
                    fixed[x2][y2]=grid[x2][y2];
                    fixed[x3][y3]=grid[x3][y3];
                    fixed[x4][y4]=grid[x4][y4];
                    clear_lines();
                    piece_gen(-1);
                    l=1;
                }
                if(i==6 && l==1){
                    grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=0;
                    int q=current_piece;
                    piece_gen(alt_piece);
                    alt_piece=q;
                    l=0;
                }
                if(i==1 || i==7){
                    int u;
                    if(i==1)u=rotation_state;
                    else{
                        u=(rotation_state+1)%4; //está mal
                    }
                    grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=0;
                    if(current_piece==0){//I
                        x1+=rot_I[u][0][0];
                        x2+=rot_I[u][1][0];
                        x3+=rot_I[u][2][0];
                        x4+=rot_I[u][3][0];
                        y1+=rot_I[u][0][1];
                        y2+=rot_I[u][1][1];
                        y3+=rot_I[u][2][1];
                        y4+=rot_I[u][3][1];
                    }
                    else if(current_piece==1){//L2
                        x1+=rot_L2[u][0][0];
                        x2+=rot_L2[u][1][0];
                        x3+=rot_L2[u][2][0];
                        x4+=rot_L2[u][3][0];
                        y1+=rot_L2[u][0][1];
                        y2+=rot_L2[u][1][1];
                        y3+=rot_L2[u][2][1];
                        y4+=rot_L2[u][3][1];                        
                    }
                    else if(current_piece==2){//L
                        x1+=rot_L[u][0][0];
                        x2+=rot_L[u][1][0];
                        x3+=rot_L[u][2][0];
                        x4+=rot_L[u][3][0];
                        y1+=rot_L[u][0][1];
                        y2+=rot_L[u][1][1];
                        y3+=rot_L[u][2][1];
                        y4+=rot_L[u][3][1];                        
                    }
                    else if(current_piece==3){//S
                        x1+=rot_S[u][0][0];
                        x2+=rot_S[u][1][0];
                        x3+=rot_S[u][2][0];
                        x4+=rot_S[u][3][0];
                        y1+=rot_S[u][0][1];
                        y2+=rot_S[u][1][1];
                        y3+=rot_S[u][2][1];
                        y4+=rot_S[u][3][1];
                    }
                    else if(current_piece==4){//Z
                        x1+=rot_Z[u][0][0];
                        x2+=rot_Z[u][1][0];
                        x3+=rot_Z[u][2][0];
                        x4+=rot_Z[u][3][0];
                        y1+=rot_Z[u][0][1];
                        y2+=rot_Z[u][1][1];
                        y3+=rot_Z[u][2][1];
                        y4+=rot_Z[u][3][1];
                    }
                    else if(current_piece==5){//T
                        x1+=rot_T[u][0][0];
                        x2+=rot_T[u][1][0];
                        x3+=rot_T[u][2][0];
                        x4+=rot_T[u][3][0];
                        y1+=rot_T[u][0][1];
                        y2+=rot_T[u][1][1];
                        y3+=rot_T[u][2][1];
                        y4+=rot_T[u][3][1];                        
                    }
                    if(y1<10 && y2<10 && y3<10 && y4<10 && y1>=0 && y2>=0 && y3>=0 && y4>=0 && x1<22 && x2<22 && x3<22 && x4<22 && x1>=0 && x2>=0 && x3>=0 && x4>=0 && fixed[x1][y1]==0 && fixed[x2][y2]==0 && fixed[x3][y3]==0 && fixed[x4][y4]==0){}
                    else{
                        x1+=2;x2+=2;x3+=2;x4+=2;
                        int g=0;
                        while(y1>9 || y2>9 || y3>9 || y4>9 || y1<0 || y2<0 || y3<0 || y4<0 || x1>21 || x2>21 || x3>21 || x4>21 || x1<0 || x2<0 || x3<0 || x4<0 || fixed[x1][y1]==1 || fixed[x2][y2]==1 || fixed[x3][y3]==1 || fixed[x4][y4]==1){
                            if(g==0){
                                y1--;y2--;y3--;y4--;
                            }
                            else if(g==1){
                                y1+=2;y2+=2;y3+=2;y4+=2;
                            }
                            else{
                                y1--;y2--;y3--;y4--;
                                x1--;x2--;x3--;x4--;
                            }
                            g=(g+1)%3;
                        }
                    }

                    grid[x1][y1]=grid[x2][y2]=grid[x3][y3]=grid[x4][y4]=1;
                    if(i==1) rotation_state=(rotation_state+1)%4;
                    else rotation_state=(rotation_state+3)%4;
                }
                print_game();
            }
        }
    }

    void clear_lines(){
        for(int i=0;i<22;i++){
            int r=1;
            for(int j=0;j<10;j++){
                r = r && fixed[i][j];
            }
            if(r==1){
                for(int m=i;m>0;m--){
                    for(int n=0;n<10;n++){
                        fixed[m][n]=grid[m][n]=fixed[m-1][n];
                    }
                    for(int z=0;z<10;z++)
                        fixed[0][z]=grid[0][z]=0;
                }
            }
        }
    } //quando criar pontuacao, tenho de dar return à quantidade de linhas limpas(max 4);

    game(){
        print_game();
        piece_gen(-1);
        print_game();
        thread t1(&game::piece_control, this ); //current_piece.load()
        thread t2(&game::gravity, this);
        t1.join();
        t2.join();
    }
    
};



class menu{
public:
    int state=0;
    void print_menu(){
        clear_screen();
        cout << endl<< endl << endl << endl << endl;
        cout <<     "                             ######  #######  ######  #####   ###   #####" << endl <<
                    "                               ##    ##         ##   ##  ##   ##   ##     " << endl <<
                    "                               ##    #####      ##   #####    ##    ####  " << endl <<
                    "                               ##    ##         ##   ##  ##   ##       ## "  << endl << 
                    "                               ##    #######    ##   ##   ##  ###  ###### " << endl << endl << endl << endl;
        switch(state){
            case 0:
                cout <<     "                                                -->PLAY" << endl;
                cout <<     "                                                   High Score" << endl;
                cout <<     "                                                   Quit" << endl;
                break;
            case 1:
                cout <<     "                                                   PLAY" << endl;
                cout <<     "                                                -->High Score" << endl;
                cout <<     "                                                   Quit" << endl;       
                break;
            case 2:
                cout <<     "                                                   PLAY" << endl;
                cout <<     "                                                   High Score" << endl;
                cout <<     "                                                -->Quit" << endl;
                break;
        }
    }

    int changestate(){
        int i=inputkey();
        switch(i){
            case 1:
                state+=2;
                break;
            case 3:
                state+=1;
                break;
            case 5:
                return 1;
        }    
        state%=3;
        return 0;
    }

    menu(){
        int enterkey=0;
        do{
            print_menu();
            enterkey=changestate();
        }   while(enterkey==0);
    }
};

class highscore{
    public:
    highscore(){
        int i;
        cout << endl<< endl << endl << endl << endl;
        cout << "                                    Esta função ainda não foi implementada";
        cout << endl<< endl << endl << endl << endl;
        cout << "                                                -->Go Back" << endl;
        i= inputkey();
        while(true) if(i==5) break;
    }
};
void aftergame(){
    int i;
    cout << endl<< endl << endl;
    cout << "you final score is XXXXX"; //tenho de criar alguma ficheiro externo para guardar os scores na appdata;
    cout << endl<< endl << endl; 
    cout << "                                                -->Go to Menu" << endl;
    i= inputkey();
    while(true) if(i==5) break;
}


int main(){
inicio:
    int t;
    menu m;
    clear_screen();
    if(m.state==0){
        game g;
        Sleep(500);
        aftergame();
        goto inicio;
    }
    else if(m.state==1){ //tenho de criar alguma ficheiro externo para guardar os scores na appdata;
        highscore h;
        goto inicio;
    }
    return 0;  
}