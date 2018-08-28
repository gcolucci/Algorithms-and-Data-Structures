package datastructures.linkedlists;

import datastructures.linkedlists.singlelinkedlists.SingleLinkedListNode;

/**
 * An element of a Linked List data structure. It stores an info, which value the user can retrieve and update.
 * @author Guilherme Colucci
 * @param <T> The type of elements stored in the nodes.
 */
public interface Node<T> {
    /**
     * Retrieves the info stored by the node.
     * @return the info stored in the node.
     */
    public T getInfo();

    /**
     * Updates the info stored by the node.
     * @param info The info stored in the node.
     */
    public void setInfo(T info);
    
       /**
     * Updates the node successor.
     * @param next The node to be successor.
     */    
    public void setNext(Node<T> next);
    
    /**
     * Retrieves the node successor.
     * @return the node successor.
     */    
    public SingleLinkedListNode<T> getNext();
}