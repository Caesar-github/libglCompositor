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

#define MAXLayer 160
typedef struct layer_info {
    int fd;
    int afbc_falg;
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
} layer_info_t;

typedef struct layer_list {
    layer_info_t srcLayerInfo[MAXLayer];
    layer_info_t dstLayerInfo[MAXLayer];
    int numLayer;
    float wfRgb[3];
    float fcfRgb[3];
    int px;
    int pxfc;
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


