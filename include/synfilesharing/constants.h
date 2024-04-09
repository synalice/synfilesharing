#ifndef SYNFILESHARING_CONSTANTS_H
#define SYNFILESHARING_CONSTANTS_H

#include <string>

namespace synfs::constants {
    const std::string INTERFACE_NAME = "ru.synfs.FileSharing";
    const std::string OBJECT_PATH = "/ru/synfs/filesharing";
    const std::string METHOD_SENDFILES_NAME = "sendFiles";
    const std::string DEFAULT_SERVER_NAME = "ru.synfs.FileSharing";
    const std::string DEFAULT_EXEC_FLAG = "--launched-via-dbus";
}

#endif //SYNFILESHARING_CONSTANTS_H
