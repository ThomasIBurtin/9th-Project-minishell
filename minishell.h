/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:57 by transfo           #+#    #+#             */
/*   Updated: 2024/03/19 00:52:39 by transfo          ###   ########.fr       */
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


typedef struct s_variable
{
    char *cle;
    char *valeur;
    struct s_variable *next; 
}                   t_variable;

typedef struct s_len
{
    int compteur_commande;
    int compteur_outfile;
    int compteur_append;
    int compteur_infile;
    int compteur_heredoc;
}                   t_len;


typedef enum s_type
{
    commande,
    argument,
    trunc,
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
    t_data **liste_data;
    t_variable **liste_variable;
}   t_programme;


// init et free
void init_data(t_programme *programme);
void free_programme(t_programme *programme);
void free_t_token(t_token *token);
void free_t_data(t_data *data);
void free_t_variable(t_variable *variable);

// parsing
int parse(t_programme *programme);
int check_quotes(char *str);
char *add_space_redirection(char *str);
int get_tokens(t_token **liste_token, char **args, t_variable *liste_variable);
void add_data(t_data **liste_data, t_token **liste_token);

    // token
    t_token	*ft_newtoken(char *str, t_variable *liste_variable);
    void add_back_front(t_token **liste_token, t_token *new);
    t_type get_type_arg(t_token **liste_token);
    int modife_liste(t_token *current, t_type type, t_token **liste_token);
    
        // utils_token
        void len_commande(char *str, t_variable *liste_variable, t_token *new);
        void create_commande(t_token *new, char *str, t_variable *liste_variable);
        int len_var(char *str, int *i, t_variable *liste_variable);
        void input_var(t_token *new, char *str, t_variable *liste_variable, int *i, int *j);
        char *extracte_cle(char *str, int *i);

    // data
    t_data *ft_newcmd(t_token *current);
    void add_back_fronts(t_data **liste_data, t_data *new);
    void input_all_tab(t_token *current, t_data *new);
    void len_all_tab(t_token *current, t_len *len, int position);
    
        // utils_data
        void algo_outfile(t_token *current, t_data *new);
        void algo_infile(t_data *new, int position, char *last_outfile);
        char *find_last_outfile(char **tab);
        int remplir_data(char *str, char **tab, int compteur);
        void init_compteurs(t_len *len);
        void allocation_tab(t_len len, t_data *new, int position, t_token *current, char *last_outfile);

// variable
int variable(t_programme *programme);
int check_ifonly_var(char **cmd_arg);
void remplir_liste_var(char **cmd_arg, t_programme *programme);
char **replace_commande(char **cmd_arg, int index);
        
        // utils_variable
        void replace_value(int index, t_variable *liste_variable, int len_valeur, char *str);
        int check_if_exsite(char *str, t_variable *liste_variable, int len_cle);
        void add_back_frontss(t_variable **liste_variable, t_variable *new);
        t_variable *new_variable(char *str, int len_cle, int len_valeur);

// execution
void test(t_programme *programme);

#endif