# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char	*env;
	struct s_list *next;
}	t_list;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	num_env_word(char *str, t_list *env)
{
	int	i;

	while (env)
	{
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] != '$')
		{
			if (str[i] != env->env[i])
				break ;
			i++;
		}
		if (env->env[i] == '=' && (str[i] == '$' || str[i] == ' ' || str[i] == '\0'))
			return (ft_strlen(&(env->env[i + 1])));
		env = env->next;
	}
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	return (-i - 1);
}


char	*quote(char *str, t_list *env)
{
	int		i;
	int		j;
	int		flag;
	char	*src;

	i = 0;
    j = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '$' && flag == 0)
		{
			j += num_env_word(&str[i + 1], env);
		}
		if (str[i] == '\'')
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		i++;
	}
    printf("i : %d\nj : %d\n", i, j);
	src = malloc(sizeof(char) * (i + j + 1));
    return (src);
}
int main()
{
    char str[] = "$as$$$$$$dd$QQ$ABC$nxQ$";
    t_list *env;

    env = malloc(sizeof(t_list) * 1); 
    env->env = "ABC=12345";
    env->next = NULL;
    quote(str, env);
}