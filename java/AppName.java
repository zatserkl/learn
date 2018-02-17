/*
javac AppName.java
java AppName
*/

import java.util.Properties;
 
public class AppName
{
    public static void main(String args[])
    {
        Properties p = System.getProperties();
         
        p.list(System.out);

        System.out.println("\nIn the above list:");
        System.out.println("System.getProperty(\"user.dir\") = " + System.getProperty("user.dir"));
        System.out.println("System.getProperty(\"sun.java.command\") = " + System.getProperty("sun.java.command"));
    }
}
