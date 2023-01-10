#include "huffman.h"
#include "arcd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>



int main()
{
     FILE *in; //開原本檔案

     //(1)表示huffman (2)表示arcd
     FILE *out1; //將編碼寫入檔案
     FILE *input1; // 將編碼檔案打開
     FILE *decode1; // 寫入解碼檔案

     FILE *out2; //將編碼寫入檔案
     FILE *input2; // 將編碼檔案打開
     FILE *decode2; // 寫入解碼檔案

     clock_t start, end; //計算時間
 


     //--------------------------------Huffman------------------------------//
     //1.測試檔案編碼
     start = clock();
     in = fopen("../test/origin", "rb");
     out1 = fopen("../test/output_huffman","wb");  
     huffman_encode_file(in, out1);
     fclose(in);
     fclose(out1);
     end = clock();
     double diff1 = end - start;
     printf(" %.2f  ms \n" , diff1);

     //2.將編碼後的測試檔案解碼
     start = clock();
     input1=fopen("../test/output_huffman","rb");
     decode1 = fopen("../test/decode/huffman","wb");
     huffman_decode_file(input1, decode1);
     fclose(input1);
     fclose(decode1);
     end = clock();

     double diff2 = end - start;
     printf(" %.2f  ms \n" , diff2);
          
    //--------------------------------arcd------------------------------//
    //1.測試檔案編碼
     in = fopen("../test/origin", "rb");


     //2.將編碼後的測試檔案解碼
     out2 = fopen("../test/output_arcd","wb");

     fclose(in);
     fclose(out2);
     

     return 0;
}