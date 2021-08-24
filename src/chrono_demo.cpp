#include <chrono>
#include <iostream>
#include <type_traits>

// Measure Time
// ============

int isPrime(unsigned int p)
{
    if (p < 2)
        return true;

    if (p % 2 == 0)
        return false;

    for (unsigned int n = 3; n < p/2; n++)
    {
        if (p % n == 0)
            return false;
    }
    return true;
}

int countPrimes(unsigned int p_max, int verbose=0)
{
    int number_of_primes = 0;

    for (unsigned int p = 1; p <= p_max; p++)
    {
        if (isPrime(p))
        {
            number_of_primes ++;
            if (verbose >= 1)
                std::cout << p << "\tPRIME!\n";
        } 
        else if (verbose >= 2)
            std::cout << p << "\tnot prime\n";
    }

    return number_of_primes;
}


void measureExecutionTime()
{
    std::cout << "MEASURE TIME\n";

    std::chrono::time_point<std::chrono::steady_clock> t_start = std::chrono::steady_clock::now();

    uint p_max = 150000;
    auto n = countPrimes(p_max);

    std::chrono::time_point<std::chrono::steady_clock> t_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> td_s = t_end - t_start;

    std::cout << "There are " << n << " primes up to a value of " << p_max << "." << std::endl;
    std::cout << "This operation took " << td_s.count() << "s." << std::endl;

    std::cout << std::endl;
}


// Use as Template Parameter
// =========================

template <typename T>
struct is_chrono_duration
{
    static constexpr bool value = false;
};

template <typename Rep, typename Period>
struct is_chrono_duration<std::chrono::duration<Rep, Period>>
{
    static constexpr bool value = true;
};

template <typename Duration>
double inSeconds( Duration d )
{
    typedef std::chrono::duration<double> Seconds;

    static_assert(is_chrono_duration<Duration>::value, "duration must be a std::chrono::duration");

    return std::chrono::duration_cast<Seconds>(d).count();
}

void chronoTypesInTemplates()
{
    std::cout << "USING CHRONO TYPES IN TEMPLATES\n";
    std::cout << "24 hours are " << inSeconds( std::chrono::hours(24) ) << " seconds" << std::endl;
    std::cout << "525 ms are " << inSeconds( std::chrono::milliseconds(500) ) << " seconds" << std::endl;
    // inSeconds(30); // FAILS TO COMPILE 

    std::cout << std::endl;
}

// RUN DEMO
// ========

int main()
{
    measureExecutionTime();
    chronoTypesInTemplates();
}