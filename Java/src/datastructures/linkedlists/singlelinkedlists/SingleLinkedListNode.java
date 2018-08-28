package datastructures.linkedlists.singlelinkedlists;

import datastructures.linkedlists.Node;

/**
 * An element of a Single Linked List data structure. It stores an info, which value the user can retrieve and update, and a pointer to the node successor.
 * @author Guilherme Colucci
 * @param <T> The type of elements stored in the nodes.
 */
public class SingleLinkedListNode<T> implements Node<T> {
    private T info; // The info stored in the node.
    private SingleLinkedListNode<T> next; // A pointer to the successor node.
    
    /**
     * Constructs a node storing an initial value. It sets the successor to null.
     * @param info the info to be stored in the node.
     */    
    public SingleLinkedListNode(T info) {
        this.info = info;
        this.next = null;
    }
    
    @Override
    public T getInfo() {
        return this.info;
    }

    @Override
    public void setInfo(Object info) {
        this.info = (T) info;
    }

    @Override
    public void setNext(Node<T> next) {
        this.next = (SingleLinkedListNode<T>) next;
    }

    @Override
    public SingleLinkedListNode<T> getNext() {
        return this.next;
    }
}