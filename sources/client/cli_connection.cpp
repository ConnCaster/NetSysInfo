#include "cli_connection.h"
#include <fstream>

// TODO (Viktor): Добавить деструктор для unique (decltype) Прочитать про это в книжке "42 совета ..."

// Поиск наименования жесткого диска в системе
inline std::string findDeviceHardDisk () {

    std::ifstream pathHardDisk ("/proc/mounts");
    if (!pathHardDisk.is_open()) std::cerr << "[ERROR] File not open" << std::endl;

    MountEntry hardDisk;

    while (!pathHardDisk.eof()) {
        pathHardDisk >> hardDisk;
        for (auto it : kFsTypesSet) {
            if (hardDisk.GetFsType() == it) {
                return hardDisk.GetDevice();
            }
        }
    }
}

// Получение серийного номера жесткого диска
inline std::string serial_hard_drive () {

    char c_serial[20];
    const std::string deviceHardDisk = findDeviceHardDisk();

    const std::string outSerialHardDisk = "udevadm info --query=all --name=" + deviceHardDisk + " | grep ID_SERIAL_SHORT";

    std::unique_ptr<FILE, decltype(&pclose)> fp (popen(outSerialHardDisk.data(), "r"), pclose);
    if (fp == nullptr) std::cerr << "[ERROR] File not open" << std::endl;

    while (fgets(c_serial, sizeof(c_serial), fp.get()) != nullptr) {} // Почему-то не работает, если я вместо с_serial пишу str.data() (заранее созданный)

    // TODO (Viktor): нет проверки работы fgets()

    std::string s_serial{std::string(c_serial)}; //22413C462705

    return s_serial;
}

// Для ввода никнейма
inline std::string nickname() {
    std::cout << "Enter your nickname: ";
    std::string nicknmae{};
    std::cin >> nicknmae;

    return nicknmae;
}

Conection::Conection(const int sock_fd)
    : socket_fd_(sock_fd), input_buffer_(), output_buffer_() {
    DoStart();
}

void Conection::DoStart() {
    nlohmann::json im_json;
    im_json["action"] = "authUser";

    im_json["args"] = { {"name", nickname()}, {"serial", serial_hard_drive()} };
    Send_msg(im_json);
}

void Conection::Recv_msg() {
    // Получение сообщения от пользователя
    if (const ssize_t received = recv(socket_fd_, input_buffer_.data(), 512, 0); received <= 0) {
        std::cerr << Time() << "[ERROR] Error recv()" << std::endl;
        return;
    }
    // Парс JSON
    nlohmann::json answer = nlohmann::json::parse(input_buffer_.data());

    std::cout <<Time() << "[SERVER] " << answer["answer"] << std::endl;

}

void Conection::Send_msg(const nlohmann::json &send_json) {
    // TODO (Viktor): Сериализация строки data
    // Не смог привязать output
    // А что если тип не string?

    const std::string str_json = send_json.dump();
    if (const size_t transmitted = send(socket_fd_, str_json.data(), str_json.size(), 0); transmitted != str_json.size()) {
        std::cerr << Time() << "[ERROR] not all data transmitted" << std::endl;
    }
    Recv_msg();
}


