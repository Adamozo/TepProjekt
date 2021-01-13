#include <iostream>
#include <string>
#include <exception>

using namespace std;

class MyVecException : public std::exception
{

public:
    MyVecException(const string& msg) : msg_(msg) {}
    ~MyVecException() {}
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
