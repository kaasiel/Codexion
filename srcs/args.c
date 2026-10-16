#include "codexion.h"


static int	is_all_digits(const char *s)
{
	int	i;

	i = 0;
	if (!s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	str_to_long(const char *s, long *out)
{
	long	result;
	int		i;
	int		digit;

	if (s[0] == '-')
	{
		return (-1);
	}
	if (!is_all_digits(s))
	{
		fprintf(stderr, "codexion: error: not a valid integer: %s\n", s);
		return (-1);
	}
	result = 0;
	i = 0;
	while (s[i])
	{
		digit = s[i] - '0';
		if (result > (LONG_MAX - digit) / 10)
		{
			fprintf(stderr, "codexion: error: value out of range: %s\n", s);
			return (-1);
		}
		result = result * 10 + digit;
		i++;
	}
	*out = result;
	return (0);
}

static int	parse_field(const char *s, const char *name, long min, long *dest)
{
	if (str_to_long(s, dest) < 0)
		return (-1);
	if (*dest < min)
	{
		fprintf(stderr, "codexion: error: %s must be >= %ld (got %ld)\n",
			name, min, *dest);
		return (-1);
	}
	return (0);
}

static int	parse_scheduler(const char *s, t_scheduler *out)
{
	if (!strcmp(s, "fifo"))
	{
		*out = AL_FIFO;
		return (0);
	}
	if (!strcmp(s, "edf"))
	{
		*out = AL_EDF;
		return (0);
	}
	fprintf(stderr,
		"codexion: error: scheduler must be \"fifo\" or \"edf\" (got \"%s\")\n",
		s);
	return (-1);
}

static int	print_usage(const char *prog)
{
	fprintf(stderr, "Usage: %s number_of_coders time_to_burnout "
		"time_to_compile time_to_debug time_to_refactor "
		"number_of_compiles_required dongle_cooldown scheduler\n", prog);
	fprintf(stderr, "  scheduler: fifo | edf\n");
	return (-1);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	long	value;

	if (argc != 9)
		return (print_usage(argv[0]));
	if (parse_field(argv[1], "number_of_coders", 1, &value) < 0)
		return (-1);
	args->number_of_coders = (int)value;
	if (parse_field(argv[2], "time_to_burnout", 1, &args->time_to_burnout) < 0)
		return (-1);
	if (parse_field(argv[3], "time_to_compile", 1, &args->time_to_compile) < 0)
		return (-1);
	if (parse_field(argv[4], "time_to_debug", 0, &args->time_to_debug) < 0)
		return (-1);
	if (parse_field(argv[5], "time_to_refactor", 0, &args->time_to_refactor) < 0)
		return (-1);
	if (parse_field(argv[6], "number_of_compiles_required", 1, &value) < 0)
		return (-1);
	args->number_of_compiles_required = (int)value;
	if (parse_field(argv[7], "dongle_cooldown", 0, &args->dongle_cooldown) < 0)
		return (-1);
	if (parse_scheduler(argv[8], &args->scheduler) < 0)
		return (-1);
	return (0);
}