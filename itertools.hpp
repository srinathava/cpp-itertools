#pragma once

#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>

// A free function which allows us to zip multiple ranges into a single
// range-tuple.
template <typename... T>
auto zip(const T&... containers) -> boost::iterator_range<boost::zip_iterator<decltype(boost::make_tuple(std::begin(containers)...))>>
{
    auto zip_begin = boost::make_zip_iterator(boost::make_tuple(std::begin(containers)...));
    auto zip_end = boost::make_zip_iterator(boost::make_tuple(std::end(containers)...));
    return boost::make_iterator_range(zip_begin, zip_end);
}

template <typename RangeT>
struct EnumerateRange
{
    typedef typename RangeT::iterator OrigIterT;
    typedef typename std::pair<typename RangeT::iterator::value_type, size_t> value_type;

    EnumerateRange(RangeT origRange)
        : m_origRange(origRange)
    {
    }

    struct iterator: public std::iterator<std::forward_iterator_tag, 
                                          value_type, 
                                          ptrdiff_t, 
                                          value_type*, 
                                          value_type>
    {
        iterator(OrigIterT origIter)
            : m_origIter(origIter)
            , m_counter(0U)
        {}

        bool operator!=(const iterator& other)
        {
            return m_origIter != other.m_origIter;
        }

        bool operator==(const iterator& other)
        {
            return m_origIter == other.m_origIter;
        }

        iterator& operator++()
        {
            ++m_origIter;
            ++m_counter;
            return *this;
        }

        value_type operator*() const
        {
            return std::make_pair(*m_origIter, m_counter);
        }

      private:
        OrigIterT m_origIter;
        size_t m_counter;
    };
    
    iterator begin() const
    {
        return iterator(m_origRange.begin());
    }

    iterator end() const
    {
        return iterator(m_origRange.end());
    }


  private:
    RangeT m_origRange;
};

template <typename RangeT>
EnumerateRange<RangeT> enumerate(const RangeT& origRange)
{
    return EnumerateRange<RangeT>(origRange);
}

