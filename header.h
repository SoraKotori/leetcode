#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iomanip>
#include <queue>
#include <functional>
#include <queue>
#include <limits>
#include <deque>
#include <set>
#include <stack>
#include <map>

using namespace std;

template <std::ranges::range R>
auto print_1D(const R& r)
{
    using ElementType = std::ranges::range_value_t<R>;

    ranges::copy(r, ostream_iterator<ElementType>(std::cout, " "));
    cout << endl;
}

template <std::ranges::range R>
auto print_2D_line(const R& r)
{
    using ElementType = std::ranges::range_value_t<R>;

    cout << '[';
    for (const auto r2 : r)
    {
        cout << '[';
        ranges::copy(r2, ostream_iterator<std::ranges::range_value_t<ElementType>>(std::cout, " "));
        cout << ']';
    }
    cout << ']' << endl;
}
