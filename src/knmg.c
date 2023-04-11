#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

#define GRUB_CFG_PATH "/boot/grub/grub.cfg"
#define KERNEL_PATH "/boot/vmlinuz-%s"
#define INITRD_PATH "/boot/initrd.img-%s"
#define DEFAULT_KERNEL_OPTION "GRUB_DEFAULT=saved\nGRUB_SAVEDEFAULT=true\n"
#define DEFAULT_KERNEL_INDEX_PATH "/boot/grub/default"

void print_usage(char *program_name) {
    printf("Usage: %s <command> [kernel_version]\n", program_name);
    printf("Commands:\n");
    printf("  list                     - List available kernel versions\n");
    printf("  install [kernel_version] - Install a new kernel version\n");
    printf("  switch  [kernel_version] - Switch to a different kernel version\n");
}

void list_kernels() {
    printf("[~] Available kernel versions:\n");
    // Popen usage??????
    FILE *fp = popen("dpkg -l | grep linux-image | awk '{print $2}' | sed 's/linux-image-//'", "r");
    if (fp == NULL) {
        printf("[!] Error: cannot execute command 'dpkg'\n");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("- %s", line);
    }

    fclose(fp);

    // Print the currently running kernel
    struct utsname uname_data;
    if (uname(&uname_data) == 0) {
        printf("[~] Current kernel version: %s\n", uname_data.release);
    } else {
        printf("[!] Error: cannot get current kernel version\n");
    }
}

void install_kernel(char *kernel_version) {
    char command[256];

    sprintf(command, "sudo apt-get install linux-image-%s linux-headers-%s", kernel_version, kernel_version);
    system(command);

    // Update grub config
    system("sudo update-grub");
    printf("[+] Kernel version %s installed\n", kernel_version);
}

void switch_kernel(char *kernel_version) {
    char kernel_path[256];
    char initrd_path[256];
    char grub_default[256];
    int kernel_index = 0;

    // Building file paths
    sprintf(kernel_path, KERNEL_PATH, kernel_version);
    sprintf(initrd_path, INITRD_PATH, kernel_version);

    FILE *fp;
    char line[256];

    fp = fopen(GRUB_CFG_PATH, "r");
    if (fp == NULL) {
        printf("[!] Error: cannot open %s\n", GRUB_CFG_PATH);
        exit(1);
    }

    while (fgets(line, sizeof(line), fp)) {
        // Find the index of the kernel in the GRUB configuration file
        if (strstr(line, kernel_path) != NULL) {
            sprintf(grub_default, "GRUB_DEFAULT=%d\n", kernel_index);
            break;
        }
        if (strstr(line, "menuentry") != NULL) {
            kernel_index++;
        }
    }

    fclose(fp);

    // Write the index of the kernel to the GRUB default file
    FILE *fp_default;
    fp_default = fopen(DEFAULT_KERNEL_INDEX_PATH, "w");
    if (fp_default == NULL) {
        printf("[!] Error: cannot open %s\n", DEFAULT_KERNEL_INDEX_PATH);
        exit(1);
    }
	
	fputs(grub_default, fp_default);
    fclose(fp_default);
	printf("[+] Switched to kernel version %s\n", kernel_version);
}

int main(int argc, char *argv[]) {
	// Sudo check!
	if (geteuid() != 0){
        printf("[!] Please run this program as sudo!\n");
		exit(EXIT_FAILURE);
    }

	if (argc < 2) {
        print_usage(argv[0]);
        return 1;
	}

	if (strcmp(argv[1], "list") == 0) {
        list_kernels();
	}

	else if (strcmp(argv[1], "install") == 0) {
		if (argc < 3) {
            printf("[!] Error: missing kernel version argument\n");
            return 1;
        }
		install_kernel(argv[2]);
	}

	else if (strcmp(argv[1], "switch") == 0) {
	    if (argc < 3) {
            printf("[!] Error: missing kernel version argument\n");
            return 1;
        }
		switch_kernel(argv[2]);
	}

	else {
		printf("[!] Error: unknown command %s\n", argv[1]);
		return 1;
	}

	return 0;
}
