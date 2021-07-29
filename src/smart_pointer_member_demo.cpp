/**
 * @file smart_pointer_member_demo.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <memory>

#define DO_IT(MSG,CMD) { std::cout << "\n# " MSG << ":\n# " #CMD << std::endl; CMD }

struct Fruit
{
    virtual void eat() = 0;    
};

struct Apple : public Fruit
{
    Apple () { std::cout << "Apple Created" << std::endl; }

    ~Apple () { std::cout << "Apple Destroyed" << std::endl; }

    Apple ( const Apple& other ) { std::cout << "Apple Copied" << std::endl; }

    Apple& operator= ( const Apple& other ) { std::cout << "Apple Copied" << std::endl; }

    Apple ( const Apple&& other ) { std::cout << "Apple Moved" << std::endl; }

    Apple& operator= ( const Apple&& other ) { std::cout << "Apple Moved" << std::endl; }

    // 

    void eat()
    {
        std::cout << "This apple is delicious!" << std::endl;
    }
};

struct Banana : public Fruit
{
    Banana () { std::cout << "Banana Created" << std::endl; }

    ~Banana () { std::cout << "Banana Destroyed" << std::endl; }

    Banana ( const Banana& other ) { std::cout << "Banana Copied" << std::endl; }

    Banana& operator= ( const Banana& other ) { std::cout << "Banana Copied" << std::endl; }

    Banana ( const Banana&& other ) { std::cout << "Banana Moved" << std::endl; }

    Banana& operator= ( const Banana&& other ) { std::cout << "Banana Moved" << std::endl; }

    // 

    void eat()
    {
        std::cout << "This banana is delicious!" << std::endl;
    }
};

struct Basket
{
    std::shared_ptr<Fruit> m_fruit;

    Basket () : m_fruit(nullptr) {}

    template <typename F>
    Basket ( std::shared_ptr<F> fruit )
            : m_fruit( fruit )
    { std::cout << "Basket Created (with constructor Basket( std::shared_ptr<F> fruit))" << std::endl; }

    template <typename F>
    Basket ( const F& fruit )
            : m_fruit( std::make_shared<F>(fruit) )
    { std::cout << "Basket Created (with constructor Basket(const F& fruit))" << std::endl; }

    template <typename F>
    Basket ( const F&& fruit )
            : m_fruit( std::make_shared<F>(std::move(fruit)) )
    { std::cout << "Basket Created (with constructor Basket(const F&& fruit))" << std::endl; }

    // ~Basket () { std::cout << "Basket Destroyed" << std::endl; }

    void eat ()
    {
        m_fruit -> eat();
    }    
};


int main ()
{
    // Polymorphic Examples

    DO_IT ( "Create Object first and provide reference to object",
        Apple a;
        Basket b( a );

        b.eat();
    );


    DO_IT ( "Provide rvalue reference to object",
        Basket b = Basket( Apple() );
        b.eat();
    );

    DO_IT ( "Provide a shared pointer",
        std::shared_ptr<Apple> p_a = std::make_shared<Apple>();
        Basket b (p_a);
        b.eat();
    );

    DO_IT ( "Provide a shared pointer to two baskets",
        std::shared_ptr<Apple> p_a = std::make_shared<Apple>();
        std::cout << "apple use counter: " << p_a.use_count() << std::endl;
        Basket b1 (p_a);
        std::cout << "apple use counter: " << p_a.use_count() << std::endl;
        {
            Basket b2 (p_a);
            std::cout << "apple use counter: " << p_a.use_count() << std::endl;
        }
        std::cout << "apple use counter: " << p_a.use_count() << std::endl;
    );
}

