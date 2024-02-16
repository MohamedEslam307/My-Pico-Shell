#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define MAX_PATH_SIZE	100

/**
 * @breif : -this funtion displays a line of text like echo in the shell  
 * 	    	
 * @parameters : -Node * cmd_line_data: it's a pointer to the node where the input command line stored in
 * 		  , number of arguments and num of redirections
 *
 * @return : -the function returns 0 if it executed correctly and 1 othewise
 *
 */
char my_echo(Node * cmd_line_data);
/**
 * @breif : -this funtion Changes the current directory to the entered direcory
 * 	     by the user
 *
 * @parameters : -char **parsed_input_string: it's a pointer to 2-d array of the input command line
 * 					      which contains the directory the user want
 *               -char arguments_size: it's number of arguments in that command line
 *
 * @return : -the function returns 0 if it executed correctly
 * 	     -1 if the directory can't be reached
 * 	     -2 if the user entered wrong number of argumenrs to cd
 *
 */
char my_cd(char **parsed_input_string, char arguments_size);
/**
 * @breif : -this funtion print name of current/working directory
 *
 * @parameters : -void
 *
 * @return : -the function returns 0 if it executed correctly
 * 	     -1 if the size exceeds the configured max path size for the directory
 *
 */
char my_pwd(void);
/**
 * @breif : -it parses the command line entered by the user and dived it into arguments
 * 	     and allocate them dynamicly for flexible number of arguments
 * 	    -it's also support multiple successive spaces
 *
 * @parameters : -char *string : it's a pointer to 1-d array contains the line which the user entered
 * 		 -char *arguments_num : it's a poiter to the variable at which the function would return
 * 		 		        the arguments number 
 *
 * @return : -the function returns the address of the dynamiclly allocated 2-d array which contains the
 * 	      command line
 *
 */
char **parse_line(char *string, char *arguments_num);
/**
 * @breif : -this function execute the I/O Redirections ( < , > , 2> )
 * 	    -it allows users to use the input or the output of a file instead of stdin and stdout
 * 	    -it also support multiple I/O Redirections
 *
 * @parameters : -Node * cmd_line_data: it's a pointer to the node where the input command line stored in
 * 		  , number of arguments and num of redirections
 *
 * @return : -the function returns 0 if it executed correctly , 1 othewise
 *
 */
char execute_io_redirections(Node * cmd_line_data);
/**
 * @breif : -this function execute the output Redirections ( > )
 *
 * @parameters : -char *output_file: -It's a pointer to the path file which the output would print on
 *	
 * @return : -the function returns 0 if it executed correctly , 1 othewise
 *
 */
char execute_output_redirection(char *output_file);
/**
 * @breif : -this function execute the error Redirections ( 2> )
 *
 * @parameters : -char *error_file: -It's a pointer to the path file which the error would print on
 *
 * @return : -the function returns 0 if it executed correctly , 1 othewise
 *
 */
char execute_error_redirection(char *error_file);
/**
 * @breif : -this function execute the input Redirections ( < )
 *
 * @parameters : -char *input_file: -It's a pointer to the path file which the input would taken from
 *
 * @return :-the function returns 0 if it executed correctly , 1 othewise
 *
 */
char execute_input_redirection(char *input_file);
/**
 * @breif : -this function execute the input Redirections ( < )
 *
 * @parameters : -Node * cmd_line_data: it's a pointer to the node where the input command line stored in
 * 		  , number of arguments and num of redirections
 *               -char **parsed_input_string: it's a pointer to 2-d array of the input command line
 * 					      which contains the directory the user want
 *               -char arguments_size: it's number of arguments in that command line
 * @return :-the function returns 0 if it executed correctly , 1 othewise
 *
 */
char calculate_num_of_io_redirections(char **parsed_input_string,
				      char arguments_size,
				      char *redirections_num,
				      Node * command_node_ptr);
