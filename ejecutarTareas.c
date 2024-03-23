#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 100

int main() {
    FILE *archivo;
    char linea[MAX_LINE_LENGTH];

    archivo = fopen("tareas.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    while (fgets(linea, MAX_LINE_LENGTH, archivo) != NULL) {
        // Eliminar el salto de línea al final de la línea
        linea[strcspn(linea, "\n")] = 0;

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            // Proceso hijo
            if (execlp(linea, linea, NULL) < 0) {
                perror("exec");
                exit(1);
            }
        } else {
            // Proceso padre
            wait(NULL); // Esperar a que el proceso hijo termine
        }
    }

    fclose(archivo);
    return 0;
}
