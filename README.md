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
$ osquery> select * from bash_history; #This command outputs bash_history

$ osquery> select * from fs_history; #This command outputs fs_history

$ osquery> select * from vim_history; #This command outputs vim_history
```
### Инструкция по использованию `_build/extension`

```ShellSession
$ _build/extension --help

Options:
  --help                outputs help message
  --filesystem          outputs filesystem's history
  --bash                outputs bash history
  --vim                 outputs vim  history
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
$ _build/extension --filesystem
$ _build/extension --bash
$ _build/extension --vim
```
### Интеграция в OSquery
![Alt Text](https://github.com/devborz/osquery_history_extension/blob/master/images/extension-osquery.gif)
```ShellSession
$ osqueryi
Using a virtual database. Need help, type '.help'
osquery>
$ #in second shell window:
$ python sources/extension.py --socket /home/${USERNAME}/.osquery/shell.em
$ #in first shell window:
$ osqueryi
Using a virtual database. Need help, type '.help'
$ osquery> select * from bash_history;
$ osquery> select * from fs_history;
$ osquery> select * from vim_history;
$ osquery> .exit
```

### Cкачивание необходимых пакетов

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
- [ ] Добавить возможность получения истории `vim`
