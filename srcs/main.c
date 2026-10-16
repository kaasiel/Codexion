#include "codexion.h"


int main(int argc, char **argv)
{
	int i;
	t_args args;
	t_dongles *dongles;
	t_coder *coders;
	t_data	data;
	long	now;

	data.simulation_end = 0;
	data.start_time = get_time();
	if (parse_args(argc, argv, &args) != 0)
		return (1);
	data.strategy = args.scheduler;
	data.cooldown = args.dongle_cooldown;
	data.ticket = 0;
	pthread_mutex_init(&data.sched_mutex, NULL);
	pthread_mutex_init(&data.sched_cond, NULL);
	pthread_mutex_init(&data.print_mutex, NULL);
	dongles = calloc((size_t)args.number_of_coders, sizeof(*dongles));
	coders = calloc((size_t)args.number_of_coders, sizeof(*coders));
	if (dongles == NULL || coders == NULL)
	{
		free(dongles);
		free(coders);
		return (1);
	}
	if (init_fork(args, dongles) != 0
	|| init_coder(coders, dongles, args, &data) != 0)
	{
		free(dongles);
		free(coders);
		return (1);
	}
	now = data.start_time;
	i = 0;
	while (i < args.number_of_coders)
	{
		coders[i].last_compile_start = now;
		i++;
	}
	launcher(coders, args.number_of_coders);
	free(dongles);
	free(coders);
	return (0);
}