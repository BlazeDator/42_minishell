
#include "../inc/minishell.h"

void 	exec_cd(char *cd, char **envp)
{
	char *home_dir;
	char current_dir[PATH_MAX];
	char *new_dir;

	home_dir = getenv("HOME");
	if (cd == NULL || ft_strcmp(cd, "~") == 0)
		chdir(home_dir);
	else if (ft_strcmp(cd, "..") == 0)
	{
			chdir("..");
			return ;
	}
	else if (cd[0] == '$')
	{
		new_dir = find_expand_variable(cd, envp);
		if (chdir(new_dir) != 0)
			printf("cd: %s: No such file or directory\n", cd);
		return;
	}
	else
	{
		getcwd(current_dir, sizeof(current_dir));
		ft_strlcpy(current_dir, "/", 1);
		new_dir = ft_strjoin(current_dir, cd);
		if (chdir(new_dir) != 0)
			printf("cd: %s: No such file or directory\n", new_dir);
		free(new_dir);
	}
}

char *find_expand_variable(char *str, char **envp)
{
	int i;
	char *dir;
	size_t len_str;

	i = 0;
	dir = NULL;
	str++;
	len_str = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], len_str - 1))
			dir = ft_substr(envp[i],  len_str + 1, ft_strlen(envp[i]));
		i++;
	}
	return (dir);
}

