#include "codexion.h"

int launcher(t_coder *coders, int nb)
{
    int i;
    t_moni  m;
    pthread_t *threads;
    pthread_t mon;

    m.nb = nb;
    m.coders = coders;
    threads = malloc(sizeof(pthread_t) * nb);
    pthread_create(&mon, NULL, monitoring, &m);
    if (!threads)
        return(1);
    i = 0;
    while (i < nb)
    {
        if (pthread_create(&threads[i], NULL, routine, &coders[i]) !=0)
            return (free(threads), 1);
        i++;
    }
    i = 0;
    while (i < nb)
    {
        pthread_join(threads[i], NULL);
        pthread_join(mon, NULL);
        i++;
    }
    free(threads);
    return (0);
}

void *routine(void *arg)
{   
    t_coder *coder = (t_coder *)arg;
    while (coder->max_compile != 0)
    {
        compile(coder);
        debug(coder);
        refrcatinng(coder);
    }
    return (NULL);
}
