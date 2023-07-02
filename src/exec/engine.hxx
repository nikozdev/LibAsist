#ifndef LIBASIST_EXEC_ENGINE_HXX
#define LIBASIST_EXEC_ENGINE_HXX 1

#include "../head.hxx"

/* headers */

#include "../meta/single.hxx"

/* content */

namespace libasist { namespace exec { /* typedef */

/* abstract state type */
class a_engine_state_t
{
public: /* typedef */
    using name_t = std::string;
    using this_t = a_engine_state_t;
public: /* codetor */
    virtual ~a_engine_state_t() = default;
public: /* actions */
    virtual inline v1bit_t init() { return TRUTH; }
    virtual inline v1bit_t quit() { return TRUTH; }
    virtual inline v1bit_t work() { return TRUTH; }
}; /* abstract engine state */

/* template engine type */
template<class t_class_t, class t_state_t = a_engine_state_t>
class engine_t : public meta::single_t<t_class_t>
{
public: /* typedef */
    /*
	using work_proc_t = t_delegator_t<bool_t(void_t)>;
    */
    using work_proc_t = std::function<bool_t(void_t)>;
	using work_flow_t = std::thread;
	using work_flag_t = v1bit_t;
	using state_t = t_state_t;
	using state_list_t = darray_t<state_t*>;
    using this_t = engine_t<t_class_t>;
public: /* getters */
    inline work_flow_t&get_work_flow()
    { return this->work_flow; }
    inline work_flag_t&get_work_flag()
    { return this->work_flag; }
    inline state_t*get_state(index_t index)
    {
        _EFNOT(this->vet_state(index), return NULL, "not found!");
        return this->state_list[index];
    }
public: /* setters */
    template<class t_value_t, typename...t_vargs_t>
    this_t&create_state(t_vargs_t&&...vargs)
    {
        this->state_list.push_back(new t_value_t(std::forward<vargs>(vargs)...));
        return *this;
    }
    this_t&delete_state(index_t index)
    {
        _EFNOT(this->vet_state(index), return *this, "index error!");
        delete this->state_list[index];
        this->state_list.erase(this->state_lsit.begin() + index);
        return *this;
    }
    this_t&delete_state()
    {
        return this->state_list.empty()
            ? *this
            : this->delete_state(this->state_list.size() - 1);
    }
public: /* vetters */
    inline v1bit_t vet_work(bool_t work_flag = TRUTH) const
    { return this->work_flag == work_flag; }
    inline v1bit_t vet_state() const
    { return !this->state_list.empty(); }
    inline v1bit_t vet_state(index_t index) const
    { return this->state_list.size() > index; }
public: /* actions */
    virtual inline v1bit_t init()
    {
        for (auto&iter : this->state_list)
        {
            _EFNOT(iter->init(), return FALSE, "state init error!");
        }
		return TRUTH;
	}
    virtual inline v1bit_t quit()
    {
        for (auto&iter : this->state_list)
        {
            _EFNOT(iter->quit(), return FALSE, "quit error!");
        }
        while (this->vet_state())
        { this->delete_state(); }
		this->state_list.clear();
		return TRUTH;
	}
    virtual inline v1bit_t work()
    {
        for (auto&iter : this->state_list)
        { _EFNOT(iter->work(), return FALSE, "work error!"); }
		return TRUTH;
	}
    inline v1bit_t exec()
    {
        _EFNOT(vet_work(FALSE), return FALSE, "already working!");
		this->work_flow = work_flow_t(this->work_proc);
		this->work_flag = TRUTH;
		return TRUTH;
	}
    inline v1bit_t stop()
    {
		_EFNOT(vet_work(TRUTH), return FALSE, "already quitted!");
		this->work_flag = FALSE;
		return TRUTH;
	}
protected: /* datadef */
	work_flow_t work_flow;
	work_flag_t work_flag;
	work_proc_t work_proc = [this]()->v1bit_t {
		_PCALL({
			_EFNOT(init(), return stop(), "init error!");
            while (vet_work())
            { _EFNOT(this->work(), return stop(), "work error!"); }
			_EFNOT(quit(), return stop(), "quit error!");
		}, return FALSE, "work error!");
		return TRUTH;
	};
	state_list_t state_list;
}; /* engine_t */

} } /* typedef */

#endif/*LIBASIST_EXEC_ENGINE_HXX*/
