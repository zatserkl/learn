/**
A simple example to read a text file.
 */

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileNotFoundException;	// just an example

/**
 * Example of how to read file using FileReader.
 */
public class FileReaderExample
{
    public static void main(String [] args) {

        final String fileName;
        if (args.length > 0) fileName = args[0];
        else fileName = FileReaderExample.class.getSimpleName() + ".java"; // "FileReaderExapmple.java"

        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = new BufferedReader(fileReader);

            String line;
            while((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }   

            // Always close files.
            bufferedReader.close();         
        }
        catch(FileNotFoundException ex) {
            System.out.println("Unable to open file '" + fileName + "'");                
        }
        catch(IOException ex) {
            System.out.println("Error reading file '" + fileName + "'");                  
            // ex.printStackTrace();    // possible alternative
        }
    }
}
