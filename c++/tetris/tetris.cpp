#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string>
#include <string.h>
#define TETRIS_WIDETH 18 
#define TETRIS_HEIGHT 24 
#define TETRIS_PAUSE_MSG "Game Pause"
#define BASE_X 5 
#define BASE_Y 5 
#define RANDOM_MIN 0
#define RANDOM_MAX 6


bool god_flag = false;
pthread_mutex_t lock;

typedef enum COLOR_ { EMPTY=0, RED=10, GREEN, BLUE, YELLOW, PURPLE, BORDER } COLOR;
typedef enum BLOCK_TYPE_ { O=0, T, I, L, LM, N, NL} BLOCK_TYPE;
typedef enum ACTION_ { DOWN=0, LEFT, RIGHT, ROLL } ACTION;

void GamePause();

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
		void MoveRight() { ++position_x_; };
		void GetBLoc(int &x, int &y) { x=position_x_, y=position_y_;};
		void OverTurn();
		void ClearShape();
		void DrawShape();
		void EarseShape();
	private:
		int blocktype_;
		int blockcol;
		int position_x_;
		int position_y_;
};

void BlockShape::OverTurn() {
	int tmp[3][3];
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++){
			tmp[i][j] = (*block)[2-j][i];
		}
	}
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			(*block)[i][j] = tmp[i][j];
		}
	}
}

void BlockShape::ClearShape() {
	int tmp = blockcol;
	blockcol = EMPTY;
	Pixel p(blockcol);
	for (int i = 0; i < 3; i++) {
		for ( int j = 0; j < 3; j++) {
			p.SetPLoc(position_x_ + j, position_y_ + i);
    		p.DrawPixel();	
		}
	}
	blockcol = tmp;
}

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
	if (god_flag) { return (new BlockShape(BLUE, I)); }
	int type = RANDOM_MIN + rand() % (RANDOM_MAX - RANDOM_MIN +1); 
	return (new BlockShape(BLUE, type));
}

void GamePause() {
	int len = ((std::string)TETRIS_PAUSE_MSG).length();
	printf("\33[s");
	MoveLoc(9-2, (TETRIS_HEIGHT - 1) / 2);
	printf("Game Pause");		
	stop_flag = true;
	printf("\33[u");
}

void GameOver() {
	int len = ((std::string)TETRIS_PAUSE_MSG).length();
	printf("\33[s");
	MoveLoc(9-2, (TETRIS_HEIGHT - 1) / 2);
	printf("Game Over");		
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

/* The game board */
class TetrisMap {
	public:
		TetrisMap();
		~TetrisMap() {};
		void TetrisRun();
		void TetrisTrick(int);
		bool IsAttachLeft();
		bool IsAttachRight();
		bool IsGrounding();
		bool IsRoll();
		void UpdateMap();
		void CalcScore();
		void ScoreInfo();
		void BlockInfo();
		void OperInfo();
		void DrawMap();
		void TetrisRoll();
		static void *ListenKey(void *);
	private:
		int map[TETRIS_HEIGHT][TETRIS_WIDETH] = {0};
		BlockShape *cur_block;
		BlockShape *nxt_block;
		int score;
};

void TetrisMap::OperInfo() {
	printf("\033[s");
	MoveLoc(22, 11);
	printf("a: move left.");
	printf("\033[u");	
	printf("\033[s");
	MoveLoc(22, 13);
	printf("d: move right.");
	printf("\033[u");	
	printf("\033[s");
	MoveLoc(22, 15);
	printf("s: acceler");
	printf("\033[u");	
	printf("\033[s");
	MoveLoc(22, 17);
	printf("w: rotate");
	printf("\033[u");	
	printf("\033[s");
	MoveLoc(22, 19);
	printf("p: Game pasue   r: Game Continue");
	printf("\033[u");	
}

void TetrisMap::BlockInfo() {
	BlockShape *tmp_block = (BlockShape *)malloc(sizeof(BlockShape));
	memcpy(tmp_block, nxt_block, sizeof(BlockShape));
	tmp_block->SetBLoc(30, 5);
	tmp_block->ClearShape();
	printf("\033[s");
	MoveLoc(22, 6);
	printf("The next block:  ");
	printf("\033[u");	
	tmp_block->DrawShape();
	free(tmp_block);
}

void TetrisMap::ScoreInfo() {
	printf("\033[s");
	MoveLoc(22, 1);
	printf("Score: %d", score);
	printf("\033[u");	
}

bool TetrisMap::IsRoll() {
	int tmp[3][3];
	int pos_x, pos_y;
	cur_block->GetBLoc(pos_x, pos_y);	
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			tmp[i][j] = (*(cur_block->block))[2-j][i];
		}
	}
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (map[pos_y+i][pos_x+j] == 1 && tmp[i][j] == 1)
			{
				return false;
			}
		}
	} 
	return true;
}

