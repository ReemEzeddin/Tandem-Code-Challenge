
#include "trivia.h"

void	start(void)
{
	char	*start;
	size_t	flag;

	start = (char *)malloc(10);
	flag = 0; 	
	do{
		printf("When you are ready to start the game, enter 'GO'\n");
		fgets(start , 10, stdin);
		*start = toupper((unsigned char) *start);
		if (*start++ == 'G')
		{
			*start = toupper((unsigned char) *start);
			if(*start == 'O')
				flag = 1;
		}
		}while(!flag);
}
int		get_buffer(FILE *fp, char *buffer)
{
	char	*restrict line;
	int		flag;

	flag = 3;
	 do{
		line = malloc(500);
		fgets(line, 500, fp);
		if(line[0] == ']')
			return (-1);
		buffer = strcat(buffer, line);
		if(line[strlen(line) - 2] == '}')
			flag = 2;
		}while (line[strlen(line) - flag] != '}');
	free(line);
	return(flag);
}
int		get_answer(int num)
{
	char	*answer;
	int		intAnswer;
	 answer = (char *)malloc(50);
	do{
		printf("\nYour answer is :  ");
		fgets(answer, 50, stdin);
		intAnswer = atoi(answer);
		if( intAnswer <= num  && intAnswer > 0)
			return(intAnswer);
		else
		printf("please enter a valid input\n");
		}while(1);
	return(0);
}

int		check_answer(int answer,int correctNumber,struct  json_object *correct)
{
	int	points;

	points = 0;
   if (answer - 1 == correctNumber)
	{
		printf("\n *********** CORRECT :D **********\n");
		points = 1;
	}
	else
	{
		printf("\n *********** NOT correct :( **********\n");
		printf("--- The correct answer is **  %s  **\n", json_object_get_string(correct));
	}
	  json_object_put(correct);
	return(points);
}

void	print_score(double points,double base, int finished)
{
	double	score;

	score = 0.0;
	score = 100 * (points / base);
	if (finished == 1)
		printf(" your final score is >>>>> %.2f %c\n\n", score, '%'); 
	else
		printf(" --- Your score till now is >>>>> %.2f %c\n\n", score, '%');
}

void	to_continue(void)
{
	char	*cont;

	cont = (char *)malloc(20);
	do{
		printf("Enter Y if you are ready to contiue followed by enter key\n");
		fgets(cont, 20, stdin);
		*cont = toupper(*cont);
		}while (!(*cont == 'Y'));
}