int main()
{
    char *command_line;
    char **parsed_input_string;
    int size_input_string = 0;
    char arguments_size = 0;
    unsigned long n = 0;
    char ret = 0;
    linkedlist list;
    Node *command_line_node_ptr = NULL;
    char num_of_redirections = 0;
    pid_t pid_ret;
    int wstatus;
    list.listSize = 0;
    list.head = NULL;
    printf
	("\n-------------------------- Welcome To My PicoShell --------------------------\n\n");

    while (1) {
	printf(">>>>");

	size_input_string = getline(&command_line, &n, stdin);	// get the command line from user

	if ((command_line[0] == '\n')) {
	    continue;
	}

	command_line[strlen(command_line) - 1] = 0;	//remove '\n' from the end of the line
	parsed_input_string = parse_line(command_line, &arguments_size);	//parsing the line into 2-d array

	command_line_node_ptr =
	    addNode(&list, parsed_input_string, arguments_size);

	ret =
	    calculate_num_of_io_redirections(parsed_input_string,
					     arguments_size,
					     &num_of_redirections,
					     command_line_node_ptr);

	if (parsed_input_string != NULL) {
	    if ('!' == parsed_input_string[0][0]) {
		int line_num = atoi((parsed_input_string[0] + 1));	//convert the number after '!' into integer
		Node *node_ptr = list.head;
		for (int i = 1; i < line_num; i++) {
		    node_ptr = node_ptr->next;
		}
		parsed_input_string = node_ptr->Data;	// copy the data from the line into the parsed_input_string array 
		command_line_node_ptr->Data = node_ptr->Data;	// copy the data from the line into the command line node array 
		command_line_node_ptr->num_of_arguments = node_ptr->num_of_arguments;	// copy the number of arguments from the line into the command line node array 
		command_line_node_ptr->num_of_redirections =
		    node_ptr->num_of_redirections;
		num_of_redirections = node_ptr->num_of_redirections;

		for (int i = 0; i < node_ptr->num_of_arguments+node_ptr->num_of_redirections*2; i++) {
		    printf("%s ", parsed_input_string[i]);	// print the seleced line
		}
		printf("\n");
	    }

	    if ((strcmp(parsed_input_string[0], "exit") == 0)) {
		destroyList(&list);
		break;
	    } else if (strcmp(parsed_input_string[0], "history") == 0) {
		pid_ret = fork();
		if (pid_ret > 0) {
		    //wait the child process to terminate
		    wait(&wstatus);
		} else if (pid_ret == 0) {
		    ret = execute_io_redirections(command_line_node_ptr);
		    //execute the command
		    if (ret == 0) {
			Print(&list);
			return 0;
		    } else {
			printf
			    ("ERROR: faild to execute i/o redirections\n");
		    }
		} else {
		    printf("ERROR: I could not get a child\n");
		}

	    } else if (strcmp(parsed_input_string[0], "echo") == 0) {
		pid_ret = fork();
		if (pid_ret > 0) {
		    //wait the child process to terminate
		    wait(&wstatus);
		} else if (pid_ret == 0) {
		    ret = execute_io_redirections(command_line_node_ptr);

		    //execute the command
		    ret = my_echo(command_line_node_ptr);
		    return ret;
		} else {
		    printf("ERROR: I could not get a child\n");
		}

	    } else if ((strcmp(parsed_input_string[0], "cd") == 0)) {
		ret = my_cd(parsed_input_string, arguments_size);
	    } else if ((strcmp(parsed_input_string[0], "pwd") == 0)) {
		pid_ret = fork();
		if (pid_ret > 0) {
		    //wait the child process to terminate
		    wait(&wstatus);
		} else if (pid_ret == 0) {
		    ret = execute_io_redirections(command_line_node_ptr);

		    //execute the command
		    ret = my_pwd();
		    return ret;
		} else {
		    printf("ERROR: I could not get a child\n");
		}
	    } else {
		//fork the process to create a chile process to execute the command
		pid_ret = fork();
		if (pid_ret > 0) {
		    //wait the child process to terminate
		    wait(&wstatus);
		} else if (pid_ret == 0) {
		    ret = execute_io_redirections(command_line_node_ptr);

		    //execute the command
		    execvp(parsed_input_string[0], parsed_input_string);
		    //if the execvp function executed correctly the program won't return here
		    printf("ERROR: Command not found\n");
		    return -1;
		} else {
		    printf("ERROR: I could not get a child\n");
		}
	    }
	    num_of_redirections = 0;
	    free(command_line);
	    command_line = NULL;
	}
    }

    return 0;
}

