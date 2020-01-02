[![Build Status](https://travis-ci.com/devborz/osquery_history_extension.svg?token=rrbTiACLSyD7Yjcuyygg&branch=master)](https://travis-ci.com/devborz/osquery_history_extension)

# Osquery History Extension

This extension allows the user to view the history of their actions on a computer (Linux OS)

### Functions

* Providing the user with **Bash** command line history
* Providing the user with a list of modified files
* Providing the user with **Vim** history (command history and file opening history)

### User Guide

```ShellSession
$ osquery> select * from bash_history; # outputs bash history

$ osquery> select * from filesystem_history; # outputs recently changed files

$ osquery> select * from vim_commandline_history; # outputs vim cmd history

$ osquery> select * from vim_filemarks_history; # outputs vim filemarks history
```
### `_build/extension` options

```ShellSession
$ _build/extension --help

Options:
  --help                outputs help message
  --filesystem          updates filesystem's history
  --bash                updates bash history's file
  --vim                 updates vim history's files
  --all                 updates all history's files
```

### Downoloading

```ShellSession
$ cat > ~/.profile << EOF
>
> export PROMPT_COMMAND='if [ "$(id -u)" -ne 0 ]; then echo "$(date "+%Y-%m-%d.%H:%M:%S") $(pwd) $(history 1)"
> >> ~/bash-history.log; fi'
> EOF
$ git clone https://github.com/devborz/osquery_history_extension
$ cd osquery_history_extension
```
### Building and data updating
![Alt Text](https://github.com/devborz/osquery_history_extension/blob/master/images/extension-building-saving.gif)
```ShellSession
$ cmake -H. -B_build
$ cmake --build _build
$ _build/extension --all
```
### Osquery integration
![Alt Text](https://github.com/devborz/osquery_history_extension/blob/master/images/extension-osquery.gif)
```ShellSession
$ osqueryi
Using a virtual database. Need help, type '.help'
osquery>
$ #in second shell window:
$ python sources/extension.py --socket /home/${USERNAME}/.osquery/shell.em
$ #and going back to first shell window:
```
### Using extension
#### Getting **Bash** history
```ShellSession
$ osquery> select * from bash_history;
+------------+-------------------+---------+
| Time       | Execute directory | Command |
+------------+-------------------+---------+
|    ...     |         ...       |   ...   |

```
#### Getting file change history
```ShellSession
$ osquery> select * from filesystem_history;
+----------------+------------+----------+
| Time           | Path       | Filename |
+----------------+------------+----------+
|       ...      |      ...   |    ...   |

```
#### Getting **Vim** history
![Alt Text](https://github.com/devborz/osquery_history_extension/blob/master/images/extension-vim-history.gif)
##### **Vim** command line history 
```ShellSession
$ osquery> select * from vim_commandline_history;
+-------------+---------+
| Time        | Command |
+-------------+---------+
|   ...       |   ...   |

```
##### **Vim** session history
```ShellSession
$ osquery> select * from vim_filemarks_history;
+---------+-------------+----------+--------------+-----------------+
| Time    | File's path | Filename | Position row | Position column |
+---------+-------------+----------+--------------+-----------------+
|   ...   |      ...    |   ...    |     ...      |       ...       |

```

#### Download required packages

```ShellSession
$ pip install osquery
```
### Tasks

- [x] Set program_options
- [x] Implement **bash** history option
- [x] Implement file change history option
- [x] Implement sorting by date
- [x] Implement data storage in **json** format
- [x] Integrate into **osquery** as an extension
- [x] Add **vim** history option
