#include "c_factory.h"

using json = nlohmann::json;


json ClientTurnOff::execute() {
    json j_end;
    j_end["response"] = "I'm breaking the connection";
    return j_end;
}
