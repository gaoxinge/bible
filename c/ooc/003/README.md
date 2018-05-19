## 运行

```
> gcc -o main main.c String.c new.c
> main
```

## 如何扩展一个新类

```c
// xxx.c
#include <stdarg.h>
#include "xxx.h"
#include "new.h"
#include "new.r"

struct xxx {
    const void* class;
    //...
};

static void* xxx_ctor(void* _self, va_list* app);
static void* xxx_dtor(void* _self);
static void* xxx_clone(const void* _self);
static int   xxx_differ(const void* _self, const void* _b);

static const struct Class _xxx = {
    sizeof(struct xxx),
    xxx_ctor,
    xxx_dtor,
    xxx_clone,
    xxx_differ
};

const void* xxx = &_xxx;
```

```c
// xxx.h
#ifndef xxx_H
#define xxx_H

extern const void* xxx;

#endif
```

### new如何运作

```
       struct String                  struct Class
p --->       *            String --->    _String
```

```
       struct String                  struct Class
p --->       *         =  String --->    _String
```