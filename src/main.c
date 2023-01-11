#include "arcd.h"
#include "adaptive_model.h"
#include "huffman.h"

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
     in = fopen("../test/origin", "rb");
     out1 = fopen("../test/encode/output_huffman","wb");  
     huffman_encode_file(in, out1);
     fclose(in);
     fclose(out1);
     end = clock();
     double diff1 = end - start;
     printf(" Huffman壓縮時間: %.2f  ms \n\n" , diff1);

     //2.將壓縮後的測試檔案解碼
     start = clock();
     input1=fopen("../test/encode/output_huffman","rb");
     decode1 = fopen("../test/decode/huffman","wb");
     huffman_decode_file(input1, decode1);
     fclose(input1);
     fclose(decode1);
     end = clock();
     double diff2 = end - start;
     printf(" Huffman解碼時間: %.2f  ms \n\n" , diff2);
          
    //--------------------------------arcd------------------------------//

     adaptive_model model;
	adaptive_model_create(&model, EOS + 1);

    //1.壓縮測試檔案
     start = clock();
     in = fopen("../test/origin", "rb");
     out2 = fopen("../test/encode/output_arcd","wb");


     arcd_enc enc;
     arcd_enc_init(&enc, adaptive_model_getprob, &model, output, out2);
     symbol_t sym;
     while (0 < fread(&sym, sizeof(sym), 1, in))
     {
          arcd_enc_put(&enc, sym);
     }
     arcd_enc_put(&enc, EOS);
     arcd_enc_fin(&enc);

     fclose(in);
     fclose(out2);
     end = clock();
     double diff3 = end - start;
     printf(" arcd壓縮時間: %.2f  ms \n\n" , diff3);

     //2.將壓縮後的測試檔案解碼
     start = clock();
     input2=fopen("../test/encode/output_arcd","rb");
     decode2 = fopen("../test/decode/arcd","wb");

     arcd_dec dec;
     arcd_dec_init(&dec, adaptive_model_getch, &model, input, input2);
     arcd_char_t ch;
     while (EOS != (ch = arcd_dec_get(&dec)))
     {
          const symbol_t sym = (unsigned char)ch;
          fwrite(&sym, sizeof(sym), 1, decode2);
     }

     adaptive_model_free(&model); 
     fclose(input2);
     fclose(decode2);
     end = clock();
     double diff4 = end - start;
     printf(" arcd解碼時間: %.2f  ms \n\n" , diff4);

     return 0;
}