#ifndef REF_PTR_H
#define REF_PTR_H
/*
Qt has some weird ownership issues for pointers, they usually get parented
and deleted by the parent but sometimes they don't.

What if we had a smart pointer that owns a pointer on construction, but 
gives up ownership if asked to whilst still containing the pointer for
use?

Ok just writing this makes it smell bad.

Also there is probably a Qt class to do this for Qt objects...
*/

template <typename T>
class ref_ptr
{
public:
    explicit ref_ptr(T* pointer, bool isOwner = true) :
        m_pointer{ pointer },
        m_isOwner{ isOwner }
    {}
    ~ref_ptr()
    {
        if (m_isOwner)
            delete m_pointer;
    }

    ref_ptr(ref_ptr const& other) = delete;
    ref_ptr& operator=(ref_ptr const& other) = delete;

    T* release()
    {
        m_isOwner = false;
        return m_pointer;
    }
    T* get() const
    {
        return m_pointer;
    }
    void reset(T* pointer = nullptr)
    {
        if (m_isOwner)
            delete m_pointer;
        m_isOwner = true;
        m_pointer = pointer;
    }

    bool isOwner() const
    {
        return m_isOwner;
    }

    T& operator*() const
    {
        return *m_pointer;
    }
    T* operator->() const
    {
        return m_pointer;
    }
    explicit operator bool() const
    {
        return m_pointer == nullptr;
    }

private:
    T* m_pointer
    bool m_isOwner;
};


#endif // REF_PTR_H