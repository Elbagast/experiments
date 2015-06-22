#ifndef GRID_H
#define GRID_H
/*
Using an array of arrays to store a grid of items gets a bit messy, so here's some thoughts
about doing it a little differently.
*/

#include <array>
#include <vector>
#include <type_traits>
#include <stack>

class GridCoordinate
{
public:
    using size_type = std::size_t;
    GridCoordinate(size_type width, size_type height) :
        m_width{ width },
        m_height{ height }
    {}

    size_type getWidth() const         { return m_width; }
    void setWidth(size_type width)     { m_width = width; }

    size_type getHeight() const        { return m_height; }
    void setHeigt(size_type height)    { m_height = height; }

private:
    size_type m_width, m_height;
};

/*

Grid<T,5,3> stores:

T T T T T
T T T T T
T T T T T

But actually it stores it as:

T T T T T T T T T T T T T T T

*/

template <typename T, std::size_t Width, std::size_t Height>
class Grid
{
    static_assert(Width >0, 
        "Cannot instantiate Grid<T, Width, Height> with an Width of 0.");
    static_assert(Height >0,
        "Cannot instantiate Grid<T, Width, Height> with an Height of 0.");
    static_assert(std::is_default_constructible<T>::value,
        "Cannot instantiate Grid<T, Width, Height> with a type T that has no default constructor.");
public:
    // Typedefs
    //============================================================
    using array_type = std::array < T, Width*Height >;
    using coord_type = GridCoordinate;

    using value_type = typename array_type::value_type;
    using size_type = typename array_type::size_type;
    
    // Special 6
    //============================================================
    Grid() = default;
    explicit Grid(array_type const& inputArray) :
        m_array{ inputArray }
    {}
    explicit Grid(array_type && inputArray) :
        m_array{ std::move(inputArray) }
    {}

    //Implicit default copy
    //Implicit default move

    // Interface
    //============================================================
    //constexpr
    size_type size() const     { return Width*Height; }
    //constexpr
    size_type width() const    { return Width; }
    //constexpr
    size_type height() const   { return Height; }
    
    // Index and Coordinate conversions
    size_type indexToWidth(size_type index) const                           { return index % Width; }
    size_type indexToHeight(size_type index) const                          { return index / Height; }
    coord_type indexToCoordinate(size_type index) const                     { return coord_type(indexToWidth(index), indexToHeight(index)); }
    size_type coordinateToIndex(size_type width, size_type height) const    { return width + height * Height; }
    size_type coordinateToIndex(GridCoordinate coord) const                 { return coordinateToIndex(coord.getWidth(), coord.getHeight()); }

    value_type& at(size_type index)                                 { return m_array.at(index); }
    value_type& at(size_type width, size_type height)               { return m_array.at(coordinateToIndex(width, height)); }
    value_type& at(coord_type coord)                                { return m_array.at(coordinateToIndex(coord)); }

    // These
    //value_type const& at(size_type index) const                   { return m_array.at(index); }
    //value_type const& at(size_type width, size_type height) const { return m_array.at(coordinateToIndex(width, height)); }
    //value_type const& at(coord_type coord) const                  { return m_array.at(coordinateToIndex(coord)); }

    value_type const& cat(size_type index) const                    { return m_array.at(index); }
    value_type const& cat(size_type width, size_type height) const  { return m_array.at(coordinateToIndex(width, height)); }
    value_type const& cat(coord_type coord) const                   { return m_array.at(coordinateToIndex(coord)); }

    // Reveal the array - this is instead of forwarding all the functions it has...for now
    // I'm not clear on what would be meaningful yet - like iterators
    array_type& getArray()                                          { return m_array; }
    array_type const& getArray() const                              { return m_array; }
    array_type const& cgetArray() const                             { return m_array; }
    
    void setArray(array_type const& inputArray)                     { m_array = inputArray; }
    void setArray(array_type && inputArray)                         { m_array = std::move(inputArray); }

private:
    // Data Members
    //============================================================
    array_type m_array;
};




/*
An alternative implementation based on std::vector that doesn't require a type abstraction to switch between sizes.

This has the problem that it doesn't enforce limits on capacity...
...which is probably an argument against this version since this type was conceived to be something that could 
represent a fixed game / puzzle board...
*/

template <typename T>
class GridVector
{
    static_assert(std::is_default_constructible<T>::value,
        "Cannot instantiate GridVector<T> with a type T that has no default constructor.");
public:
    // Typedefs
    //============================================================
    using vector_type = std::vector < T >;
    using coord_type = GridCoordinate;

    using value_type = typename vector_type::value_type;
    using size_type = typename vector_type::size_type;

    // Special 6
    //============================================================
    explicit GridVector(size_type width, size_type height) :
        m_vector{ width*height }, // initialise to the size it will stay at
        m_width{ width },
        m_height{ height }
    {}

    //Implicit default copy
    //Implicit default move

    // Interface
    //============================================================
    //constexpr
    size_type size() const     { return m_width * m_height; }
    //constexpr
    size_type width() const    { return m_width; }
    //constexpr
    size_type height() const   { return m_height; }

    // Index and Coordinate conversions
    size_type indexToWidth(size_type index) const                           { return index % m_width; }
    size_type indexToHeight(size_type index) const                          { return index / m_height; }
    coord_type indexToCoordinate(size_type index) const                     { return coord_type(indexToWidth(index), indexToHeight(index)); }
    size_type coordinateToIndex(size_type width, size_type height) const    { return width + height * m_height; }
    size_type coordinateToIndex(GridCoordinate coord) const                 { return coordinateToIndex(coord.getWidth(), coord.getHeight()); }

    value_type& at(size_type index)                                 { return m_vector.at(index); }
    value_type& at(size_type width, size_type height)               { return m_vector.at(coordinateToIndex(width, height)); }
    value_type& at(coord_type coord)                                { return m_vector.at(coordinateToIndex(coord)); }

    // These
    //value_type const& at(size_type index) const                   { return m_array.at(index); }
    //value_type const& at(size_type width, size_type height) const { return m_array.at(coordinateToIndex(width, height)); }
    //value_type const& at(coord_type coord) const                  { return m_array.at(coordinateToIndex(coord)); }

    value_type const& cat(size_type index) const                    { return m_vector.at(index); }
    value_type const& cat(size_type width, size_type height) const  { return m_vector.at(coordinateToIndex(width, height)); }
    value_type const& cat(coord_type coord) const                   { return m_vector.at(coordinateToIndex(coord)); }

    // Reveal the vector - this is instead of forwarding all the functions it has...
    vector_type& getVector()                                          { return m_vector; }
    vector_type const& getVector() const                              { return m_vector; }
    vector_type const& cgetVector() const                             { return m_vector; }

    void setVector(vector_type const& inputVector)                     { m_vector = inputArray; }
    void setVector(vector_type && inputVector)                         { m_vector = std::move(inputVector); }
private:
    // Data Members
    //============================================================
    vector_type m_vector;
    size_type m_width, m_height; // can't be const if you want this type to be assignable...
};

#endif