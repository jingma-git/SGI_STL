#include <string>
#include <stdexcept>

const int MINIMUM_PSWD_LEN = 10;

void encrypt(std::string &pwd) {}

std::string encrypt_password(const std::string &password)
{
    if (password.size() < MINIMUM_PSWD_LEN)
    {
        throw std::logic_error("Password is too short");
    }
    // try to postphone definiton until you have initialization arguments for it
    std::string encrypted(password);
    encrypt(encrypted);
    return encrypted;
}