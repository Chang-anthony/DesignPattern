#include "../include/Teacher.hpp"
#include "../include/Studnet.hpp"

Teacher::Teacher(/* args */)
{
    //this->students = std::vector<Student*>();
    this->students = std::set<Student*>();
}

void Teacher::Teach(Student* student)
{
    std::cout << "teach this student" << std::endl;
    this->students.insert(student);
    student->AddTeacher(this);
    //建立與學生的雙向關聯
    // this->students.push_back(student);
    // std::vector<Teacher*> teachers = student->GetTeachers();
    // teachers.push_back(this);
    // student->SetTeachers(teachers);
}

// std::vector<Student*> Teacher::GetStudents()
// {
//     return this->students;
// }

// void Teacher::SetStudents(std::vector<Student*> students)
// {
//     this->students = students;
// }


Teacher::~Teacher()
{
    
}