char execute_error_redirection(char *error_file)
{
    char ret = 1;
    int file_descriptor = 0;
    if (NULL == error_file) {
	ret = 1;
    } else {
	// open a file to print errors in it
	file_descriptor =
	    open(error_file, O_RDWR | O_CREAT | O_TRUNC, 0644);

	if (file_descriptor != -1) {	// if the file opened correcltly
	    ret = dup2(file_descriptor, 2);	//creates a copy of the file_descriptor closed fd 2 and 
	    //make it points to the copy we made atomiclly

	    ret = close(file_descriptor);
	} else {
	    printf("%s Faild to be created\n", error_file);
	    ret = 1;
	}
    }
    return ret;

}

char execute_input_redirection(char *input_file)
{
    char ret = 1;
    int file_descriptor = 0;
    if (NULL == input_file) {
	ret = 1;
    } else {
	// open a file to take input from it
	file_descriptor =
	    open(input_file, O_RDONLY | O_CREAT | O_TRUNC, 0644);

	if (file_descriptor != -1) {	// if the file opened correcltly
	    ret = dup2(file_descriptor, 0);	//creates a copy of the file_descriptor closed fd 0 and 
	    //make it points to the copy we made atomiclly

	    ret = close(file_descriptor);
	} else {
	    printf("%s Faild to be created\n", input_file);
	    ret = 1;
	}
    }
    return ret;

}

char execute_output_redirection(char *output_file)
{
    char ret = 1;
    int file_descriptor = 0;
    if (NULL == output_file) {
	ret = 1;
    } else {
	// open a file to print output on it
	file_descriptor =
	    open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (file_descriptor != -1) {	// if the file opened correcltly
	    ret = dup2(file_descriptor, 1);	//creates a copy of the file_descriptor closed fd 1 and 
	    //make it points to the copy we made atomiclly

	    ret = close(file_descriptor);
	} else {
	    printf("%s Faild to be created\n", output_file);
	    ret = 1;
	}
    }
    return ret;

}

char calculate_num_of_io_redirections(char **parsed_input_string,
				      char arguments_size,
				      char *redirections_num,
				      Node * command_node_ptr)
{
    char ret = 1;
    if ((NULL == parsed_input_string)) {
	ret = 1;
    } else {
	//compare all the line elemnts with the i/o redirections
	for (int index = 0; index < arguments_size; index++) {
	    if ((strcmp(parsed_input_string[index], ">") == 0)) {
		(*redirections_num)++;
	    } else if ((strcmp(parsed_input_string[index], "2>") == 0)) {
		(*redirections_num)++;
	    } else if ((strcmp(parsed_input_string[index], "<") == 0)) {
		(*redirections_num)++;
	    } else {
		continue;
	    }
	    command_node_ptr->num_of_redirections = *redirections_num;
	    command_node_ptr->num_of_arguments-=(command_node_ptr->num_of_redirections*2);
	}
	ret = 0;
    }
    return ret;
}

