#include "../head.hxx"

/* headers */

#include "args.hxx"
#include "help.hxx"

/* content */

namespace libasist { namespace term { /* datadef */
} }

namespace libasist { namespace term { /* getters */

sdstr_t get_opt(const svstr_t&name)
{
    if (args.size() == 1 || name.size() < 2)
    { return ""; }
    const auto head = args.begin() + 1;
    const auto tail = args.end() - 1;
    const auto last = args.end();
    if (name[0] == '-')
    {
        if (name[1] == '-')
        {
            for (auto iter = head; iter != last; iter++)
            {
                auto offset = (*iter).find('=');
                if (offset == -1)
                {
                    if (*iter == name)
                    {
                        if (iter == tail)
                        {
                            help( error_argv );
                            return "";
                        }
                        return sdstr_t(*(++iter));
                    }
                }
                else if ((*iter).find(name) != -1)
                {
                    return sdstr_t(*iter).substr(offset + 1);
                }
            }
        }
        else
        {
            for (auto iter = head; iter < last; iter++)
            {
                if (*iter == name) { return sdstr_t(*( ++iter )); }
            }
        }
    }
    return "";
}

} } /* getters */

namespace libasist { namespace term { /* vetters */

bool_t vet_opt(const svstr_t&name)
{
    const auto head = args.begin() + 1;
    const auto last = args.end();
    for (auto iter = head; iter < last; iter++)
    {
        if ((*iter).find(name) != -1)
        { return TRUTH; }
    }
    return FALSE;
}

} } /* vetters */

namespace libasist { namespace term { /* setters */
} } /* setters */

namespace libasist { namespace term { /* actions */
} } /* actions */
