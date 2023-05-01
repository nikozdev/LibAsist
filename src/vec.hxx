#pragma once

#include "./enum.hxx"

#include "./val.hxx"
#include "./num.hxx"

namespace libasist
{

    template < typename value_t, count_t count >
    class vector_t_t
    {
        /* typedefs */

        using this_t = vector_t_t< value_t, count >;

        using vdata_t = value_t[ count ];

        public:

        /* codetor */

        vector_t_t():
            vdata{ ZERO }
        {
        }
        vector_t_t( std::initializer_list< value_t > ilist ):
            vdata{ ZERO }
        {
            auto iter = ilist.begin();
            for ( auto index = 0; index < ilist.size(); index++ )
            {
                this->vdata[ index ] = *(iter++);
            }
        }
        vector_t_t( value_t value ):
            this_t()
        {
            for ( auto index = 0; index < count; index++ )
            {
                this->vdata[ index ] = value;
            }
        }
        vector_t_t( const vector_t_t& copy ):
            this_t()
        {
            std::memcpy( this, &copy, get_msize() );
        }
        vector_t_t( vector_t_t&& copy ):
            this_t()
        {
            std::memmove( this, &copy, get_msize() );
        }

        /* getters */

        static count_t get_count()
        {
            return count;
        }
        static msize_t get_msize()
        {
            return count * sizeof( value_t );
        }

        /* operators */

        this_t& operator= ( value_t value )
        {
            for ( auto index = 0; index < count; index++ )
            {
                this->vdata[ index ] = value;
            }
            return *this;
        }
        this_t& operator= ( const this_t& copy )
        {
            std::memcpy( this, &copy, get_msize() );
            return *this;
        }
        this_t& operator= ( this_t&& copy )
        {
            std::memmove( this, &copy, get_msize() );
            return *this;
        }

        template< typename stream_t = std::ostream >
        stream_t& operator<<( stream_t& stream ) const
        {
            for ( auto index = 0; index < count; index++ )
            {
                stream << this->vdata[ index ] << " ";
            }
            return stream;
        }
        template< typename stream_t = std::istream >
        const stream_t& operator>>( const stream_t& stream )
        {
            for ( auto index = 0; index < count; index++ )
            {
                stream >> this->vdata[ index ];
            }
            return stream;
        }

#   define _VECTOR_DEF_ARITH( sign ) \
        \
        this_t& operator sign##=( value_t value ) \
        { \
            for ( auto index = 0; index < count; index++ ) \
            { \
                this->vdata[ index ] = this->vdata[ index ] sign value; \
            } \
            return *this; \
        } \
        this_t operator sign ( value_t value ) const \
        { \
            this_t result; \
            for ( auto index = 0; index < count; index++ ) \
            { \
                result.vdata[ index ] = this->vdata[ index ] sign value; \
            } \
            return result; \
        } \
        this_t& operator sign##=( const this_t& vector ) \
        { \
            for ( auto index = 0; index < count; index++ ) \
            { \
                this->vdata[ index ] = this->vdata[ index ] sign vector.vdata[ index ]; \
            } \
            return *this; \
        } \
        this_t operator sign ( const this_t& vector ) const \
        { \
            this_t result; \
            for ( auto index = 0; index < count; index++ ) \
            { \
                result.vdata[ index ] = this->vdata[ index ] sign vector.vdata[ index ]; \
            } \
            return result; \
        } \
        /* _VECTOR_DEF_ARITH */
        _VECTOR_DEF_ARITH( + )
        _VECTOR_DEF_ARITH( - )
        _VECTOR_DEF_ARITH( / )
        _VECTOR_DEF_ARITH( * )
#   undef _VECTOR_DEF_ARITH

        value_t&operator[]( index_t index )
        {
            return this->vdata[ index ];
        }
        value_t operator[]( index_t index ) const
        {
            return this->vdata[ index ];
        }

        private:

        /* variables */

        vdata_t vdata;
    };
    template< typename stream_t, typename value_t, count_t count >
    stream_t& operator<<( stream_t& stream, const vector_t_t< value_t, count >& vector )
    {
        for ( auto index = 0; index < count; index++ )
        {
            stream << vector[ index ] << " ";
        }
        return stream;
    }
    template< typename stream_t, typename value_t, count_t count >
    const stream_t& operator>>( const stream_t& stream, vector_t_t< value_t, count >& vector )
    {
        for ( auto index = 0; index < count; index++ )
        {
            stream >> vector[ index ];
        }
        return stream;
    }

#define _PRIM_FOR( _ACT_ ) \
    \
    _ACT_( c, 2 ) \
    _ACT_( c, 3 ) \
    _ACT_( c, 4 ) \
    _ACT_( u, 2 ) \
    _ACT_( u, 3 ) \
    _ACT_( u, 4 ) \
    _ACT_( s, 2 ) \
    _ACT_( s, 3 ) \
    _ACT_( s, 4 ) \
    /* _PRIM_FOR */
#   define _PRIM_DEF_ACT( tchar, count ) \
    typedef vector_t_t< v1##tchar##_t, count > v##count##tchar##_t;
    _PRIM_FOR( _PRIM_DEF_ACT )
#   undef _PRIM_DEF_ACT
#   undef _PRIM_FOR

    using coord_t = v2s_t;
    using sizes_t = v2u_t;

}
