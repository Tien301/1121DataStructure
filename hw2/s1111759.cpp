#include <iostream>
#include <cstdlib>
#include <limits> // �ޤJ limits ���Y�ɮ�
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
            cout << "Heap���F!!! �z���F " << endl;
            cout << "�Y�N�����{��... \n" << endl;
            system("pause");
            exit(EXIT_FAILURE);  //�������� 
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
            cout << "Heap ���O�Ū�" << endl;
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
        cout << "Heap ���O�Ū�" << endl;
        return;
    }

    cout << "Heap ���ƭȵ��c�G" << endl;       //��heap�i�H�̷өҦb���h�L�X �AHeap�}�C�O�q0�}�l 

    int level = 1;
    int count = 0;
    for (int i = 0; i < size; ++i) {
    	
        if (i == count) {                //�ˬd�O�_�w�g��F�U�@�h���}�l��m�C
            cout << "\nlevel " << level << "�G ";
            level++;
            count = 2 * count + 1;      //count ���Ȫ�ܶi�J"�U�@�h"���}�l��m
        }                               //level 1 ���U�@�h(level 2)�}�l��m�N�O2*0+1 = 1�A�u�|�L�Ĥ@�Ӽƭ�  
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
        cout << "\n�i���檺(heap)�B��p�U�G\n";
        cout << "1. �s�W����(�̦h�x�s31�Ӽƭ�)\n2. �R����n���̤j��\n3. �C�L��Ӱ�n\n4. �����{��\n\n�п�J���:\n  ";

        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "��J�L�ġA�Э��s��J���: \n  ";
            cin.clear();                                                // ���b���� �A�� cin�Q���O�����~�u�Ѱ��v 
            cin.ignore( numeric_limits<streamsize>::max(),   '\n');    //�M�����b�w�İϸ̪��Ҧ����e�A�άO�J���1��'\n'����
        	
            
		}

        switch (choice) {
            case 1: {
                Element newItem;
                cout << "��J0�פ�s�W\n�п�J�n�s�W����: ";

                while (!(cin >> newItem.key) || newItem.key < 0) {
                    cout << "��J�L�ġA�Э��s��J�n�s�W����: ";
                    cin.clear();                                          // ���b���� �A�� cin�Q���O�����~�u�Ѱ��v  
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  //�M�����b�w�İϸ̪��Ҧ����e�A�άO�J���1��'\n'���� 
                	
				}

                while (newItem.key != 0) {
                    maxHeap.insert(newItem);
                    cout << "�п�J�n�s�W����: ";
                    while (!(cin >> newItem.key) || newItem.key < 0) {
                        cout << "��J�L�ġA�Э��s��J�n�s�W����: ";
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
                    cout << "�w�R���̤j�� " << deletedValue << endl;
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
                cout << "�{������" << endl;
                break;
            default:
                cout << "�L�Ī���ܡA�Э��s��J\n";
                system("pause");
                system("cls");
        }
    } while (choice != 4);

    return 0;
}

 
