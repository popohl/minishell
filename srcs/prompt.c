#include <unistd.h>
#include <stdlib.h>
#include "config.h"
#include "libft/libft.h"

char	*print_prompt(char *buf)
{
	int		n;

	write(1, "$> ", 3);
	n = read(0, buf, MAX_CMD_LEN - 1);
	buf[n - 1] = 0;
	return (buf);
}

int		main(void)
{
	char	*buf;
	int		n;

	if (!(buf = (char *)malloc(sizeof(*buf) * MAX_CMD_LEN)))
		return (1);
	while ((n = ft_strcmp(buf, "exit")))
	{
		print_prompt(buf);
	}
	return (0);
}
