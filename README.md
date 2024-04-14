# synfilesharing

Тестовое задание для "Открытой Мобильной Платформы".

## Содержимое репозитория

- Фреймворк для обмена файлами между приложениями через DBus (на основе
  библиотеки [sdbus-cpp](https://github.com/Kistler-Group/sdbus-cpp)).
- [Демо приложение для демонстрации работы фреймворка (Qt Widgets).](https://github.com/synalice/synfilesharingDemo)
- [`.deb` пакеты как для фреймворка, так и для демо приложения.](https://github.com/synalice/synfilesharing/releases/tag/latest)
- `Dockerfile` для демонстрации компиляции на "чистой" Ubuntu 20.04.

## Компиляция проекта

Для установки необходимо установить зависимость `pkg-config` и `libsystemd-dev`, а также все остальные базовые
зависимости, необходимые для сборки проекта:

```shell
sudo apt-get install pkg-config libsystemd-dev
sudo apt-get install g++ cmake
```

```shell
mkdir build
cd build
cmake ..
cmake --build .
```

## Компиляция `.deb` пакетов

```shell
cpack -G DEB
```

Желаемый `.deb` пакет будет находиться в директории `synfilesharing/build/_CPack_Packages/Linux/DEB`.

## Использование фреймворка в собственном проекте

1. Установите фреймворк с помощью `.deb` пакета.
2. Добавьте в файле `CMakeLists.txt` своего проекта следующие строки:
    ```cmake
    target_link_libraries(projectName
        PRIVATE synfilesharing sdbus-c++ systemd
    )
    
    target_include_directories(projectName
        PRIVATE synfilesharing
    )
    ```
3. Для проверки того, что линковка прошла успешно, можно использовать вызов метода `synfs::helloWorld()`.

## Примеры использования

Примеры использования фреймворка можно увидеть в папке [examples/](examples) и
в [репозитории с приложением на Qt](https://github.com/synalice/synfilesharingDemo).
