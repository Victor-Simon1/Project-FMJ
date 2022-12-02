#include "vector.h"
#include <cmath>
#include "matrix.h"
using namespace aline;
using namespace std;
int main()
{
    std::cout << "Test on matrix"<< std::endl;
    Matrix<int,2,2> m {{2,2},{2,2}};
    std::cout <<m;
    Matrix<int,2,2> a = m;
    //std::cout <<a.at(0,0);

    Matrix<int,3ul,3ul> isInversible {{2,3,8},{6,0,-3},{-1,3,2}};
    Matrix<double,3,3> inverseMatrice {{1/15,2/15,-1/15},{-1/15,4/45,2/5},{2/15,-1/15,-2/15}};
    
    std::cout<< inverse(isInversible) << std::endl;
    std::cout << "Test on vector"<< std::endl;


    Vector<int,5> v;
    cout << "success" << endl;
    cout << v;

    Vector<int,5> v1 { 5,2 ,3,4,5};
    Vector<int,5> v2 { 1,1 ,1,1,1};
    cout << "success" << endl;
    cout << v1;
    cout << v1.at(0)<< endl;
    cout << norm(v1) <<endl;
    cout << to_string(v1) <<endl;

    Vector<double,4> v3 { 1.0, 3.0, 1.0, 4.0 };
    Vector<double,4> v4  { 2.0, 7.0, 2.4, 8.8 };
    cout << dot(v3,v4)<<endl;
    cout << -v4<<endl;

    Vector<double,4> v5  { 2.0, NAN, 2.4, 8.8 };
    cout << isnan(v5)<<endl;

    Vector<double,3> v6 { 1.0, 1.0, 0.0 };
    cout << "univt"<<endl;
    cout << unit_vector( v6 )<<endl;
    cout << norm(unit_vector( v6 ))<<endl;
    cout << is_unit( unit_vector( v6 ))<<endl;
    //cout << (is_unit( unit_vector( v1 ) ) == true);
}