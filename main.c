#include <stdio.h>
// #include <sys/mmap.h>
#include <fcntl.h>
#include <kora/mcrs.h>
#include "gfx.h"

void *mmap(void *addr, size_t length, int prot, int flags, int fd, __off_t off);

int x = 0;
bool on_repaint(gfx_t *gfx, void *arg, gfx_seat_t *seat)
{
    return true;
}

void on_expose(gfx_t *gfx, void *arg, gfx_seat_t *seat)
{
    gfx_rect(gfx, x++, 0, 120, 120, 0x10a6a6);
}

void on_resize(gfx_t *gfx, void *arg)
{
}

void on_key_up(gfx_t *gfx, void *arg, gfx_seat_t *seat, int key_code)
{
}

void on_key_down(gfx_t *gfx, void *arg, gfx_seat_t *seat, int key_code)
{
}


void on_mse_up(gfx_t *gfx, void *arg, gfx_seat_t *seat, int btn)
{
}

void on_mse_down(gfx_t *gfx, void *arg, gfx_seat_t *seat, int btn)
{
}

void on_mse_move(gfx_t *gfx, void *arg, gfx_seat_t *seat)
{
}

void on_mse_wheel(gfx_t *gfx, void *arg, gfx_seat_t *seat, int disp)
{
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

gfx_handlers_t handlers = {
    .repaint = (void*)on_repaint,
    .expose = (void*)on_expose,
    .resize = (void*)on_resize,
    .key_up = (void*)on_key_up,
    .key_down = (void*)on_key_down,
    .mse_up = (void*)on_mse_up,
    .mse_down = (void*)on_mse_down,
    .mse_move = (void*)on_mse_move,
    .mse_wheel = (void*)on_mse_wheel,
};





int main()
{
    int fb0 = open("/fb0", O_RDWR);
    int kdb = open("/kdb", O_RDONLY);
    int mouse = open("/mouse", O_RDONLY);

    // int event[4];

    // WRITE, PRIVATE | RESOLVE
    unsigned *scr = mmap(NULL, 4 * _Mib_, 2, 0x10000, fb0, 0);

    gfx_t *gfx = calloc(sizeof(gfx_t), 1);
    gfx->width = 1280;
    gfx->height = 720;
    gfx->fd = fb0;
    gfx->fi = kdb;

    gfx_t *win = gfx;
    int i;

    gfx_map(win);

    on_expose(win, NULL, NULL);
    gfx_loop(win, NULL, &handlers);
    gfx_unmap(win);
    gfx_destroy(win);

    // for (;;) {
    //     read(kdb, event, sizeof(int) * 4);
    //     // printf("Key event %d\n", event);
    //     for (i = 0; i < 1280 * 720; ++i)
    //         scr[i] = 0xa61010;
    //     fcntl(fb0, 800);
    // }

    // write(1, "Hello", 5);
    return 0;
}

