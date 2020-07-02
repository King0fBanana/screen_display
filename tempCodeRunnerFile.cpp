#include <cstring>
#include <stdio.h>

const int operationMax = 10;
const int mapmax = 9;
const int screensize = 5;

struct windowparam
{
    int start;
    int size;
    int end;
    int pointer;
    int toscreen;
};

typedef enum optioin
{
    start = 1,
    reinit,
    up,
    down,
    sizeup,
    sizedown,
    end = operationMax
} option;

void initwindow(windowparam *wp)
{
    printf("DEBUG, initwindow\n");
    wp->start = 0;
    wp->size = 0;
    wp->end = 0;
    wp->pointer = 0;
    wp->toscreen = 0;
}

void sortwindow(windowparam *wp, int rownum, option opt)
{
    printf("DEBUG, sortwindow E\n");
    static int lastpointer = wp->pointer;
    wp->end = wp->start + wp->size - 1;
    if (wp->pointer <= wp->start)
    {
        wp->start = (wp->pointer == 0) ? 0 : (wp->pointer - 1);
        wp->toscreen = (wp->pointer == 0 && lastpointer == 1) ? (wp->toscreen - 1) : (wp->toscreen);
        wp->end = wp->start + wp->size - 1;
    }
    else if (wp->pointer >= wp->end)
    {
        wp->end = (wp->pointer == (rownum - 1)) ? (rownum - 1) : (wp->pointer + 1);
        wp->toscreen = (wp->pointer == (rownum - 1) && lastpointer == (rownum - 2)) ? (wp->toscreen + 1) : (wp->toscreen);
        wp->start = wp->end - wp->size + 1;
    }
    else
    {
        if(opt == up)
        {
            wp->toscreen--;
        }
        else if (opt == down)
        {
            wp->toscreen++;
        }
    }

    if (wp->size == 1)
    {
        wp->start = wp->pointer;
        wp->end = wp->pointer;
    }

    lastpointer = wp->pointer;
    printf("DEBUG, sortwindow X\n");
    return;
}

char **initmap(int rownum)
{
    printf("DEBUG, initmap E\n");
    static char **map;
    if (map != NULL)
    {
        delete map;
    }

    map = new char *[rownum];

    for (int i = 0; i <= rownum - 1; i++)
    {
        map[i] = new char[rownum];
    }

    for (int i = 0; i <= rownum - 1; i++)
    {
        for (int j = 0; j <= rownum - 1; j++)
        {
            if (i >= j)
            {
                map[i][j] = '0' + i + 1;
            }
            else
            {
                map[i][j] = '\0';
            }
        }
    }
    printf("DEBUG, initmap X\n");
    return map;
}

void ondisplay(windowparam wp, char **map)
{
    printf("DEBUG, ondislay E\n");
    for (int i = (wp.pointer - wp.start) ; i <= wp.toscreen; i++)
    {
        printf("   *********\n");
    }

    for (int i = wp.start; i <= wp.end; i++)
    {
        if (i == wp.pointer)
        {
            printf("-->%s\n", map[i]);
        }
        else
        {
            printf("   %s\n", map[i]);
        }
    }

    for (int i = (wp.end - wp.pointer) ; i <= (screensize - wp.toscreen -1); i++)
    {
        printf("   *********\n");
    }

    printf("DEBUG, ondislay %d %d %d %d X\n", wp.end, wp.pointer, screensize,wp.toscreen);
    return;
}

int main()
{
    option opt;
    char **map = NULL;
    bool startlock = false;
    int rownum;
    windowparam wp;
    do
    {
        printf("INFO, starting, please enter %d to start\n", start);
        scanf("%d", &opt);
    } while (start != opt);

    while (end != opt)
    {
        switch (opt)
        {
        case start:
        {
            if (false == startlock)
            {
                startlock = true;
            }
            else
            {
                printf("WARNING, you have started before, try again\n");
                break;
            }
        }

        case reinit:
        {
            do
            {
                initwindow(&wp);
                //printf("INFO, enter row number(1-%d) to init\n", mapmax);
                //scanf("%d", &rownum);
                printf("INFO, set rownum to mapmax\n");
                rownum = mapmax;
            } while (rownum > mapmax || rownum < 1);

            do
            {
                //printf("INFO, enter screen size number(1-%d) to init\n", rownum);
                //scanf("%d", &wp.size);
                printf("INFO, set init windows size to screen size\n");
                wp.size = screensize;
            } while (wp.size > rownum || wp.size < 1);

            if (map != NULL)
            {
                delete map;
            }

            map = initmap(rownum);
            break;
        }

        case down:
        {
            wp.pointer++;

            if (wp.pointer > rownum - 1)
            {
                wp.pointer--;
            }
            break;
        }

        case up:
        {
            wp.pointer--;
    
            if (wp.pointer < 0)
            {
                wp.pointer++;
            }
            break;
        }

        case sizeup:
        {
            wp.size++;
            if (wp.size > screensize)
            {
                printf("WARNING, invalid rownum, restored\n");
                wp.size--;
                
            }
            else if ((wp.start + wp.size - 1) > rownum - 1)
            {
                wp.start--;
            }
            break;
        }

        case sizedown:
        {
            wp.size--;
            if (wp.size < 1)
            {
                printf("WARNING, invalid rownum, restored\n");
                wp.size++;
            }
            break;
        }

        case end:
        {
            printf("WARNING, program ending now\n");
            break;
        }

        default:
        {
            printf("WARNING, unknow command, pls retry\n");
            break;
        }
        }

        sortwindow(&wp, rownum, opt);
        ondisplay(wp, map);

        printf("INFO, now enter a command :\n\
                    start       :  %d\n\
                    reinit      :  %d\n\
                    scrollup    :  %d\n\
                    scrolldown  :  %d\n\
                    sizeup      :  %d\n\
                    sizedown    :  %d\n\
                    end         :  %d\n",
               start, reinit, up, down, sizeup, sizedown, end);
        scanf("%d", &opt);
    }
}