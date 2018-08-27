///
/// \file
/// \brief Header file for compile-time checking type of std::tuple.
///

#ifndef CHECK_TUPLE_H
#define CHECK_TUPLE_H

#include <tuple>
#include <type_traits>

template<class T>
struct is_onetype_tuple;

template<class Head, class Neck, class... Tail>
struct is_onetype_tuple<std::tuple<Head, Neck, Tail...>>
{
  static const bool value =
    (std::is_same<Head, Neck>::value) ? is_onetype_tuple<std::tuple<Neck, Tail...>>::value : false;
};

template<class Head>
struct is_onetype_tuple<std::tuple<Head>>
{
  static const bool value = true;
};

template<>
struct is_onetype_tuple<std::tuple<>>
{
  static const bool value = false;
};

static_assert(is_onetype_tuple<std::tuple<>>::value == false, "Empty tuple");
static_assert(is_onetype_tuple<std::tuple<int>>::value == true, "Tuple with one type");
static_assert(is_onetype_tuple<std::tuple<int, int>>::value == true, "Tuple with two equal types");
static_assert(is_onetype_tuple<std::tuple<bool, int>>::value == false, "Tuple with two not equal types");
static_assert(is_onetype_tuple<std::tuple<int, int, int>>::value == true, "Tuple with three equal types");
static_assert(is_onetype_tuple<std::tuple<int, int, bool>>::value == false, "Tuple with three not equal types");

#endif // CHECK_TUPLE_H
