#include <client.h>

int main() {
    const int ret = start_client();
    if (ret == 1) {
        std::cerr << m_time() << "[ERROR] The client could not be started" << std::endl;
    }
    return 0;
}
