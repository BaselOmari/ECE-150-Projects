#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif // MARMOSET_TESTING
int checksum_output(int num);
unsigned int add_checksum(unsigned int n);
void add_checksum(unsigned int array[], std::size_t capacity);
bool verify_checksum(unsigned int n);
unsigned int remove_checksum(unsigned int n);
void remove_checksum(unsigned int array[], std::size_t capacity);

#ifndef MARMOSET_TESTING
int main()
{
    unsigned int value_to_protect{21352411};
    unsigned int protected_value = add_checksum(value_to_protect);

    std::cout << "The value " << value_to_protect << " with the checksum add is " << protected_value << "." << std::endl;

    if (verify_checksum(protected_value))
    {
        std::cout << "The checksum is valid." << std::endl;
    }
    else
    {
        std::cout << "The checksum is invalid." << std::endl;
    }

    std::size_t qty_values {3};
    unsigned int value_series[qty_values] {20201122, 20209913, 20224012};

    add_checksum(value_series, qty_values);

    std::cout << "Series with checksums added: ";
    for (std::size_t series_index {0}; series_index < qty_values; series_index++)
        {
            std::cout << value_series[series_index] << " ";
        }
    std::cout << std::endl;

    return 0;
}
#endif // MARMOSET_TESTING

int checksum_output(int num)
{
    int sum{};
    int checksum{};
    int index{0};
    int numTemp{num};
    int numList[8] = {100,100,100,100,100,100,100,100};

    while (true)
    {
        int dig{numTemp%10};

        numTemp /= 10;
        numList[index] = dig;

//        std::cout << numList[index] << std::endl;

        ++index;

        if (numTemp < 1)
        {
            break;
        }
    }

    for (int i = 0; i < 8; i+=2)
    {
        if (numList[i] == 100)
        {
            break;
        }

        int mult = numList[i]*2;

        if (mult > 9)
        {
            int multSum{};

            multSum += mult%10;
            mult /= 10;
            multSum += mult%10;

            mult = multSum;

        }

        numList[i] = mult;
    }

    for (int i = 0; i < 8; ++i)
    {
        if (numList[i] == 100)
        {
            break;
        }

        sum += numList[i];
    }

    sum *= 9;
    checksum = sum%10;

    return checksum;
}

unsigned int add_checksum(unsigned int n)
{
    if (n > 99999999 || n < 0)
    {
        return UINT_MAX;
    }

    int checksum = checksum_output(n);

    n *= 10;
    n += checksum;


//    std::cout << n << std::endl;
    return n;
}

void add_checksum(unsigned int array[], std::size_t capacity)
{
    for (int index{0}; index < capacity; index++)
        {
            array[index] = add_checksum(array[index]);
        }
}

bool verify_checksum(unsigned int n)
{
    if (n > 999999999)
    {
        return false;
    }

    int without_checksum = n/10;
    int last_digit = n%10;

    if (checksum_output(without_checksum) != last_digit)
    {
        return false;
    }

    return true;
}

unsigned int remove_checksum(unsigned int n)
{
    if (!verify_checksum(n))
    {
        return UINT_MAX;
    }

    n = n/10;
//    std::cout << n << std::endl;
    return n;
}

void remove_checksum(unsigned int array[], std::size_t capacity)
{
    for (int index{0}; index < capacity; index++)
    {
        array[index] = remove_checksum(array[index]);
    }
}

