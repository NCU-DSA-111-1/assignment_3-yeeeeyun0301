#include "huffman.h"
#include "arcd.h"
#include <adaptive_model.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void output(const arcd_buf_t buf, const unsigned buf_bits, void *const io)
{
	(void)buf_bits;
	FILE *const f = (FILE *)io;
	fwrite(&buf, sizeof(buf), 1, f);
}

unsigned input(arcd_buf_t *const buf, void *const io)
{
	FILE *const f = (FILE *)io;
	return 8 * fread(buf, sizeof(*buf), 1, f);
}

typedef unsigned char symbol_t;
static const arcd_char_t EOS = 1 << (8 * sizeof(symbol_t));

int main()
{
     FILE *in; //開原本檔案

     //(1)表示huffman (2)表示arcd
     FILE *out1; //壓縮完的檔案
     FILE *input1; // 將壓縮檔案打開
     FILE *decode1; // 寫入解碼檔案

     FILE *out2; //壓縮完的檔案
     FILE *input2; // 將壓縮檔案打開
     FILE *decode2; // 寫入解碼檔案

     clock_t start, end; //計算時間
 


     //--------------------------------Huffman------------------------------//
     //1.壓縮測試檔案
     start = clock();
     printf(" %.2ld  ms \n" , start);
     in = fopen("../test/origin", "rb");
     out1 = fopen("../test/output_huffman","wb");  
     huffman_encode_file(in, out1);
     fclose(in);
     fclose(out1);
     end = clock();
     double diff1 = end - start;
     printf(" Huffman壓縮時間: %.2f  ms \n" , diff1);

     //2.將壓縮後的測試檔案解碼
     start = clock();
     input1=fopen("../test/output_huffman","rb");
     decode1 = fopen("../test/decode/huffman","wb");
     huffman_decode_file(input1, decode1);
     fclose(input1);
     fclose(decode1);
     end = clock();
     double diff2 = end - start;
     printf(" Huffman解碼時間: %.2f  ms \n" , diff2);
          
    //--------------------------------arcd------------------------------//

     adaptive_model model;
	adaptive_model_create(&model, EOS + 1);
     
    //1.壓縮測試檔案
     in = fopen("../test/origin", "rb");
     out2 = fopen("../test/output_arcd","wb");


     //2.將壓縮後的測試檔案解碼



     

     adaptive_model_free(&model);

     fclose(in);
     fclose(out2);

     

     return 0;
}