[![Build Status](https://travis-ci.com/devborz/osquery_extension.svg?token=rrbTiACLSyD7Yjcuyygg&branch=master)](https://travis-ci.com/devborz/osquery_extension)

# OSquery History Extension

Данное расширение предоставляет пользователю возможность просмотра истории
своих действий на компьютере (OS Linux)

### Функции

* История командной строки
- Недавно измененные файлы
+ Недавно запущенные программы

### Инструкция
```
>>>  help

Commands:
 filesystem ${PATH_TO_DIRECTORY} ${PERIOD} - give list of recently changed files
 commandline ${PERIOD} - give history of command line
Periods:
 -h -- last hour
 -d -- last day
 -w -- last week
 -m -- last month
 -a -- all*
```
