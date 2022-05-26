#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Person
{
public:
    Person(): height (0) {}
    Person(const string& firstName, const string& lastName, int height)
    : firstName(firstName), lastName(lastName), height(height) {}

    const string& FirstName() const
    {
        return firstName;
    }

    const string& LastName() const
    {
        return lastName;
    }

    int Height() const
    {
        return height;
    }

    virtual string Info() const
    {
        return firstName + " " + lastName + " " + to_string(height);
    }

    virtual ~Person(){}

private:
    string firstName, lastName;
    int height;
};

bool compare_by_lastName(const Person& p1, const Person& p2)
{
    return p1.LastName() < p2.LastName()
    || (p1.LastName() == p2.LastName() && p1.FirstName() < p2.FirstName());
}

bool compare_by_lastName_ptr(const Person* p1, const Person* p2)
{
    return p1->LastName() < p2->LastName()
    || (p1->LastName() == p2->LastName() && p1->FirstName() < p2->FirstName());
}

bool compare_by_height(const Person& p1, const Person& p2)
{
    return p1.Height() > p2.Height()
    || (p1.Height() == p2.Height() && p1.LastName() < p2.LastName());
}

bool compare_by_height_ptr(const Person* p1, const Person* p2)
{
    return p1->Height() > p2->Height()
    || (p1->Height() == p2->Height() && p1->LastName() < p2->LastName());
}

class Student : public Person
{};

class Worker : public Person
{
public:
    Worker(const string& firstName, const string& lastName, int height)
    : Person(firstName,lastName,height) {}
    string Info() const override
    {
        return Person::Info() + " (worker) ";
    }
};

int main()
{
    vector<Person*> source;
    source.push_back(new Person("Petr", "Ivanov", 175));
    source.push_back(new Person("Ivan", "Sidorov", 195));
    source.push_back(new Worker("Ivan", "Molchanov", 177));
    source.push_back(new Person("Alexey", "Molchanov", 170));

    vector<Person*> byLastName = source;
    sort(byLastName.begin(),byLastName.end(),compare_by_lastName_ptr);
    for (auto p : byLastName)
    {
        cout <<p->Info() <<endl;
    }
    cout <<"===================================" <<endl;

    vector<Person*> byHeight = source;
    sort(byHeight.begin(),byHeight.end(),compare_by_height_ptr);
    for (auto p : byHeight)
    {
        cout <<p->Info() <<endl;
    }

    return 0;
}
