#ifndef GLPORCESS_H
#define GLPORCESS_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>

#define EGL_ITU_REC601_EXT                0x327F
#define EGL_ITU_REC709_EXT                0x3280
#define EGL_ITU_REC2020_EXT               0x3281
#define EGL_YUV_FULL_RANGE_EXT            0x3282
#define EGL_YUV_NARROW_RANGE_EXT          0x3283
#define OP_RENDER_TEXTURE 0
#define OP_COLOR_FILL    1
#define OP_DRAW_LINES    2 


#define MAXLayer 160 

#define MAXLines 64

typedef struct point {
    int x;
    int y;  
} point_t;

typedef struct line{
    point_t startPt;
    point_t endPt;
    int lineW;
    float color[3];
} line_t;

typedef struct lines{
    line_t linesArray[MAXLines];
    int numlines;
} lines_t;

typedef struct quadrl_info {
    float color[3];
    int coord[8];  
    // [0]=x0 [1]=y0, [2]=x1 [3]=y1,  [4]=x2 [5]=y2,  [6]=x3 [7]=y3
    //        (x0,y0)------- (x3,y3)
    //               |     |
    //               |     |
    //               |     |
    //        (x1,y1)------- (x2,y2)
    
    int lineW;
    int quadBox;   // If you want to render the border this flag is set to 1
} quadrl_t;

typedef struct _mosaic_info{
    int left;
    int top;
    int right;
    int bottom;
    int bsize;
    int mode;
} mosaic_info_t;


typedef struct _wireframe_info_t{
    int left;
    int top;
    int right;
    int bottom;
    float color[3];
    int lpx;
    int tpx;
    int rpx;
    int bpx;
 
} wireframe_info_t;

typedef struct layer_info {
    int fd;
    int afbc_flag;
    int format;
    int color_space ;
    int sample_range;
    int width;
    int height;
    int left;
    int top;
    int right;
    int bottom;
    int focuswin;
    int rotation;
    quadrl_t quadril_info;
    mosaic_info_t mosic_info;
    wireframe_info_t wireframe_info;
} layer_info_t;

typedef struct layer_list {
    layer_info_t srcLayerInfo[MAXLayer];
    layer_info_t dstLayerInfo[MAXLayer];
    lines_t lineSet;
    int numLayer;
    int op;
    float wfRgb[3];
    float fcfRgb[3];
    int px;
    int pxfc;
    int imgReserve;
} layer_list_t;

#ifdef __cplusplus
extern "C"
{
#endif

void *doByGpuCreate();
int doByGpuInit(void *p,int screenW,int screenH,int priority);
int doByGpuComposition(void *p,layer_list_t *layerinfo);
void* doByGpucreateFence(void *p);
int doByGpuwaitFence(void *p,void *fence);
int doByGpuDestroy(void *p);

#ifdef __cplusplus
}
#endif
#endif


