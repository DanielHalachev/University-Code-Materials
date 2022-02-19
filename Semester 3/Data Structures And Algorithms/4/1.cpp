https://www.hackerrank.com/contests/sda-hw-4/challenges/insert-a-node-at-a-specific-position-in-a-linked-list

/*
 * Complete the 'insertNodeAtPosition' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER data
 *  3. INTEGER position
 */

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
     SinglyLinkedListNode *head = llist;
    for (int i = 1; i < position; i++) {
        if (llist->next == nullptr) {
            throw std::out_of_range("Wrong position");
        }
        llist=llist->next;
    }
    SinglyLinkedListNode *temp = new SinglyLinkedListNode(data);
    temp->next = llist->next;
    llist->next = temp;
    return head;
}
