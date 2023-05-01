#pragma once

#include <unordered_map>

namespace libasist
{
    template< typename index_t, typename value_t >
    using table_t = std::unordered_map< index_t, value_t >;
#if 0
    template< typename index_t, typename value_t >
    class table_t
    {
        public: /* typedef */
        using this_t = table_t< index_t, value_t >;
        public: /* codetor */
        table_t()
        {
        }
        ~table_t()
        {
        }
        public: /* opertor */
        public: /* getters */
        public: /* vetters */
        public: /* setters */
        public: /* actions */
    };
#endif
}
