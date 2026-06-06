#include<iostream>
#include <cstdlib> 
#include <ctime>

using namespace std;
struct Point{
    int x, y;
};
struct Snake{
    Point sn[100];
    int length;
    char durex; 
};
void init(Snake*ran, int width, int height){
    ran->length = 3 ;
    int x = rand() % (width - 4) + 1;
    int y = rand() % (height - 2) + 1;
    ran->sn[0].x = x + 2;
    ran->sn[0].y = y;
    ran->sn[1].x = x + 1;
    ran->sn[1].y = y;
    ran->sn[2].x = x ;
    ran->sn[2].y = y;
    ran->durex ='d';
}
void position(Point* moi, int width, int height){
    
    moi->x = rand() % (width - 2) + 1;
    moi->y = rand() % (height - 2) + 1;
}

string check(int width, int height,int i, int j, Point moi, Snake* ran){
    if(i == 0 || j == 0 || i == height - 1 || j == width - 1){
        //khung 
        return "+ ";
    }
    if( i  == moi.y && j == moi.x){
        return "* ";
    }
    Point dau = ran->sn[0];
    if(dau.x ==j && dau.y == i) return "O ";
    for(int k = 1; k<ran->length; k++){
        Point direct = ran->sn[k];
        int x = direct.x;
        int y = direct.y;
        if(direct.x ==j && direct.y == i) return "o ";
    }
    return "  ";    
}

void bounder(Point moi, int width, int height, Snake*ran ){
    for( int i = 0; i < height ;i++){
        for( int j = 0; j < width; j++){
            string prt = check(width, height, i, j, moi, ran);
            cout << prt;
        }
        // check = 1 +, 2 * ,3(dau) O
        cout<< endl;
    }
}

int main(){
    int width = 10;
    int height = 7; 
    srand(time(0));   
    Point moi;
    position(&moi, width, height);
    Snake ran;
    init(&ran, width, height);
    bounder(moi, width, height, &ran);
}