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
