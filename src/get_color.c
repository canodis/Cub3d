#include "../include/cub3d.h"

char	*ft_strrev(char *str)
{
	int		len;
	int		i;
	char	tmp;

	len = 0;
	i = 0;
	while (str[len])
		len++;
	len -= 1;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
	return (str);
}

int	ft_len_hex(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

char	*double_str_join(char **str)
{
	int		idx;
	char	*res;

	res = malloc(1);
	idx = 0;
	while (*(str + idx))
	{
		res = ft_strjoin(res, *(str + idx));
		idx++;
	}
	return (res);
}

char	*convert(int res, char *value)
{
	char		*hexvalue;
	long long	tempDecimal;
	char		*hex;
	int			index;
	int			rem;

	index = 0;
	hexvalue = malloc(sizeof(char) * 17);
	ft_strlcpy(hexvalue, "0123456789ABCDEF\0", 17);
	tempDecimal = res;
	hex = malloc(sizeof(char) * ft_len_hex(res) + 1);
	while(tempDecimal !=0)
	{
		rem = tempDecimal % 16;
		hex[index] = hexvalue[rem];
		tempDecimal /= 16;
		index++;
	}
	hex[index] = '\0';
	ft_strrev(hex);
	free(hexvalue);
	free(value);
	return (hex);
}

int		ft_atoi_base(const char *str)
{
	int	i;
	int	n;
	int	len;
	int	result;

	i = 0;
	n = 1;
	result = 0;
	if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		result *= 16;
		if (str[i] >= '0' && str[i] <= '9')
			result += str[i] - 48;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			result += str[i] - 55;
		else if (str[i] >= 'a' && str[i] <= 'z')
			result += str[i] - 87;
		i++;
	}
	return (result * n);
}

int	get_color(char *str)
{
	char	**double_array;
	int		len;
	char	*str_result;
	int		result;

	len = -1;
	double_array = ft_split(str, ',');
	while (double_array[len])
		len++;
	while (--len >= 0)
		double_array[len] = convert(ft_atoi(double_array[len]), double_array[len]);
	str_result = double_str_join(double_array);
	result = (ft_atoi_base(str_result));
	free(str_result);
	free_2d_array(double_array);
	return (result);
}
