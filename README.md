[![Build Status](https://travis-ci.com/devborz/osquery_history_extension.svg?token=rrbTiACLSyD7Yjcuyygg&branch=master)](https://travis-ci.com/devborz/osquery_history_extension)

# OSquery History Extension

Данное расширение предоставляет пользователю возможность просмотра истории
своих действий на компьютере (OS Linux)

### Функции

* Предоставление пользователю истории командной строки **Bash**
* Предоставление пользователю списка измененных файлов
* Предоставление пользователю истории **Vim**

### Инструкция по использованию расширения

```ShellSession
$ osquery> select * from bash_history; # outputs bash history

$ osquery> select * from filesystem_history; # outputs recently changed files

$ osquery> select * from vim_commandline_history; # outputs vim cmd history

$ osquery> select * from vim_filemarks_history; # outputs vim filemarks history
```
### Инструкция по использованию `_build/extension`

```ShellSession
$ _build/extension --help

Options:
  --help                outputs help message
  --filesystem          updates filesystem's history
  --bash                updates bash history's file
  --vim                 updates vim history's files
  --all                 updates all history's files
```

### Скачивание

```ShellSession
$ cat > ~/.profile << EOF
>
> export PROMPT_COMMAND='if [ "$(id -u)" -ne 0 ]; then echo "$(date "+%Y-%m-%d.%H:%M:%S") $(pwd) $(history 1)"
> >> ~/bash-history.log; fi'
> EOF
$ git clone https://github.com/devborz/osquery_history_extension
$ cd osquery_history_extension
```
### Сборка и обновление данных
![Alt Text](https://github.com/devborz/osquery_history_extension/blob/master/images/extension-building-saving.gif)
```ShellSession
$ cmake -H. -B_build
$ cmake --build _build
$ _build/extension --all
```
### Интеграция в OSquery
![Alt Text](https://github.com/devborz/osquery_history_extension/blob/master/images/extension-osquery.gif)
```ShellSession
$ osqueryi
Using a virtual database. Need help, type '.help'
osquery>
$ #in second shell window:
$ python sources/extension.py --socket /home/${USERNAME}/.osquery/shell.em
$ #and going back to first shell window:
```
### Использование расширения
#### Получение истории **Bash**
```ShellSession
$ osquery> select * from bash_history;
+------------+-------------------+---------+
| Time       | Execute directory | Command |
+------------+-------------------+---------+
|    ...     |         ...       |   ...   |

```
#### Получение истории изменения файлов
```ShellSession
$ osquery> select * from filesystem_history;
+----------------+------------+----------+
| Time           | Path       | Filename |
+----------------+------------+----------+
|       ...      |      ...   |    ...   |

```
#### Получение истории командной строки **Vim**
```ShellSession
$ osquery> select * from vim_commandline_history;
+-------------+---------+
| Time        | Command |
+-------------+---------+
|   ...       |   ...   |

```
#### Получение истории сеансов **Vim**
```ShellSession
$ osquery> select * from vim_filemarks_history;
+---------+-------------+---------------+--------------+-----------------+
| Time    | File's path | Filename      | Position row | Position column |
+---------+-------------+---------------+--------------+-----------------+
|   ...   |      ...    |      ...      |     ...      |       ...       |

```

#### Cкачивание необходимых пакетов

```ShellSession
$ pip install osquery
```
### Tasks

- [x] Настроить program_options
- [x] Реализовать получение истории `bash`
- [x] Реализовать получение истории изменения файлов
- [x] Реализовать сортировку по дате
- [x] Реализовать проверку настройки bash_history на сохранение времени и директории
- [x] Реализовать сохрaнение полученных данных в формате `json`
- [x] Интегрировать в osquery в виде расширения
- [x] Добавить возможность получения истории `vim`
