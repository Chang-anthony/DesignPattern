#include "../include/Adventurer.hpp"
#include "../include/World.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>


Adventurer::Adventurer(World* world):world(world)
{
    
}

void Adventurer::RolltheDice()
{
    // 使用時間作為種子
    srand(time(NULL));

    int forward = 0;
    int arr1[3] = {1,2,3};
    int arr2[3] = {4,5,6};

    // 使用時間作為種子
    std::random_device rd;
    std::mt19937 gen(rd());

    // 創建一個均勻分佈的浮點數生成器
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    //int rand_number = rand() % 15;// 生成0到15的數子
    double random_float = dis(gen);

    if(random_float < 0.33)
    {
        /* 指定亂數範圍 */
        int min = 0;
        int max = 3;

        /* 產生 [min , max] 的整數亂數 */
        int x = rand() % (max - min + 1) + min;
        forward = arr1[x];
    }
    else if(random_float >= 0.33 && random_float < 0.53)
    {
        /* 指定亂數範圍 */
        int min = 0;
        int max = 3;

        /* 產生 [min , max] 的整數亂數 */
        int x = rand() % (max - min + 1) + min;
        forward= arr2[x];
    }
    else
        int forward = 0;
    std::cout << forward << std::endl;
    //Do forward
    world->MoveForward(this,forward);

}

void Adventurer::AddStep(int steps)
{
    step += steps;
}

Adventurer::~Adventurer()
{
}