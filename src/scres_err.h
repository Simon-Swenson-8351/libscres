#ifndef SCRES_ERR_H
#define SCRES_ERR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <inttypes.h>
#include <pthread.h>

typedef enum scres_err_lvl {
    SCRES_ERR_LVL_WARN,
    SCRES_ERR_LVL_ERR,
    // INSERT NEW VALUES ABOVE
    SCRES_ERR_LVL_COUNT
} scres_err_lvl_t;
extern const char *const SCRES_ERR_LVL_STRS[SCRES_ERR_LVL_COUNT];

typedef struct scres_err_type {
    uint32_t code;
    scres_err_lvl_t level;
    char *type_name;
    char *friendly_name;
} scres_err_type_t;

const size_t SCRES_ERR_STR_LEN = 256;
typedef struct scres_err {
    scres_err_type_t *type;
    pthread_rwlock_t lock;
    bool initd;
    char *file;
    char *function;
    uint32_t line;
    char *site_info; // any extra info provided at the site the error happened.
                     // for example, a domain error alone might not be clear, 
                     // but this string might contain additional helpful info 
                     // like "buffer length given for 2nd buffer argument was 0"
    char str[SCRES_ERR_STR_LEN];
} scres_err_t;

extern const scres_err_type_t SCRES_ERR_TYPE_ALLOC_FAILED;
extern const scres_err_type_t SCRES_ERR_TYPE_DOMAIN;
extern const scres_err_type_t SCRES_ERR_TYPE_FILE_FORMAT_WRONG;
extern const scres_err_type_t SCRES_ERR_TYPE_FILE_IO_ERR;
extern const scres_err_type_t SCRES_ERR_TYPE_MISMATCHED_BUFFER_SIZES;

void scres_err_set_str(scres_err_t *self);

// macro for initializing an error type
#define SCRES_ERR_TYPE_INIT(type_var_name, in_code, in_level, in_friendly_name) \
    const scres_err_type_t type_var_name = {\
        .code = in_code,\
        .level = in_level,\
        .type_name = #type_var_name ,\
        .friendly_name = in_name\
    }

// Needs to be a macro to obtain proper values for __FILE__, __FUNCTION__, and 
// __LINE__
#define SCRES_ERR_VARNAME2(id) scres_err_ ## id
#define SCRES_ERR_VARNAME(id) SCRES_ERR_VARNAME2(id)
#define SCRES_ERR_COMMON(ret_or_set_stmt, type_ptr, f, fn, l)\
    do {\
        static scres_err_t SCRES_ERR_VARNAME(l) = {\
            .type = type_ptr,\
            .lock = PTHREAD_RWLOCK_INITIALIZER,\
            .initd = false,\
            .file = f,\
            .function = fn,\
            .line = l\
        };\
        pthread_rwlock_rdlock(&(SCRES_ERR_VARNAME(l).lock));\
        if(!SCRES_ERR_VARNAME(l).initd) {\
            pthread_rwlock_unlock(&(SCRES_ERR_VARNAME(l).lock));\
            pthread_rwlock_wrlock(&(SCRES_ERR_VARNAME(l).lock));\
            if(!SCRES_ERR_VARNAME(l).initd) {\
                scres_err_set_str(&SCRES_ERR_VARNAME(l));\
                SCRES_ERR_VARNAME(l).initd = true;\
            }\
        }\
        pthread_rwlock_unlock(&(SCRES_ERR_VARNAME(l).lock));\
        ret_or_set_stmt;\
    } while(0);
#define SCRES_ERR_RETURN_STMT(id)\
    do {\
        return &SCRES_ERR_VARNAME(id);\
    } while(0);
#define SCRES_ERR_SET_STMT(err_var, id)\
    do {\
        err_var = &SCRES_ERR_VARNAME(id);\
    } while(0);
#define SCRES_ERR_RETURN(type_ptr, file, fn, line)\
    SCRES_ERR_COMMON(SCRES_ERR_RETURN_STMT(line), type_ptr, file, fn, line)
#define SCRES_ERR_SET(err_var, type_ptr, file, fn, line)\
    SCRES_ERR_COMMON(SCRES_ERR_SET_STMT(err_var, line), type_ptr, file, fn, line)


#ifdef __cplusplus
}
#endif

#endif // #ifndef SCRES_ERR_H