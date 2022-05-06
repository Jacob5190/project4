// C file that implements a circular doubly-linked list of generic pointer types.
#include "stdio.h"
#include "assert.h"
#include "malloc.h"
#include "stdbool.h"
#include "list.h"

struct list {
	int count;
	struct node *head;
	int (*compare)();
};
typedef struct list LIST;

struct node {
	void *data;
	struct node *next;
	struct node *prev;
};
typedef struct node NODE;

static void *search (LIST *lp, void *item, bool *flag) {
	assert(lp != NULL);
	assert(lp->compare != NULL);
	NODE *node = lp->head->next;
	*flag = false;
	while (node != lp->head) {
		if (lp->compare(item, node->data) == 0) {
			*flag = true;
			return node;
		}
		node = node->next;
	}
	return node;
}

LIST *createList(int (*compare)()) {
	printf("Create List\n");
	struct list *lp;
	lp = malloc(sizeof(struct list));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(struct node));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}

void destroyList(LIST *lp) {
	assert(lp != NULL);
	NODE *pDel = lp->head->prev;
	NODE *pPrev;
	while (pDel != lp->head) {
		pPrev = pDel->prev;
		free(pDel);
		pDel = pPrev;
	}
	free(pDel);
	free(lp);
}

int numItems(LIST *lp) {
	return lp->count;
}

void addFirst(LIST *lp, void *item) {
	assert(lp != NULL);
	assert(item != NULL);
	NODE *oldNode = lp->head->next;
	NODE *newNode = malloc(sizeof(struct node));
	newNode->data = item;
	newNode->prev = lp->head;
	newNode->next = oldNode;
	oldNode->prev = newNode;
	lp->count++;
}

void addLast(LIST *lp, void *item) {
	assert(lp != NULL);
	assert(item != NULL);
	NODE *oldNode = lp->head->prev;
	NODE *newNode = malloc(sizeof(struct node));
	newNode->data = item;
	newNode->next = lp->head;
	newNode->prev = oldNode;
	oldNode->next = newNode;
	lp->count++;
}

void *removeFirst(LIST *lp) {
	assert(lp != NULL);
	assert(lp->head != lp->head->next);
	NODE *delNode = lp->head->next;
	NODE *newFirstNode = delNode->next;
	lp->head->next = newFirstNode;
	newFirstNode->prev = lp->head;
	lp->count--;
	return delNode;
}

void *removeLast(LIST *lp) {
	assert(lp!= NULL);
	assert(lp->head != lp->head->prev);
	NODE *delNode = lp->head->prev;
	NODE *newLastNode = delNode->prev;
	lp->head->prev = newLastNode;
	newLastNode->next = lp->head;
	lp->count--;
	return delNode;
}

void *getFirst(LIST *lp) {
	assert(lp != NULL);
	assert(lp->head != lp->head->next);
	NODE *firstNode = lp->head->next;
	return firstNode;
}

void *getLast(LIST *lp) {
	assert(lp != NULL);
	assert(lp->head != lp->head->prev);
	NODE *lastNode = lp->head->prev;
	return lastNode;
}

void removeItem(LIST *lp, void *item) {
	bool flag;
	NODE *node = search(lp, item, &flag);
	if (!flag) {
		return;
	}
	NODE *prevNode = node->prev;
	NODE *nextNode = node->next;
	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	lp->count--;
	free(node);
}

void *findItem(LIST *lp, void *item) {
	bool flag;
	NODE *node = search(lp, item, &flag);
	if (!flag) {
		return NULL;
	}
	return node;
}

void *getItems(LIST *lp) {
	assert(lp != NULL);
	assert(lp->head != lp->head->next);
	int i = 0;
	void **items;
	items = malloc(lp->count * sizeof(void*));
	NODE *node = lp->head->next;
	while (node != lp->head) {
		items[i] = node->data;
		node = node->next;
		i++;
	}
	return items;
}
