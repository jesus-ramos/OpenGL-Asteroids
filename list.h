#ifndef _LIST_H
#define _LIST_H

/*
 * List implementation based on the linked list implementation within
 * the Linux Kernel. This is a stripped down version that contains
 * only what I really needed
 */

#include <stddef.h>

struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};

static inline void _list_add(struct list_head *new,
                             struct list_head *prev,
                             struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    _list_add(new, head->prev, head);
}

static inline void list_del(struct list_head *entry)
{
    struct list_head *prev;
    struct list_head *next;

    prev = entry->prev;
    next = entry->next;

    next->prev = prev;
    prev->next = next;
}

static inline void init_list_head(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

/* Good luck understanding any code beyond this point */
#define container_of(ptr, type, member)                         \
    ({                                                          \
        const typeof(((type *)0)->member) *__mptr = (ptr);      \
        (type *)((char *)__mptr - offsetof(type, member));      \
    })

#define list_entry(ptr, type, member)           \
    container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member)                          \
    for (pos = list_entry((head)->next, typeof(*pos), member);          \
         &pos->member != (head);                                        \
         pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member)			\
    for (pos = list_entry((head)->next, typeof(*pos), member),          \
             n = list_entry(pos->member.next, typeof(*pos), member);	\
         &pos->member != (head); 					\
         pos = n, n = list_entry(n->member.next, typeof(*n), member))

#endif /* _LIST_H */
