// Java For Dummies, 7th Edition.pdf p.461
// Modified Andriy Zatserklyaniy <zatserkl@gmail.com> Aug 19, 2018

import static java.lang.System.out; // out.println -- System.out.println
import java.io.File;

class ListMyFiles {
    public static void main(String args[])
    {
        out.println("args.length = " + args.length);
        for (int i=0; i<args.length; ++i)
        {
            // // possible conversion of int to String
            // // see http://javadevnotes.com/java-integer-to-string-examples
            // out.println(Integer.toString(i) + "\t" + args[i]);
            // out.println(String.valueOf(i) + "\t" + args[i]);
            // out.println("" + i + "\t" + args[i]);

            // printf-like format
            out.println(String.format("%d\t%s", i, args[i]));
        }
        out.println();
        
        // String dirName = "/Users";
        // if (args.length > 0) dirName = args[0]; // use the first argument
        String dirName = args.length > 0? args[0]: ".";
        // out.println(String.format("dirName = %s", dirName));
        out.println("dirName = " + dirName);

        File myDir = new File(dirName);

        String dir[] = myDir.list();

        //
        // The problem: myDir correctly processes the Unix's root dir ("/"),
        // but myDir.getName() returns empty string.
        //
        // NB: Initialization of myDir with empty string
        // File myDir = new File("");
        //
        // raises java.lang.NullPointerException exception
        // in the methods exists(), isFile(), isDirectory(), etc.
        //

        out.println("myDir.getName().length() = " + myDir.getName().length());
        out.println("myDir.getName() = " + myDir.getName());
        out.println("myDir.exists() = " + myDir.exists());
        out.println("myDir.isFile = " + myDir.isFile());
        out.println("myDir.isDirectory = " + myDir.isDirectory());

        // out.println("\nContent of directory " + myDir.getName());
        out.println("\nContent of directory " +
                (myDir.getName().length() > 0? myDir.getName(): "/"));

        try {
            for (String fileName: dir) {
                out.println(fileName);
            }
        } catch(Exception e) {
            // possible NullPointerException in case of wrong dir name
            out.println("--> caught an exception:");
            System.err.println("e.getMessage: " + e.getMessage());
            out.println("e.printStackTrace():");
            e.printStackTrace();
        }
    }
}
