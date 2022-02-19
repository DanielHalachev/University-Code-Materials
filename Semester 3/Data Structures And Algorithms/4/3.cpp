https://www.hackerrank.com/contests/sda-hw-4/challenges/delete-a-node-from-a-linked-list

/*
 * Complete the 'deleteNode' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER position
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

SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position) {
    if(position==0){
        SinglyLinkedListNode* temp=llist->next;
        delete llist;
        return temp;
    }
    SinglyLinkedListNode *temp = llist;
    for (int i = 0; i < position - 1; i++) {
        temp = temp->next;
    }
    SinglyLinkedListNode *newStart = temp->next->next;
    delete temp->next;
    temp->next = newStart;
    return llist;
}
