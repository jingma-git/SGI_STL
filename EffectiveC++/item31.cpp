
#include <iostream>
#include <memory>
class Date;
Date today();

class Person
{
public:
    virtual ~Person(){};
    virtual std::string name() const = 0;
    virtual std::string birthDate() const = 0;
};

class RealPerson : public Person
{
public:
    RealPerson(const std::string &name, const std::string &birthday)
        : m_name(name), m_birthday(birthday)
    {
    }
    virtual ~RealPerson() {}
    virtual std::string name() const { return m_name; }
    virtual std::string birthDate() const { return m_birthday; }

private:
    std::string m_name;
    std::string m_birthday;
};
std::shared_ptr<Person> create(const std::string &name, const std::string &birthday)
{
    return std::shared_ptr<Person>(new RealPerson(name, birthday));
}
int main()
{
    std::shared_ptr<Person> pP = create("Bella", "April 22th");
    return 0;
}