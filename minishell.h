/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:57 by transfo           #+#    #+#             */
/*   Updated: 2024/03/26 13:51:36 by tburtin          ###   ########.fr       */
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


typedef struct s_liste
{
    char *cle;
    char *valeur;
    struct s_liste *next; 
}                   t_liste;

typedef struct s_len
{
    int compteur_commande;
    int compteur_outfile;
    int compteur_append;
    int compteur_infile;
    int compteur_heredoc;
    int flag1;
    int flag2;
}                   t_len;


typedef enum s_type
{
    commande,
    argument,
    outfile,
    append,
    infile,
    pip,
    here_doc,
    none,
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
	char			*str;
	t_type				type;
	struct s_token	*prev;
	struct s_token	*next;
}                   t_token;


typedef struct s_programme
{
    char *args;
    char *const *split_args;
    t_token **liste_token;
    t_list **liste_variable;
    
    t_data **liste_data;
    t_list **liste_env;
}   t_programme;


// init_free
void init_programme(t_programme *programme, char **envp);
void free_programme(t_programme *programme);
void init_data(t_programme *programme);
void free_data(t_programme *programme);
    //utils_init_free
    void free_t_token(t_token *token);
    void free_t_data(t_data *data);
    void free_t_liste(t_list *var);
    
// parsing
int parse(t_programme *programme);
int check_quotes(char *str);
char *add_space(char *str);
int get_tokens(char **args, t_programme *programme);
void add_data(t_data **liste_data, t_token *liste_token);

    // token
    t_token	*ft_newtoken(char *str, t_programme *programme);
    void create_commande(t_token *new, char *str, t_programme *programme);
    void add_back_front(t_token **liste_token, t_token *new);
    t_type get_type_arg(t_token **liste_token);
    int modife_liste(t_token *current, t_type type, t_token **liste_token);
        // utils_token
        char **find_value(t_list *list, char *cle);
        int len_commande(char *str, t_programme *programme);
        int len_var(char *str, int *i, t_programme *programme);
        void input_var(t_token *new, char *str, t_programme *programme, int *i, int *j);
        char *extracte_cle(char *str, int *i);

    // data
    t_data *ft_newcmd(t_token *liste_token);
    void add_back_fronts(t_data **liste_data, t_data *new);
    void allocation_tab(t_len len, t_data *new);
    void input_all_tab(t_token *liste_token, t_data *new);
    void len_all_tab(t_token *liste_token, t_len *len, int position);
        // utils_data
        void algo_outfile(t_token *liste_token, t_data *new);
        void algo_infile(t_data *new, int position, char *last_outfile);
        char *find_last_outfile(char **tab);
        int remplir_data(char *str, char **tab, int compteur);
        void check_position(t_token *liste_token, int *position);
        void init_compteurs(t_len *len);

// variable
int variable(t_programme *programme);
int check_ifonly_var(char **cmd_arg);
void remplir_liste(char **tab, t_list **list);
char **replace_commande(char **cmd_arg, int index);
    // utils_variable
    int	check_already_exist(char *variable_split, t_list *list);
    void replace_var(int index, char *var, t_list **list);

// chek_command
int chek_command(t_data *liste_data);

// execution
void test(t_programme *programme);

#endif