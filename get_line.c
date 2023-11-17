#include "custom_shell.h"

/**
 * custom_get_input - Read user input from stdin.
 * Return: User input as a string.
 */
char *custom_get_input()
{
    int index, buffer_size = CUSTOM_BUFSIZE, read_count;
    char current_char = 0;
    char *input_buffer = malloc(buffer_size);

    if (input_buffer == NULL)
    {
        free(input_buffer);
        return (NULL);
    }

    for (index = 0; current_char != EOF && current_char != '\n'; index++)
    {
        fflush(stdin);
        read_count = read(STDIN_FILENO, &current_char, 1);

        if (read_count == 0)
        {
            free(input_buffer);
            exit(EXIT_SUCCESS);
        }

        input_buffer[index] = current_char;

        if (input_buffer[0] == '\n')
        {
            free(input_buffer);
            return ("\0");
        }

        if (index >= buffer_size)
        {
            input_buffer = custom_realloc(input_buffer, buffer_size, buffer_size + 1);

            if (input_buffer == NULL)
            {
                return (NULL);
            }
        }
    }

    input_buffer[index] = '\0';
    custom_hashtag_handle(input_buffer);
    return (input_buffer);
}

/**
 * custom_hashtag_handle - Remove everything after # in the input.
 * @input_buffer: Input string.
 * Return: void
 */
void custom_hashtag_handle(char *input_buffer)
{
    int i;

    for (i = 0; input_buffer[i] != '\0'; i++)
    {
        if (input_buffer[i] == '#')
        {
            input_buffer[i] = '\0';
            break;
        }
    }
}

