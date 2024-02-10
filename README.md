# My-Enhanced-Pico-Shell
This project focuses on enhancing and cleaning up my Pico Shell, which already includes built-in functionalities such as echo, pwd, cd, and exit commands. The implementation involves robust command line parsing to handle user input, breaking it into arguments with space as the separator. For commands other than the built-ins, the shell utilizes fork/exec system calls for execution. Notably, the shell supports executing programs using their names directly, eliminating the need for the full path.

To enhance flexibility and prevent memory leaks, dynamic allocation is employed for managing arguments. As an optional feature, I/O redirection has been implemented, providing users with extended functionality for managing input and output streams.

Explore and contribute to this improved Pico Shell, making command-line interactions more seamless and efficient.
