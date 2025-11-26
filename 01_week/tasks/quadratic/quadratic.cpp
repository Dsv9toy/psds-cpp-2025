#include <stdexcept>
#include <iomanip> 
#include <math.h>
#include <iostream>


// Дискриминант 
//---если < 0 то корней нет(Если школьную версию пишем).
//---Если = 0. то два одинаковых корня. Выводим один. например x1
//---Если > 0 - два корня и выводим их как x1,x2 (ps x1 < x2)
// У нас простой случай функции. ax^2+bx+c=0
// Из тестов видно что если получается целое в результате то пишем int, а иначе double. Мне нужноо большее статик кастов

void SolveQuadratic(int a, int b, int c) {

std::cout << std::setprecision(6); // конструкция для вывода. В целом и без нее всё проходится, но пусть будет по заданию

    //Особые случаи
    if (a == 0 && b == 0 &&  c == 0){
    std::cout << "infinite solutions";   
    return;
    } 

    if (a == 0) { 

        if (b == 0) {
            std::cout << "no solutions";
            return; }

        else {  
            double Ans = -static_cast<double>(c) / b;
           
            if (Ans == static_cast<int>(Ans)) {
                std::cout << static_cast<int>(Ans); 
            } else {
                std::cout << Ans;
            }
            return;
        }
    } 
//Решение 
    int D = b*b-4*a*c;

//отриц дискриминант
    if(D < 0){
        std::cout << "no solutions";
        return ;
    }

    double x1 = (-b - sqrt(D)) / (2.0 * a);
    double x2 = (-b + sqrt(D)) / (2.0 * a);

//Для нулевого дискриминанта
    if (D == 0) {        
        if (x1 == static_cast<int>(x1)) {
            std::cout << static_cast<int>(x1);
        } else {
            std::cout << x1;
        }
    } else {
//Когда всё хорошо
        if (x1 == static_cast<int>(x1)) {
            std::cout << static_cast<int>(x1);
        } else {
            std::cout << x1;
        }
        
        std::cout << " ";
        
        if (x2 == static_cast<int>(x2)) {
            std::cout << static_cast<int>(x2);
        } else {
            std::cout << x2;
        }
    }
}
