#include<stdio.h>
#include<stdlib.h>

#define size 21

 #define EAST 3
 #define WEST 4
 #define SOUTH 5
 #define NORTH 6

int unDefined = 0;
int wall=1;
int path=2;

// int east=3;
// int west=4;
// int south=5;
// int north=6;

int greed[size][size]={0};

// int setDirection(int pathDirection){
//     int direction = rand()%4+2;
//     while(1){
//         if(direction==pathDirection){
//             direction = rand()%4+2;
//         }
//         else{
//             break;
//         }
//     }
//     return direction;
// 
void setWall(){
    int i=0;
    for(i=0;i<size;i++){
        greed[0][i]=wall; //상단라인
        greed[size-1][i]=wall; //하단라인
        greed[i][0]=wall; //왼쪽라인
        greed[i][size-1]=wall; //오른쪽라인
    }
    for(i=0;i<size;i+=2){
        for(int j=0;j<size;j+=2){
            greed[i][j]=wall; //모서리 초기화
        }
    }
}
int* randomDirection(int myDirection){
    int static directions[3]={0};
    int i,k;
    for(k=0; k<3; k++){
        while(1){  
            int n=rand()%4+3;
            for(i=0;i<3;i++){
                if(n==directions[i]||n==myDirection){
                    n=0;
                    break;
                }
            }
            if(n!=0){
                directions[k]=n;
                printf("%d\n",directions[k]);
                break;
            }
        }
    }
    
    return directions;
}
void makePath(int myX,int myY,int pathDirection){
    int *directions=randomDirection(pathDirection);
    for(int i=0;i<3;i++){
        switch(directions[i]){
            case EAST:
                if(myX+2<21){
                    if(greed[myX+2][myY]==unDefined){
                        greed[myX+2][myY]=path;
                        makePath(myX+2,myY,WEST);
                    }else{ //if(greed[myX+2][myY]==path)
                        greed[myX+1][myY]=wall;
                    }
                }
                break;
            case WEST:
                if(myX-2>0){
                    if(greed[myX-2][myY]==unDefined){
                        greed[myX-2][myY]=path;
                        makePath(myX-2,myY,EAST);
                    }else{ //if(greed[myX-2][myY]==path)
                        greed[myX-1][myY]=wall;
                    }
                }
                break;
            case SOUTH:
                if(myY-2>0){
                    if(greed[myX][myY-2]==unDefined){
                        greed[myX][myY-2]=path;
                        makePath(myX,myY-2,NORTH);
                    }else{ //if(greed[myX][myY-2]==path)
                        greed[myX][myY-1]=wall;
                    }
                }
                break;
            case NORTH:
                if(myY+2<21){
                    if(greed[myX][myY+2]==unDefined){
                        greed[myX][myY+2]=path;
                        makePath(myX,myY+2,SOUTH);
                    }else{ //if(greed[myX][myY+2]==path)
                        greed[myX][myY+1]=wall;
                    }
                }
                break;
        }
    }
}
int main(){
    setWall();
    makePath(1,1,SOUTH);
    return 0;
}
/* 21x21칸에서 벽공간 길공간 벽공간 길공간 벽공간의 형태로 되어있다.
   1.[0][0]의 블록부터 시작한다. 뱡향을 선택하고 그 방향으로 +2칸의 위치가 0인지, 1인지를 확인한다.
   2. 1일 경우 +1칸에 벽을 세운다. 그리고 다시 돌아와 다른 방향을 선택한다. 모든 방향을 처리하면 코드는 종료된다.[x(i)번째 줄의][y(j)번째 칸]
*/
