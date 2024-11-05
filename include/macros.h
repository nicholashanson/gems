#include <tuple>

#define first(tuple) std::get<0>(tuple)
#define middle(tuple) std::get<1>(tuple)
#define last(tuple) std::get<2>(tuple)

#define left(pair) std::get<0>(pair)
#define right(pair) std::get<1>(pair)
