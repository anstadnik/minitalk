#include "server.h"

char 	g_bit;

void	usr1_handler()
{
	g_bit = 0;
}

void 	usr2_handler()
{
	g_bit = 1;
}

int 	main()
{
	int		i;
	char 	c;
//	char	buf[4096];
//	int 	buf_size;
//
	i = 8;
	c = 0;
//	buf_size = 0;
//	ft_bzero(buf, 4096);
	ft_printf("%d\n", getpid());
	while (1)
	{
//		if (buf_size == 4094)
//		{
//			ft_printf("%s\n", buf);
//			buf_size = 0;
//		}
		signal(SIGUSR1, usr1_handler);
		signal(SIGUSR2, usr2_handler);
		if (g_bit == 1)
			c |= 1 << i;
//		//ft_printf("%b\n", c);
//		if (i == 0 && c == 0)
//		{
//			//ft_printf("%s\n", buf);
//			buf_size = 0;
//			i = 8;
//		}
//		else if (i == 0)
//		{
//			buf[buf_size++] = c;
//			c = 0;
//			i = 8;
//		}
		if (i == 0)
		{
			ft_printf("c = %c\n", c);
//			ft_printf("%d\n", c);
			i = 8;
			c = 0;

		}
//			ft_printf("i = %i\n", i);
		--i;
		pause();
	}
}
