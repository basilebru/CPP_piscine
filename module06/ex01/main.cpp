
#include <cstdlib> // std::rand std::srand
#include <ctime> // std::time
#include <iostream>
#include <limits>

struct Data 
{ 
    std::string s1;
    int n;
    std::string s2;
};

void print_data_before_serializing(char tab1[8], char tab2[8], int n)
{
    std::cout << "before serialization:" << std::endl;
    std::cout << "array 1: ";
    for (size_t i = 0; i < 8; i++)
    {
        std::cout << tab1[i];
    }
    std::cout << std::endl;
    std::cout << "array 2: ";
    for (size_t i = 0; i < 8; i++)
    {
        std::cout << tab2[i];
    }
    std::cout << std::endl;
    std::cout << "int: " << n << std::endl;
    
}

void fill_random(char tab[8])
{
    for (size_t i = 0; i < 8; i++)
    {
        if (rand() % 2 == 0)
            tab[i] = rand() % 10 + 48;
        else
            tab[i] = rand() % 25 + 97;
    }
}

Data* deserialize(void *raw)
{
    Data *ptr_data = new Data;
    ptr_data->s1 = "";
    ptr_data->s2 = "";
    char *str = reinterpret_cast<char*>(raw);
    for (size_t i = 0; i < 8; i++)
    {
        ptr_data->s1 = ptr_data->s1 + str[i];
    }
    for (size_t i = 0; i < 8; i++)
    {
        ptr_data->s2 = ptr_data->s2 + str[i + 12];
    }
    int *i = reinterpret_cast<int*>(str + 8);
    ptr_data->n = *i;
    return ptr_data;
}

void* serialize(void)
{
    std::srand(time(NULL));
    char tab1[8];
    char tab2[8];
    fill_random(tab1);
    fill_random(tab2);
    int i = rand() % std::numeric_limits<int>::max();
    print_data_before_serializing(tab1, tab2, i);

    char *tab_ptr = new char[8 + 4 + 8]; // we will store our data into an array of char
    int index = 0;
    for (size_t i = 0; i < 8; i++)
    {
        tab_ptr[index] = tab1[i];
        index++;
    }
    char *ptr_i_char = reinterpret_cast<char*>(&i); // we reinterpret our int* as a char*, in order to fill our char*
    for (size_t i = 0; i < 4; i++)
    {
        tab_ptr[index] = ptr_i_char[i];
        index++;
    }
    for (size_t i = 0; i < 8; i++)
    {
        tab_ptr[index] = tab2[i];
        index++;
    }
    void *data = tab_ptr;
    return data;
}

int main()
{
    void *data;
    data = serialize();

    Data *output;
    output = deserialize(data);
    std::cout << "after desezialization:" << std::endl;
    std::cout << "string1: " << output->s1 << std::endl;
    std::cout << "string2: " << output->s2 << std::endl;
    std::cout << "int: " << output->n << std::endl;
    
    char *tab_ptr; // we need to cast out void* to char* in order to delete it
    tab_ptr = reinterpret_cast<char*>(data);
    delete []tab_ptr; // was allocated with new []
    delete output;
}