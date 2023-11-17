#include "custom_shell.h"

/**
 * custom_exit - Exits the custom shell.
 * @data: Structure containing relevant information.
 *
 * Return: Exits with a given exit status.
 *         (0) if data->arguments[0] != "exit"
 */
int custom_exit(shell_data_t *data)
{
    int exit_code;

    if (data->arguments[1])  /* If there is an exit argument */
    {
        exit_code = _custom_atoi(data->arguments[1]);
        if (exit_code == -1)
        {
            data->status = 2;
            print_custom_error(data, "Illegal number: ");
            _custom_puts(data->arguments[1]);
            _custom_putchar('\n');
            return (1);
        }
        data->error_number = _custom_atoi(data->arguments[1]);
        return (-2);
    }
    data->error_number = -1;
    return (-2);
}

/**
 * custom_change_directory - Changes the current directory of the process.
 * @data: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int custom_change_directory(shell_data_t *data)
{
    char *current_dir, *target_dir, buffer[1024];
    int chdir_result;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _custom_puts("TODO: >>getcwd failure emsg here<<\n");
    
    if (!data->arguments[1])
    {
        target_dir = _get_custom_env(data, "HOME=");
        if (!target_dir)
            chdir_result = chdir((target_dir = _get_custom_env(data, "PWD=")) ? target_dir : "/");
        else
            chdir_result = chdir(target_dir);
    }
    else if (_custom_strcmp(data->arguments[1], "-") == 0)
    {
        if (!_get_custom_env(data, "OLDPWD="))
        {
            _custom_puts(current_dir);
            _custom_putchar('\n');
            return (1);
        }
        _custom_puts(_get_custom_env(data, "OLDPWD=")), _custom_putchar('\n');
        chdir_result = chdir((target_dir = _get_custom_env(data, "OLDPWD=")) ? target_dir : "/");
    }
    else
        chdir_result = chdir(data->arguments[1]);

    if (chdir_result == -1)
    {
        print_custom_error(data, "can't cd to ");
        _custom_eputs(data->arguments[1]), _custom_eputchar('\n');
    }
    else
    {
        _set_custom_env(data, "OLDPWD", _get_custom_env(data, "PWD="));
        _set_custom_env(data, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * custom_help - Displays help information.
 * @data: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int custom_help(shell_data_t *data)
{
    char **arg_array;

    arg_array = data->arguments;
    _custom_puts("help call works. Function not yet implemented \n");
    if (0)
        _custom_puts(*arg_array); /* temp att_unused workaround */
    return (0);
}

