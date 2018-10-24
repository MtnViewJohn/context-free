//
//  backwards.h
//  Context Free
//
// Copyright (c) 2018, Adam Nevraumont
// Creative Commons CC-BY-SA license
// https://creativecommons.org/licenses/by-sa/4.0/
//

#ifndef backwards_h
#define backwards_h

template<class R>
struct backwards_t {
    R r;
    constexpr auto begin() const { using std::rbegin; return rbegin(r); }
    constexpr auto begin() { using std::rbegin; return rbegin(r); }
    constexpr auto end() const { using std::rend; return rend(r); }
    constexpr auto end() { using std::rend; return rend(r); }
};
// Do NOT, I repeat do NOT change this to `backwards_t<std::decay_t<R>>.
// This code is using forwarding references in a clever way.
template<class R>
constexpr backwards_t<R> backwards( R&& r ) { return {std::forward<R>(r)}; }


#endif /* backwards_h */
