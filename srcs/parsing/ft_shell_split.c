//char	**malloc_cmd(char **str, int start)
//{
//		char **cmd;
//		int nb_word;
//
//		nb_word = start;
//		while (str[nb_word] && str[nb_word][0] != '|')
//				nb_word++;
//		cmd = malloc(sizeof(char *) * (nb_word - start + 1));
//		if (cmd == NULL)
//				return (NULL);
//		return (cmd);
//}
//
//char	**one_cmd(char **str)
//{
//		char	**cmd;
//		int nb_word;
//
//		cmd = malloc_cmd(str);
//		if (cmd == NULL)
//				return (NULL);
//
//		nb_word = 0;
//		while (cmd[nb_word] && cmd[nb_word][0] != '|')
//				nb_word++;
//}
