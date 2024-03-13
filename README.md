# My-Enhanced-Femto-Shell
This project focuses on enhancing and cleaning up my Femto Shell, which already includes built-in functionalities such as echo, pwd, cd, export, linked list storing all pervious commands , printing them using history command. The implementation involves robust command line parsing to handle user input, breaking it into arguments with space as the separator. For commands other than the built-ins, the shell utilizes fork/exec system calls for execution. Notably, the shell supports executing programs using their names directly, eliminating the need for the full path.

To enhance flexibility and prevent memory leaks, dynamic allocation is employed for managing arguments. As an optional feature, I/O redirection has been implemented, providing users with extended functionality for managing input and output streams.

also some features like (!linenum) it execute the command line with from the previous commands you wrote eg. (!3) if the thrid command was echo hello theb perform it again
background operations eg. (gedit &)

Explore and contribute to this improved Pico Shell, making command-line interactions more seamless and efficient.
