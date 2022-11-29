#include "vector.h"

using namespace aline;
using namespace std;
int main()
{
    Vector<int,5> v;
    cout << "success" << endl;
    cout << v;

    Vector<int,5> v1 { 5,2 ,3,4,5};
    cout << "success" << endl;
    cout << v1;
    cout << v1.at(0)<< endl;
    cout << norm(v1) <<endl;
    cout << to_string(v1) <<endl;
    cout << (is_unit( unit_vector( v1 ) ) == true);
}