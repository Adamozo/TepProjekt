#include <iostream>
#include <string>
#include <exception>

using namespace std;

class Exception : public std::exception
{

public:
    Exception(const string& msg) : msg_(msg) {}
    ~Exception() {}
    const char* what() const noexcept
    {
        return msg_.c_str();
    }

private:
    string msg_;
};

/*
    void f()
{
    throw(Exception(":("));
}
*/