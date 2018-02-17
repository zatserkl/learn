// From http://www.geeksforgeeks.org/java-and-multiple-inheritance/
//
// See there different cases, including diamond inheritance.
//

/**
 * Java does not support multiple inheritance with classes,
 * but Java 8 supports default methods where interfaces can provide
 * default implementation of the methods
 */

// A simple Java program to demonstrate multiple
// inheritance through default methods.
interface PI1
{
    // default method
    default void show() // AZ: both declaration and implementation for default method
    {
        System.out.println("Default PI1");
    }
}
 
interface PI2
{
    // default method
    default void show()
    {
        System.out.println("Default PI2");
    }
}
 
// Implementation class code
class MultipleInheritanceIssue implements PI1, PI2
{
    // Overriding default show method
    public void show()
    {
        // use super keyword to call the show
        // method of PI1 interface
        PI1.super.show();
 
        // use super keyword to call the show
        // method of PI2 interface
        PI2.super.show();
    }
 
    public static void main(String args[])
    {
        MultipleInheritanceIssue d = new MultipleInheritanceIssue();
        d.show();
    }
}
