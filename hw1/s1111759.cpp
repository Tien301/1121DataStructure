#include <iostream>
#include <cstring>
using namespace std;

template <class T> class Stack                                      //定義一個通用的stack類別。 
{                                                                   //其中 T 是一個型別參數，代表堆疊可以儲存不同型別的元素。 
	                                                                //表示可以創建一個 Stack 物件，並指定所需的元素型別。  
    int top;
    int capacity;
    T *itemArray;                                                   //用 itemArray記錄走過的座標  

	public:
    Stack(const int StackCapacity = 17) : capacity(StackCapacity)   // 動態分配 T 型別的陣列，大小為 capacity 
	{
        itemArray = new T[capacity];                                // 使用 memset 函數初始化itemArray中的元素為 0 
        memset(itemArray, 0, capacity * sizeof(T));
        top = -1;                                                   // 將 top 初始化為 -1，表示Stack沒東西
    }  

    ~Stack()  //解構用 
	{
        delete[] itemArray;
    }

    bool IsEmpty() const 
	{
        return top == -1;
        /*如果 top 等於 -1，表示Stack空空，並 return true。
		否則，如果 top 不等於 -1，表示Stack中至少有一個元素，return false。*/
    }

    T &Top() 
	{
        if (IsEmpty()) 
		{
            throw "Stack 是空的!!\n";
        }
        
        return itemArray[top];
    }

    void Push(const T &next)                                         //stack 類別的 Push 函數    
	{
        if (top == capacity - 1)                                     //表示Stack已滿 
		{
            T *tempArray = new T[2 * capacity];                      //創建一個新的 T 型別的，2倍大的 tempArray
            memset(tempArray, 0, 2 * capacity * sizeof(T));          //一樣先初始化所有元素為 0
            memcpy(tempArray, itemArray, capacity * sizeof(T));      //再把itemArray 的內容複製到 tempArray 
            
            delete[] itemArray;
            itemArray = tempArray;
            capacity *= 2;                                         
        }

        top += 1;
        itemArray[top] = next;                                       //itemArray就又有空間可以存了 
    }

    void Pop() 
	{
        itemArray[top--];
    }
};

class Position 
{
	public:
    Position() {}
    
    Position(int x, int y) 
	{
        X = x;
        Y = y;
    }
    int X;
    int Y;
};



int maze[13][17] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int mark[13][17] = {};

struct Dir 
{              
    int X;       //定義下面 Dir[8]的含意 ：{-1 指X座標, 0 指Y座標} 
    int Y;
};

Dir Dir[8] = {    
    {-1, 0}, // N
    {-1, 1}, // NE
    {0, 1},  // E
    {1, 1},  // SE
    {1, 0},  // S
    {1, -1}, // SW
    {0, -1}, // W
    {-1, -1} // NW
};

int EXIT_ROW = 11;                    //終點的座標 
int EXIT_COL = 15;

int main() 
{
    Stack<Position> stack;
    Position start(1, 1);  
    stack.Push(start);                //(1,1是起點)             
    mark[1][1] = 1;                   //mark紀錄(1,1)已經走過

    while (!stack.IsEmpty()) 
	{
    	
        Position now = stack.Top();    
        int row = now.X;
        int col = now.Y;
        int dir = 0;

        while (dir < 8) 
		{
            int nextRow = row + Dir[dir].X;                       //下一個X座標是從 current.X 加上 Dir[dir].X 而成 
            int nextCol = col + Dir[dir].Y;

            if (nextRow == EXIT_ROW && nextCol == EXIT_COL) 
			{                                                      //下一步就走到終點的話  
                mark[nextRow][nextCol] = 1;                       //直接記錄終點 
                stack.Push(Position(nextRow, nextCol));           //把終點push到stack裡面 
                break;                                            //結束while (dir < 8)
            } 
            
			else if (maze[nextRow][nextCol] != 1 && mark[nextRow][nextCol] == 0)     ////沒有遇到牆壁(1)且mark陣列顯示0(還沒走過) 
			{
                mark[nextRow][nextCol] = 1;                       //mark紀錄走過了 
                stack.Push(Position(nextRow, nextCol));           //push 進去Stack，top改變，上面now的值也一起變 
                row = nextRow;
                col = nextCol;
                dir = 0;                                          // dir 歸 0，跳出 while(dir < 8) 繼續找下一步 
            } 
			else 
			{
                dir++;
            }
        }
        
         // 輸出迷宮圖 
    	if (row == EXIT_ROW && col == EXIT_COL) 
		{                               
            cout << "迷宮路線：\n" << "---------------------------------\n" ;
          
            for (int i = 0; i < 13; i++) 
			{
                for (int j = 0; j < 17; j++) 
				{
                    if (maze[i][j] == 1) 
                        cout << ". ";   //  牆壁 
                    else if (mark[i][j] == 1) 
                        cout << "● ";  // 正確的路
                    else 
                        cout << "x ";   // 走不通的路 
                }
                cout << endl;
            }
            
            break;  // 找到出口後跳出 while (!stack.IsEmpty()) 結束找迷宮 
        }
    }
}
   

