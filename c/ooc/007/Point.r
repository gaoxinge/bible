struct Point {
    const void* class;
    int x, y;
};

#define x(p)        (((const struct Point*)(p)) -> x)
#define y(p)        (((const struct Point*)(p)) -> y)
#define set_x(p, v) (((struct Point*)(p)) -> x = (v))
#define set_y(p, v) (((struct Point*)(p)) -> y = (v))