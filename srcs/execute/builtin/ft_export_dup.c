#include "../../../includes/minishell.h"

static int ft_checkalldup(t_struct *s, char *str)
{
    if (ft_strccmp(s->env->content, str, '=', 0) == 0)
    {
        if (ft_strgetchar(str, '=') == 1)
        {
            if (ft_strncmp(str, "PATH=", 5) == 0)
            {
                s->data.env_path = ft_split((str), ':');
                s->data.env_path[0] = (s->data.env_path[0] + 5);
            }
            else if (ft_strncmp(str, "HOME=", 5) == 0)
            {
                printf("str = %s\n", str);
                s->home.content = str;
            }
            s->env->content = str;
        }
        return (0);
    }
}

static int ft_checkequal(t_struct *s, char *str)
{
    if (ft_strccmp(s->env->content, str, '=', 0) == 0)
    {
        if (ft_strgetchar(str, '=') == 1)
        {
            if (ft_strncmp(str, "PATH=", 5) == 0)
            {
                s->data.env_path = ft_split((str), ':');
                s->data.env_path[0] = (s->data.env_path[0] + 5);
            }
            else if (ft_strncmp(str, "HOME=", 5) == 0)
                s->home.content = str;
            s->env->content = str;
        }
        return (0);
    }
}

int ft_checkdup(t_struct *s, char *str)
{
    s->env = s->first;
    while (s->env->next != NULL)
    {
        if (ft_strccmp(s->env->content, str, '=', 0) == 0)
        {
            if (ft_checkalldup(s, str) == 0)
                return (0);
        }
        s->env = s->env->next;
    }
    if (ft_checkequal == 0)
        return (0);
    if (ft_strncmp(str, "PATH=", 5) == 0)
    {
        s->data.env_path = ft_split((str), ':');
        s->data.env_path[0] = (s->data.env_path[0] + 5);
    }
    else if (ft_strncmp(str, "HOME=", 5) == 0)
    {
        printf("str = %s\n", str);
        s->home.content = str;
    }
    return (1);
}