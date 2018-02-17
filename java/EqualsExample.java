/*
 * Java program to understand
 * the concept of == operator
 *
 * Output:
 * 
 * false        // for ==
 * true         // for equals
 */ 
public class EqualsExample {
    public static void main(String[] args)
    {
        /*
         * The operator == compares a memory location (= addresses, references).
         * The String method equals() compares the content (= state).
         */ 

        String method = "\nUse a String object\n";

        String s1 = new String("HELLO");
        String s2 = new String("HELLO");

        /*
        // Optional: call intern() method explicitly for String objects
        // the result will the same as for String literal (see below).
        s1 = s1.intern();
        s2 = s2.intern();
        method = "\nUse a String object, but call extern() explicitly\n";
        */
        
        System.out.println(method);

        System.out.println("s1 = " + s1 + " s2 = " + s2);
        System.out.println("s1 == s2: " + (s1 == s2));
        System.out.println("s1.equals(s2): " + s1.equals(s2));
        System.out.println("s1 == \"HELLO\": " + (s1 == "HELLO"));
        System.out.println("s1.equals(\"HELLO\"): " + s1.equals("HELLO"));

        method = "\nNow use a String literal\n";

        String s3 = "HELLO";
        String s4 = "HELLO";
        
        System.out.println(method);

        System.out.println("s3 = " + s3 + " s4 = " + s4);
        System.out.println("s3 == s4: " + (s3 == s4));
        System.out.println("s3.equals(s4): " + s3.equals(s4));
        System.out.println("s3 == \"HELLO\": " + (s3 == "HELLO"));
        System.out.println("s3.equals(\"HELLO\"): " + s3.equals("HELLO"));
    }
}
