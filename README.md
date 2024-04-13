# synfilesharing

Тестовое задание для "Открытой Мобильной Платформы".

## Содержимое репозитория

- Фреймворк для обмена файлами между приложениями через DBus (на основе
  библиотеки [sdbus-cpp](https://github.com/Kistler-Group/sdbus-cpp)).
- [Демо приложение для демонстрации работы фреймворка (Qt Widgets).](https://github.com/synalice/synfilesharingDemo)
- [`.deb` пакеты как для фреймворка, так и для демо приложения.](https://github.com/synalice/synfilesharing/releases/tag/latest)
- `Dockerfile` для демонстрации работы вышеперечисленного на "чистой" системе (без предустановок).

## Компиляция проекта

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

Желаемый `.deb` пакет будет находиться в директории `build/_CPack_Packages/Linux/DEB`.

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
3. Для проверки того, что линковка прошла успешно можно использовать метод `synfs::helloWorld()`.

## Примеры использования

Примеры использования фреймворка можно увидеть в папке [examples/](examples). Оба файла оттуда компилируются
автоматически вместе со сем проектом.