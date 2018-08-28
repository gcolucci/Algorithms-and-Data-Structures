package datastructures.linkedlists;

/**
 * A collection of ordered elements, as a Linked List data structure. It provides the user with the basic operations to manipullate a linked list, such as adding and removing nodes.
 * @author Guilherme Colucci
 * @param <T> The type of elements stored in the nodes of this list.
 */
public interface LinkedList<T> {
    /**
     * Adds a node to the beginning of the linked list.
     * @param node The node to be added.
     */
    public void addNodeToBeginning(Node<T> node);

    /**
     * Adds a node to the end of the linked list.
     * @param node The node to be added.
     */
    public void addNodeToEnd(Node<T> node);
    
    /**
     * Removes a node containing the info passed by parameter. It does not receive the node to be removed as parameter, but an info value the same type as those stored by the nodes. In case there is more than one node with the same info, it removes the first occurence in the list.
     * @param info The info held by the node to be removed.
     */
    public void removeNode(T info);

    /**
     * Returns the list head.
     * @return the head node of the list.
     */
    public Node<T> getHead();
    
    /**
     * Returns the number of elements in the list.
     * @return the number of elements in the list.
     */
    public int size();
}
