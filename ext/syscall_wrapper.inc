#include <unistd.h>

/*
 *  call-seq:
 *     syscall(num [, args...])   -> integer
 *
 *  Calls the operating system function identified by _num_ and
 *  returns the result of the function or raises SystemCallError if
 *  it failed.
 *
 *  Arguments for the function can follow _num_. They must be either
 *  +String+ objects or +Integer+ objects. A +String+ object is passed
 *  as a pointer to the byte sequence. An +Integer+ object is passed
 *  as an integer whose bit size is same as a pointer.
 *  Up to nine parameters may be passed (14 on the Atari-ST). 
 *
 *  The function identified by _num_ is system
 *  dependent. On some Unix systems, the numbers may be obtained from a
 *  header file called <code>syscall.h</code>.
 *
 *     syscall 4, 1, "hello\n", 6   # '4' is write(2) on our box
 *
 *  <em>produces:</em>
 *
 *     hello
 *
 *
 *  Calling +syscall+ on a platform which does not have any way to
 *  an arbitrary system function just fails with NotImplementedError.
 *
 * Note::
 *  Taken from io.c in 1.9.2-p290. There is a warning that the global function
 *  (Kernel.syscall) will soon be removed, so I figured I'd remove the warning
 *  and keep it here.
 */

static VALUE syscalls_syscall(int argc, VALUE *argv)
{
#ifdef atarist
    VALUE arg[13]; /* yes, we really need that many ! */
#else
    VALUE arg[8];
#endif
#if SIZEOF_VOIDP == 8 && defined(HAVE___SYSCALL) && SIZEOF_INT != 8 /* mainly *BSD */
# define SYSCALL __syscall
# define NUM2SYSCALLID(x) NUM2LONG(x)
# define RETVAL2NUM(x) LONG2NUM(x)
# if SIZEOF_LONG == 8
    long num, retval = -1;
# elif SIZEOF_LONG_LONG == 8
    long long num, retval = -1;
# else
#  error ---->> it is asserted that __syscall takes the first argument and returns retval in 64bit signed integer. <<----
# endif
#elif defined linux
# define SYSCALL syscall
# define NUM2SYSCALLID(x) NUM2LONG(x)
# define RETVAL2NUM(x) LONG2NUM(x)
    /*
     * Linux man page says, syscall(2) function prototype is below.
     *
     *     int syscall(int number, ...);
     *
     * But, it's incorrect. Actual one takes and returned long. (see unistd.h)
     */
    long num, retval = -1;
#else
# define SYSCALL syscall
# define NUM2SYSCALLID(x) NUM2INT(x)
# define RETVAL2NUM(x) INT2NUM(x)
    int num, retval = -1;
#endif
    int i;

    /* from io.c */
#define numberof(array) (int)(sizeof(array) / sizeof((array)[0]))
 
    /*
    if (RTEST(ruby_verbose)) {
	rb_warning("We plan to remove a syscall function at future release. DL(Fiddle) provides safer alternative.");
    }
    */

    rb_secure(2);
    if (argc == 0)
	rb_raise(rb_eArgError, "too few arguments for syscall");
    if (argc > numberof(arg))
	rb_raise(rb_eArgError, "too many arguments for syscall");
    num = NUM2SYSCALLID(argv[0]); ++argv;
    for (i = argc - 1; i--; ) {
	VALUE v = rb_check_string_type(argv[i]);

	if (!NIL_P(v)) {
	    StringValue(v);
	    rb_str_modify(v);
	    arg[i] = (VALUE)StringValueCStr(v);
	}
	else {
	    arg[i] = (VALUE)NUM2LONG(argv[i]);
	}
    }

    switch (argc) {
      case 1:
	retval = SYSCALL(num);
	break;
      case 2:
	retval = SYSCALL(num, arg[0]);
	break;
      case 3:
	retval = SYSCALL(num, arg[0],arg[1]);
	break;
      case 4:
	retval = SYSCALL(num, arg[0],arg[1],arg[2]);
	break;
      case 5:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3]);
	break;
      case 6:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4]);
	break;
      case 7:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4],arg[5]);
	break;
      case 8:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4],arg[5],arg[6]);
	break;
#ifdef atarist
      case 9:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4],arg[5],arg[6],
	  arg[7]);
	break;
      case 10:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4],arg[5],arg[6],
	  arg[7], arg[8]);
	break;
      case 11:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4],arg[5],arg[6],
	  arg[7], arg[8], arg[9]);
	break;
      case 12:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4],arg[5],arg[6],
	  arg[7], arg[8], arg[9], arg[10]);
	break;
      case 13:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4],arg[5],arg[6],
	  arg[7], arg[8], arg[9], arg[10], arg[11]);
	break;
      case 14:
	retval = SYSCALL(num, arg[0],arg[1],arg[2],arg[3],arg[4],arg[5],arg[6],
	  arg[7], arg[8], arg[9], arg[10], arg[11], arg[12]);
        break;
#endif
    }

    if (retval == -1)
	rb_sys_fail(0);
    return RETVAL2NUM(retval);
#undef SYSCALL
#undef NUM2SYSCALLID
#undef RETVAL2NUM
}
