/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Manager.hpp"
#include "../include/Employee.hpp"

int main()
{
    Employee* A = new Employee();
    Employee* B = new Employee();

    Manager* C = new Manager();

    C->Manage(A);
    C->Manage(B);

    return 0;
}