void TetrisMap::TetrisRoll() {
	if (IsRoll()) {
	//	cur_block->EarseShape();
	//	cur_block->OverTurn();	
	//	cur_block->DrawShape();	
		TetrisTrick(ROLL);
	}
}

void TetrisMap::DrawMap() {
	Pixel p(GREEN);
	Pixel p1(EMPTY);
	for (int i = TETRIS_HEIGHT-2; i >= 1; i--){
		for (int j = 1; j < TETRIS_WIDETH - 1; j++){
			if ( map[i][j] == 1) {
				p.SetPLoc(j, i);
				p.DrawPixel();		
			} else {
				p1.SetPLoc(j, i);
				p1.DrawPixel();		
			}
		}
	}
}

void TetrisMap::CalcScore() {
	int level = 0;
	bool flag = true;
	for (int i = TETRIS_HEIGHT - 2; i >= 1; i--) {
		for (int j = 1; j < TETRIS_WIDETH - 1; j++) {
			if (map[i][j] == 0) {
				flag = false;
			}
		}
		if (flag) {
			for (int m = i; m >= 2; m--){
				for (int n = 1; n < TETRIS_WIDETH - 1; n++) {
					map[m][n] = map[m-1][n];
				}
			}
			i++;
			score++;
		}
		flag = true;
	}
	ScoreInfo();
}

bool TetrisMap::IsAttachRight() {
	int pos_x, pos_y;
	cur_block->GetBLoc(pos_x, pos_y);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if((*(cur_block->block))[j][i] == 1 && map[ pos_y + j] [pos_x + i + 1] == 1) {
				return true;
			}
		}
	}
	return false;
}

bool TetrisMap::IsAttachLeft() {
	int pos_x, pos_y;
	cur_block->GetBLoc(pos_x, pos_y);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if((*(cur_block->block))[j][i] == 1 && map[ pos_y + j] [pos_x + i - 1] == 1) {
				return true;
			}
		}
	}
	return false;
}

void * TetrisMap::ListenKey(void *context) {
	while(1) {
		char key;
		system("stty -icanon -echo");
		scanf("%c", &key);
		system("stty icanon echo");
		switch(key) {
			case 'a': ((TetrisMap *)context)->TetrisTrick(LEFT); break;
			case 'd': ((TetrisMap *)context)->TetrisTrick(RIGHT); break;
			case 'w': ((TetrisMap *)context)->TetrisRoll(); break;
			case 's': ((TetrisMap *)context)->TetrisTrick(DOWN); break;
			case 'm': god_flag = false; break;
			case 'n': god_flag = true; break;
			case 'p': GamePause(); break;
			case 'r': GameContin(); break;
			case 'x': exit(1);
			default: break;
		}
	}
	return NULL;
}

void TetrisMap::UpdateMap() {
	int pos_x, pos_y;
	cur_block->GetBLoc(pos_x, pos_y);
	for (int i = 2; i >= 0; i--) {
		for (int j = 2; j >= 0; j--) {
			map[pos_y+i][pos_x+j] += (*(cur_block->block))[i][j];
			if(map[pos_y+i][pos_x+j] > 1) {
				GameOver();
				system("stty icanon echo");
				exit(0);
			}
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
		TetrisTrick(DOWN);
	}
}


void TetrisMap::TetrisTrick(int action) {
	if (stop_flag){ return;}
	/* earse */
	pthread_mutex_lock(&lock);
	cur_block->EarseShape();
	switch(action) {
		case DOWN: {
			if ( IsGrounding() == false ) {
				cur_block->MoveDown();	
				cur_block->DrawShape();
			} else {
				UpdateMap();
				BlockInfo();
				CalcScore();
				DrawMap();
			}
			break;
		}
		case LEFT: {
			if ( IsAttachLeft() == false ) {
				cur_block->MoveLeft();
			}
			cur_block->DrawShape();
			break;
		}
		case RIGHT: {
			if ( IsAttachRight() == false ) {
				cur_block->MoveRight();
			}
			cur_block->DrawShape();
			break;
		}
		case ROLL: {
			cur_block->OverTurn();	
			cur_block->DrawShape();	
			break;
		}
	}
	pthread_mutex_unlock(&lock);
}


TetrisMap::TetrisMap():score(0),cur_block(GetRandomShape()),nxt_block(GetRandomShape()) {
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
	ScoreInfo();
	BlockInfo();
	OperInfo();
}


int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));
	pthread_t listen_task;
	system("clear");
	TetrisMap bamboo;
	pthread_create(&listen_task, NULL, &TetrisMap::ListenKey, &bamboo);
	bamboo.TetrisRun();
	return 0;
}
