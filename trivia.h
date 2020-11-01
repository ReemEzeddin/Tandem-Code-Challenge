
#ifndef TRIVIA_H
# define TRIVIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <ctype.h>

void	start(void);
int		get_buffer(FILE *fp, char *buffer);
int		get_answer(int num);
int		check_answer(int answer, int correctNumber, struct json_object *correct);
int		trivia(char *buffer, size_t i);
void	print_score(double points, double base, int finished);
void	to_continue(void);

#endif
