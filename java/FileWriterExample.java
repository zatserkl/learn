/**
A simple class to write a text file.
Based on http://www.homeandlearn.co.uk/java/write_to_textfile.html

Audit with checkstyle:
java$ java -jar checkstyle*.jar -c google_checks_indent4.xml FileWriterExample.java
 */

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * FileWriterExample uses simple way to write down the simple text file.
 */ 
public class FileWriterExample {
    String pathname;
    PrintWriter printer;

    /**
     * FileWriter constructor.
     * @param           fname           the name of output file
     * @exception       IOException
     */
    public FileWriterExample(String fname) throws IOException {
        pathname = fname;
        // open the file here (this operation may throw IOException)
        FileWriter fileWriter = new FileWriter(pathname);
        printer = new PrintWriter(fileWriter);
    }

    /**
     * Closes output file.
     */
    public void close() {
        if (printer != null) {
            printer.close();
        }
    }
    
    /** 
     * Returns the PrintWriter object.
     */ 
    public PrintWriter getPrinter() {
        return printer;
    }

    /**
     * main function.
     */
    public static void main(String[] args) {
        String fname = "FileWriterExample.txt";
        
        FileWriterExample fileWriterExample;

        try {
            fileWriterExample = new FileWriterExample(fname);
        } catch (IOException e) {
            System.out.println("Cannot open output file " + e);
            return;
        }

        fileWriterExample.getPrinter().printf("This is the line %d\n", 1);
        fileWriterExample.getPrinter().printf("This is the line %d\n", 2);

        double val = 3.14159;
        fileWriterExample.getPrinter().printf("pi = %.2f\n", val);

        fileWriterExample.close();
    }
}
