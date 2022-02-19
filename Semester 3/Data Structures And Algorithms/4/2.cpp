https://www.hackerrank.com/contests/sda-hw-4/challenges/find-the-merge-point-of-two-joined-linked-lists

// Complete the findMergeNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    SinglyLinkedListNode *temp1 = head1;
    SinglyLinkedListNode *temp2 = head2;
    while (temp1 != temp2) {        
        temp1=(temp1)?temp1->next:head1;
        temp2=(temp2)?temp2->next:head2;
    }
    if (temp1) {
        return temp1->data;
    }
    return temp2->data;
}
