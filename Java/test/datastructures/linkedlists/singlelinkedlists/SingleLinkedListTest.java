package datastructures.linkedlists.singlelinkedlists;

import java.util.NoSuchElementException;
import static org.junit.Assert.assertEquals;
import org.junit.Test;

/** Unit tests for SingleLinkedList class.
 *
 * @author Guilherme Colucci
 */
public class SingleLinkedListTest {
    // ----------------------------------------------------------------- //
    // --------------------------  EMPTY LIST -------------------------- //
    // ----------------------------------------------------------------- //
        
    // --------------------------- //
    //  Add null node to beginning //
    // --------------------------- //
    
    /**
     * Test of addNodeToBeginning method, of class SingleLinkedList. It tries to insert a null node in the beginning of an empty list.
     */
    @Test(expected=NullPointerException.class)
    public void testAddNullNodeToBeginningOfEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        
        list.addNodeToBeginning(null);
        assertEquals(list.size(), 0);
    }

    // ---------------------------- //
    //  Add valid node to beginning //
    // ---------------------------- //
    
    /**
     * Test of addNodeToBeginning method, of class SingleLinkedList. It tries to insert a new node in the beginning of an empty list.
     */
    @Test
    public void testAddNodeToBeginningOfEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node = new SingleLinkedListNode(3);
        
        list.addNodeToBeginning(node);
        
        assertEquals(list.getHead(), node);
        assertEquals(list.size(), 1);
    }

    // --------------------- //
    //  Add null node to end //
    // --------------------- //

    /**
     * Test of addNodeToEnd method, of class SingleLinkedList. It tries to insert a null node in the end of an empty list.
     */
    @Test(expected=NullPointerException.class)
    public void testAddNullNodeToEndOfList() {        
        SingleLinkedList list = new SingleLinkedList();
        
        list.addNodeToEnd(null);
        assertEquals(list.size(), 0);
    }

    // ---------------------- //
    //  Add valid node to end //
    // ---------------------- //
    
    /**
     * Test of addNodeToEnd method, of class SingleLinkedList. It tries to insert a new node in the end of an empty list.
     */
    @Test
    public void testAddNodeToEndOfEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node = new SingleLinkedListNode(3);
        
        list.addNodeToEnd(node);
        
        assertEquals(list.getHead(), node);
        assertEquals(list.size(), 1);
    }

    // ---------------- //
    //  Remove any node //
    // ---------------- //
    
    /**
     * Test of removeNode method, of class SingleLinkedList. It tries to remove a node of an empty list.
     */
    @Test(expected=NullPointerException.class)
    public void removeNodeOfEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        
        list.removeNode(3);
        
        assertEquals(list.size(), 0);
    }

    // ------------- //
    //  Reverse list //
    // ------------- //

    /**
     * Test of reverse method, of class SingleLinkedList. It tries to reverse an empty list.
     */
    @Test(expected=NullPointerException.class)
    public void testReverseEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        
        list.reverse();
    }
    
    /**
     * Test of toString method, of class SingleLinkedList. It tries to generate a string representing an empty list.
     */
    @Test
    public void testToStringOfEmptyList() {
        SingleLinkedList list = new SingleLinkedList();

        assertEquals(list.toString(), "null");
    }    


    // --------------------------------------------------------------------- //
    // --------------------------  NON-EMPTY LIST -------------------------- //
    // --------------------------------------------------------------------- //
    
    // --------------------------- //
    //  Add null node to beginning //
    // --------------------------- //

    /**
     * Test of addNodeToBeginning method, of class SingleLinkedList. It tries to insert a null node in the beginning of a non-empty list.
     */
    @Test(expected=NullPointerException.class)
    public void testAddNullNodeToBeginningOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node = new SingleLinkedListNode(3);
        
        list.addNodeToBeginning(node);
        list.addNodeToBeginning(null);

        assertEquals(list.size(), 1);
        assertEquals(list.getHead(), node);
    }

    // ---------------------------- //
    //  Add valid node to beginning //
    // ---------------------------- //

    /**
     * Test of addNodeToBeginning method, of class SingleLinkedList. It tries to insert a new node in the beginning of a non-empty list.
     */
    @Test
    public void testAddNodeToBeginningOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        
        SingleLinkedListNode node1 = new SingleLinkedListNode(3);
        SingleLinkedListNode node2 = new SingleLinkedListNode(4);
        list.addNodeToBeginning(node2);
        list.addNodeToBeginning(node1);
        
        // Expected list: 3 -> 4
        
        SingleLinkedListNode listHead = (SingleLinkedListNode) list.getHead();
        assertEquals(listHead, node1);
        assertEquals(listHead.getNext(), node2);
        assertEquals(list.size(), 2);
    }

    // --------------------- //
    //  Add null node to end //
    // --------------------- //

    /**
     * Test of addNodeToEnd method, of class SingleLinkedList. It tries to insert a null node in the end of a non-empty list.
     */
    @Test(expected=NullPointerException.class)
    public void testAddNullNodeToEndOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node = new SingleLinkedListNode(3);
        
        list.addNodeToEnd(node);
        list.addNodeToEnd(null);

        assertEquals(list.size(), 1);
        assertEquals(list.getHead(), node);
    }

    // ---------------------- //
    //  Add valid node to end //
    // ---------------------- //

    /**
     * Test of addNodeToEnd method, of class SingleLinkedList. It tries to insert a new node in the end of a non-empty list.
     */
    @Test
    public void testAddNodeToEndOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        
        SingleLinkedListNode node1 = new SingleLinkedListNode(3);
        SingleLinkedListNode node2 = new SingleLinkedListNode(4);
        list.addNodeToEnd(node1);
        list.addNodeToEnd(node2);
        
        // Expected list: 3 -> 4
        
        SingleLinkedListNode listHead = (SingleLinkedListNode) list.getHead();
        assertEquals(listHead, node1);
        assertEquals(listHead.getNext(), node2);
        assertEquals(list.size(), 2);
    }

    // ------------------------------------ //
    //  Remove existing node from beginning //
    // ------------------------------------ //
    
    /**
     * Test of removeNode method, of class SingleLinkedList. It tries to remove an existing node of a non-empty list.
     */
    @Test
    public void removeExistingNodeFromBeginningOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node1 = new SingleLinkedListNode(3);
        SingleLinkedListNode node2 = new SingleLinkedListNode(4);
        SingleLinkedListNode node3 = new SingleLinkedListNode(5);        
        
        list.addNodeToEnd(node1);
        list.addNodeToEnd(node2);
        list.addNodeToEnd(node3);
        
        list.removeNode(3);
        
        assertEquals(list.getHead(), node2);
        assertEquals(list.getHead().getNext(), node3);
        assertEquals(list.size(), 2);
    }

    // --------------------------------- //
    //  Remove existing node from middle //
    // --------------------------------- //
    
    /**
     * Test of removeNode method, of class SingleLinkedList. It tries to remove an existing node of a non-empty list.
     */
    @Test
    public void removeExistingNodeFromMiddleOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node1 = new SingleLinkedListNode(3);
        SingleLinkedListNode node2 = new SingleLinkedListNode(4);
        SingleLinkedListNode node3 = new SingleLinkedListNode(5);        
        
        list.addNodeToEnd(node1);
        list.addNodeToEnd(node2);
        list.addNodeToEnd(node3);

        list.removeNode(4);
        
        assertEquals(list.getHead(), node1);
        assertEquals(list.getHead().getNext(), node3);
        assertEquals(list.size(), 2);
    }

    // ------------------------------ //
    //  Remove existing node from end //
    // ------------------------------ //
    
    /**
     * Test of removeNode method, of class SingleLinkedList. It tries to remove an existing node of a non-empty list.
     */
    @Test
    public void removeExistingNodeFromEndOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node1 = new SingleLinkedListNode(3);
        SingleLinkedListNode node2 = new SingleLinkedListNode(4);
        SingleLinkedListNode node3 = new SingleLinkedListNode(5);        
        
        list.addNodeToEnd(node1);
        list.addNodeToEnd(node2);
        list.addNodeToEnd(node3);

        list.removeNode(5);
        
        assertEquals(list.getHead(), node1);
        assertEquals(list.getHead().getNext(), node2);
        assertEquals(list.size(), 2);
    }

    // ------------------------- //
    //  Remove non-existing node //
    // ------------------------- //

    /**
     * Test of removeNode method, of class SingleLinkedList. It tries to remove a non-existing node of a non-empty list.
     */
    @Test(expected=NoSuchElementException.class)
    public void removeNonExistingNodeOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node = new SingleLinkedListNode(3);
        
        list.addNodeToBeginning(node);
        
        list.removeNode(5);
        
        assertEquals(list.getHead(), node);
        assertEquals(list.size(), 1);
    }

    // ---------------------------- //
    //  Reverse single-element list //
    // ---------------------------- //

    /**
     * Test of reverse method, of class SingleLinkedList. It tries to reverse a list containing just 1 element.
     */
    @Test
    public void testReverseListWithOneElement() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node = new SingleLinkedListNode(3);
        
        list.addNodeToBeginning(node);
        
        list.reverse();

        assertEquals(list.getHead(), node);
        assertEquals(list.getHead().getNext(), null);
        assertEquals(list.size(), 1);
    }

    // -------------------------------- //
    //  Reverse list of size at least 2 //
    // -------------------------------- //

    /**
     * Test of reverse method, of class SingleLinkedList. It tries to reverse a list containing at least 2 elements.
     */
    @Test
    public void testReverseListWithAtLeastTwoElements() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node1 = new SingleLinkedListNode(3);
        SingleLinkedListNode node2 = new SingleLinkedListNode(4);
        
        list.addNodeToEnd(node1);
        list.addNodeToEnd(node2);
        
        list.reverse();

        // Expected list: 4 -> 3

        assertEquals(list.getHead(), node2);
        assertEquals(list.getHead().getNext(), node1);
        assertEquals(list.getHead().getNext().getNext(), null);
        assertEquals(list.size(), 2);
    }

    /**
     * Test of toString method, of class SingleLinkedList. It tries to generate a string representing a non-empty list.
     */
    @Test
    public void testToStringOfNonEmptyList() {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode node1 = new SingleLinkedListNode(3);
        SingleLinkedListNode node2 = new SingleLinkedListNode(4);
        SingleLinkedListNode node3 = new SingleLinkedListNode(5);        
        
        list.addNodeToEnd(node1);
        list.addNodeToEnd(node2);
        list.addNodeToEnd(node3);
        
        assertEquals(list.toString(), "3 -> 4 -> 5 -> -\n");
    }    
}