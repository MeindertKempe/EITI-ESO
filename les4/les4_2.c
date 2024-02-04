#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node_t;

void print_list(node_t *head) {
	/* Traverse list, printing each value */
	while (head) {
		printf("%d (%x)\n", head->val, head->val);
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

/* We give a pointer to a pointer so that we can modify the value of the
 * pointer for the caller when freeing the head node.   */
int pop(node_t **head) {
	int retval;
	node_t *next_node;
	/* Making -1 an error seems a bit questionable here, since it would prevent
	 * you from returning -1 as a value or create ambiguity. */
	if (!*head) return -1;
	next_node = (*head)->next;
	retval    = (*head)->val;
	free(*head);
	/* Set head to next node. */
	*head = next_node;
	return retval;
}

int remove_by_value(node_t **head, int val) {
	/* Iterate over list use pop function when we find the value. */
	while (*head) {
		if ((*head)->val == val) return pop(head);
		head = &(*head)->next;
	}
	return -1;
}

int main(void) {
	/* Initialise and fill list with pseudo random numbers. */
	node_t *test_list = list_init(rand());
	for (int i = 0; i < 3; ++i) add_node(test_list, rand());
	add_node(test_list, 0xDEADBEEF);
	for (int i = 0; i < 3; ++i) add_node(test_list, rand());

	/* Print list. */
	print_list(test_list);

	/* Remove value from list. */
	remove_by_value(&test_list, 0xDEADBEEF);
	printf("\n");

	/* Print list. */
	print_list(test_list);

	/* Free list. */
	list_free(test_list);

	return EXIT_SUCCESS;
}
