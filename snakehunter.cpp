#include<iostream>
#include <cstdlib> 
#include <ctime>
#include <conio.h> // Nhớ thêm thư viện này ở đầu file để dùng _kbhit() và _getch()
#include<windows.h>

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
    int x = width/2;
    int y = height/2;
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
void move(Snake* ran) {
    // 1. Cập nhật tọa độ cho phần thân (chạy ngược từ đuôi lên đầu)
    for (int k = ran->length - 1; k > 0; k--) {
        ran->sn[k] = ran->sn[k - 1];
    }

    // 2. Cập nhật tọa độ cho đầu rắn dựa vào hướng "durex"
    if (ran->durex == 'd') {          // Sang phải
        ran->sn[0].x++;
    } else if (ran->durex == 'a') {   // Sang trái
        ran->sn[0].x--;
    } else if (ran->durex == 'w') {   // Đi lên (trong console, càng lên trên y càng giảm)
        ran->sn[0].y--;
    } else if (ran->durex == 's') {   // Đi xuống (càng xuống dưới y càng tăng)
        ran->sn[0].y++;
    }
}
bool checkWall(Snake* ran, int width, int height) {
    Point dau = ran->sn[0];
    
    // Nếu đầu chạm vào tường bao quanh
    if (dau.x <= 0 || dau.x >= width - 1 || dau.y <= 0 || dau.y >= height - 1) {
        return true; // Bị đâm tường
    }
    for(int l = 2; l < ran->length; l++){
        if(ran->sn[0].x == ran->sn[l].x &&ran->sn[0].y == ran->sn[l].y){
            return true;
        }
    }
    return false; // Vẫn an toàn
}

void input(Snake* ran) {
    if (_kbhit()) { // Nếu người chơi có bấm phím
        char key = _getch(); // Lấy phím đó ra
        
        // Kiểm tra và đổi hướng (chặn quay đầu 180 độ)
        if (key == 'w' && ran->durex != 's') {
            ran->durex = 'w';
        } else if (key == 's' && ran->durex != 'w') {
            ran->durex = 's';
        } else if (key == 'a' && ran->durex != 'd') {
            ran->durex = 'a';
        } else if (key == 'd' && ran->durex != 'a') {
            ran->durex = 'd';
        }
    }
}
void eatFood(Snake*ran, Point* moi, int width, int height){
    if(ran->sn[0].x == moi->x && ran->sn[0].y == moi->y){
        ran->length++;
        position(moi, width, height);
    }
}

int main(){
    int width = 30;
    int height = 10; 
    srand(time(0));   
    Point moi;
    position(&moi, width, height);
    Snake ran;
    init(&ran, width, height);
    COORD coord;
    coord.X = 0, coord.Y = 0;
    CONSOLE_CURSOR_INFO cursor;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(handle, &cursor); // Lấy thông tin con trỏ hiện tại
    cursor.bVisible = false;
    while(true){
        SetConsoleCursorPosition(handle, coord);
        SetConsoleCursorInfo(handle, &cursor);
        bounder(moi, width, height, &ran);
        input(&ran);
        move(&ran);
        eatFood(&ran, &moi, width, height);
        if (checkWall(&ran, width, height)){
            system("cls"); // Xóa màn hình game đi
            cout << "=========================" << endl;
            cout << "   GAME OVER X_X !!!     " << endl;
            cout << "=========================" << endl;
            break; // Thoát vòng lặp, kết thúc game
        }
        Sleep(150);
    }
    system("pause");
    return 0;
}