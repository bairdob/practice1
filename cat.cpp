// cat.cpp
// https://ru.wikipedia.org/wiki/BMP#BITMAPFILEHEADER
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <optional>
#include <vector>
using namespace std;
const int SIZE = 64;

static unsigned short read_u16(FILE* pFile){
    unsigned char b0, b1;
    b0 = getc(pFile);
    b1 = getc(pFile);
    return ((b1 << 8) | b0);
}

static unsigned int read_u32(FILE* pFile){
    unsigned char b0, b1, b2, b3;
    b0 = getc(pFile);
    b1 = getc(pFile);
    b2 = getc(pFile); 
    b3 = getc(pFile);
    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

static int read_s32(FILE* pFile){
    unsigned char b0, b1, b2, b3;
    b0 = getc(pFile);
    b1 = getc(pFile);
    b2 = getc(pFile);
    b3 = getc(pFile);
    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

typedef struct
{
    int   rgbBlue;
    int   rgbGreen;
    int   rgbRed;
    int   rgbReserved;
} RGBQUAD;

//____________
int part_binary(int n){ //part of binary number 
    if (n >= 0 && n < 64 ) return 0;
        else if (n >= 64 && n <128) return 1;
            else if (n >= 128 && n <192) return 10; //0b
                else if (n >= 192 && n <256) return 11;//10
                    else return -1;
}

class image{
private:
    int Size; //filesize
    int Width;
    int Height;
    int BitCount;//bits per pixel
    int Compression; // if 0    Storage of pixels - array[][]
    RGBQUAD **rgb;
    //указатель или массив статический?
     
public:
    int **color;
    int Gist[SIZE];
    int oGist[SIZE];//гисторграмма процентная
    image(){
        for (int i = 0; i < SIZE; i++) {Gist[i]=0; oGist[i]=0;}
    };
    void fill(FILE* pFile){
        Size = setSize(pFile);
        Width = setWidth(pFile);
        Height = setHeight(pFile);
        BitCount = setBitCount(pFile);
        Compression = setCompression(pFile);
        rgb = data(pFile);
        color = color_arr(pFile);
        gist();
        o_gist();
    };
    // int my_Size(FILE *pFile){//считывание из памяти напрямую почему не работает с другими?
    //     fpos_t position = 2;
    //     fsetpos(pFile,&position);
    //     return read_s32(pFile);
    // }
    // int my_Width(FILE *pFile){
    //     fpos_t position = 18;
    //     fsetpos(pFile,&position);
    //     return read_s32(pFile);
    // }
    // int my_Height(FILE *pFile){
    //     fpos_t position = 22;
    //     fsetpos(pFile,&position);
    //     return read_s32(pFile);
    // }

    // int my_BitCount(FILE *pFile){
    //     fpos_t position = 28;
    //     fsetpos(pFile,&position);
    //     return read_u16(pFile);
    // }

    // int my_Compression(FILE *pFile){
    //     fpos_t position = 30;
    //     fsetpos(pFile,&position);
    //     return read_u32(pFile);
    // }
    // int my_Offset(FILE *pFile){
    //     fpos_t position = 10;
    //     fsetpos(pFile,&position);
    //     return read_u32(pFile);
    // }
    int getWidth(){return Width;}
    int getHeight(){return Height;}
    friend int getWidth(image &p);
    friend int getHeight(image &p);
    friend int getColor(image &p, int x, int y);
    int setSize(FILE *pFile){
        read_u16(pFile); 
        return read_u32(pFile);
    }

    int setWidth(FILE *pFile){
        read_u16(pFile);
        read_u16(pFile);
        read_u32(pFile);
        read_u32(pFile);
        return read_s32(pFile);
    }

    int setHeight(FILE *pFile){
        return read_s32(pFile);
    }

    int setBitCount(FILE *pFile){
        read_u16(pFile);
        return read_u16(pFile);
    }

    int setCompression(FILE *pFile){
       
        return read_u32(pFile);
    }

    void pass(FILE *pFile){
        read_u32(pFile);
        read_s32(pFile);
        read_s32(pFile);
        read_u32(pFile);
        read_u32(pFile);
    }

    void show(){
        cout << "Size = "<< Size << "\t"<< Width << " x " << Height << "\tbitCount = " << BitCount <<"\tCompression = "<< Compression << endl;
    };

    RGBQUAD **data(FILE *pFile){
        //pass(pFile);
        // fpos_t position = 54;
        // fsetpos(pFile,&position);
        RGBQUAD **rgb = new RGBQUAD*[Width];
        for (int i = 0; i < Width; i++) {
            rgb[i] = new RGBQUAD[Height];
        }
        for (int i = 0; i < Width; i++) {
            for (int j = 0; j < Height; j++) {
                rgb[i][j].rgbBlue = getc(pFile);
                rgb[i][j].rgbGreen = getc(pFile);
                rgb[i][j].rgbRed = getc(pFile);
            }
        // пропускаем последний байт в строке
        getc(pFile);
        }
        return rgb;
    }

    int **color_arr (FILE *pFile){
        int **color = new int*[Width];
        for (int i = 0; i < Width; i++) {
            color[i] = new int[Height];
        }

        for (int i = 0; i < Width; i++) {
            for (int j = 0; j < Height; j++) {
                color[i][j] = 0;
                color[i][j] +=  (part_binary(rgb[i][j].rgbBlue) / 10) * pow(2, 1) + (part_binary(rgb[i][j].rgbBlue)%10) * pow(2,0);
                color[i][j] +=  (part_binary(rgb[i][j].rgbGreen) / 10) * pow(2, 3) + (part_binary(rgb[i][j].rgbGreen)%10) * pow(2,2);
                color[i][j] +=  (part_binary(rgb[i][j].rgbRed) / 10) * pow(2, 5) + (part_binary(rgb[i][j].rgbRed)%10) * pow(2,4);
            }
        
        }
        return color;
    }

    void showrgb(){
        for (int i = 0; i < Width; i++) {
            for (int j = 0; j < Height; j++) {
                printf("%d %d %d\n", rgb[i][j].rgbRed, rgb[i][j].rgbGreen, rgb[i][j].rgbBlue);
            }
        printf("\n");
        }
    }

    void showcolor(){
        for (int i = 0; i < Width; i++) {
            for (int j = 0; j < Height; j++) {
                printf("%d\n", color[i][j]);
            }
        printf("\n");
        }
    }

    void gist(){
        //for (int k = 0; k < SIZE; k++) { //более оптимальное заполнение гистограммы без 1 цикла
            for (int i = 0; i < Width; i++) {
                for (int j = 0; j < Height; j++) {
                    //if (color[i][j] == k) Gist[k]++;
                    Gist[color[i][j]]++;
                }
            }
        //}
    }

    void o_gist(){
        int size = Width * Height * 0.01;
        for (int i = 0; i < Width; i++){
            for (int j = 0; j < Height; j++){
                oGist[color[i][j]]++;
            }
        }
        for (int i = 0; i < SIZE; i++){
                oGist[i] /= size;
        }
    }    

    void show_gist_data(){
        int cnt = 0;
        for (int i = 0; i < SIZE; i++) {cout << i << "-"<< Gist[i] << " ";cnt+=Gist[i];}
        cout << " all = "<<cnt <<endl;
    }

    void show_o_gist_data(){
        int cnt = 0;
        for (int i = 0; i < SIZE; i++) {cout << i << "-"<< oGist[i] << " ";cnt+=oGist[i];}
        cout << " all = "<<cnt <<endl;
    }

    void show_gist(){
        for (int i = 0; i < SIZE; i++){
            cout << i <<"| ";
                for (int j = 0; j < Gist[i]; j++){
                    cout << "* ";
                }
            cout << endl;
        }
    }
void fill_one(int* coord,int nine[9][64]){
    cout << coord[14] << "x" << coord[15]-1<< endl;
    for (int i = coord[0]; i < coord[3];i++){//1
        for (int j = coord[0]; j < coord[5];j++){
            nine[0][color[i][j]]++;
        }
    }
    for (int i = coord[3]; i < coord[5]-1;i++){//3
        for (int j = coord[5]; j < 259;j++){//warning
            nine[3][color[i][j]]++;
        }
    }    
    for (int i = coord[14]; i < coord[14]+63;i++){//8
        for (int j = coord[15]; j < coord[15]+128;j++){
            nine[7][color[i][j]]++;
        }
    }      
}
   
};
void fill_coord(int *coord, image *img){//заполняем координаты углов прямоугольников отсчет с левого верхнего 
    coord[0]=0; coord[1]=0; //1
    coord[2]=0; coord[3]=img->getWidth()/4;  //2
    coord[4]=0; coord[5]=img->getWidth()/2;//3
    coord[6]=img->getHeight()/4; coord[7]=0;  //4
    coord[8]=img->getHeight()/4; coord[9]=img->getWidth()/4;   //5
    coord[10]=img->getHeight()/4; coord[11]=img->getHeight()/4; //6
    coord[12]=img->getHeight()/2; coord[13]=0;    //7
    coord[14]=img->getHeight()/2; coord[15]=img->getWidth()/4; //8
    coord[16]=img->getHeight()/2; coord[17]=img->getWidth()/2;    //9
}
double lenght(const int *arr1,const int *arr2){
    long long summ = 0;//ll
    for (int i = 0; i < SIZE; i++) 
        summ += pow (arr1[i]- arr2[i],2);
    return sqrt(summ);
}
bool is_match(const int *original,const int *arr2){
    double cnt = 0; //процент совпадения
    for (int i = 1; i < SIZE; i++){
        if (original[i] >= arr2[i]) {cnt++ ;}
            //else cout << i << " ";
    }   
    cnt = cnt / SIZE * 100;
    //cout << cnt << " ";
    if (cnt >= 92) return true;
        else return false;
}

int getWidth(image &p){
    return p.Width;
};
int getHeight(image &p){
    return p.Height;
};

typedef struct {
    int   x;
    int   y;
} decart;

typedef struct {
    decart   top_left;
    decart   bottom_right;
    int gist[64] = {0};
} angle;

void fill_angle(angle *coord, int width, int height){
    coord[0].top_left.x = 0; //1
    coord[0].top_left.y = 0; 
    coord[0].bottom_right.x = coord[0].top_left.x + width / 2 ; 
    coord[0].bottom_right.y = coord[0].top_left.y  + height / 2;

    coord[1].top_left.x = width / 4; //2
    coord[1].top_left.y = 0;  
    coord[1].bottom_right.x = coord[1].top_left.x + width / 2 ; 
    coord[1].bottom_right.y = coord[1].top_left.y  + height / 2;

    coord[2].top_left.x = width / 2; //3
    coord[2].top_left.y = 0; 
    coord[2].bottom_right.x = coord[2].top_left.x + width / 2 ; 
    coord[2].bottom_right.y = coord[2].top_left.y  + height / 2;

    coord[3].top_left.x = 0; //4
    coord[3].top_left.y = height / 4; 
    coord[3].bottom_right.x = coord[3].top_left.x + width / 2 ; 
    coord[3].bottom_right.y = coord[3].top_left.y  + height / 2;

    coord[4].top_left.x = width / 4; //5
    coord[4].top_left.y = height / 4; 
    coord[4].bottom_right.x = coord[4].top_left.x + width / 2 ; 
    coord[4].bottom_right.y = coord[4].top_left.y  + height / 2;

    coord[5].top_left.x = width / 2; //6
    coord[5].top_left.y = height / 4; 
    coord[5].bottom_right.x = coord[5].top_left.x + width / 2 ; 
    coord[5].bottom_right.y = coord[5].top_left.y  + height / 2;

    coord[6].top_left.x = 0; //7
    coord[6].top_left.y = height / 2; 
    coord[6].bottom_right.x = coord[6].top_left.x + width / 2 ; 
    coord[6].bottom_right.y = coord[6].top_left.y  + height / 2;

    coord[7].top_left.x = width / 4; //8
    coord[7].top_left.y = height / 2; 
    coord[7].bottom_right.x = coord[7].top_left.x + width / 2 ; 
    coord[7].bottom_right.y = coord[7].top_left.y  + height / 2;    

    coord[8].top_left.x = width / 2; //9
    coord[8].top_left.y = height / 2; 
    coord[8].bottom_right.x = coord[8].top_left.x + width / 2 ; 
    coord[8].bottom_right.y = coord[8].top_left.y  + height / 2; 
 }

 void fill_angle_gist(image &img, angle &rectangle){
    for (int i = rectangle.top_left.x; i < rectangle.bottom_right.x;i++){//1
        for (int j = rectangle.top_left.y; j < rectangle.bottom_right.y;j++){
            rectangle.gist[img.color[i][j]]++;
        }
    }

    //cout << (rectangle.bottom_right.x - rectangle.top_left.x) << "x" <<(rectangle.bottom_right.y - rectangle.top_left.y)<< " ";

    //ogist
    // int size = (rectangle.bottom_right.x - rectangle.top_left.x) * 
    //     (rectangle.bottom_right.y - rectangle.top_left.y) * 0.01;
    // for (int i = 0; i < SIZE; i++){
    //     rectangle.gist[i] /= size;
    // }    
 }

 int getColor(image &p, int x, int y){
    return p.color[x][y];
 }
optional<pair<int, int>> getSubmatrixIndices(vector<vector<int>> A, vector<vector<int>> B) {
    bool found = false;
    size_t bigMatrixSize = A.size();
    size_t smallMatrixSize = B.size();
    size_t deltaSize = bigMatrixSize - smallMatrixSize;

    for (int xOffset = 0; xOffset <= deltaSize ; xOffset++) {
        for (int yOffset = 0; yOffset <= deltaSize ; yOffset++) {
            found = true;

            for (int i = 0; i < smallMatrixSize; i++) {
                for (int j = 0; j < smallMatrixSize; j++) {
                    if (A[i][j] != B[i][j]) {
                        found = false;
                        break;
                    }
                }
                if (!found)
                    break;
            }

            if (found) {
                return pair<int, int>(xOffset, yOffset);
            }
        }
    }
    return nullopt;
}

int main(){

    //FILE* pFile = fopen("/Users/bair/Desktop/MaximovCpp/practice1/cat_grey.bmp", "rb");
    //i1.showrgb();
    //i1.showcolor();
    //i1.show_gist_data();
    //i1.show_gist();
    //cout << i1.my_Offset(pFile);
    
    FILE* pImg1 = fopen("/Users/bair/Desktop/MaximovCpp/practice1/cat/image/cat_grey1.bmp", "rb");
    FILE* pImg2 = fopen("/Users/bair/Desktop/MaximovCpp/practice1/cat/image/mouse1.bmp", "rb");
    image cat, mouse;
    angle rectangle[9];
    cat.fill(pImg1);  mouse.fill(pImg2); 

    //cat.show();
    //mouse.show();
    //cat.show_gist_data();
    //mouse.show_gist_data();
    //mouse.showcolor();

    fill_angle(rectangle, getWidth(cat), getHeight(cat));
       for (int i = 0;i < 9;i++ ){
        fill_angle_gist(cat,rectangle[i]);
    }


    // for (int i = 0; i < 9; i++)
    // {
    //     cout << i+1 << " = "<< rectangle[i].top_left.x <<  ","<< rectangle[i].top_left.y << " "
    //     << rectangle[i].bottom_right.x <<  ","<< rectangle[i].bottom_right.y <<"\t";
    // }

    // cout << endl; 
    // int cnt = 0;
    // int p = 0;
    // for (int i = 0; i< SIZE; i++){
    //     cnt +=rectangle[p].gist[i];
    //     cout << i << "-" <<rectangle[p].gist[i] << " ";
    // }
    // cout << "all = " << cnt << endl;

    //cout << is_match(rectangle[0].gist, mouse.Gist);

    // for (int i = 0; i< 9; i++)
    //         if (is_match(rectangle[i].gist, mouse.Gist)) cout << i + 1 << " ";
    
    int temp[64]={0};
    bool found = false;
    int deltaSize = getHeight(cat) - getHeight(mouse);
    for (int xOffset = 0; xOffset <= deltaSize ; xOffset++) {
        for (int yOffset = 0; yOffset <= deltaSize ; yOffset++) {
            found = true;
            for (int i = 0; i < getHeight(mouse); i++) {
                for (int j = 0; j < getHeight(mouse); j++) {
                    temp[cat.color[i+xOffset][j+yOffset]]++;
                    if (temp[cat.color[i+xOffset][j+yOffset]]++ != mouse.color[i][j]) {
                        found = false;
                        break;
                    }
                }
                if (!found)
                    break;
            }
            if (found) {
                cout << "asda";
            }
        }
    }
    return 0;
}


