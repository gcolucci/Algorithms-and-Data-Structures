package datastructures.linkedlists.singlelinkedlists;

import datastructures.linkedlists.LinkedList;
import datastructures.linkedlists.Node;
import java.util.NoSuchElementException;

/**
 * A collection of ordered elements, as a Single Linked List data structure. It
 * provides the user with the basic operations to manipullate a single linked
 * list, such as adding and removing nodes and reversing the list.
 *
 * @author Guilherme Colucci
 * @param <T> The type of elements stored in the nodes of this list.
 */
public class SingleLinkedList<T> implements LinkedList<T> {

    private SingleLinkedListNode head;
    private int nElems;

    /**
     * Creates an empty single linked list.
     */
    public SingleLinkedList() {
        this.head = null;
        this.nElems = 0;
    }

    @Override
    public void addNodeToBeginning(Node<T> node) {
        // Custom message for attempts of adding null nodes.
        if (node == null) {
            throw new NullPointerException("Cannot add null node in the linked list.");
        }

        node.setNext(this.head);
        this.head = (SingleLinkedListNode<T>) node;
        this.nElems++;
    }

    @Override
    public void addNodeToEnd(Node<T> node) {
        // Custom message for attempts of adding null nodes.
        if (node == null) {
            throw new NullPointerException("Cannot add null node in the linked list.");
        }

        // Prevents the list structure from getting messed.
        node.setNext(null);

        SingleLinkedListNode p = this.head;

        if (p == null) {
            this.head = (SingleLinkedListNode) node;
        }
        else {
            // Searches the end of list
            while (p.getNext() != null) {
                p = p.getNext();
            }
            p.setNext(node);
        }

        this.nElems++;
    }

    @Override
    public void removeNode(T info) {
        // Throws exception if list is empty.       
        if (this.head == null) {
            throw new NullPointerException("Cannot remove node from empty linked list.");
        }

        // Special case: node to be deleted is the head.
        if (this.head.getInfo().equals(info)) {
            this.head = this.head.getNext();
            this.nElems--;
        } 
        else {
            // Searches for the provided value.
            SingleLinkedListNode p1 = null, p2 = this.head;
            while (p2 != null && !p2.getInfo().equals(info)) {
                p1 = p2;
                p2 = p2.getNext();
            }

            // Throws exception, if not found.
            if (p2 == null) {
                throw new NoSuchElementException(info + " is not in the linked list.");
            } //  Deletes the node, otherwise.
            else {
                // Safely adjust the pointers. p1 can never be null because it is predecessor of a non-null node in a list with at least two elements.
                p1.setNext(p2.getNext());
                this.nElems--;
            }
        }
    }

    /**
     * Reverses the order of the elements in the list. It changes the successor
     * pointer of each node to point to its original predecessor.
     */
    public void reverse() {
        // Special case: empty list
        if (this.head == null) {
            throw new NullPointerException("Cannot reverse an empty list.");
        }

        // If list contains only 1 node, there is nothing to do.
        if (this.head.getNext() != null) {
            SingleLinkedListNode pLeft, pMiddle, pRight;
            pLeft = pRight = null;
            pMiddle = this.head;

            // At each iteration, it reverses the pointer of the middle node.
            // All nodes appearing before the middle are already reversed.
            while (pMiddle != null) {
                // Advances the rightmost pointer. It must be done in the beginning
                // of the loop to avoid segmentation fault.
                pRight = pMiddle.getNext();

                // Reverses the middle pointer.
                pMiddle.setNext(pLeft);

                // Advances the other pointers.
                pLeft = pMiddle;
                pMiddle = pRight;
            }

            this.head = pLeft;
        }
    }

    @Override
    public String toString() {
        SingleLinkedListNode p = this.head;

        if (p == null) {
            return "null";
        }

        String output = "";
        while (p != null) {
            output += p.getInfo() + " -> ";
            p = p.getNext();
        }
        output += "-\n";

        return output;
    }

    @Override
    public Node<T> getHead() {
        return this.head;
    }

    @Override
    public int size() {
        return this.nElems;
    }
}