template <typename T>
inline T min(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
inline T max(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
inline T clamp(T x, T a, T b) {
    x = min(x, b);
    x = max(x, a);
    return x;
}
