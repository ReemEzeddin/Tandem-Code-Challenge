
#include "trivia.h"

int		trivia(char *buffer, size_t i)
{
	struct  json_object *parsed_json;
	struct  json_object *question;
	struct  json_object *incorrect;
	struct  json_object *incorrect1;
	struct  json_object *correct;
	size_t  n_incorrects;
	size_t  j;
	int		points;
	int		num;
	int     correctNumber;
	int		answer;

	num  = 0;
	j = 0;
	correctNumber = -1;
	answer = 0;
	n_incorrects = 0;
	points = 0;
 	parsed_json = json_tokener_parse(buffer);
	json_object_object_get_ex(parsed_json, "question", &question);
	json_object_object_get_ex(parsed_json, "incorrect", &incorrect);
	json_object_object_get_ex(parsed_json, "correct", &correct);
	printf("\n **************************************************\n\n");
	printf(" Q%ld --> %s\n",i , json_object_get_string(question));
	num = 0;
	correctNumber = rand() % 4;
	n_incorrects = json_object_array_length(incorrect);
	j = 0;
	while (j < n_incorrects)
	{
		if (num++ == correctNumber)
		{
			printf(" %d _ %s\n", num,  json_object_get_string(correct));
			continue;
		}
		else
		{
			incorrect1 = json_object_array_get_idx(incorrect, j++);
			 printf(" %d _ %s\n",num ,json_object_get_string(incorrect1));
		}
		if (j == n_incorrects && num == correctNumber)
			printf(" %d _ %s\n", ++num, json_object_get_string(correct));
	}
		answer = get_answer(num);
		points += check_answer(answer, correctNumber, correct);
		json_object_put(incorrect1);
		json_object_put(question);
		json_object_put(incorrect);
		json_object_put(parsed_json);
		json_object_put(correct);
		return(points);
}  

int main()
{

	FILE	*fp;
	char	*buffer;
	char	*restrict firstline;
	size_t	i;
	int		points;
	int		flag;

	points = 0;
	flag = 0;
	fp = fopen("trivia.json","r");
	firstline = malloc(10);
	fgets(firstline, 10, fp);
	i = 0;
	start();
	printf("\nEnter the number of the correct answer followed by enter key..\n");
	while (1)
	{	
		i++;
		buffer = malloc(4568);
		memset(buffer , '\0', strlen(buffer));
		flag = get_buffer(fp, buffer);
		if(flag == -1)
		{
			printf("       ...... Finished ......\n");
			print_score(points, i, 1);
			break;
		}
		buffer[strlen(buffer) - (flag - 1)] = '\0';
		points += trivia(buffer, i);
		print_score(points, i, 0);
		to_continue();
		free(buffer);
	}
	free(buffer);
	fclose(fp);
}
