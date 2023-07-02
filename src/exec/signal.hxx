#ifndef LIBASIST_UTIL_SIGNAL_HXX
#define LIBASIST_UTIL_SIGNAL_HXX 1

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace util { /* typedef */

template <typename...args_t>
class signal_t
{
public: /* typedef */
    using signal_t = signal_t<args_t...>;
    using func_t = std::function<void(args_t...)>;
    class link_t
    {
    public: /* codetor */
        inline link_t(signal_t&signal, index_t index, const func_t&func)
            : signal(&signal), index(index), func(func) {}
        inline link_t(const link_t&copy)
            : signal(copy.signal), index(copy.index), func(copy.func) {}
        inline link_t(link_t&&copy)
            : signal(copy.signal), index(copy.index), func(copy.func) {}
        inline ~link_t() = default;
    public: /* vetters */
        inline bool vet() const { return this->signal; }
    public: /* actions */
        inline bool quit()
        {
            this->signal->drop(this->index);
            return TRUTH;
        }
    public: /* symbols */
        inline link_t&operator=(link_t&&copy)
        { std::memmove(this, &copy, sizeof(link_t)); return *this; }
        inline link_t&operator=(const link_t&copy)
        { std::memcpy(this, &copy, sizeof(link_t)); return *this; }
    private: /* datadef */
        signal_t*signal;
        index_t index;
        const func_t func;
    private: /* friends */
        friend signal_t;
    };
    using relink_t = link_t*;
    using relink_list_t = darray_t<relink_t>;
public: /* codetor */
    signal_t() {}
    ~signal_t() { this->quit(); }
public: /* actions */
    inline relink_t find(index_t index)
    {
        return this->relink_list.size() > index ?
            this->relink_list[index] : relink_t();
    }
    inline relink_t bind(const func_t&func)
    {
        auto index = this->relink_list.size();
        relink_t relink;
        /*
        memo::owner->new_one(relink, *this, index, func);
        */
        relink = new link_t(*this, index, func);
        this->relink_list.push_back(relink);
        return relink;
    }
    inline bool_t quit()
    {
        while (this->relink_list.size() > 0)
        {
            this->relink_list.back()->quit();
        }
        return TRUTH;
    }
    inline bool_t drop(index_t index)
    {
        auto liter = this->relink_list.begin() + index;
        /*
        memo::owner->del_one(*liter);
        */
        delete *liter;
        this->relink_list.erase(liter);
        for (auto iter = index; iter < this->relink_list.size(); iter++)
        { this->relink_list[iter]->index = iter; }
        return TRUTH;
    }
    inline void call(args_t...args)
    {
        for (auto&relink : this->relink_list)
        { relink->func(std::forward<args_t&&...>(args)...); }
    }
private:
    relink_list_t relink_list;
}; /* signal_t */

} } /* typedef */

#endif/*LIBASIST_UTIL_SIGNAL_HXX*/
