#include "./libasist.hxx"

#ifdef _TYPE_RUN
#   undef _TYPE_RUN
int main( int argc, const char** argv )
{
    return libasist::main( argc, argv );
}
#endif /* _TYPE_RUN */
