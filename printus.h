#pragma once
#include <type_traits>
#include <iostream>
#include <vector>
#include <tuple>
#include <list>


template<class T>
typename std::enable_if<std::is_integral_v<T>, T>::type
print_ip(const T& octet) {
    static constexpr uint8_t b_size = 8, m_byte = 255, b_shift = 1;
    for (auto sz = sizeof(T); sz != 0; --sz) {
        std::cout << ((octet >> (b_size * (sz - b_shift))) & m_byte) << (sz != b_shift ? "." : "");
    }
    return {};
}

//
template<typename T>
struct is_string {
    static const bool value = false;
};

template<>
struct is_string<std::string> {
    static const bool value = true;
};


template <typename T>
typename std::enable_if<is_string<T>::value>::type print_ip(const T& octet) {
    std::cout << octet;
}


// Vector and List
template<typename T>
struct is_list_or_vector {
    static const bool value = false;
};

template<typename T>
struct is_list_or_vector<std::vector<T>> {
    static const bool value = true;
};


template<typename T>
struct is_list_or_vector<std::list<T>> {
    static const bool value = true;
};


template <typename T>
std::enable_if_t<is_list_or_vector<T>::value> print_ip(const T& octet) {
    auto ip = octet.begin();
    while (ip != octet.end()) {
        std::cout << *ip;
        ++ip;
        ip != octet.end() ? std::cout << "." : std::cout << "";
    }
}

// Tuple
template <typename ...>
struct are_same : std::true_type {};

template <typename S, typename T, typename ... Ts>
struct are_same <S, T, Ts...> : std::false_type {};

template <typename T, typename ... Ts>
struct are_same <T, T, Ts...> : are_same<T, Ts...> {};

template<typename T, size_t ArgPos, size_t LastPos>
struct unpack_tuple {
    static void print_tuple(const T& octet) {
        std::cout << std::get<ArgPos>(octet) << ".";
        unpack_tuple<T, ArgPos + 1, LastPos>::print_tuple(octet);
    }
};

template<typename Type, size_t ArgPos>
struct unpack_tuple<Type, ArgPos, ArgPos> {
    static void print_tuple(const Type& octet) {
        std::cout << std::get<ArgPos>(octet);
    }
};

template<typename ...Args>
typename std::enable_if_t<are_same<Args...>::value, void> print_ip(const std::tuple<Args...> &octet) {
    constexpr int num_args_tuple = std::tuple_size<std::tuple<Args...>>::value;
    unpack_tuple<std::tuple<Args...>, 0, num_args_tuple - 1>::print_tuple(octet);
}
