#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <string>
#define TETRIS_WIDETH 18
#define TETRIS_HEIGHT 24
#define TETRIS_PAUSE_MSG "Game Pause"
#define BASE_X 5
#define BASE_Y 5

typedef enum COLOR_ { EMPTY=0, RED=10, GREEN, BLUE, YELLOW, PURPLE, BORDER } COLOR;
typedef enum BLOCK_TYPE_ { O, T, I, L, LM, N, NL} BLOCK_TYPE;

bool stop_flag = false;
int blocks[7/* kind */][3][3] = {
    // square
    {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0}
    },
    // T Shape
    {
        {1, 1, 1},
        {0, 1, 0},
        {0, 0, 0}
    },
    // I Shape
    {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    },
    // L Shape
    {
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 0}
    },
    // LM Shape
    {
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0}
    },
    // N Shape
    {
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0}
    },
    // NM Shape
    {
        {0, 1, 0},
        {1, 1, 0},
        {1, 0, 0}
    }
};

void MoveLoc(int x, int y);

class Pixel {
    public:
        Pixel(): x_(0), y_(0),color((COLOR)0) {};
        Pixel(int col): color((COLOR)col), x_(0), y_(0) {};
        Pixel(int col, int x, int y): x_(x), y_(y),color((COLOR)col) {};
        ~Pixel() {};
        void operator ()(int col, int x, int y) { x_ = x, y_ = y, color = (COLOR)col; };
        void DrawPixel();
        void SetPColor(int col) { color = (COLOR)col; };
        void SetPLoc(int x, int y) { x_ = x; y_ = y;};
        void GetPLoc(int *x, int *y) { *x = x_; *y = y_; };
        friend void MoveLoc(int x, int y);
    private:
        COLOR color;
        int x_;
        int y_;
};

void MoveLoc(int x, int y) {
    for ( int i = 0; i < y + BASE_Y; i++)
        printf("\33[1B");
    for (int i = 0; i < x + BASE_X; i++)
        printf("\33[2C");
}


void Pixel::DrawPixel() {
    printf("\33[s");
    MoveLoc(x_, y_);
    switch(color) {
        case RED: printf("\033[47;31m\u25A0\033[0m"); break;
        case GREEN: printf("\033[47;32m\u25A0\033[0m"); break;
        case BLUE: printf("\033[47;34m\u25A0\033[0m"); break;
        case YELLOW: printf("\033[47;33m\u25A0\033[0m"); break;
        case PURPLE: printf("\033[47;35m\u25A0\033[0m"); break;
        case EMPTY: printf("\33[8m  "); break;
        case BORDER: printf("\033[46;36m\u25A0\033[0m"); break;
        default: break;
    }
    printf("\33[u");
}

/* The Game Block */
class BlockShape {
    public:
        int (*block)[3][3] = NULL;
        BlockShape():block(&blocks[O]), blockcol(11), blocktype_(0), position_x_(TETRIS_WIDETH/2 - 1), position_y_(1) {};
        // constructor param color, type, position_x, position_y
        BlockShape(int col, int type): blockcol(col), blocktype_(type), position_x_(TETRIS_WIDETH/2 - 1), position_y_(1) { block = &blocks[blocktype_];};
        ~BlockShape() {};
        void SetBLoc(int x, int y) { position_x_ = x; position_y_ = y;};
        void MoveDown() { ++position_y_; };
        void MoveLeft() { --position_x_; };
        void MoveRight() { ++position_y_; };
        void GetBLoc(int &x, int &y) { x=position_x_, y=position_y_;};
        void DrawShape();
        void EarseShape();
    private:
        int blocktype_;
        int blockcol;
        int position_x_;
        int position_y_;
};


void BlockShape::EarseShape() {
    int tmp = blockcol;
    blockcol = EMPTY;
    DrawShape();
    blockcol = tmp;
}

void BlockShape::DrawShape() {
    Pixel p(blockcol);
    for (int i = 0; i < 3; i++) {
        for ( int j = 0; j < 3; j++) {
            if ((*block)[i][j] == 1) {
                p.SetPLoc(position_x_ + j, position_y_ + i);
                p.DrawPixel();
            }
        }
    }
}

BlockShape * GetRandomShape() {
    return (new BlockShape(BLUE, I));
}


/* The game board */
class TetrisMap {
    public:
        TetrisMap();
        ~TetrisMap() {};
        void TetrisRun();
        void TetrisTrick();
        bool IsGrounding();
        void UpdateMap();
    private:
        int map[TETRIS_HEIGHT][TETRIS_WIDETH] = {0};
        BlockShape *cur_block;
        BlockShape *nxt_block;
};

void TetrisMap::UpdateMap() {
    int pos_x, pos_y;
    cur_block->GetBLoc(pos_x, pos_y);
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            map[pos_y+i][pos_x+j] = (*(cur_block->block))[i][j];
            }
        }
    delete cur_block;
    cur_block = nxt_block;
    nxt_block = GetRandomShape();
    cur_block->DrawShape();
}

bool TetrisMap::IsGrounding() {
    int pos_x, pos_y;
    cur_block->GetBLoc(pos_x, pos_y);
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            if((*(cur_block->block))[i][j] == 1 && map[ pos_y + i + 1] [pos_x + j] == 1) {
                return true;
            }
        }
    }
    return false;
}


void TetrisMap::TetrisRun() {
    while(1) {
        fflush(stdout);
        usleep(500000);
        TetrisTrick();
    }
}


void TetrisMap::TetrisTrick() {
    if (stop_flag){ return;}
    /* earse */
    cur_block->EarseShape();
    if ( IsGrounding() == false ) {
        cur_block->MoveDown();
        cur_block->DrawShape();
    } else {
        cur_block->DrawShape();
        UpdateMap();
    }
}


TetrisMap::TetrisMap():cur_block(GetRandomShape()),nxt_block(GetRandomShape()) {
    Pixel p;
    for (int i = 0; i < TETRIS_HEIGHT; i++) {
        map[i][0] = 1;
        p(BORDER, 0, i);
        p.DrawPixel();
        map[i][TETRIS_WIDETH - 1] = 1;
        p(BORDER, TETRIS_WIDETH-1, i);
        p.DrawPixel();
    }
    for (int i = 0; i < TETRIS_WIDETH; i++) {
        map[0][i] = 1;
        p(BORDER, i, 0);
        p.DrawPixel();
        map[TETRIS_HEIGHT - 1][i] = 1;
        p(BORDER, i, TETRIS_HEIGHT-1);
        p.DrawPixel();
    }
    cur_block->DrawShape();
}


void GamePause() {
    int len = ((std::string)TETRIS_PAUSE_MSG).length();
    printf("\33[s");
    MoveLoc(9-2, (TETRIS_HEIGHT - 1) / 2);
    printf("Game Pause");
    stop_flag = true;
    printf("\33[u");
}

void GameContin() {
    stop_flag = false;
    printf("\33[s");
    MoveLoc(9-2, (TETRIS_HEIGHT - 1) / 2);
    printf("\33[8m          ");
    printf("\33[u");

}

void * ListenKey(void *) {
    while(1) {
        char key;
        system("stty -icanon -echo");
        scanf("%c", &key);
        system("stty icanon echo");
        switch(key) {
            case 'p': GamePause(); break;
            case 'r': GameContin(); break;
            case 'x': exit(1);
            default: break;
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    pthread_t listen_task;
    pthread_mutex_t lock;
    system("clear");
    TetrisMap bamboo;
    pthread_create(&listen_task, NULL, ListenKey, NULL);
    bamboo.TetrisRun();
    return 0;
}
