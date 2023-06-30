#include "main.hxx"
#ifdef _TYPE_RUN
#   undef _TYPE_RUN
int main(int argc, const char**argv)
{
    return libasist::term::main(argc, argv);
}
#endif
