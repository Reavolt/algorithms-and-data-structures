#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

//-------------------------------------------------------------------------------------------------
void sieve_of_eratosthenes(int n);
//-------------------------------------------------------------------------------------------------
int main()
{
    sieve_of_eratosthenes(100);
    return 0;
}
//-------------------------------------------------------------------------------------------------
void sieve_of_eratosthenes(int n)
{
    std::vector<int> numbers(n - 1);
    std::iota(numbers.begin(), numbers.end(), 2);

    auto itr_b = numbers.begin();
    while (itr_b != numbers.end())
    {
        numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
        [itr_b](int a)
        {
            return ((!(a % (*itr_b))) && a != (*itr_b));
        }), numbers.end());
        ++itr_b;
    }
    std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(std::cout,"\n"));
}
//-------------------------------------------------------------------------------------------------