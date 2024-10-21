#include <iostream>
#include <cstring>
using namespace std;

template <class T> class Stack                                      //�w�q�@�ӳq�Ϊ�stack���O�C 
{                                                                   //�䤤 T �O�@�ӫ��O�ѼơA�N����|�i�H�x�s���P���O�������C 
	                                                                //��ܥi�H�Ыؤ@�� Stack ����A�ë��w�һݪ��������O�C  
    int top;
    int capacity;
    T *itemArray;                                                   //�� itemArray�O�����L���y��  

	public:
    Stack(const int StackCapacity = 17) : capacity(StackCapacity)   // �ʺA���t T ���O���}�C�A�j�p�� capacity 
	{
        itemArray = new T[capacity];                                // �ϥ� memset ��ƪ�l��itemArray���������� 0 
        memset(itemArray, 0, capacity * sizeof(T));
        top = -1;                                                   // �N top ��l�Ƭ� -1�A���Stack�S�F��
    }  

    ~Stack()  //�Ѻc�� 
	{
        delete[] itemArray;
    }

    bool IsEmpty() const 
	{
        return top == -1;
        /*�p�G top ���� -1�A���Stack�ŪšA�� return true�C
		�_�h�A�p�G top ������ -1�A���Stack���ܤ֦��@�Ӥ����Areturn false�C*/
    }

    T &Top() 
	{
        if (IsEmpty()) 
		{
            throw "Stack �O�Ū�!!\n";
        }
        
        return itemArray[top];
    }

    void Push(const T &next)                                         //stack ���O�� Push ���    
	{
        if (top == capacity - 1)                                     //���Stack�w�� 
		{
            T *tempArray = new T[2 * capacity];                      //�Ыؤ@�ӷs�� T ���O���A2���j�� tempArray
            memset(tempArray, 0, 2 * capacity * sizeof(T));          //�@�˥���l�ƩҦ������� 0
            memcpy(tempArray, itemArray, capacity * sizeof(T));      //�A��itemArray �����e�ƻs�� tempArray 
            
            delete[] itemArray;
            itemArray = tempArray;
            capacity *= 2;                                         
        }

        top += 1;
        itemArray[top] = next;                                       //itemArray�N�S���Ŷ��i�H�s�F 
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
    int X;       //�w�q�U�� Dir[8]���t�N �G{-1 ��X�y��, 0 ��Y�y��} 
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

int EXIT_ROW = 11;                    //���I���y�� 
int EXIT_COL = 15;

int main() 
{
    Stack<Position> stack;
    Position start(1, 1);  
    stack.Push(start);                //(1,1�O�_�I)             
    mark[1][1] = 1;                   //mark����(1,1)�w�g���L

    while (!stack.IsEmpty()) 
	{
    	
        Position now = stack.Top();    
        int row = now.X;
        int col = now.Y;
        int dir = 0;

        while (dir < 8) 
		{
            int nextRow = row + Dir[dir].X;                       //�U�@��X�y�ЬO�q current.X �[�W Dir[dir].X �Ӧ� 
            int nextCol = col + Dir[dir].Y;

            if (nextRow == EXIT_ROW && nextCol == EXIT_COL) 
			{                                                      //�U�@�B�N������I����  
                mark[nextRow][nextCol] = 1;                       //�����O�����I 
                stack.Push(Position(nextRow, nextCol));           //����Ipush��stack�̭� 
                break;                                            //����while (dir < 8)
            } 
            
			else if (maze[nextRow][nextCol] != 1 && mark[nextRow][nextCol] == 0)     ////�S���J�����(1)�Bmark�}�C���0(�٨S���L) 
			{
                mark[nextRow][nextCol] = 1;                       //mark�������L�F 
                stack.Push(Position(nextRow, nextCol));           //push �i�hStack�Atop���ܡA�W��now���Ȥ]�@�_�� 
                row = nextRow;
                col = nextCol;
                dir = 0;                                          // dir �k 0�A���X while(dir < 8) �~���U�@�B 
            } 
			else 
			{
                dir++;
            }
        }
        
         // ��X�g�c�� 
    	if (row == EXIT_ROW && col == EXIT_COL) 
		{                               
            cout << "�g�c���u�G\n" << "---------------------------------\n" ;
          
            for (int i = 0; i < 13; i++) 
			{
                for (int j = 0; j < 17; j++) 
				{
                    if (maze[i][j] == 1) 
                        cout << ". ";   //  ��� 
                    else if (mark[i][j] == 1) 
                        cout << "�� ";  // ���T����
                    else 
                        cout << "x ";   // �����q���� 
                }
                cout << endl;
            }
            
            break;  // ���X�f����X while (!stack.IsEmpty()) ������g�c 
        }
    }
}
   

