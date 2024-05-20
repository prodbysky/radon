#pragma once

#include <iostream>
#include <optional>
#include <string>

class Error {
public:
    Error() = default;
    Error(std::string message);
    std::string GetError();

private:
    std::string msg;
};

template <class T> class Result {
public:
    Result<T>();
    Result<T>(T value);
    Result<T>(Error error);

    bool Ok();

    std::string GetError();
    T GetValue();

private:
    std::optional<T> value;
    std::optional<Error> error;
};

inline Error::Error(std::string message) : msg(message) {}
inline std::string Error::GetError() { return msg; }

template <class T> Result<T>::Result() : value({}), error({}) {}
template <class T> Result<T>::Result(T value) : value(value), error({}) {}
template <class T> Result<T>::Result(Error error) : value({}), error(error) {}

template <class T> bool Result<T>::Ok() { return value.has_value(); }

template <class T> std::string Result<T>::GetError() {
    return error->GetError();
}
template <class T> T Result<T>::GetValue() {
    if (error.has_value()) {
        std::cerr << "Tried to get value of result which has error: "
                  << error->GetError() << std::endl;
        std::exit(-1);
    }
    return value.value();
}
