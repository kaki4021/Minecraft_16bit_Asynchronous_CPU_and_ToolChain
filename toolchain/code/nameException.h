#pragma once

class NameException : public std::exception
{
private:
    std::string message;
public:
    NameException(const std::string message) : message(message) {};

    const char* what() const noexcept override {
        return message.c_str();
    }
};