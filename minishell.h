/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:57 by transfo           #+#    #+#             */
/*   Updated: 2024/03/08 11:51:38 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "1st-Project-Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>


typedef struct s_len
{
    int compteur_outfile;
    int compteur_outfile_append;
    int compteur_infile;
    int compteur_here_doc;
}                   t_len;


typedef enum s_type
{
    commande,
    argument,
    trunc,
    append,
    input,
    pip,
    here_doc,
}           t_type;


typedef struct s_data
{
    char **cmd_arg;
    char **outfile;
    char **outfile_append;
    char **infile;
    char **here_doc;

    struct s_data *prev;
    struct s_data *next; 
}                   t_data;


typedef struct	s_token
{
	char			str[3000];
	t_type				type;
	struct s_token	*prev;
	struct s_token	*next;
}                   t_token;


typedef struct s_programme
{
    char *args;
    char *const *split_args;
    t_token **liste_token;
    t_data **liste_data;
   
}   t_programme;


// init et free
void init_data(t_programme *programme);
void free_programme(t_programme *programme);
void free_t_token(t_token *token);
void free_t_data(t_data *data);

// parsing
int parse(t_programme *programme);
int check_quotes(char *str);
char *add_space_redirection(char *str);
void get_tokens(t_token **liste_token, char **args);
int add_data(t_programme *programme);

    // token
    t_type get_type_arg(t_token *token, char *str);
    t_token	*ft_newtoken(char *str);
    void add_back_front(t_token **liste_token, t_token *new);

    // data
    void init_compteurs(t_len *len);
    int remplir_data(char *str, char **tab, int compteur);
    t_data *parse_redirection(t_token *current, t_programme *programme, t_data *new);
    t_data *ft_newcmd(t_programme *programme, t_token *current);
    void add_back_fronts(t_data **liste_data, t_data *new);
    t_data *algo_outfile(t_token *current, t_data *new);
    t_data *algo_infile(t_data *new, int position, char *last_outfile);
    char *find_last_outfile(char **tab);
    t_data *algo_redirection(t_token *current, t_programme *programme, t_data *new, t_len *len);
    int compare(char *str, char *strr);

// execution
int redirection(char *file, int i);
char *find_path(char *const *envp, char *const cmd);
void exec(char *const * av, char *const *envp);
void test(t_programme *programme);

#endif