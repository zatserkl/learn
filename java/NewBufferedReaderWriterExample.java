// https://docs.oracle.com/javase/tutorial/essential/io/file.html#textfiles

// import java.io.IOException;
// import java.io.BufferedReader;
// import java.io.BufferedWriter;
// import java.nio.charset.Charset;
// import java.nio.file.Files;
// import java.nio.file.Path;
// import java.nio.file.Paths;

public class NewBufferedReaderWriterExample
{
    private final String fname;

    public NewBufferedReaderWriterExample(String fname) {
        this.fname = fname;
        System.out.println("constructor NewBufferedReaderWriter: this.fname = " + this.fname);
    }

    public void writeFile() throws java.io.IOException
    {
        java.nio.file.Path path = java.nio.file.Paths.get(fname);   // NB: Path ... = Paths

        java.nio.charset.Charset charset = java.nio.charset.Charset.forName("US-ASCII");  // optional

        java.io.BufferedWriter writer = java.nio.file.Files.newBufferedWriter(path, charset);
        writer.write("");
        writer.write("This is a line number one.\n");
        writer.write("This is a line number two.\n");
        writer.write("This is a line number three.\n");
        writer.close();
    }

    public void readFile() throws java.io.IOException   // catch this exception in caller
    {
        java.nio.file.Path path = java.nio.file.Paths.get(fname);   // NB: Path ... = Paths

        java.nio.charset.Charset charset = java.nio.charset.Charset.forName("US-ASCII");  // optional

        /// // try-with-resources
        /// try (java.io.BufferedReader reader = java.nio.Files.newBufferedReader(path, charset))
        /// {
        ///     String line = null;
        ///     while ((line = reader.readLine()) != null) {
        ///         System.out.println(line);
        ///     }
        /// } catch (java.io.IOException e) {
        ///     System.err.format("java.io.IOException: %s%n", e);
        /// }

        java.io.BufferedReader reader = java.nio.file.Files.newBufferedReader(path, charset);
        String line = null;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        reader.close();
    }

    public static void main(String[] args)
    {
        final String fname;

        if (args.length > 0) fname = args[0];
        else fname = NewBufferedReaderWriterExample.class.getName() + ".txt";

        NewBufferedReaderWriterExample newBufferedReaderWriterExample = new NewBufferedReaderWriterExample(fname);

        // write a new file

        try {
            newBufferedReaderWriterExample.writeFile();
        }
        catch (java.io.IOException e) {
            System.err.format("java.io.IOException: %s%n", e);
        }

        // read the file

        try {
            newBufferedReaderWriterExample.readFile();
        }
        catch (java.io.IOException e) {
            System.err.format("java.io.IOException: %s%n", e);
        }
    }
}
