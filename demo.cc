#include "Hidan.h"
#include <stdio.h>

int main() {
    FILE *fout=fopen("result.dat", "w+"); 
    Hidan hd(3, 3, 3, 3, 1, 1);
    hd.run();
    fprintf(fout, "input image:\n");
    hd.image_in.output(fout);
    fprintf(fout, "filter:\n");
    hd.filters[0].output(fout);
    fprintf(fout, "result:\n");
    hd.image_out.output(fout);
    fflush(fout);
    fclose(fout);
    return 0;
}
