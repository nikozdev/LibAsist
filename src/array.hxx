#pragma once

#include <vector>

namespace libasist {

    template< typename value_t >
    using array_t = std::vector< value_t >;
#if 0
    template< typename value_t >
    class array_t
    {
        public: /* typedef */
        using this_t = array_t< value_t >;
        public: /* codetor */
        array_t()
        {
        }
        ~array_t()
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
