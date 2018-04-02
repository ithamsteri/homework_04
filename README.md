## Домашнее задание 04

[![Build Status](https://travis-ci.org/ithamsteri/homework_04.svg?branch=master)](https://travis-ci.org/ithamsteri/homework_04)

**Цель:** Создание и публикация документации с помощью Doxygen и Travis CI.

**Необходимо:**
* Написать программу для отображения IP-адресов;
* Настроить Doxygen совместно с Travis CI для публикации документации.

**Дополнительно:**
* Добавить поддержку вывода IP-адреса из `std::tuple`.

### Документация

Ссылка на документацию: https://ithamsteri.github.io/homework_04/

### Установка пакета

Для Ubuntu Trusty нужно сделать следующее:

```shell
echo "deb http://dl.bintray.com/hamsterisoftware/deb-repo trusty main" | sudo tee -a /etc/apt/sources.list
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 379CE192D401AB61
sudo apt-get update && sudo apt-get install print_ip
```

### Генерация сборки

Запустить в корневом каталоге проекта

```shell
cmake -H. -BBuild -DBUILD_TESTING=ON
```

### Сборка проекта

Запустить в каталоге Build

```shell
cmake --build .
```

### Тестирование проекта

Запустить в каталоге Build

```shell
cmake --build . --target test
```

### Сборка пакета

Запустить в каталоге Build

```shell
cmake --build . --target package
```
