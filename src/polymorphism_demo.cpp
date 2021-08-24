#include <iostream>
#include <memory>
#include <string>

class Car
{
    public:
    Car()
    {
        std::cout << "Car created" << std::endl;
    }

    virtual const std::string drive () = 0;
};

class Mercedes : public Car
{
    public:
    Mercedes ()
    {
        std::cout << "Mercedes created" << std::endl;
    }

    virtual const std::string drive () override
    {
        return "I am a Mercedes!";
    }
};


class Audi : public Car
{
    std::string m_name;

    public:
    Audi ()
    {
        std::cout << "Audi created without a name" << std::endl;
    }

    Audi (const std::string& name)
     : m_name(name)
    {
        std::cout << "Audi created with name: " << m_name << std::endl;
    }

    virtual const std::string drive () override
    {
        return "I am an Audi!";
    }
};

class AudiTT : public Audi
{
    public:
    AudiTT ()
    {
        std::cout << "AudiTT created" << std::endl;
    }

    AudiTT (const std::string& name)
     : Audi(name)
    {
        std::cout << "AudiTT created" << std::endl;
    }

    virtual const std::string drive () override
    {
        return Audi::drive() + " More specifically an Audi TT!";
    }
};


int main()
{
    std::cout << "\nAudiTT audi_tt" << std::endl;
    AudiTT audi_tt;
    std::cout << audi_tt.drive() << std::endl;

    {
        std::cout << "\nstd::unique_ptr<Car> car_p (new AudiTT)" << std::endl;
        std::unique_ptr<Car> car_p (new AudiTT);
        std::cout << car_p->drive() << std::endl;
    }

    {
        std::cout << "\nstd::unique_ptr<Car> car_p (new AudiTT(Gustaf))" << std::endl;
        std::unique_ptr<Car> car_p (new AudiTT("Gustaf"));
        std::cout << car_p->drive() << std::endl;
    }

    {
        std::cout << "\nstd::unique_ptr<Car> car_p (new Audi)" << std::endl;
        std::unique_ptr<Car> car_p (new Audi);
        std::cout << car_p->drive() << std::endl;
    }

    {
        std::cout << "\nstd::unique_ptr<Car> car_p (new Mercedes)" << std::endl;
        std::unique_ptr<Car> car_p (new Mercedes);
        std::cout << car_p->drive() << std::endl;
    }

}