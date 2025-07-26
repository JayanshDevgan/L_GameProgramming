#include <iostream>
#include <cmath>
#include <type_traits>

template<typename T>
class Vector2D {
public:
    T m_x, m_y;

    Vector2D() : m_x(T{}), m_y(T{}) {}
    Vector2D(T x, T y) : m_x(x), m_y(y) {}

    template<typename T1, typename T2>
    friend auto operator+(const Vector2D<T1>& a, const Vector2D<T2>& b)
        -> typename std::enable_if<
            std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value,
            Vector2D<decltype(T1{} + T2{})>
        >::type;

    T length() const {
        return std::hypot(m_x, m_y);
    }

    void print() const {
        std::cout << "(" << m_x << ", " << m_y << ")" << std::endl;
    }
};

template<typename T1, typename T2>
auto operator+(const Vector2D<T1>& a, const Vector2D<T2>& b)
    -> typename std::enable_if<
        std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value,
        Vector2D<decltype(T1{} + T2{})>
    >::type
{
    return Vector2D<decltype(T1{} + T2{})>(a.m_x + b.m_x, a.m_y + b.m_y);
}

int main() {
    Vector2D<int> __I__vec(14, 141);
    Vector2D<double> __D__vec(252.23, 120.214);
    Vector2D<float> __F__vec(252.02f, 1.2422f);

    __I__vec.print();
    __D__vec.print();
    __F__vec.print();

    std::cout << __I__vec.length() << std::endl;
    std::cout << __D__vec.length() << std::endl;
    std::cout << __F__vec.length() << std::endl;
    std::cout << "\n" << std::endl;

    auto Result = (__I__vec + __I__vec) + __I__vec;
    Result.print();

    auto Mixed = (__I__vec + __D__vec) + __F__vec;
    Mixed.print();

    return 0;
}
