#ifndef PATH_H
#define PATH_H

#include <string>

class Path {
public:
    explicit Path(const std::string& rawPath);
    bool operator==(const Path& other) const { return value_ == other.value_; }
    bool operator!=(const Path& other) const { return !(*this == other); }
    std::string value() const { return value_; }

private:
    void validate() const;

    std::string value_;
};
#endif // PATH_H
