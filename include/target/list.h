/* SPDX-License-Identifier: GPL-2.0 */
#ifndef LIST_H
#define LIST_H


#ifndef __ASSEMBLY__

/*
 * Macro based list_head, functioning similar as what is provided in
 * many other OSen.
 */
/*
 * Copied from include/linux/...
 */


/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                      \
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - offsetof(type,member) );})


struct list_head {
	struct list_head *next, *prev;
};


#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name)	\
	struct list_head name = LIST_HEAD_INIT(name)


static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}


#define list_first_entry(head, type, member) \
		((head)->next == (head)) ? NULL : list_entry((head)->next, type, member)

#define list_last_entry(head, type, member) \
		((head)->prev == (head)) ? NULL : list_entry((head)->prev, type, member)


/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *_new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = _new;
	_new->next = next;
	_new->prev = prev;
	prev->next = _new;
}

/**
 * list_add - add a new entry
 * @entry: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
#define list_add(entry, head)					\
	do {							\
		(head)->next->prev = entry;			\
		(entry)->next = (head)->next;			\
		(entry)->prev = head; (head)->next = entry;	\
	} while (0)

/**
 * list_add_tail - add a new entry
 * @entry: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
#define list_add_tail(entry, head)				\
	do {							\
		(head)->prev->next = entry;			\
		(entry)->prev = (head)->prev;			\
		(head)->prev = entry; (entry)->next = head;	\
	} while (0)

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
#define __list_del(node, entry)					\
	do {							\
		(entry)->prev = node; (node)->next = entry;	\
	} while (0)

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)
/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this,
 * the entry is in an undefined state.
 */
#define list_del(entry)						\
	do {							\
		(entry)->next->prev = (entry)->prev;		\
		(entry)->prev->next = (entry)->next;		\
		(entry)->next = LIST_POISON1;			\
		(entry)->prev = LIST_POISON2;			\
	} while (0)

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
#define list_del_init(entry)					\
	do {							\
		(entry)->next->prev = (entry)->prev;		\
		(entry)->prev->next = (entry)->next;		\
		INIT_LIST_HEAD(entry);				\
	} while (0)

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
#define list_move(list, head)					\
	do {							\
		struct list_head * tmp = list;			\
		__list_del((list)->prev, (list)->next);	\
		list_insert_head(tmp, head);			\
	} while (0)

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
#define list_move_tail(list, head)				\
	do {							\
		struct list_head * tmp = list;			\
		__list_del((list)->prev, (list)->next);	\
		list_insert_tail(tmp, head);			\
	} while (0)


/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
#define list_is_last(list, head)				\
	((list)->next == (head))

/**
 * list_is_first - tests whether @list is the first entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
#define list_is_first(list, head)				\
	((list)->prev == (head))

/**
 * list_splice - join two lists
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
#define list_splice(list, head)					\
	do {							\
		if (!list_empty(list)) {			\
			struct list_head *first = (list)->next;	\
			struct list_head *last = (list)->prev;	\
			struct list_head *at = (head)->next;	\
			first->prev = head;			\
			(head)->next = first;			\
			last->next = at; at->prev = last;	\
		}						\
	} while (0)

/**
 * list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
#define list_splice_init(list, head)				\
	do {							\
		if (!list_empty(list)) {			\
			struct list_head *first = (list)->next;	\
			struct list_head *last = (list)->prev;	\
			struct list_head *at = (head)->next;	\
			first->prev = head;			\
			(head)->next = first;			\
			last->next = at; at->prev = last;	\
			list_init(list);			\
		}						\
	} while (0)

/**
 * list_entry - get the struct for this entry
 * @node: the &list pointer.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define list_entry(node, type, member)				\
	((type *)((char *)(node) - (size_t)&((type *)0)->member))

/**
 * list_first_entry - get the first element from a list
 * @head:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(head, type, member) \
	((head)->next == (head)) ? NULL : list_entry((head)->next, type, member)

/**
 * list_last_entry - get the last element from a list
 * @head:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_last_entry(head, type, member) \
	((head)->prev == (head)) ? NULL : list_entry((head)->prev, type, member)

/**
 * list_iterate_forward	- iterate over a list safe against removal of list entry
 * @pos: the &list to use as a loop counter.
 * @n: another &list to use as temporary storage
 * @head: the head for your list.
 */
#define list_iterate_forward(pos, n, head)			\
	for (pos = (head)->next, n = pos->next;			\
		pos != (head); pos = n, n = pos->next)

/**
 * list_iterate_backward - iterate over a list safe against removal of list entry
 * @pos: the &list to use as a loop counter.
 * @n: another &list to use as temporary storage
 * @head: the head for your list.
 */
#define list_iterate_backward(pos, n, head)			\
	for (pos = (head)->prev, n = pos->prev;			\
		pos != (head); pos = n, n = pos->prev)


#ifdef NDEBUG
/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry(type, pos, head, member)		\
	for (pos = list_entry((head)->next, type, member);	\
	     &pos->member != (head); 				\
	     pos = list_entry(pos->member.next, type, member))

#else
/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry(type, pos, head, member)		\
	for (pos = ((head) == (head)->next ? NULL :		\
	     list_entry((head)->next, type, member));		\
	     pos && &pos->member != (head); 			\
	     pos = ((head) == pos->member.next ? NULL :		\
	     list_entry(pos->member.next, type, member)))

#endif

/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry_2(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))


/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

#define list_insert_before(entry, the_head)			\
	list_add_tail(entry, the_head)
#define list_insert_after(entry, the_head)			\
	list_add(entry, the_head)
#define list_insert_tail(entry, the_head)			\
	list_add_tail(entry, the_head)
#define list_insert_head(entry, the_head)			\
	list_add(entry, the_head)
#define list_move_head(list, head)				\
	list_move(list, head)

#endif /* __ASSEMBLY__ */

#endif /* __LIST_H_INCLUDE__ */
