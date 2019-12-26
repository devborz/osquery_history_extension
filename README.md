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
  --commandline         outputs command line's history
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
$ _build/extension --commandline
```
### Tasks

- [x] Настроить program_options
- [x] Реализовать получение истории командной строки
- [x] Реализовать получение истории изменения файлов
- [x] Реализовать сортировку по дате
- [x] Реализовать проверку настройки bash_history на сохранение времени и директории
- [x] Реализовать табличный вывод
- [ ] Интегрировать в osquery в виде расширения
