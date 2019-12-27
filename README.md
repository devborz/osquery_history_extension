[![Build Status](https://travis-ci.com/devborz/osquery_history_extension.svg?token=rrbTiACLSyD7Yjcuyygg&branch=master)](https://travis-ci.com/devborz/osquery_history_extension)

# OSquery History Extension

Данное расширение предоставляет пользователю возможность просмотра истории
своих действий на компьютере (OS Linux)

### Функции

* Предоставление пользователю истории командной строки
- Предоставление пользователю списка измененных файлов

### Инструкция по использованию
```ShellSession
$ _build/extension --help

Options:
  --help                outputs help message
  --filesystem          outputs filesystem's history
  --bash                outputs bash history
```
### Скачивание и сборка
```ShellSession
$ cat > ~/.profile << EOF
>
> export PROMPT_COMMAND='if [ "$(id -u)" -ne 0 ]; then echo "$(date "+%Y-%m-%d.%H:%M:%S") $(pwd) $(history 1)" >> ~/bash-history.log; fi'
> EOF
$ git clone https://github.com/devborz/osquery_history_extension
$ cd osquery_history_extension
$ cmake -H. -B_build
$ cmake --build _build
$ _build/extension --filesystem
$ _build/extension --bash
```
### Интеграция в OSquery
```ShellSession
$ osqueryi
Using a virtual database. Need help, type '.help'
osquery>
```
<!--- open second shell window: --->
```
$ python sources/history_extension.py --socket /home/${USERNAME}/.osquery/shell.em
```
<!--- in first shell window: --->
```
$ osqueryi
Using a virtual database. Need help, type '.help'
osquery> select from * bash_history;
```
<!--- outputs bash_history --->
```
osquery> select from * filesystem_history;
```
<!--- outputs filesystem history --->
```
$ .exit
```
### Tasks

- [x] Настроить program_options
- [x] Реализовать получение истории `bash`
- [x] Реализовать получение истории изменения файлов
- [x] Реализовать сортировку по дате
- [x] Реализовать проверку настройки bash_history на сохранение времени и директории
- [x] Реализовать сохрaнение полученных данный в формате `json`
- [x] Интегрировать в osquery в виде расширения

### Cкачивание необходимых пакетов
```ShellSession
$ pip install osquery
```
