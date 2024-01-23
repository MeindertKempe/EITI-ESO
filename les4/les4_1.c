#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 25

typedef struct node {
	int val;
	struct node *next;
} node_t;

void print_list(node_t *head) {
	/* Traverse list, printing each value */
	while (head) {
		printf("%d\n", head->val);
		head = head->next;
	}
}

/* Initialisation function to prevent caller from allocating the list on the
 * stack. (If we want to allow this we need to avoid freeing it in the list_free
 * function, however this would give the caller the responsibility of freeing
 * the head node.) */
node_t *list_init(int val) {
	node_t *list = calloc(1, sizeof *list);
	/* In case of allocation failure exit, not very graceful, however this is
	 * most likely caused by a lack of available memory, in which case there is
	 * little that can be done. */
	if (!list) exit(EXIT_FAILURE);
	list->val = val;
	return list;
}

void add_node(node_t *head, int val) {
	/* Traverse until the end of the list. */
	while (head->next) head = head->next;
	node_t *new = calloc(1, sizeof *new);
	/* Exit in case of allocation failure. */
	if (!new) exit(EXIT_FAILURE);
	new->val   = val;
	head->next = new;
}

void list_free(node_t *head) {
	/* Traverse list, saving the next node, then freeing the current one. */
	while (head) {
		node_t *next = head->next;
		free(head);
		head = next;
	}
}

int main(void) {
	/* Initialise and fill list with pseudo random numbers */
	node_t *test_list = list_init(rand());
	for (int i = 0; i < LIST_SIZE - 1; ++i) add_node(test_list, rand());

	/* Print list. */
	print_list(test_list);

	/* Free list. */
	list_free(test_list);

	return EXIT_SUCCESS;
}
