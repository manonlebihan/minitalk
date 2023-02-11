/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:52:43 by mle-biha          #+#    #+#             */
/*   Updated: 2023/02/09 18:01:03 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	Function to create the string that is going be printed on the standard 
	output.
	If the string passed as an argument is NULL, it malloc with the
	size of a char (1), then checks if the malloc worked, if not,
	it returns NULL, then it puts '\0' in the string.
	Gets the length of the string, then malloc res, 
	then checks if the malloc worked, if not, it frees str and it returns NULL.
	Then, it copies the bytes from str to res. After that, it adds the
	reconstructed char at the end of res and then the '\0' char.
	It then frees str and returns res.
*/
static char	*create_str(char *str, char c, int pid)
{
	char	*res;
	int		len;

	if (str == NULL)
	{
		str = (char *)malloc(sizeof(char));
		if (str == NULL)
		{
			kill(pid, SIGUSR2);
			exit(EXIT_FAILURE);
		}
		str[0] = '\0';
	}
	len = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (len + 2));
	if (res == NULL)
	{
		free(str);
		kill(pid, SIGUSR2);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(res, str, len);
	res[len] = c;
	res[len + 1] = '\0';
	free(str);
	return (res);
}

/* 	This function uses thre	static varaibles :
		int c, to store the current character being reconstructured
		from the signal,
		int i, to keep track of the current bit being processed,
		char *str, to store the reconstructured string,
	When it receives SIGUSR2, the current bit being processed is set in c
	by performing a bitwise OR operation between c and 1 shifted left by i.
	Once 8 bits have been processed, c will contain the character that has been
	reconstructed.
	If c = 0, the current string str is printed to stdout and then it checks
	if str is different than NULL it frees it. It then add the '\0' char
	and reset str to NULL. Else, c is added to str by calling the 
	create_str function. Then i and c are reste to 0.
	Then a usleep of a 100 is done and SIGUSR1 is sent to the client.
*/
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	c = 0;
	static int	i = 0;
	static char	*str = NULL;

	(void)context;
	if (sig == SIGUSR2)
		c = (c | (1 << i));
	if (++i == 8)
	{
		if (c == 0)
		{
			ft_putstr_fd(str, 1);
			if (str != NULL)
				free(str);
			ft_putchar_fd('\n', 1);
			str = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		else
			str = create_str(str, c, info->si_pid);
		c = 0;
		i = 0;
	}
	usleep(100);
	kill(info->si_pid, SIGUSR1);
}

/*
	Prints the PID of the server on the standard output (fd 1).
	Then register the signal handler "signal_handler"
	for the signals SIGUSR1 and SIGUSR2.
	It then waits for the signals to be received.
*/
int	main(void)
{
	struct sigaction	action;

	ft_putstr_fd("[SERVER PID]: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	ft_bzero(&action, sizeof(action));
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &signal_handler;
	while (1)
	{
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);
		pause();
	}
	return (0);
}