char execute_io_redirections(Node * cmd_line_data)
{
    char ret = 1;
    if ((NULL == cmd_line_data)) {
	ret = 1;
    } else {
	//compare all the line elemnts with the i/o redirections
	for (int index = 0; index < cmd_line_data->num_of_arguments + cmd_line_data->num_of_redirections;
	     index++) {
	    if ((strcmp(cmd_line_data->Data[index], ">") == 0)) {

		ret =
		    execute_output_redirection(cmd_line_data->Data
					       [index + 1]);
	    } else if ((strcmp(cmd_line_data->Data[index], "2>") == 0)) {
		ret =
		    execute_error_redirection(cmd_line_data->Data
					      [index + 1]);

	    } else if ((strcmp(cmd_line_data->Data[index], "<") == 0)) {
		ret =
		    execute_input_redirection(cmd_line_data->Data
					      [index + 1]);
	    } else {
		continue;
	    }
	}
	ret = 0;
    }
    return ret;

}
char my_echo(Node * cmd_line_data)
{
    char ret = 1;
    if (NULL == cmd_line_data) {
	ret = 1;
    } else {
	if (1 == cmd_line_data->num_of_arguments) {
	    printf("\n");	//if the user echo nothing it prints new line
	    ret = 0;
	} else {
	    char arg_index = 1;
	    //printing the arguments the user entered
	    for (arg_index = 1;
		 arg_index < cmd_line_data->num_of_arguments; arg_index++)
	    {
		printf("%s ", cmd_line_data->Data[arg_index]);
	    }
	    printf("\n");
	    ret = 0;
	}
    }
    return ret;
}

char my_cd(char **parsed_input_string, char arguments_size)
{
    char ret = 1;
    if (NULL == parsed_input_string) {
	ret = 1;
    } else {
	if (2 == arguments_size) {
	    //chdir returns 0 when it execute correctly 
	    if (chdir(parsed_input_string[1]) != 0) {
		printf("directory can't be reatched\n");
		ret = 1;
	    } else {
		ret = 0;
	    }
	} else {
	    printf("wrong number of argumenrs to cd\n");
	    ret = 2;
	}
    }
    return ret;
}

char my_pwd(void)
{
    char ret = 1;
    char *current_path = NULL;
    /*this function returns the path as string and null if the size exceeds max path size */
    current_path = getcwd(NULL, MAX_PATH_SIZE);
    if (NULL == current_path) {
	printf("size exceeds max path size current directory\n");
	ret = 1;
    } else {
	printf("%s\n", current_path);
	/*now freeing the allocated array */
	free(current_path);
	current_path = NULL;
	ret = 0;
    }
    return ret;
}

char **parse_line(char *string, char *arguments_num)
{
    char **parsed_string = NULL;
    int token_size = 0;
    int string_size = strlen(string);
    int arr_index = 0;
    *arguments_num = 1;
    //remove the spaces before the command line
    while ((arr_index < string_size) && (string[arr_index] == ' ')) {
	arr_index++;
    }
    //remove the spaces after the command line
    while ((string_size > 0) && (string[string_size - 1] == ' ')) {
	string_size--;
    }
    //this loop counts the number of arguments and skip spaces
    while (arr_index < string_size) {
	if (string[arr_index] == ' ') {	//skip spaces if the user pressed between arguments
	    if ((string[arr_index + 1] == ' ')) {
		arr_index++;
		continue;
	    } else {
		(*arguments_num)++;
		arr_index++;
	    }
	} else if (string[arr_index] == ' ') {

	} else {
	    arr_index++;
	}
    }
    char *token = strtok(string, " ");	//make token points to the frist word
    if (token == NULL) {	//there was no string
	*arguments_num = 0;
	parsed_string = NULL;
    } else {
	parsed_string = (char **) malloc(*arguments_num * sizeof(char *));	//allocate memory space by number of arguments
	for (arr_index = 0; arr_index < *arguments_num; arr_index++) {
	    token_size = strlen(token);	//calculate the size of every argument
	    parsed_string[arr_index] = (char *) malloc(token_size * sizeof(char));	//allocate memory space for every argument
	    strcpy(parsed_string[arr_index], token);	//copy a argument into an array elemnt
	    token = strtok(NULL, " ");	//make token points to the next word
	}
	return parsed_string;
    }
}
