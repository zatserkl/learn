// import java.io.*;
import java.io.File;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

import java.io.IOException;             // to use throws IOException instead of throws java.io.IOException
import java.io.FileNotFoundException;   // to use throws FileNotFoundException instead of throws java.io.FileNotFoundException

public class ReadWriteFileExample
{
    public final String fname;
    //-- public String fname;

    public ReadWriteFileExample(String fname) {
        this.fname = fname;
        System.out.println("constructor ReadWriteFileExample: this.fname = " + this.fname);
    }

    public void readFile() throws FileNotFoundException, IOException    // catch them in caller
    {
        BufferedReader bufferedReader = null;

        ///////////////////////////////////////////////////////////////////////////////////////
        //
        //  You may try/catch the exceptions instead of throwing them (in function declaration)
        //
        ///////////////////////////////////////////////////////////////////////////////////////

        /// try {
        ///     bufferedReader = new BufferedReader(new FileReader(fname)); 
        ///     String line;
        ///     while ((line = bufferedReader.readLine()) != null) {
        ///         System.out.println(line);
        ///     }
        /// }
        /// catch (FileNotFoundException e) {
        ///     System.err.println("catch of FileNotFoundException:");
        ///     System.err.println(e.getMessage());
        /// }
        /// catch (IOException e) {
        ///     System.err.println(e.getMessage());
        /// }

        bufferedReader = new BufferedReader(new FileReader(fname)); 
        String line;
        while ((line = bufferedReader.readLine()) != null) {
            System.out.println(line);
        }

        // close the input file
        bufferedReader.close();
    }

    /**
     * Calls the method readFile and catches its exceptions
     */
    public void readFileCatchException()
    {
        try {
            readFile();
        }
        catch (FileNotFoundException e) {
            System.err.println("readFileCatchException: catch of FileNotFoundException:");
            System.err.println(e.getMessage());
        }
        catch (IOException e) {
            System.err.println("readFileCatchException: catch of IOException:");
            System.err.println(e.getMessage());
        }
    }

    /**
      version of the method readFile that does not throws the exceptions
      */
    public void readFileNotThrow()
    {
        BufferedReader bufferedReader = null;

        try {
            bufferedReader = new BufferedReader(new FileReader(fname)); 
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }
        }
        catch (FileNotFoundException e) {
            System.err.println("catch of FileNotFoundException:");
            System.err.println(e.getMessage());
        }
        catch (IOException e) {
            System.err.println(e.getMessage());
        }

        // close the input file
        try {
            bufferedReader.close();
        }
        catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }

    public void writeFile() throws IOException  // catch IOException in the caller
    {
        System.out.println("ReadWriteFileExample.writeFile create a new file " + fname);

        BufferedWriter bufferedWriter = null;

        // try {
        //     bufferedWriter = new BufferedWriter(new FileWriter(fname)); 
        // }
        // catch (IOException e) {
        //     System.err.println(e.getMessage());
        // }

        bufferedWriter = new BufferedWriter(new FileWriter(fname)); 

        bufferedWriter.write("This is the first line");
        bufferedWriter.newLine();
        bufferedWriter.write("This is the second line");

        bufferedWriter.close();
    }

    public void writeFileCatchIOException()
    {
        System.out.println("ReadWriteFileExample.writeFile create a new file " + fname);

        BufferedWriter bufferedWriter = null;

        try {
            bufferedWriter = new BufferedWriter(new FileWriter(fname)); 

            bufferedWriter = new BufferedWriter(new FileWriter(fname)); 

            bufferedWriter.write("This is the first line");
            bufferedWriter.newLine();
            bufferedWriter.write("This is the second line");

            bufferedWriter.close();
        }
        catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }

    public static void main(String[] args)
            throws IOException, FileNotFoundException                       // to avoid try/catch blocks in main()
            // throws java.io.IOException, java.io.FileNotFoundException    // don't need import statements for the exceptions
        {
            final String fname;
            if (args.length > 0) fname = args[0];
            else fname = ReadWriteFileExample.class.getSimpleName() + ".txt";

            ReadWriteFileExample readWriteFile = new ReadWriteFileExample(fname);

            // write a new file

            //
            // write with writeFile() that throws IOException: needs the try block
            //
            // try {
            //     readWriteFile.writeFile();
            // }
            // catch (IOException e) {
            //     System.err.println(e.getMessage());
            // }

            //
            // or write with writeFileCatchIOException() that does not throw IOException
            //
            readWriteFile.writeFileCatchIOException();

            // read the file

            //
            // use try block if main does not have: throws java.io.IOException
            //
            // try {
            //     readWriteFile.readFile();
            // }
            // catch (IOException e) {
            //     System.err.println(e.getMessage());
            // }
            readWriteFile.readFile();

            // call readFileCatchException that catches exceptons itself
            System.out.println("call readFileCatchException that catches exceptons itself");
            readWriteFile.readFileCatchException();

            // call of the "not throw" version of the readFile
            System.out.println("call of the \"not throw\" version of the readFile");
            readWriteFile.readFileNotThrow();
        }
}
