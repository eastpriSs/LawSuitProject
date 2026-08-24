#include <stdexcept>
#include "path.h"

Path::Path(const std::string& rawPath) : value_(rawPath) {
    validate();
}

void Path::validate() const {
    if (value_.empty()) {
        throw std::invalid_argument("Путь не должен быть пустым.");
    }

    if (value_.find('\0') != std::string::npos) {
        throw std::invalid_argument("Путь содержит null символ.");
    }

    const std::string forbiddenChars = "<>:\"|?*";
    for (char c : value_) {
        if (forbiddenChars.find(c) != std::string::npos) {
            throw std::invalid_argument(
                "Неприемлемый символ в пути:" + std::string(1, c)
                );
        }
        if (static_cast<unsigned char>(c) < 32) {
            throw std::invalid_argument("Путь содержит контрольный символ.");
        }
    }
}
