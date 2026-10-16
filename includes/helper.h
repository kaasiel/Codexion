#ifndef HELPER_H
# define HELPER_H

# include <stdio.h>
# include <sys/time.h>

typedef struct s_coder t_coder;

void    push(t_coder *queue, t_coder coder);
void    pop(t_coder * queue);
void    printlog(t_coder *coder,char   *msg);
long    get_time(void);
void    pop(t_coder * queue);
void    push(t_coder *queue, t_coder coder);

#endif