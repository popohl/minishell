#include <unistd.h>
#include <stdlib.h>
#include "config.h"

char	*print_prompt(char *buf)
{
	int		n;

	write(1, "$> ", 3);
	n = read(0, buf, MAX_CMD_LEN - 1);
	buf[n] = 0;
	DD(n);
	DS(buf);
	return (buf);
}

int		main(void)
{
	char	*buf;

	if (!(buf = (char *)malloc(sizeof(*buf) * MAX_CMD_LEN)))
		return (1);
	if (print_prompt(buf))
		return (1);
	return (0);
}
