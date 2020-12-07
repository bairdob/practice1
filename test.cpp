#include <iostream>

using namespace std;
 
int main(){
    const int n1 = 8;
    const int n2 = 2; 
    const int m1 = 8;
    const int m2 = 3;
    int a[n1][m1] =  {
    {1, 2, 3, 4, 5, 6, 7, 8},
    {6, 3, 4, 5, 6, 7, 8, 9},
    {1, 7, 2, 9, 3, 7, 3, 2},
    {6, 2, 4, 5, 6, 7, 0, 2},
    {5, 3, 3, 7, 3, 2, 5, 2},
    {1, 8, 2, 5, 1, 9, 0, 0},
    {0, 9, 2, 5, 6, 7, 2, 1},
    {2, 0, 3, 0, 6, 2, 5, 7}
    };
    int b[n2][m2] ={
        {5,1,4},
        {3,6,7}
    };

    int k,l;//строка, столбец
    bool bad;
    for (int i = 0; i < n1 - n2;i++){
        for (int j = 0; j < m1-m2; j++){
            if (a[i][j] == b[0][0]) {
                
                bad = false;
                k = 0;
                 
                do {
                    l = 0 ; 
                    do {
                        l++;
                        if (a[i+k][j+l] != b[k][l]) bad = true;
                    } while (l > m2 && !bad);
                   k++;
                   if (a[i+k][j+l] != b[k][l]) bad = true;
                } while (k >n2 && !bad);
            if (!bad) cout << i +1<< ","<< j+1 << " ";        
            }
        
        }
        
    }


    return 0;
}    