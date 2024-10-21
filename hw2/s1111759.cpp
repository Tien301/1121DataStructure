#include <iostream>
#include <cstdlib>
#include <limits> // 引入 limits 標頭檔案
using namespace std;

const int MAX_HEAP_SIZE = 31;
struct Element {
    int key;
};

class MaxHeap {
private:
    Element heap[MAX_HEAP_SIZE];
    int size=0;

public:
    

    void insert(Element item) {
        if (size == MAX_HEAP_SIZE) {
            cout << "Heap滿了!!! 爆掉了 " << endl;
            cout << "即將結束程式... \n" << endl;
            system("pause");
            exit(EXIT_FAILURE);  //結束執行 
        }

        int i = size++;
        while (i > 0 && item.key > heap[(i - 1) / 2].key) {
            heap[i] = heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        heap[i] = item;
    }

    int deleteMax() {
        if (size == 0) {
            cout << "Heap 內是空的" << endl;
            return -1;
        }

        Element item = heap[0];
        Element temp = heap[--size];

        int parent = 0;
        int child = 1;
        while (child < size) {
            if (child + 1 < size && heap[child].key < heap[child + 1].key) {
                ++child;
            }

            if (temp.key >= heap[child].key) {
                break;
            }

            heap[parent] = heap[child];
            parent = child;
            child = 2 * child + 1;
        }

        heap[parent] = temp;
        return item.key;
    }

    void printHeap() {
    if (size == 0) {
        cout << "Heap 內是空的" << endl;
        return;
    }

    cout << "Heap 內數值結構：" << endl;       //讓heap可以依照所在階層印出 ，Heap陣列是從0開始 

    int level = 1;
    int count = 0;
    for (int i = 0; i < size; ++i) {
    	
        if (i == count) {                //檢查是否已經到達下一層的開始位置。
            cout << "\nlevel " << level << "： ";
            level++;
            count = 2 * count + 1;      //count 的值表示進入"下一層"的開始位置
        }                               //level 1 的下一層(level 2)開始位置就是2*0+1 = 1，只會印第一個數值  
        cout << heap[i].key << " ";       
        
    }
    cout << endl;
}


    int getSize() const {
        return size;
    }
};

int main() {
    MaxHeap maxHeap;
    int choice;

    do {
        cout << "\n可執行的(heap)運算如下：\n";
        cout << "1. 新增元素(最多儲存31個數值)\n2. 刪除堆積的最大值\n3. 列印整個堆積\n4. 結束程式\n\n請輸入選擇:\n  ";

        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "輸入無效，請重新輸入選擇: \n  ";
            cin.clear();                                                // 防呆機制 ，把 cin被註記的錯誤「解除」 
            cin.ignore( numeric_limits<streamsize>::max(),   '\n');    //清除掉在緩衝區裡的所有內容，或是遇到第1個'\n'為止
        	
            
		}

        switch (choice) {
            case 1: {
                Element newItem;
                cout << "輸入0終止新增\n請輸入要新增的值: ";

                while (!(cin >> newItem.key) || newItem.key < 0) {
                    cout << "輸入無效，請重新輸入要新增的值: ";
                    cin.clear();                                          // 防呆機制 ，把 cin被註記的錯誤「解除」  
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  //清除掉在緩衝區裡的所有內容，或是遇到第1個'\n'為止 
                	
				}

                while (newItem.key != 0) {
                    maxHeap.insert(newItem);
                    cout << "請輸入要新增的值: ";
                    while (!(cin >> newItem.key) || newItem.key < 0) {
                        cout << "輸入無效，請重新輸入要新增的值: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                system("cls");
                break;
            }
            case 2: {
                int deletedValue = maxHeap.deleteMax();
                if (deletedValue != -1) {
                    cout << "已刪除最大值 " << deletedValue << endl;
                }
                system("pause");
                system("cls");
                break;
            }
            case 3:
                maxHeap.printHeap();
                cout << endl;
                system("pause");
                system("cls");
                break;
            case 4:
                cout << "程式結束" << endl;
                break;
            default:
                cout << "無效的選擇，請重新輸入\n";
                system("pause");
                system("cls");
        }
    } while (choice != 4);

    return 0;
}

 
