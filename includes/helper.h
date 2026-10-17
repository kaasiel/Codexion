#ifndef HELPER_H
# define HELPER_H

# include <stdio.h>
# include <sys/time.h>

typedef struct s_coder t_coder;

void    printlog(t_coder *coder, char *msg);
long    get_time(void);

#endif