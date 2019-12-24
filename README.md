[![Build Status](https://travis-ci.com/devborz/osquery_extension.svg?token=rrbTiACLSyD7Yjcuyygg&branch=master)](https://travis-ci.com/devborz/osquery_extension)

# OSquery History Extension

Данное расширение предоставляет пользователю возможность просмотра истории
своих действий на компьютере (OS Linux)

### Функции

* Предоставление истории командной строки
- Предоставление списка измененных файлов

### Инструкция
```
>>> _build/extension --help

Options:
  --help                give list of recently changed files
  --filesystem          outputs filesystem's history
  --commandline         outputs commandline's history
```
### Скачивание и сборка
```
```
### Tasks

- [x] Настроить program_options
- [x] Реализовать получение истории командной строки
- [x] Реализовать получение истории изменения файлов
- [x] Реализовать сортировку по дате
- [x] Реализовать проверку настройки bash_history на сохранение времени и директории
- [ ] Реализовать табличный вывод
- [ ] Интегрировать в osquery в виде расширения
