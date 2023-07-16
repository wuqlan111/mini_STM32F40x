
#ifndef  DRIVER_UTIL_H
#define  DRIVER_UTIL_H


#define  CHECK_PARAM_VALUE(param, max)     {        \
                        if ((param) > (max)) {      \
                            return  -1;       \
                        }                   \
                    }

#define  CHECK_PARAM_NULL(param)     {        \
                        if ((param) == (NULL)) {      \
                            return  -1;       \
                        }                   \
                    }



















#endif

