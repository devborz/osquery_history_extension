[![Build Status](https://travis-ci.com/devborz/osquery_extension.svg?token=rrbTiACLSyD7Yjcuyygg&branch=master)](https://travis-ci.com/devborz/osquery_extension)

# OSquery History Extension

Данное расширение предоставляет пользователю возможность просмотра истории
своих действий на компьютере (OS Linux)

### Функции

* История командной строки
- Недавно измененные файлы

### Инструкция
```
>>> _build/extension --help

Options:
  --help                give list of recently changed files
  --filesystem          outputs filesystem's history
  --commandline         outputs commandline's history
  --path arg            add path to directory
  --period arg          add period of history
  --r                   search recursively


Periods:
  --period=h    last hour
  --period=d    last day
  --period=w    last week
  --period=m    last month
  --period=a    all time
```
### Tasks

- [x] Настроить program_options
- [x] Реализовать получение истории командной строки
- [x] Реализовать получение истории изменения файлов
- [x] Реализовать сортировку по дате
- [x] Реализовать проверку настройки bash_history на сохранение времени и директории
- [ ] Реализовать табличный вывод
- [ ] Интегрировать в osquery в виде расширения
