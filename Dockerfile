FROM ubuntu:20.04

# Фикс для пакета tzdata, который ломает в докере установку зависимостей
# https://serverfault.com/questions/949991/how-to-install-tzdata-on-a-ubuntu-docker-image
RUN apt-get update && DEBIAN_FRONTEND=noninteractive TZ=Europe/Moscow apt-get -y install tzdata

# Установка зависимостей.
RUN apt-get update && apt-get install -y g++ cmake pkg-config libsystemd-dev

# Копируем файлы.
WORKDIR synfilesharing
COPY . .
RUN mkdir build

# Компилируем. Можно было бы использовать volumes для кэширования объектов компиляции.
WORKDIR build
RUN cmake .. && cmake --build .

# Копируем результат компиляции из контейнера на хост
RUN mkdir /compilation-result
RUN chmod +x /synfilesharing/entrypoint.sh
CMD /synfilesharing/entrypoint.sh
