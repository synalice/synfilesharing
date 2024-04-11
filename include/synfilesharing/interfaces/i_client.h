#ifndef SYNFILESHARING_I_CLIENT_H
#define SYNFILESHARING_I_CLIENT_H

#include <vector>
#include <string>

namespace synfs {
    class IClient {
    public:
        /**
         * Создаёт новое приложение, передавая в него указанные файлы.
         * Получает ошибку, если указанные файлы не разрешены.
         * */
        virtual void sendFiles(std::vector<std::string> filePaths) = 0;

        virtual ~IClient() = default;
    };
}


#endif //SYNFILESHARING_I_CLIENT_H
