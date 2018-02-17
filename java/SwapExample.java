public class SwapExample {
    public void swap(int a, int b)
    {
        // NB: this code does not work in java
        // because the parameters are pass by value
        // and there is no references to basic types in java.
        // -- No pointers in Java.

        int buf = a;
        a = b;
        b = buf;
    }
    public static void main(String[] args)
    {
        //--TODO System.out.println("Hello from " + java.awt.SwapExample);

        SwapExample swapExample = new SwapExample();

        int a = 5;
        int b = 7;
        System.out.println("Before: a = " + a + " b = " + b);
        swapExample.swap(a, b);
        System.out.println("After:  a = " + a + " b = " + b);
    }
}
