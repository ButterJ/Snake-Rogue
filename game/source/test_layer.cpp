#include "test_layer.h"

void Test_layer::on_start()
{
    for (int i = 0; i < 100; i++)
    {
        int random_number = std::discrete_distribution<int> { 10.0, 20.0, 30.0, 40.0, 100.0 }(Random_number_generator::mersenne_twister);
        std::cout << random_number << "\n";
    }
}
