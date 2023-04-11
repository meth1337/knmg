# knmg (kernel manager)
This is a command-line tool written in C that helps to manage and switch between different installed kernel versions on a Linux system. The tool has been tested on Ubuntu and Mint distributions.

# Usage
```
Usage: ./knmg <command> [kernel_version]
Commands:
  list                     - List available kernel versions
  install [kernel_version] - Install a new kernel version
  switch  [kernel_version] - Switch to a different kernel version
```
## Examples:
- `sudo ./knmg list` - lists all available kernels, including the one that is currently used 
- `sudo ./knmg install 5.15.0-56-generic` - installs `5.15.0-56-generic` kernel version
- `sudo ./knmg switch 5.15.0-56-generic` - switches current kernel version to `5.15.0-56-generic`

# Limitations
- The tool only works with superuser privileges (`sudo`)
- The tool only works for Linux systems with `GRUB` as the bootloader
- The tool only works for Linux systems that use `apt-get` as the package manager

# ...
Sorry for this project, I'm just experimenting with my C and Linux knowledge :(
<img src="img/nah.gif">

