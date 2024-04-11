#ifndef SYNFILESHARING_I_SERVER_H
#define SYNFILESHARING_I_SERVER_H

namespace synfs {
    class IServer {
    public:
        /**
         * Запускает процесс в качестве сервера, если он был вызван с помощью DBus через .service файл.
         * (для такого запуска проверяется наличие определенного флага).
         * */
        virtual void run(int argc, char *argv[]) = 0;

        virtual ~IServer() = default;
    };
}


#endif //SYNFILESHARING_I_SERVER_H
