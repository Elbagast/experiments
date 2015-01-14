#ifndef PARSE_ID_H
#define PARSE_ID_H
/*
You want to parse a class to and from a streams. You need an identifier so that the correct parse logic can be 
applied in cases where an item in a stream may be one of many different objects (e.g. if you are parsing commands,
then the command name). You also want to avoid code dulpication since this is going to be used in a lot of 
different classes which may or may not be related.

So how do you go about this?
*/
#include <iostream>
#include <string>

// Option 1 - use an abstract base class. Pretty simple but the identification code isn't shared...
class ParsableBase1
{
public:
    virtual ~ParsableBase1() = default;

    virtual std::ostream& serialise(std::ostream& oStream) const = 0;
    virtual std::istream& unserialise(std::istream& iStream) = 0;
};

template <typename T>
class ParseableBase2
{
public:
    using base_type = ParseableBase2 < T > ;
    using derived_type = T;
    
    virtual ~ParsableBase2() = default;

    virtual std::string className() const = 0;
    bool isClassName(std::string const& name) const { return name == className(); } // virtual call to derived class

    std::ostream& serialise(std::ostream& oStream) const
    {
        return oStream
    }
    // does it actually make sense to have this inside the class....
    std::istream& unserialise(std::istream& iStream)
    {

    }

    virtual std::ostream& serialiseData(std::ostream& oStream) const = 0;
    virtual std::istream& unserialiseData(std::istream& iStream) = 0;
};

#endif // PARSE_ID_H