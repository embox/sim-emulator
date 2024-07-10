#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Function prototypes
void profileDownload();
void installProfile();
void disableProfile();
void exitEmulator();

void start_process(const char *program, int pipefd[2]);
void read_from_pipe(int pipefd[2], const char *process_name);

int main() {
    int choice;

    // Display the menu
    printf("\nWelcome to eSIM Emulator:\n");
    printf("1. Profile Download\n");
    printf("2. Install Profile\n");
    printf("3. Delete Profile\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Handle the user's choice
    switch (choice) {
        case 1:
            profileDownload();
            break;
        case 2:
            installProfile();
            break;
        case 3:
            disableProfile();
            break;
        case 4:
            exitEmulator();
            break;
        default:
            printf("Invalid choice, please try again.\n");
    }

    return 0;
}

void profileDownload() {
    // Message to user 
    printf("\n->Initiating profile download procedure\n");
    printf("->Establishing Secure Connection between IPAd and eIM \n");

    int server_pipe[2];
    int client_pipe[2];

    // Create pipes
    if (pipe(server_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(client_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Start the server process
    printf("\nStarting eIM as server...\n");
    start_process("./architecture/eIM", server_pipe);

    // Give the server some time to start up and listen
    sleep(2);

    // Start the client process
    printf("\nStarting IPAd as client...\n");
    start_process("./architecture/IoTDevice/IPAd", client_pipe);

    // Read and print the outputs from both processes
    read_from_pipe(server_pipe, "Server");
    read_from_pipe(client_pipe, "Client");

    // Message to user
    printf("\n->Re-establishing Secure Connection between IPAd and SM-DPPlus\n");

    // Recreate pipes for the next pair of processes
    if (pipe(server_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(client_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Start the SM-DPPlus process
    printf("\nStarting SM-DPPlus as server...\n");
    start_process("./architecture/SM-DPPlus", server_pipe);

    // Give the server some time to start up and listen
    sleep(2);

    // Start the client process again
    printf("\nStarting IPAd as client...\n");
    start_process("./architecture/IoTDevice/IPAd", client_pipe);

    // Read and print the outputs from both processes
    read_from_pipe(server_pipe, "Server");
    read_from_pipe(client_pipe, "Client");
}

void installProfile() {
    
    printf("Installing profile \n");

    char input_data[] = "TS48 V3.0 eSIM_GTP_SAIP2.1_BERTLV.txt\n";
    char command[256];
    sprintf(command, "echo \"%s\" | python architecture/IoTDevice/eUICC/profileInstaller.py", input_data);
    int result = system(command);

    if (result == 0) {
        printf("Installation executed successfully.\n");
    } else {
        printf("Error executing installation script.\n");
    }

    
}

void disableProfile() {
    printf("You have entered Mode 3.\n");
    // Add more functionality here for Mode 3
}

void exitEmulator() {
    printf("Exiting the emulator. Goodbye!\n");
    exit(0); // Exit the program
}

void start_process(const char *program, int pipefd[2]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Close the read end of the pipe
        close(pipefd[0]);

        // Redirect stdout to the write end of the pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe (it's duplicated now)
        close(pipefd[1]);

        // Execute the program
        execl(program, program, (char *)NULL);
        // If execl fails
        perror("execl");
        exit(EXIT_FAILURE);
    }
}

void read_from_pipe(int pipefd[2], const char *process_name) {
    // Close the write end of the pipe
    close(pipefd[1]);

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Read the output of the process from the pipe
    while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, sizeof(char), bytesRead, stdout);
    }

    // Close the read end of the pipe
    close(pipefd[0]);

    // Wait for the process to finish
    int status;
    wait(&status);
    if (WIFEXITED(status)) {
        printf("%s exited with status %d\n", process_name, WEXITSTATUS(status));
    } else {
        printf("%s did not exit normally\n", process_name);
    }
}
