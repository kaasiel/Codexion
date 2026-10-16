#include "codexion.h"
#include "helper.h"

void    compile(t_coder *coder)
{
    if (!acquire_dongles(coder))
        return;
    
    pthread_mutex_lock(&coder->mutex);
    coder->last_compile_start = get_time();
    pthread_mutex_unlock(&coder->mutex);
    printlog(coder, "is compiling");
    usleep(coder->time_to_compile * 1000);
    release_dongles(coder);
    pthread_mutex_lock(&coder->mutex);
    coder->max_compile--;
    pthread_mutex_unlock(&coder->mutex);
}

void    debug(t_coder *coder)
{
    printlog(coder, "is debugging");
    usleep(coder->time_to_debug * 1000);
}

void    refrcatinng(t_coder *coder)
{
    printlog(coder, "is refracting");
    usleep(coder->time_to_refactor * 1000);
}

void    burnout(t_coder *coder)
{
    if (coder)
        printlog(coder, "has burmed out");
    else
        printf("Coder has burned out\n");
}
