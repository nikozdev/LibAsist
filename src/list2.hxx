#pragma once

#include <list>

namespace libasist {

    template< typename value_t >
    using list2_t = std::list< value_t >;
#if 0
    template< typename value_t >
    class list2_t
    {
        public: /* typedef */
        using this_t = list2_t< value_t >;
        public: /* codetor */
        list2_t()
        {
        }
        ~list2_t()
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
