int	check_map_ber(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		i++;
	i--;
	if (file[i] != 'b' || file[i - 1] != 'u' || file[i - 2] != 'c'
		|| file[i - 3] != '.')
		return (1);
	return (0);
}
