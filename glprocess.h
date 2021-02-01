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

typedef enum {
    RKGCC_NVR_OP_RENDER_TEXTURE = 0,
    RKGCC_NVR_OP_COLOR_FILL,
    RKGCC_NVR_OP_DRAW_LINES,
} RKGCC_NVR_OP;

#define MAXLayer 160 

#define MAXLines 64


typedef struct RKGFX_NVR_point_s {
    int x;
    int y;  
} RKGFX_NVR_point_t;

typedef struct RKGFX_NVR_line_s{
    RKGFX_NVR_point_t startPt;
    RKGFX_NVR_point_t endPt;
    int lineW;
    float color[3];
} RKGFX_NVR_line_t;

typedef struct RKGFX_NVR_lines_s{
    RKGFX_NVR_line_t linesArray[MAXLines];
    int numlines;
} RKGFX_NVR_lines_t;

typedef struct RKGFX_NVR_quadrl_info_s {
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
} RKGFX_NVR_quadrl_t;

typedef struct RKGFX_NVR_mosaic_info_s{
    int left;
    int top;
    int right;
    int bottom;
    int bsize;
    int mode;
} RKGFX_NVR_mosaic_info_t;


typedef struct RKGFX_NVR_wireframe_info_s{
    int left;
    int top;
    int right;
    int bottom;
    float color[3];
    int lpx;
    int tpx;
    int rpx;
    int bpx;
 
} RKGFX_NVR_wireframe_info_t;

typedef struct RKGFX_NVR_alpha_lut_info_s{
   unsigned char map_0;
   unsigned char map_1;
   
} RKGFX_NVR_alpha_lut_info_t;


typedef struct RKGFX_NVR_layer_info_s{
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
    RKGFX_NVR_quadrl_t quadril_info;
    RKGFX_NVR_mosaic_info_t mosic_info;
    RKGFX_NVR_wireframe_info_t wireframe_info;
    RKGFX_NVR_alpha_lut_info_t alpha_lut_info;
} RKGFX_NVR_layer_info_t;

typedef struct RKGFX_NVR_layer_list_s{
    RKGFX_NVR_layer_info_t srcLayerInfo[MAXLayer];
    RKGFX_NVR_layer_info_t dstLayerInfo[MAXLayer];
    RKGFX_NVR_lines_t lineSet;
    int numLayer;
    int op;
    float wfRgb[3];
    float fcfRgb[3];
    int px;
    int pxfc;
    int imgReserve;
} RKGFX_NVR_layer_list_t;

#ifdef __cplusplus
extern "C"
{
#endif

void* RKGFX_NVR_create();
int   RKGFX_NVR_init(void *p,int screenW,int screenH,int priority);
int   RKGFX_NVR_composite(void *p,RKGFX_NVR_layer_list_t *layerinfo);
void* RKGFX_NVR_create_fence(void *p);
int   RKGFX_NVR_wait_fence(void *p,void *fence);
int   RKGFX_NVR_destroy(void *p);

#ifdef __cplusplus
}
#endif
#endif


