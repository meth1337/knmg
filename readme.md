# knmg (kernel manager)
This is a command-line tool written in C that helps to manage and switch between different installed kernel versions on a Linux system. The tool has been tested on Ubuntu and Mint distributions.

# Usage
```
./knmg <command> [kernel_version]
```
The following commands are available:
- `list` - Lists all available kernel versions, including currently running kernel version
- `install` - Installs a new kernel version. Requires a kernel version name as an argument
- `switch` - Switches to a different installed kernel version. Requires a kernel version name as an argument.

# Limitations
- The tool only works with superuser privileges (`sudo`)
- The tool only works for Linux systems with `GRUB` as the bootloader
- The tool only works for Linux systems that use `apt-get` as the package manager

# ...
Sorry for this project, I'm just experimenting with my C and Linux knowledge :(
<img src="img/nah.gif">

