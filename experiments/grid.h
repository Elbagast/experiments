#ifndef GRID_H
#define GRID_H
/*
Using an array of arrays to store a grid of items gets a bit messy, so here's some thoughts
about doing it a little differently.
*/

#include <array>
#include <type_traits>

class GridCoordinate
{
public:
    using index_type = std::size_t;
    GridCoordinate(index_type width, index_type height) :
        m_width{ width },
        m_height{ height }
    {}

    index_type getWidth() const         { return m_width; }
    void setWidth(index_type width)     { m_width = width; }

    index_type getHeight() const        { return m_height; }
    void setHeigt(index_type height)    { m_height = height; }

private:
    index_type m_width, m_height;
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
    using value_type = T;
    using index_type = std::size_t;
    using coord_type = GridCoordinate;
    using array_type = std::array < value_type, Width*Height >;
    //using iterator = typename array_type::iterator;
    //using const_iterator = typename array_type::const_iterator;
    
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
    index_type size() const     { return Width*Height; }
    //constexpr
    index_type width() const    { return Width; }
    //constexpr
    index_type height() const   { return Height; }
    
    // Index and Coordinate conversions
    index_type indexToWidth(index_type index) const                         { return index % Width; }
    index_type indexToHeight(index_type index) const                        { return index / Height; }
    coord_type indexToCoordinate(index_type index) const                    { return coord_type(indexToWidth(index), indexToHeight(index)); }
    index_type coordinateToIndex(index_type width, index_type height) const { return width + height * Height; }
    index_type coordinateToIndex(GridCoordinate coord) const                { return coordinateToIndex(coord.getWidth(), coord.getHeight()); }

    value_type& at(index_type index)                                { return m_array.at(index); }
    value_type& at(index_type width, index_type height)             { return m_array.at(coordinateToIndex(width, height)); }
    value_type& at(coord_type coord)                                { return m_array.at(coordinateToIndex(coord)); }

    value_type const& at(index_type index) const                    { return m_array.at(index); }
    value_type const& at(index_type width, index_type height) const { return m_array.at(coordinateToIndex(width, height)); }
    value_type const& at(coord_type coord) const                    { return m_array.at(coordinateToIndex(coord)); }

    value_type const& cat(index_type index) const                    { return m_array.at(index); }
    value_type const& cat(index_type width, index_type height) const { return m_array.at(coordinateToIndex(width, height)); }
    value_type const& cat(coord_type coord) const                    { return m_array.at(coordinateToIndex(coord)); }

    // Reveal the array
    array_type& getArray()                                          { return m_array; }
    array_type const& getArray() const                              { return m_array; }
    array_type const& cgetArray() const                             { return m_array; }
    
    void setArray(array_type const& inputArray)                     { m_array = inputArray; }
    void setArray(array_type && inputArray)                         { m_array = std::move(inputArray); }
private:
    // Helpers
    //============================================================

    // Data Members
    //============================================================
    array_type m_array;
};


#endif