/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:18:10 by mle-biha          #+#    #+#             */
/*   Updated: 2023/02/09 17:32:01 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	Checks if all the char are digital (between 0 and 9)
	with the function ft_isdigit, if not it retruns 0.
*/
int	check_pid(char	*pid)
{
	int	i;

	i = 0;
	while (pid[i] != 0)
	{
		if (!ft_isdigit(pid[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
	Sends a char to a process identified by the pid passed as a parameter
	Uses the function "kill" to send two different signals, SIGUSR1 and SIGUSR2,
	to the target process depending on the binary representation of the char.
	Loops through each bit of the char and send either SIGUSR1 or SIGUSR2,
	then pause while waiting for a signal from the server,
	it then waits for 100 microseconds before moving on to the next bit.
	If the "kill" function returns an error,
	the function terminates the program with exit code EXIT_FAILURE.
*/
void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((1 & (c >> i)) == 0)
		{
			if (kill(pid, SIGUSR1) != 0)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2) != 0)
				exit(EXIT_FAILURE);
		}
		i++;
		pause();
	}
}

/*
	As long as the char where we are is not '\0',
	the function sends the char to the "send_char" function.
	When the while loop is over, it sends the char '\0' 
	to the "send_char" function.
*/
void	send_message(int pid, char *message)
{
	unsigned int	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\0');
}

/*
	Sleeps for 100 microseconds.
*/
void	signal_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_putendl_fd("Server stopped. Exit.", 2);
		exit(EXIT_FAILURE);
	}
	usleep(100);
}

/*
	Checks the number of arguments, if below three, something is missing
	Then checks the pid, if not valid, it returns an error.
	Then sends the message to the other process.
*/
int	main(int argc, char	*argv[])
{
	if (argc != 3)
	{
		ft_putendl_fd("usage: ./client [server-pid] [message]", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_pid(argv[1]))
	{
		ft_putendl_fd("Invalid PID, PID should be a number", 2);
		exit(EXIT_FAILURE);
	}
	if (argv[2][0] == '\0')
	{
		ft_putendl_fd("Invalid message, message should not be empty", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
