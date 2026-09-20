#ifndef TuiLocal_h
#define TuiLocal_h

#include "TuiRef.h"

template <typename T> // Should be derived from TuiRef
class TuiLocal
{
private: // members
    T* ref;

public: // functions
    TuiLocal(TuiRef* r) : ref(r) {}

    template<typename... Args>
    TuiLocal(Args... args) : ref(new T(args...)) {}

    ~TuiLocal()
    {
        if (ref)
        {
            ref->release();
        }
    }

    // Copy operators
    TuiLocal(const TuiLocal& other) : ref(new T(*other.ref)) {}
    TuiLocal& operator=(const TuiLocal& other)
    {
        if (this != &other)
        {
            ref->release();
            ref = new T(*other.ref);
        }
        return *this;
    }

    // Access operators
    T* operator->() const { return ref; }
    T& operator*() const { return *ref; }

    // Implicit conversions
    operator TuiRef*() const { return static_cast<TuiRef*>(ref); }
    operator T*() const { return ref; }

    // Getters
    TuiRef* getRef() const { return static_cast<TuiRef*>(ref); }
    T* get() const { return ref; }
};

#endif // TuiLocal_h