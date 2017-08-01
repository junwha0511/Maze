#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define size 21
#define unDefined 0
#define wall 1
#define path 2
#define EAST 3
#define WEST 4
#define SOUTH 5
#define NORTH 6



int greed[size][size]={0};

void setWall(){
    int i=0,row,col;
    for(i=0; i<size; i++){
        greed[0][i] = wall; //왼쪽라인
        greed[size-1][i] = wall; //오른쪽라인
        greed[i][0] = wall; //상단라인
        greed[i][size-1] = wall; //하단라인
    }
    for(row=0; row<size; row+=2){
        for(col=0; col<size; col+=2){
            greed[row][col] = wall; //모서리 초기화
        }
    }
}
void makePath(int myX, int myY, int pathDirection){
    int directions[3] = {0};
    int i,j,k;
    for(k=0; k<3; k++){
        while(1){  
            int n = rand()%4+3;
            for(j=0; j<3; j++){
                if(n==directions[j] || n==pathDirection){
                    n = 0;
                    break;
                }
            }
            if(n!=0){
                directions[k] = n;
                break;
            }
        }
    }
    int checkX, checkY;
	int wallX, wallY;
	int nextDir;

	for(i=0; i<3; i++){
		checkX = myX;
		checkY = myY;
		wallX = myX;
		wallY = myY;

		switch(directions[i]){
			case EAST:
				checkX = myX + 2;
				wallX = myX + 1;
				nextDir = WEST;
				break;
			case WEST:
				checkX = myX - 2;
				wallX = myX - 1;
				nextDir = EAST;
				break;
			case SOUTH:
				checkY = myY - 2;
				wallY = myY - 1;
				nextDir = NORTH;
				break;
			case NORTH:
				checkY = myY + 2;
				wallY = myY + 1;
				nextDir = SOUTH;
				break;
		}

		if(0 < checkX && checkX < size && 0 < checkY && checkY < size){
			if(greed[checkX][checkY]==unDefined){
				greed[checkX][checkY] = path;
				makePath(checkX,checkY,nextDir);
			}else{
				greed[wallX][wallY] = wall;
			}
		}
	}
}
int main(){
    srand(time(NULL));
    int row,col;
    setWall();
    makePath(1,1,SOUTH);
    greed[2][1]=0;
    for(row=0;row<size;row++){
        for(col=0;col<size;col++){
            if(greed[col][row]==2||greed[col][row]==0){
                greed[col][row]=0;
            }
            printf((greed[col][row]==0)?"0":"1");
        }
        printf("\n");
    }
    return 0;
}
/* 21x21칸에서 벽공간 길공간 벽공간 길공간 벽공간의 형태로 되어있다.
   1.[0][0]의 블록부터 시작한다. 뱡향을 선택하고 그 방향으로 +2칸의 위치가 0인지, 1인지를 확인한다.
   2. 1일 경우 +1칸에 벽을 세운다. 그리고 다시 돌아와 다른 방향을 선택한다. 모든 방향을 처리하면 코드는 종료된다.[x(i)번째 줄의][y(j)번째 칸]
*/
