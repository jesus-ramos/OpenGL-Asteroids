#ifndef LIST_H
#define LIST_H

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

inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    _list_add(new, head->prev, head);
}

inline void list_del(struct list_head *entry)
{
    struct list_head *prev;
    struct list_head *next;

    prev = entry->prev;
    next = entry->next;

    next->prev = prev;
    prev->next = next;
}

inline void init_list_head(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

#endif /* LIST_H */
