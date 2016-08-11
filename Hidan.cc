#include "Hidan.h"

Image::Image(int w, int h, int c) {
    size=w*h*c;
    width=w;
    height=h;
    channel=c;
    data=(float*)malloc(sizeof(float)*size);
    generateRandomImage();
}

void Image::generateRandomImage() {
    srand((unsigned)time(NULL));
    for(int i=0; i<size; i++)
        data[i]=((float)rand())/((float)RAND_MAX);
}

void Image::output(FILE *fout) {
    for(int i=0; i<channel; i++) {
        int offset=i*width*height;
        for(int j=0; j<height; j++) {
            for(int k=0; k<width; k++) 
                fprintf(fout, "%.7f ", data[offset+j*width+k]);
            fprintf(fout, "\n");
        }
    }
}

Filter::Filter(int w, int h, int c) {
    size=w*h*c;
    width=w;
    height=h;
    channel=c;
    data=(float*)malloc(sizeof(float)*size);
    generateRandomFilter();
}

void Filter::generateRandomFilter() {
    srand((unsigned)time(NULL));
    for(int i=0; i<size; i++)
        data[i]=((float)rand())/((float)RAND_MAX);
}

void Filter::output(FILE *fout) {
    for(int i=0; i<channel; i++) {
        int offset=i*width*height;
        for(int j=0; j<height; j++) {
            for(int k=0; k<width; k++) 
                fprintf(fout, "%.7f ", data[offset+j*width+k]);
            fprintf(fout, "\n");
        }
    }
}

float Hidan::conv(int x, int y, int fid, int cid) {
    float acc=0.0f;
    float *fcur=&(filters[fid].data[cid*width_f*height_f]);
    float *icur=&(image_in.data[fid*width_i*height_i]);
    for(int a=0; a<width_f; a++)
        for(int b=0; b<height_f; b++) {
            acc+=fcur[(height_f-b)*width_f+(width_f-a)]*icur[(b+y)*width_i+a+x];
        }
    return acc;
}

void Hidan::run() {
    for(int iFilter=0; iFilter<filter_num; iFilter++) {
        float* icur=&(image_out.data[iFilter*width_o*height_o]);
        for(int i=0; i<height_o; i++)
            for(int j=0; j<width_o; j++)
            {
                icur[i*width_o+j]=0.0f;
                for(int iChannel=0; iChannel<channel; iChannel++) {
                    icur[i*width_o+j]+=conv(j, i, iFilter, iChannel);
                }
                
            }
    }
}
