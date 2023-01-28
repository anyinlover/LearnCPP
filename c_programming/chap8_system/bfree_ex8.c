#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#define NALLOC 1024

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
void *mymalloc(unsigned nbytes);
static Header *morecore(unsigned nu);
void myfree(void *ap);
void *bfree(void *p, size_t n);

int main()
{
    static char a[3] = {'a','b','c'};
    bfree(a, 3);
    return 0;
}

void *mymalloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    if (nbytes == 0 || nbytes > UINT_MAX - sizeof(Header)) {
        fprintf(stderr, "Error: invalid nbytes size request %d\n", nbytes);
    }
    nunits = (nbytes + sizeof(Header) - 1) /sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;;prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    myfree((void *)(up + 1));
    return freep;
}

void myfree(void *ap)
{
    if (ap == NULL) {
        fprintf(stderr, "Error: null pointer passed to myfree.\n");
        return;
    }
    Header *bp, *p;

    bp = (Header *)ap - 1;
    if (bp->s.size == 0) {
        fprintf(stderr, "Error: can't free size 0.\n");
        return;
    }

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

void *bfree(void *p, size_t n)
{
    if (n < sizeof(Header))
        return NULL;
    Header *bp = (Header *)p;
    bp->s.size = n / sizeof(Header);
    myfree(bp + 1);
}