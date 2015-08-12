# freebsd-munin-plugins
A set of FreeBSD specific plugins for Munin

## Requirements
All scripts are written in standard shell language, and `/bin/sh` would be sufficient.
They are tailored and will run on FreeBSD. 
You need to install `lang/gawk` in order to run `intr_` plugin.

## Setup
1. Make sure `sysutils/munin-node` is installed
2. Enable munin-node to run at startup: `sysrc munin_node_enable YES`
2. Clone this repo and copy all scripts to `/usr/local/share/munin/plugins`
3. run `munin-node-configure --suggest` and see if the plugins are detected.
4. run `munin-node-configure --shell | sh -x` to make appropriate symlinks
5. restart munin-node if running: `service munin-node restart`
